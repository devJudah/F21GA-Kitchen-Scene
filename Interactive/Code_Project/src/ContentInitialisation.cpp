#include "ContentInitialisation.hpp"


ContentInitialisation::ContentInitialisation() {}


void ContentInitialisation::LoadShaders(map<string, ShaderObject> &shaders)
{
    // Shadow shader
	ShaderObject s_shadow = ShaderObject("s_shadow");
	s_shadow.pipeline.CreatePipeline();
	s_shadow.pipeline.LoadShaders("shaders/vs_shadow_map.glsl", "shaders/fs_shadow_map.glsl");

	shaders[s_shadow.ShaderID] = s_shadow;


	// Simple depth - To generate depth maps for shadows
	ShaderObject s_simple_depth = ShaderObject("s_simple_depth");
	s_simple_depth.pipeline.CreatePipeline();
	s_simple_depth.pipeline.LoadShaders("shaders/vs_simple_depth.glsl", "shaders/fs_simple_depth.glsl");

	shaders[s_simple_depth.ShaderID] = s_simple_depth;

}

void ContentInitialisation::LoadModels(map<string, ModelObject> &models, vector<string> &modelSelectableID)
{
    // Note that changing this won't change positions
    glm::vec3 gScale = glm::vec3(0.3, 0.3, 0.3);


    ModelObject floor = ModelObject(
						"floor", 
						"assets/floor.gltf",
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(22.0f, 1.0f, 22.0f),
						"s_shadow"
						);

	floor.SetMaterialProperties(64);

	models[floor.ModelID] = floor;
	modelSelectableID.push_back(floor.ModelID);

	// Wall window
	ModelObject wall_window = ModelObject(
								"wall_window", 
								"assets/wall_window.gltf",
								glm::vec3(0.0f, 0.0f, 0.0f),
								glm::vec3(0.0f, 0.0f, 0.0f),
								gScale,
								"s_shadow"
							);

	wall_window.SetMaterialProperties(8);

	models[wall_window.ModelID] = wall_window;
	modelSelectableID.push_back(wall_window.ModelID);
	
	// Wall window
	ModelObject wall_door = ModelObject(
								"wall_door", 
								"assets/wall_door.gltf",
								glm::vec3(0.0f, 0.0f, 0.0f),
								glm::vec3(0.0f, 0.0f, 0.0f),
								gScale,
								"s_shadow"
							);

	wall_door.SetMaterialProperties(8);

	models[wall_door.ModelID] = wall_door;
	modelSelectableID.push_back(wall_door.ModelID);

	// Wall back
	ModelObject wall_back = ModelObject(
								"wall_back", 
								"assets/wall_back.gltf",
								glm::vec3(0.0f, 0.0f, 0.0f),
								glm::vec3(0.0f, 0.0f, 0.0f),
								gScale,
								"s_shadow"
							);

	wall_back.SetMaterialProperties(8);

	models[wall_back.ModelID] = wall_back;
	modelSelectableID.push_back(wall_back.ModelID);

	// Wall front
	ModelObject wall_front = ModelObject(
								"wall_front", 
								"assets/wall_front.gltf",
								glm::vec3(0.0f, 0.0f, 0.0f),
								glm::vec3(0.0f, 0.0f, 0.0f),
								gScale,
								"s_shadow"
							);

	wall_front.SetMaterialProperties(8);

	models[wall_front.ModelID] = wall_front;
	modelSelectableID.push_back(wall_front.ModelID);

	// Roof
	ModelObject roof = ModelObject(
								"roof", 
								"assets/roof.gltf",
								glm::vec3(0.0f, 0.0f, 0.0f),
								glm::vec3(0.0f, 0.0f, 0.0f),
								gScale,
								"s_shadow"
							);

	roof.SetMaterialProperties(8);

	models[roof.ModelID] = roof;
	modelSelectableID.push_back(roof.ModelID);

    // Window Frame
	ModelObject window_frame = ModelObject(
								"window_frame", 
								"assets/window_frame.gltf",
								glm::vec3(0.0f, 0.0f, 0.0f),
								glm::vec3(0.0f, 0.0f, 0.0f),
								gScale,
								"s_shadow"
							);

	window_frame.SetMaterialProperties(64);

	models[window_frame.ModelID] = window_frame;
	modelSelectableID.push_back(window_frame.ModelID);


    // Lights (models, not lights themselves!)
    ModelObject ceiling_light_1 = ModelObject(
								"ceiling_light_1", 
								"assets/ceiling_light.gltf",
								glm::vec3(1.25f, 0.0f, 0.0f),
								glm::vec3(0.0f, 0.0f, 0.0f),
								gScale,
								"s_shadow"
							);

	ceiling_light_1.SetMaterialProperties(8);

	models[ceiling_light_1.ModelID] = ceiling_light_1;
	modelSelectableID.push_back(ceiling_light_1.ModelID);

    ModelObject ceiling_light_bulb_1 = ModelObject(
                                    "ceiling_light_bulb_1", 
                                    "assets/ceiling_light_bulb.gltf",
                                    glm::vec3(1.25f, 0.0f, 0.0f),
                                    glm::vec3(0.0f, 0.0f, 0.0f),
                                    gScale,
                                    "s_shadow"
							    );

	ceiling_light_bulb_1.SetMaterialProperties(64);
    ceiling_light_bulb_1.castShadow = false;

	models[ceiling_light_bulb_1.ModelID] = ceiling_light_bulb_1;
	modelSelectableID.push_back(ceiling_light_bulb_1.ModelID);
    


    ModelObject ceiling_light_2 = ModelObject(
                                    "ceiling_light_2", 
                                    "assets/ceiling_light.gltf",
                                    glm::vec3(-4.0f, 0.0f, 0.0f),
                                    glm::vec3(0.0f, 0.0f, 0.0f),
                                    gScale,
                                    "s_shadow"
                                );

	ceiling_light_2.SetMaterialProperties(8);

	models[ceiling_light_2.ModelID] = ceiling_light_2;
	modelSelectableID.push_back(ceiling_light_2.ModelID);

    ModelObject ceiling_light_bulb_2 = ModelObject(
                                        "ceiling_light_bulb_2", 
                                        "assets/ceiling_light_bulb.gltf",
                                        glm::vec3(-4.0f, 0.0f, 0.0f),
                                        glm::vec3(0.0f, 0.0f, 0.0f),
                                        gScale,
                                        "s_shadow"
                                    );

	ceiling_light_bulb_2.SetMaterialProperties(64);
    ceiling_light_bulb_2.castShadow = false;

	models[ceiling_light_bulb_2.ModelID] = ceiling_light_bulb_2;
	modelSelectableID.push_back(ceiling_light_bulb_2.ModelID);

	// Bottom Cab
	ModelObject obj_bCab = ModelObject(
								"bottom_cabinet", 
								"assets/bottom_cabinet_v3.gltf",
								glm::vec3(0.0f, 0.0f, 0.0f),
								glm::vec3(0.0f, 0.0f, 0.0f),
								gScale,
								"s_shadow"
							);

	obj_bCab.SetMaterialProperties(16);
	models[obj_bCab.ModelID] = obj_bCab;
	modelSelectableID.push_back(obj_bCab.ModelID);

    // Sink
    ModelObject obj_sink = ModelObject(
								"sink", 
								"assets/sink_combined.gltf",
								glm::vec3(0.0f, 0.0f, 0.0f),
								glm::vec3(0.0f, 0.0f, 0.0f),
								gScale,
								"s_shadow"
							);

	obj_sink.SetMaterialProperties(128);
	models[obj_sink.ModelID] = obj_sink;
	modelSelectableID.push_back(obj_sink.ModelID);


    // Toaster
	ModelObject obj_toaster = ModelObject(
								"toaster", 
								"assets/toaster.gltf",
								glm::vec3(-3.4, 1.65, -3.05),
								glm::vec3(0.0f, 0.1f, 0.0f),
								glm::vec3(0.21f, 0.21f, 0.21f),
								"s_shadow"
							);

	obj_toaster.SetMaterialProperties(64);
		
	models[obj_toaster.ModelID] = obj_toaster;
	modelSelectableID.push_back(obj_toaster.ModelID);


	ModelObject obj_toast_1 = ModelObject(
								"toast_1", 
								"assets/toast.gltf",
								glm::vec3(-3.47, 1.96, -3.03),
								glm::vec3(0.0f, 0.1f, 0.0f),
								glm::vec3(0.4f, 0.4f, 0.4f),
								"s_shadow"
							);

	obj_toast_1.SetMaterialProperties(4);

	models[obj_toast_1.ModelID] = obj_toast_1;
	modelSelectableID.push_back(obj_toast_1.ModelID);

	ModelObject obj_toast_2 = ModelObject(
								"toast_2", 
								"assets/toast.gltf",
								glm::vec3(-3.33, 1.96, -3.05),
								glm::vec3(0.0f, 0.1f, 0.0f),
								glm::vec3(0.4f, 0.4f, 0.4f),
								"s_shadow"
							);

	obj_toast_2.SetMaterialProperties(4);

	models[obj_toast_2.ModelID] = obj_toast_2;
	modelSelectableID.push_back(obj_toast_2.ModelID);
	


    // Kettle
    ModelObject obj_kettle = ModelObject(
								"kettle", 
								"assets/kettle.gltf",
								glm::vec3(-3.45, 1.65, 1.35),
								glm::vec3(0.0f, 0.0f, 0.0f),
								glm::vec3(0.2f, 0.2f, 0.2f),
								"s_shadow"
							);

	obj_kettle.SetMaterialProperties(64);
		
	models[obj_kettle.ModelID] = obj_kettle;
	modelSelectableID.push_back(obj_kettle.ModelID);

    // Model - Dog
	ModelObject obj1 = ModelObject(
						"Dog", 
						"assets/dog.gltf",
						glm::vec3(0.0f, 0.0f, 0.0f),
						//glm::vec3(25.0f, 12.0f, 3.0f),
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(1.0f, 1.0f, 1.0f),
						"s_shadow"
						);

	obj1.SetMaterialProperties(16);
	// This is really terrible
	models[obj1.ModelID] = obj1;
	modelSelectableID.push_back(obj1.ModelID);
	// End of dog

}

