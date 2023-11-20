/**
 * Hold information on the different pipelines used for shaders, and which models are using them
 * 
*/
#pragma once


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


#include "Pipeline.hpp"

class ShaderObject {
    public:
        
        // Shader name/id
        string ShaderID;

        // Pipeline for this shader
        Pipeline pipeline;

        // Which models are using this shader
        vector<string> RegisteredModelIDs;

        // Constructor
        ShaderObject();

        ShaderObject(string shaderID);

        // Follows a similar idea to https://learnopengl.com/ see: shader.h - https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader.h

        // Sets gl to use the pipeline program
        void Use();

        void setInt(string name, int value);

        void setFloat(string name, float value);

        void setVec3(string name, glm::vec3 value);

        void setVec4(string name, glm::vec4 value);

        void setMat4(string name, glm::mat4 value);

        /**
         * Light properties helper functions
         * TODO: Move this to another class? They don't quite fit here
        */
        void setLightStructInt(string name, int vIndex, int value);

        void setLightStructFloat(string name, int vIndex, float value);

        void setLightStructVec3(string name, int vIndex, glm::vec3 value);

        void setLightStructMat4(string name, int vIndex, glm::mat4 value);


        // Which models are using this shader
        void RegisterModel(string modelID);

        // Remove a model
        void RemoveModel(string modelID);


    private:

        string LightStructNameHelper(string name, int vIndex);

};