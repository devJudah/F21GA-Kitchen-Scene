// 3D Graphics and Animation - Main Template
// This uses Visual Studio Code - https://code.visualstudio.com/docs/cpp/introvideos-cpp
// Two versions available -  Win64 and Apple MacOS - please see notes
// Last changed September 2023

//#pragma comment(linker, "/NODEFAULTLIB:MSVCRT")

//#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#define GL_SILENCE_DEPRECATION
#include <glad/glad.h> // Extend OpenGL Specfication to version 4.5 for WIN64 and versions 4.1 for Apple (note: two different files).

#include <imgui/imgui.h>			  // Load GUI library - Dear ImGui - https://github.com/ocornut/imgui
#include <imgui/imgui_impl_glfw.h>	  // Platform ImGui using GLFW
#include <imgui/imgui_impl_opengl3.h> // Platform new OpenGL - aka better than 3.3 core version.

#include <GLFW/glfw3.h> // Add GLFW - library to launch a window and callback mouse and keyboard - https://www.glfw.org

#define GLM_ENABLE_EXPERIMENTAL	 // Enable all functions include non LTS
#include <glm/glm.hpp>			 // Add helper maths library - GLM 0.9.9.9 - https://github.com/g-truc/glm - for example variables vec3, mat and operators.
#include <glm/gtx/transform.hpp> // Help us with transforms
using namespace glm;

//#include <tinygltf/tiny_gltf.h> // Model loading library - tiny gltf - https://github.com/syoyo/tinygltf
//#include "src/stb_image.hpp" // Add library to load images for textures

//#include "src/Mesh.hpp" // Simplest mesh holder and OBJ loader - can update more - from https://github.com/BennyQBD/ModernOpenGLTutorial

#include "src/Pipeline.hpp"		// Setup pipeline and load shaders.
#include "src/Content.hpp"		// Setup content loader and drawing functions - https://github.com/KhronosGroup/glTF - https://github.com/syoyo/tinygltf 
#include "src/Debugger.hpp"		// Setup debugger functions.

// More includes!
#include "src/CameraController.hpp"			// Camera controller code
#include "src/ModelObject.hpp"				// Wrapper for model data
#include "src/ShaderObject.hpp"				// Wrapper for shader data
#include "src/ShadowMap.hpp"				// For rendering shadows
#include "src/LightObject.hpp"				// For light info
#include "src/ContentInitialisation.hpp" 	// For loading shaders, models and lights


// Main fuctions
void startup();
void update();
void render();
void ui();
void endProgram();

// HELPER FUNCTIONS OPENGL
void hintsGLFW();
//string readShader(string name);
//void checkErrorShader(GLuint shader);
inline void errorCallbackGLFW(int error, const char *description){cout << "Error GLFW: " << description << "\n";};
void debugGL();

void APIENTRY openGLDebugCallback(GLenum source,
								  GLenum type,
								  GLuint id,
								  GLenum severity,
								  GLsizei length,
								  const GLchar *message,
								  const GLvoid *userParam);
GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)

// Setup all the message loop callbacks - do this before Dear ImGui
// Callback functions for the window and interface devices
void onResizeCallback(GLFWwindow *window, int w, int h);
void onKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void onMouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
void onMouseMoveCallback(GLFWwindow *window, double x, double y);
void onMouseWheelCallback(GLFWwindow *window, double xoffset, double yoffset);

// VARIABLES
GLFWwindow *window; 								// Keep track of the window
auto windowWidth = 1280;							// Window width					
auto windowHeight = 960;							// Window height
auto running(true);							  		// Are we still running our main loop
mat4 projMatrix;							 		// Our Projection Matrix
auto aspect = (float)windowWidth / (float)windowHeight;	// Window aspect ration
bool keyStatus[1024];								// Track key strokes
auto currentTime = 0.0f;							// Framerate
auto deltaTime = 0.0f;								// time passed
auto lastTime = 0.0f;								// Used to calculate Frame rate

auto fovy = 75.0f;									// Field of view (y axis)

CameraController camera;							// Camera

// Camera movement
// See lecture slides and https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/7.3.camera_mouse_zoom/camera_mouse_zoom.cpp
bool mouseMoved = false;							// If the mouse has been moved yet
float lastX = 0.0f;									// 
float lastY = 0.0f;									//


