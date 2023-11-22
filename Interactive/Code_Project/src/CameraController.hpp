/**
 * Code for the camera control
 *
 * Much of the ideas and code are from: https://learnopengl.com/Getting-started/Camera
 * 
 * Also from F21GA - Lab05: Interaction, Cameras, Textures
 *
 */

#ifndef CAMERA_CONTROL
#define CAMERA_CONTROL

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;




// Default values
const float MOVEMENT_SPEED = 3.0f;   // How fast the camera moves left, right, forward, back
const float LOOK_SENSITIVITY = 0.1f; // How fast the camera pans around
const float FOV_Y = 45.0f;           // Default field of view (y axis)
const float YAW = -90.0f;            // Starting yaw value (-90 so we start facing "forward")

const vec3 DEFAULT_CAMERA_POSITION = vec3(0.0f, 1.0f, 5.0f); // Where is our camera
const vec3 DEFAULT_CAMERA_FRONT = vec3(0.0f, 0.0f, -1.0f);   // Camera front vector
const vec3 DEFAULT_CAMERA_UP = vec3(0.0f, 1.0f, 0.0f);       // Camera up vector

const float DEFAULT_CAMERA_HEIGHT = 3.0f;	// How high the camera is when it's locked to the ground

class CameraController
{
  public:
	// Possible movement options for camera
	enum camera_movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	// Basic camera variables
	vec3 Position;
	vec3 Front;
	vec3 Up;

	float yaw;
	float pitch;

	float movementSpeed;
	float lookSensitivity;
	float fov_y;

	bool canFly;
	float cameraHeight;

	bool collisionCheck;

	CameraController()
	{
		this->Position = DEFAULT_CAMERA_POSITION;
		this->Front = DEFAULT_CAMERA_FRONT;
		this->Up = DEFAULT_CAMERA_UP;

		this->yaw = YAW;
		
		this->movementSpeed = MOVEMENT_SPEED;
		this->lookSensitivity = LOOK_SENSITIVITY;
		this->fov_y = FOV_Y;

		this->canFly = true;
		this->cameraHeight = DEFAULT_CAMERA_HEIGHT;

		this->collisionCheck = false;
	}

	CameraController(glm::vec3 cameraPosition, glm::vec3 cameraFront, glm::vec3 cameraUp, float movementSpeed, float lookSensitivity, float fov_y, bool canFly, float cameraHeight)
	{
		this->Position = cameraPosition;
		this->Front = cameraFront;
		this->Up = cameraUp;

		this->yaw = YAW;

		this->movementSpeed = movementSpeed;
		this->lookSensitivity = lookSensitivity;
		this->fov_y = fov_y;

		this->canFly = canFly;
		this->cameraHeight = cameraHeight;

		this->collisionCheck = false;
	}

	// Return the view matrix for the camera
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(	Position,         // eye
							Position + Front, // centre
							Up);              // up
	}

	// Handle key pressed events
	void keyPressed(camera_movement direction, float deltaTime)
	{	
		// See Lab05 for more info on these

		float velocity = movementSpeed * deltaTime;
		/*
		if(direction == FORWARD)
			Position += velocity * Front;
		if(direction == BACKWARD)
			Position -= velocity * Front;
		if(direction == LEFT)
			Position -= glm::normalize(glm::cross(Front, Up)) * velocity;
		if(direction == RIGHT)
			Position += glm::normalize(glm::cross(Front, Up)) * velocity;
		if(direction == UP)
			Position += velocity * Up;
		if(direction == DOWN)
			Position -= velocity * Up;
		*/

		// Calculate where we will be after the move
		glm::vec3 newPos = calculatePosition(direction, velocity);
		// Check if this is a valid position
		if(boundCheck(newPos)) {
			Position = newPos; // Update position
		}
		
		// Check to see if the camera should remain on the ground
		if(!canFly)
			Position.y = cameraHeight;
	}

	/*
		Handle mouse movements
		Offsets should be calculated by calling class
	*/
	void mouseMovement(GLfloat xoffset, GLfloat yoffset)
	{
		xoffset *= lookSensitivity;
		yoffset *= lookSensitivity;

		yaw += xoffset;
		pitch += yoffset;

		// Keep pitch within +- 89
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
		
		this->updateCameraVectors();
	}

	// Turn flying on 
	void canFly_On()
	{
		canFly = true;
	}

	// Turn flying off
	void canFly_Off()
	{
		canFly = false;
	}

	/*
		Update camera view vectors
	*/
	void updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		Front = glm::normalize(front);
	}

	glm::vec3 calculatePosition(camera_movement direction, float velocity)
	{
		glm::vec3 newPos;
		if(direction == FORWARD)
			newPos = Position + (velocity * Front);
		if(direction == BACKWARD)
			newPos = Position - (velocity * Front);
		if(direction == LEFT)
			newPos = Position - (glm::normalize(glm::cross(Front, Up)) * velocity);
		if(direction == RIGHT)
			newPos = Position + (glm::normalize(glm::cross(Front, Up)) * velocity);
		if(direction == UP)
			newPos = Position + (velocity * Up);
		if(direction == DOWN)
			newPos = Position - (velocity * Up);
		
		return newPos;
	}

	// Check if the newPosition is in bounds
	bool boundCheck(glm::vec3 newPosition)
	{
		/**
		 * TODO: Rewrite this using the actual model mesh/vertex so the collisions can be automatically generated
		 * 
		*/

		if(this->collisionCheck == false) return true; // Always pass if we don't check for collisions

		/*
			Thinking of the room (as viewed from above) as a box 

			Axis: 
				
			negative z
				|
				|
				|
				|________> positive x

			Floor plan:

			---------------------- lower z
			|   _____|         |
			|  |               |
			|__|               |
			|                  |
			|                  |
			|                  |
			---------------------- upper z (negative z axis is up)
			|                  |
		  lower x            upper x
		
			First check makes sure we are in the box.
			More checks for things in the room
		
		*/

		// Very simple box test to start with
		float xBound[2] = {-3.65, 10.11}; // Lower x, upper x
		float zBound[2] = {-4.57, 8.88}; // Low z, upper z

		// Test if we're outside the box
		if(xBound[0] > newPosition.x || newPosition.x > xBound[1]) {
			return false;
		}

		if(zBound[0] > newPosition.z || newPosition.z > zBound[1]) {
			return false;
		}

		// Test for the lower cabinet (probably can extend this along for upper/fridge?)
		/*
				--------------------
				|   _____|         |_ z_2
				|  |               |
				|__|               |_ z_1
				|                  |
				|                  |
				|                  |
				--------------------
				   |      |     
		 		  x_1    x_2   
		
		*/

		// Maybe this would make more sense to split into (x, z)?
		float xCab[2] = {-1.77, 3.44}; //  xCheck positions
		float zCab[2] = {2.65, -2.54}; // zCheck positions

		if(newPosition.x < xCab[0] && newPosition.z < zCab[0]) {
			return false;
		}
		if(newPosition.x < xCab[1] && newPosition.z < zCab[1]) {
			return false;
		}


		// Nothing hit (hopefully!) so return true
		return true;
	}

};

#endif
