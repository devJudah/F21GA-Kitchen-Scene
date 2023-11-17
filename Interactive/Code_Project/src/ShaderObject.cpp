
#include "ShaderObject.hpp"

ShaderObject::ShaderObject() {}

ShaderObject::ShaderObject(string shaderID) 
{
    ShaderID = shaderID;
}

void ShaderObject::Use()
{
    glUseProgram(pipeline.pipe.program);
}

void ShaderObject::setInt(string name, int value)
{
    glUniform1i(glGetUniformLocation(pipeline.pipe.program, name.c_str()), value);
}

void ShaderObject::setFloat(string name, float value)
{
    glUniform1f(glGetUniformLocation(pipeline.pipe.program, name.c_str()), value);
}

void ShaderObject::setVec3(string name, glm::vec3 value)
{
    glUniform3fv(glGetUniformLocation(pipeline.pipe.program, name.c_str()), 1, &value[0]);
}

void ShaderObject::setMat4(string name, glm::mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(pipeline.pipe.program, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void ShaderObject::RegisterModel(string modelID)
{
    RegisteredModelIDs.push_back(modelID);
}

void ShaderObject::RemoveModel(string modelID)
{   
    // TODO: fix this :(
    /*
    //auto pos = find(RegisteredModelIDs.begin(), RegisteredModelIDs.end(), "test");
    find("end");
    if (pos != RegisteredModelIDs.end())
        RegisteredModelIDs.erase(pos);
    */
}