Debugger debugger;									// Add one debugger to use for callbacks ( Win64 - openGLDebugCallback() ) or manual calls ( Apple - glCheckError() ) 

bool showWireFrame = false;		// Debug option to show glPolygonMode
bool lightViewDebug = false;

// Hold all the models
map<string, ModelObject> models;

// Holds modelsIDs which can be selected (probably all of them?) - Would rather iterate through map<> models but that doesn't seem to work well
vector<string> modelSelectableID;
int selectedModel = 0;

// vector<ShaderObject> shaders;
map<string, ShaderObject> shaders;

// Lights with shadows
vector<LightObject> lights_s;

// Depth map stuff (used for calculating shows) - https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping
//unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024; // Controls the quality of the shadows
unsigned int SHADOW_WIDTH = 4096, SHADOW_HEIGHT = 4096;

// Shadow maps - Need one per light we want to create shadows for. NOTE!! Assumes they are in the same order as vector<LightObject> lights;
vector<ShadowMap> shadowMaps;


// How fast objects can be moved around the scene
float objectMovSpeed = 0.5f;



int main()
{
	cout << endl << "===" << endl << "3D Graphics and Animation - Running..." << endl;

	if (!glfwInit()) // Check if GLFW is working, if not then stop all
	{
		cout << "Could not initialise GLFW...";
		return -1;
	} 

	glfwSetErrorCallback(errorCallbackGLFW); // Setup a function callback to catch and display all GLFW errors.
	hintsGLFW();							 // Setup glfw with various hints.

	// Set window title
	const auto windowTitle = "My 3D Graphics and Animation OpenGL Application"s;

	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor()); // Grab reference to monitor
	// If going full screen set size to match monitor
	// windowWidth = mode->width; windowHeight = mode->height; //fullscreen
	// window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), glfwGetPrimaryMonitor(), NULL); // fullscreen

	// Create our Window
	window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);
	if (!window) // Test if Window or OpenGL context creation failed
	{
		cout << "Could not initialise GLFW...";
		glfwTerminate();
		return -1;
	} 

	glfwSetWindowPos(window, 50, 50); // Place it in top corner for easy debugging.
	glfwMakeContextCurrent(window);	  // making the OpenGL context current

	// GLAD: Load OpenGL function pointers - aka update specs to newest versions - plus test for errors.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD...";
		glfwMakeContextCurrent(NULL);
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(window, onResizeCallback);	   // Set callback for resize
	glfwSetKeyCallback(window, onKeyCallback);				   // Set Callback for keys
	glfwSetMouseButtonCallback(window, onMouseButtonCallback); // Set callback for mouse click
	glfwSetCursorPosCallback(window, onMouseMoveCallback);	   // Set callback for mouse move
	glfwSetScrollCallback(window, onMouseWheelCallback);	   // Set callback for mouse wheel.
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);	// Set mouse cursor Fullscreen
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	// Set mouse cursor FPS fullscreen.

	// Setup Dear ImGui and add context	-	https://blog.conan.io/2019/06/26/An-introduction-to-the-Dear-ImGui-library.html
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO(); //(void)io;
								  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	ImGui::StyleColorsLight(); // ImGui::StyleColorsDark(); 		// Setup Dear ImGui style

	// Setup Platform/Renderer ImGui backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	const auto glsl_version = "#version 410";
	ImGui_ImplOpenGL3_Init(glsl_version);

	#if defined(__WIN64__)
		debugGL(); // Setup callback to catch openGL errors.	V4.2 or newer
	#elif(__APPLE__)
		glCheckError(); // Old way of checking for errors. Newest not implemented by Apple. Manually call function anywhere in code to check for errors.
	#endif

	glfwSwapInterval(1);			 // Ony render when synced (V SYNC) - https://www.tomsguide.com/features/what-is-vsync-and-should-you-turn-it-on-or-off
	glfwWindowHint(GLFW_SAMPLES, 4); // Multisampling - covered in lectures - https://www.khronos.org/opengl/wiki/Multisampling

	startup(); // Setup all necessary information for startup (aka. load texture, shaders, models, etc).

	cout << endl << "Starting main loop and rendering..." << endl;	

	do{											 // run until the window is closed
		auto currentTime = (float)glfwGetTime(); // retrieve timelapse
		deltaTime = currentTime - lastTime;		 // Calculate delta time
		lastTime = currentTime;					 // Save for next frame calculations.

		glfwPollEvents(); 						// poll callbacks

		update(); 								// update (physics, animation, structures, etc)
		render(); 								// call render function.
		ui();									// call function to render ui.

		#if defined(__APPLE__)
			glCheckError();				// Manually checking for errors for MacOS, Windows has a callback.
		#endif

		glfwSwapBuffers(window); 		// swap buffers (avoid flickering and tearing)

		running &= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE); // exit if escape key pressed
		running &= (glfwWindowShouldClose(window) != GL_TRUE);
	} while (running);

	endProgram(); // Close and clean everything up...

	// cout << "\nPress any key to continue...\n";
	// cin.ignore(); cin.get(); // delay closing console to read debugging errors.

	return 0;
}


