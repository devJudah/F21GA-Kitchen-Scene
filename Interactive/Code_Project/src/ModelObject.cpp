
#include "ModelObject.hpp"

ModelObject::ModelObject() {};

ModelObject::ModelObject(string modelID, string modelPath, glm::vec3 initialPosition, glm::vec3 initialRotation, string shaderID)
{   
    ModelID = modelID;

    content.LoadGLTF(modelPath);

    MshaderID = shaderID;

    Position = initialPosition;
	Rotation = initialRotation;

    Scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

ModelObject::ModelObject(string modelID, string modelPath, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, string shaderID)
{
    ModelID = modelID;

    content.LoadGLTF(modelPath);

    MshaderID = shaderID;

    Position = glm::vec3(posX, posY, posZ);
	Rotation = glm::vec3(rotX, rotY, rotZ);

    Scale = glm::vec3(1.0f, 1.0f, 1.0f);
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
