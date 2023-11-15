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

        // Which models are using this shader
        void RegisterModel(string modelID);

        // Remove a model
        void RemoveModel(string modelID);

};