void hintsGLFW(){
	
	auto majorVersion = 3; auto minorVersion = 3; // define OpenGL version - at least 3.3 for bare basic NEW OpenGL

	#if defined(__WIN64__)	
		majorVersion = 4; minorVersion = 5;					// Recommended for Windows 4.5, but latest is 4.6 (not all drivers support 4.6 version).
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); // Create context in debug mode - for debug message callback
	#elif(__APPLE__)
		majorVersion = 4; minorVersion = 1; 				// Max support for OpenGL in MacOS
	#endif

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 	// https://www.glfw.org/docs/3.3/window_guide.html
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
}

void endProgram()
{
	// Clean ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwMakeContextCurrent(NULL); 	// destroys window handler
	glfwTerminate();				// destroys all windows and releases resources.
}

void startup()
{
	// Output some debugging information
	cout << "VENDOR: " << (char *)glGetString(GL_VENDOR) << endl;
	cout << "VERSION: " << (char *)glGetString(GL_VERSION) << endl;
	cout << "RENDERER: " << (char *)glGetString(GL_RENDERER) << endl;	

	cout << endl << "Loading content..." << endl;	

	ContentInitialisation contentInit;

	// Create and load shader info
	contentInit.LoadShaders(shaders);
	
	// Models
	contentInit.LoadModels(models, modelSelectableID);
	
	/**
	 * WARNING! Assume that the number of lights in lights_s equals the number of shadows created.
	*/
	// Lights
	contentInit.LoadLightS(lights_s);


	// Shadow startup
	ShadowMap shadow_m_1;
	shadow_m_1.Initialise(SHADOW_WIDTH, SHADOW_HEIGHT);
	shadowMaps.push_back(shadow_m_1);

	
	ShadowMap shadow_m_2;
	shadow_m_2.Initialise(SHADOW_WIDTH, SHADOW_HEIGHT);
	shadowMaps.push_back(shadow_m_2);

	ShadowMap shadow_m_3;
	shadow_m_3.Initialise(SHADOW_WIDTH, SHADOW_HEIGHT);
	shadowMaps.push_back(shadow_m_3);
	

	/**
	 * TODO: Abstract/wrapper this in a nicer way
	 * 
	 * Configure shadow shader "s_shadow"
	 * !!NOTE!! This sets the locations for the expected textures
	*/
	shaders["s_shadow"].Use();
	glUniform1i(glGetUniformLocation(shaders["s_shadow"].pipeline.pipe.program, "tex"), 0); // 0 is the model texture
	// Number of shadow maps expected
	GLint shadowMap_values[shadowMaps.size()];
	for(int i=0; i < shadowMaps.size(); i++){
		// Start the index of shadowMap_values at 0, but the value should be offset since 0 is the model texture
		shadowMap_values[i] = i+1;
	}
	glUniform1iv(glGetUniformLocation(shaders["s_shadow"].pipeline.pipe.program, "shadowMap"), shadowMaps.size(), shadowMap_values);


	// Turn multi sampling (Anti-alias) on. Was probably on anyway by default
	glEnable(GL_MULTISAMPLE);

	// A few optimizations.
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Get the correct size in pixels - E.g. if retina display or monitor scaling
	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

	// Calculate proj_matrix for the first time.
	aspect = (float)windowWidth / (float)windowHeight;
	projMatrix = glm::perspective(glm::radians(fovy), aspect, 0.1f, 1000.0f);

	// Camera settings
	camera.fov_y = fovy;
	// camera.canFly_Off();	// Stop player moving from the floor

}

