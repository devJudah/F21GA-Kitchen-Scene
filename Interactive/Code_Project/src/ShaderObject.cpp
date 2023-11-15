
#include "ShaderObject.hpp"

ShaderObject::ShaderObject() {}

ShaderObject::ShaderObject(string shaderID) 
{
    ShaderID = shaderID;
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
