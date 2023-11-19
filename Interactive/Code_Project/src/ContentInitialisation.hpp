#pragma once

#include <vector>
#include <map>

#include "ShaderObject.hpp"
#include "ModelObject.hpp"
#include "LightObject.hpp"


class ContentInitialisation
{
    public:

        ContentInitialisation();

        // Load shaders into &shaders
        void LoadShaders(map<string, ShaderObject> &shaders);

        // Load models into &models and &modelSelectableID
        void LoadModels(map<string, ModelObject> &models, vector<string> &modelSelectableID);
        
        // Load lights that cast shadows into lights_s
        void LoadLightS(vector<LightObject> &lights_s);

};