void update()
{	
	

	if (keyStatus[GLFW_KEY_LEFT]) models[modelSelectableID[selectedModel]].Rotation.y += objectMovSpeed * deltaTime;
	if (keyStatus[GLFW_KEY_RIGHT]) models[modelSelectableID[selectedModel]].Rotation.y -= objectMovSpeed * deltaTime;
	if (keyStatus[GLFW_KEY_UP]) models[modelSelectableID[selectedModel]].Rotation.x += objectMovSpeed * deltaTime;
	if (keyStatus[GLFW_KEY_DOWN]) models[modelSelectableID[selectedModel]].Rotation.x -= objectMovSpeed * deltaTime;

	if (keyStatus[GLFW_KEY_Y]) models[modelSelectableID[selectedModel]].Position.y += objectMovSpeed * deltaTime;
	if (keyStatus[GLFW_KEY_I]) models[modelSelectableID[selectedModel]].Position.y -= objectMovSpeed * deltaTime;
	if (keyStatus[GLFW_KEY_U]) models[modelSelectableID[selectedModel]].Position.x += objectMovSpeed * deltaTime;
	if (keyStatus[GLFW_KEY_J]) models[modelSelectableID[selectedModel]].Position.x -= objectMovSpeed * deltaTime;
	if (keyStatus[GLFW_KEY_H]) models[modelSelectableID[selectedModel]].Position.z += objectMovSpeed * deltaTime;
	if (keyStatus[GLFW_KEY_K]) models[modelSelectableID[selectedModel]].Position.z -= objectMovSpeed * deltaTime;
	
	// Camera movement
	if (keyStatus[GLFW_KEY_W]) camera.keyPressed(camera_movement::FORWARD, deltaTime);
	if (keyStatus[GLFW_KEY_S]) camera.keyPressed(camera_movement::BACKWARD, deltaTime);
	if (keyStatus[GLFW_KEY_A]) camera.keyPressed(camera_movement::LEFT, deltaTime);
	if (keyStatus[GLFW_KEY_D]) camera.keyPressed(camera_movement::RIGHT, deltaTime);
	if (keyStatus[GLFW_KEY_Q]) camera.keyPressed(camera_movement::UP, deltaTime);
	if (keyStatus[GLFW_KEY_E]) camera.keyPressed(camera_movement::DOWN, deltaTime);

	

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void render()
{
	glViewport(0, 0, windowWidth, windowHeight);

	// Clear colour buffer
	glm::vec4 grayLilac = glm::vec4(0.831f, 0.792f, 0.803f, 1.0f);
	glm::vec4 darkGray = glm::vec4(0.05f, 0.05f, 0.05f, 1.0f);
	glm::vec4 skyBlue = glm::vec4(0.741f, 0.925f, 1.0f, 1.0f);
	glm::vec4 backgroundColor = skyBlue;
	glClearBufferfv(GL_COLOR, 0, &backgroundColor[0]);

	// Clear deep buffer
	static const GLfloat one = 1.0f;
	glClearBufferfv(GL_DEPTH, 0, &one);

	// Alternative way to clear buffer. From https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping
	//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	//glClearColor(0.831f, 0.792f, 0.803f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enable blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Render scene from light's point of view
	shaders["s_simple_depth"].Use();

	// Process each light's depth map
	for(int i=0; i < lights_s.size(); i++) {

		glm::mat4 lightProjection = lights_s[i].GetLightProjectionMatrix(shadowMaps[i].ShadowWidth, shadowMaps[i].ShadowHeight);
		glm::mat4 lightView = lights_s[i].GetLightViewMatrix();
		glm::mat4 lightSpaceMatrix = lightProjection * lightView;
	
		shaders["s_simple_depth"].setMat4("lightSpace_matrix", lightSpaceMatrix);

		// Activate the shadow map, we are going to use this to render the scene
		shadowMaps[i].SetActive();
			
		for(const string modelID : modelSelectableID) {
			
			// Skip this model if it does not cast a shadow
			if(!models[modelID].castShadow) continue;

			// Model matrix (calculates translations, rotations, scale)
			glm::mat4 modelMatrix = models[modelID].GetModelMatrix();
			
			shaders["s_simple_depth"].setMat4("model_matrix", modelMatrix);

			models[modelID].content.DrawModel(models[modelID].content.vaoAndEbos, models[modelID].content.model);
		}

	}

	// Reset buffers, so we can render the scene normally
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glViewport(0, 0, windowWidth, windowHeight);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearBufferfv(GL_COLOR, 0, &backgroundColor[0]);
	glClearBufferfv(GL_DEPTH, 0, &one);


	// Setup camera
	glm::mat4 viewMatrix = camera.GetViewMatrix();

	// Set the shader to use (TODO: Support for multiple shaders for each object?)
	shaders["s_shadow"].Use();
	shaders["s_shadow"].setInt("num_lights", lights_s.size());

	// Set as many properties as we can before looping through models
	// TODO: Can this be moved into the above loop? Just doing lights x2 here (ok for small number of lights I imagine)
	for(int i=0; i < lights_s.size(); i++) {

		glm::mat4 lightProjection = lights_s[i].GetLightProjectionMatrix(shadowMaps[i].ShadowWidth, shadowMaps[i].ShadowHeight);
		glm::mat4 lightView = lights_s[i].GetLightViewMatrix();
		glm::mat4 lightSpaceMatrix = lightProjection * lightView;

		// Set lightSpaceMatrix array
		stringstream ss;
		ss << "lightSpace_matrix[" << i << "]";
		shaders["s_shadow"].setMat4(ss.str(), lightSpaceMatrix);

		// Set LightStruct array values - using a helper function
		shaders["s_shadow"].setLightStructVec3("lightPosition", i, lights_s[i].lightPosition);
		shaders["s_shadow"].setLightStructVec3("lightColor", i, lights_s[i].lightColor);
		shaders["s_shadow"].setLightStructFloat("k_ambient", i, lights_s[i].k_ambient);
		shaders["s_shadow"].setLightStructFloat("atten_constant", i, lights_s[i].atten_constant);
		shaders["s_shadow"].setLightStructFloat("atten_linear", i, lights_s[i].atten_linear);
		shaders["s_shadow"].setLightStructFloat("atten_quadratic", i, lights_s[i].atten_quadratic);

		// Shadow depth maps
		// NOTE: Starts from GL_TEXTURE1 as GL_TEXTURE0 is the model texture!
		glActiveTexture(GL_TEXTURE1 + i);
		glBindTexture(GL_TEXTURE_2D, shadowMaps[i].DepthMap);
	}


	shaders["s_shadow"].setMat4("view_matrix", viewMatrix);
	shaders["s_shadow"].setMat4("proj_matrix", projMatrix);
	shaders["s_shadow"].setVec3("viewPosition", camera.Position);

	// Render the scene normally
	//for(const string modelID : modelSelectableID) {
	for(const auto& [modelID, model_s] : models) {

		// Check if this model should be rendered normally
		if(models[modelID].renderModel == false) continue;

		// Model matrix (calculates translations, rotations, scale)
		glm::mat4 modelMatrix = models[modelID].GetModelMatrix();
	
		// Set various shader properties
		shaders["s_shadow"].setMat4("model_matrix", modelMatrix);

		// TODO: Decide where k_diffuse and k_specular live should be (light or model)
		shaders["s_shadow"].setFloat("k_diffuse", 1.0f);
		shaders["s_shadow"].setFloat("k_specular", 1.0f);

		// Model shininess
		shaders["s_shadow"].setFloat("shininess", models[modelID].Shininess);

		// Model textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, models[modelID].content.texid);


		// Debug option to show triangles
		if (showWireFrame) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Draw lines
		} else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Draw normally
		}

		models[modelID].content.DrawModel(models[modelID].content.vaoAndEbos, models[modelID].content.model);
	}
	
	#if defined(__APPLE__)
		glCheckError();
	#endif
}

