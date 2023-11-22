
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

void ShaderObject::setVec4(string name, glm::vec4 value)
{
    glUniform4fv(glGetUniformLocation(pipeline.pipe.program, name.c_str()), 1, &value[0]);
}

void ShaderObject::setMat4(string name, glm::mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(pipeline.pipe.program, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void ShaderObject::setBool(string name, bool value)
{
    glUniform1i(glGetUniformLocation(pipeline.pipe.program, name.c_str()), (int)value);
}

void ShaderObject::setLightStructInt(string name, int vIndex, int value)
{   
    string uName = this->LightStructNameHelper(name, vIndex);
    this->setInt(uName, value);
}

void ShaderObject::setLightStructFloat(string name, int vIndex, float value)
{
    string uName = this->LightStructNameHelper(name, vIndex);
    this->setFloat(uName, value);
}

void ShaderObject::setLightStructVec3(string name, int vIndex, glm::vec3 value)
{
    string uName = this->LightStructNameHelper(name, vIndex);
    this->setVec3(uName, value);
}

void ShaderObject::setLightStructMat4(string name, int vIndex, glm::mat4 value)
{
    string uName = this->LightStructNameHelper(name, vIndex);
    this->setMat4(uName, value);
}

void ShaderObject::setLightStructBool(string name, int vIndex, bool value)
{
    string uName = this->LightStructNameHelper(name, vIndex);
    this->setBool(uName, value);
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


string ShaderObject::LightStructNameHelper(string name, int vIndex)
{
    stringstream ss;
	ss << "lights[" << vIndex << "]." << name;
    return ss.str();
}
