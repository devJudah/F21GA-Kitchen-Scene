#pragma once


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Pipeline.hpp"
#include "Content.hpp"
#include "ShaderObject.hpp"


class ModelObject
{
    public:

        // Should some of these be private with getters/setters?

        // ModelID - This should be unique! (no checks to make sure of this yet...)
        string ModelID;

        // Which shader this model should use
        string MshaderID;

        // Some of these can probably be shared between models? Or maybe better to change content

        Content content;		    // Add one content loader (+drawing).

        glm::vec3 Position;    // Model position
        glm::vec3 Rotation;    // Model rotation
        glm::vec3 Scale;       // Model scale


        ModelObject();

        ModelObject(string modelID, 
                    string modelPath, 
                    glm::vec3 initialPosition, 
                    glm::vec3 initialRotation,
                    string shaderID);

        ModelObject(string modelID, 
                    string modelPath, 
                    float posX, float posY, float posZ, 
                    float rotX, float rotY, float rotZ,
                    string shaderID);

        glm::mat4 GetModelMatrix();


    private:


};
