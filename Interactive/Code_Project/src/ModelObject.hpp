/**
 * Properties of the model objects
 * 
 * Has the model Content for loading/rendering
 * Position, rotation and scale
 * Material properties: ambient, diffuse, specular and shininess
 * 
*/

#pragma once


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

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

        // Material properties
        // TODO: Add more things here? Make multiple materials for the same object? Or maybe a PBR model?
        float Shininess;


        ModelObject();

        ModelObject(string modelID, 
                    string modelPath, 
                    glm::vec3 initialPosition, 
                    glm::vec3 initialRotation,
                    glm::vec3 scale,
                    string shaderID);

        ModelObject(string modelID, 
                    string modelPath, 
                    float posX, float posY, float posZ, 
                    float rotX, float rotY, float rotZ,
                    float scaleX, float scaleY, float scaleZ,
                    string shaderID);

        glm::mat4 GetModelMatrix();

        void SetMaterialProperties(float shininess);


    private:


};