void ContentInitialisation::LoadLightS(vector<LightObject> &lights_s)
{   
    
    LightObject light_sun = LightObject(
								glm::vec3(22.0f, 13.0f, 3.0f),
								glm::vec3(0.0f),
								glm::vec3(0.0, 1.0, 0.0),
								1.0f,
								45.0f, //55.0f,
								true,
								glm::vec3(0.3),
								0.3f,
								1.0f, 0.007f, 0.0002f
							);
	light_sun.orth_left = -20.0f;
	light_sun.orth_right = 20.0f;
	light_sun.orth_bottom = -20.0f;
	light_sun.orth_top = 20.0f;

	lights_s.push_back(light_sun);


	LightObject light1 = LightObject(
								glm::vec3(5.4f, 7.1f, 0.0f),
								glm::vec3(5.4f, 0.0f, 0.0f),
								glm::vec3(0.0, 0.0, 1.0),
								0.5f,
								20.0f, //100.0f,
								false,
								glm::vec3(0.3),
								0.3f,
								1.0f, 0.09, 0.032
							);
    light1.perspective_fov = 140.0f;
	lights_s.push_back(light1);


    LightObject light2 = LightObject(
								glm::vec3(-0.65f, 7.1, 0.0f),
								glm::vec3(-0.65f, 0.0f, 0.0f),
								glm::vec3(0.0, 0.0, 1.0),
								0.5f,
								20.0f, //100.0f,
								false,
								glm::vec3(0.3),
								0.3f,
								1.0f, 0.09, 0.032
							);
    light2.perspective_fov = 140.0f;
	lights_s.push_back(light2);
    
	
}