void ui()
{
	ImGuiIO &io = ImGui::GetIO();
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration; 
	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	window_flags |= ImGuiWindowFlags_NoSavedSettings; 
	window_flags |= ImGuiWindowFlags_NoFocusOnAppearing; 
	window_flags |= ImGuiWindowFlags_NoNav;

	const auto PAD = 10.0f;
	const ImGuiViewport *viewport = ImGui::GetMainViewport();
	ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
	ImVec2 work_size = viewport->WorkSize;
	ImVec2 window_pos, window_pos_pivot;
	window_pos.x = work_pos.x + work_size.x - PAD;
	window_pos.y = work_pos.y + work_size.y - PAD;
	window_pos_pivot.x = 1.0f;
	window_pos_pivot.y = 1.0f;

	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	window_flags |= ImGuiWindowFlags_NoMove;

	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
	bool *p_open = NULL;
	if (ImGui::Begin("Info", nullptr, window_flags)) {
		// ImGui::Text("About: 3D Graphics and Animation 2023/24"); // ImGui::Separator();
		ImGui::Text("Performance: %.3fms/Frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Pipeline: %s", shaders[models[modelSelectableID[selectedModel]].MshaderID].pipeline.pipe.error?"ERROR":"OK");
		// Camera info
		ImGui::Text("Camera position: %.3f, %.3d, %.3f", camera.Position.x, camera.Position.y, camera.Position.z);
		ImGui::Text("Camera front: %.3f, %.3d, %.3f", camera.Front.x, camera.Front.y, camera.Front.z);
		//
		ImGui::Separator();
		ImGui::Text("Object Mov Speed: %.3f", objectMovSpeed);
		// Model info
		ImGui::Text("Selected model ID: %s", modelSelectableID[selectedModel].c_str());
		ImGui::Text("Position: %.3f, %.3f, %.3f", models[modelSelectableID[selectedModel]].Position.x, models[modelSelectableID[selectedModel]].Position.y, models[modelSelectableID[selectedModel]].Position.z);
		ImGui::Text("Rotation: %.3f, %.3f, %.3f", models[modelSelectableID[selectedModel]].Rotation.x, models[modelSelectableID[selectedModel]].Rotation.y, models[modelSelectableID[selectedModel]].Rotation.z);
		ImGui::Text("Scale: %.3f, %.3f, %.3f", models[modelSelectableID[selectedModel]].Scale.x, models[modelSelectableID[selectedModel]].Scale.y, models[modelSelectableID[selectedModel]].Scale.z);
		// Light info
		int lightSelectedDB = 1;
		ImGui::Text("Light Dir: %.3f, %.3f, %.3f", lights_s[lightSelectedDB].lightDirection.x, lights_s[lightSelectedDB].lightDirection.y, lights_s[lightSelectedDB].lightDirection.z);
		ImGui::Text("Light FOV: %.3f", lights_s[lightSelectedDB].perspective_fov);
		ImGui::Text("Light near: %.3f Far: %.3f", lights_s[lightSelectedDB].near_plane, lights_s[lightSelectedDB].far_plane);
	}
	ImGui::End();

	// Rendering imgui
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void onResizeCallback(GLFWwindow *window, int w, int h)
{
	windowWidth = w;
	windowHeight = h;

	// Get the correct size in pixels
	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

	if (windowWidth > 0 && windowHeight > 0)
	{ // Avoid issues when minimising window - it gives size of 0 which fails division.
		aspect = (float)w / (float)h;
		projMatrix = glm::perspective(glm::radians(fovy), aspect, 0.1f, 1000.0f);
	}
}

void onKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{	
	/*
		Handle events that we just want 1 per key press
	*/

	// Model speed
	if (key == GLFW_KEY_O && action == GLFW_PRESS) {
		objectMovSpeed += 0.05;
	}

	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		objectMovSpeed -= 0.05;
		if(objectMovSpeed < 0) {
			objectMovSpeed = 0;
		}
	}

	// Model selection
	if (key == GLFW_KEY_COMMA && action == GLFW_PRESS) {
		if(selectedModel > 0) {
			selectedModel--;
		}
	}

	if (key == GLFW_KEY_PERIOD && action == GLFW_PRESS) {
		int numModels = modelSelectableID.size();
		if(selectedModel < numModels - 1) {
			selectedModel++;
		}
	}

	// Debug polygons on
	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		if (showWireFrame) {
			showWireFrame = false;
		} else {
			showWireFrame = true;
		}
	}

	
	// Light view
	int lightSelectedDB = 1;
	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		
		if(lightViewDebug){ 
			lightViewDebug = false;
			// Reset stuff
			projMatrix = glm::perspective(glm::radians(fovy), aspect, 0.1f, 1000.0f);
			camera.Front = vec3(0.0f, 0.0f, -1.0f);
			camera.Up = vec3(0.0, 1.0, 0.0);
		} else {
			lightViewDebug = true;
			camera.Position = lights_s[lightSelectedDB].lightPosition;
			camera.Front = lights_s[lightSelectedDB].lightDirection;
			camera.Up = lights_s[lightSelectedDB].lightUp;
			projMatrix = glm::perspective(glm::radians(lights_s[lightSelectedDB].perspective_fov), (GLfloat) SHADOW_WIDTH / (GLfloat) SHADOW_HEIGHT, lights_s[lightSelectedDB].near_plane, lights_s[lightSelectedDB].far_plane);
		}
		
	}


	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		lights_s[lightSelectedDB].lightDirection.x--;
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		lights_s[lightSelectedDB].lightDirection.x++;
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		lights_s[lightSelectedDB].lightDirection.y--;
	}
	if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		lights_s[lightSelectedDB].lightDirection.y++;
	}
	if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
		lights_s[lightSelectedDB].lightDirection.z--;
	}
	if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
		lights_s[lightSelectedDB].lightDirection.z++;
	}

	if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
		lights_s[lightSelectedDB].perspective_fov--;
	}
	if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
		lights_s[lightSelectedDB].perspective_fov++;
	}

	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		lights_s[lightSelectedDB].near_plane--;
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		lights_s[lightSelectedDB].near_plane++;
	}

	if (key == GLFW_KEY_V && action == GLFW_PRESS) {
		lights_s[lightSelectedDB].far_plane--;
	}
	if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		lights_s[lightSelectedDB].far_plane++;
	}


	/*
		General keys
	*/
	if (action == GLFW_PRESS)
		keyStatus[key] = true;
	else if (action == GLFW_RELEASE)
		keyStatus[key] = false;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void onMouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
}

