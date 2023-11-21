
#include "ModelObject.hpp"

ModelObject::ModelObject() {};

ModelObject::ModelObject(string modelID, string modelPath, glm::vec3 initialPosition, glm::vec3 initialRotation, glm::vec3 scale, string shaderID)
{   
    ModelID = modelID;

    content.LoadGLTF(modelPath);

    MshaderID = shaderID;

    Position = initialPosition;
	Rotation = initialRotation;

    Scale = scale;
}

ModelObject::ModelObject(string modelID, string modelPath, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, string shaderID)
{
    ModelID = modelID;

    content.LoadGLTF(modelPath);

    MshaderID = shaderID;

    Position = glm::vec3(posX, posY, posZ);
	Rotation = glm::vec3(rotX, rotY, rotZ);

    Scale = glm::vec3(scaleX, scaleY, scaleZ);
}

glm::mat4 ModelObject::GetModelMatrix()
{
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, Position);
	modelMatrix = glm::rotate(modelMatrix, Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, Scale);
    return modelMatrix;
}

void ModelObject::SetMaterialProperties(float shininess)
{
    Shininess = shininess;
}

// Move object in direction. Based on front and up (assumed normalised)
void ModelObject::Move(MovDir direction, float velocity, glm::vec3 front, glm::vec3 up)
{
    if(direction == MovDir::FORWARD) {
        // There's probably a better maths way to do this
		float yPos = Position.y;
		Position += velocity * front;
		Position.y = yPos;
    }
    if(direction == MovDir::BACKWARD) {
        // There's probably a better maths way to do this
		float yPos = Position.y;
		Position -= velocity * front;
		Position.y = yPos;
    }
    if(direction == MovDir::LEFT) {
		Position -= velocity * glm::normalize(glm::cross(front, up));
    }
    if(direction == MovDir::RIGHT) {
		Position += velocity * glm::normalize(glm::cross(front, up));
    }
    if(direction == MovDir::UP) {
		Position += velocity * up;
    }
    if(direction == MovDir::DOWN) {
		Position -= velocity * up;
    }
}