void onMouseMoveCallback(GLFWwindow *window, double x, double y)
{
	int mouseX = static_cast<int>(x);
	int mouseY = static_cast<int>(y);

	// Camera code from lecture slides (See Lab 05).
	// Also see - https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/7.3.camera_mouse_zoom/camera_mouse_zoom.cpp
	// Test if the mouse has moved before or not
	if (!mouseMoved) {
		lastX = mouseX;
		lastY = mouseY;
		mouseMoved = true;
	}

	// Calculate how far the mouse has moved
	GLfloat xoffset = mouseX - lastX;
	GLfloat yoffset = lastY - mouseY;

	lastX = mouseX; 
	lastY = mouseY;

	// Update the camera based on mouse movement
	camera.mouseMovement(xoffset, yoffset);
}

void onMouseWheelCallback(GLFWwindow *window, double xoffset, double yoffset)
{
	int yoffsetInt = static_cast<int>(yoffset);
}

void APIENTRY openGLDebugCallback(GLenum source,
								  GLenum type,
								  GLuint id,
								  GLenum severity,
								  GLsizei length,
								  const GLchar *message,
								  const GLvoid *userParam)  // Debugger callback for Win64 - OpenGL versions 4.2 or better.
{
	debugger.OpenGLDebugCallback(source, type, id, severity, length, message, userParam);
}

void debugGL() // Debugger function for Win64 - OpenGL versions 4.2 or better.
{
	// Enable Opengl Debug
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback((GLDEBUGPROC)openGLDebugCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);
}

GLenum glCheckError_(const char *file, int line) // Debugger manual function for Apple - OpenGL versions 3.3 to 4.1.
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR) debugger.GlGetError(errorCode, file, line);

	return errorCode;
}
