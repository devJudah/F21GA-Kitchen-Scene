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

	// Single colour - For stencil testing outline
	ShaderObject s_singleColor = ShaderObject("s_singleColor");
	s_singleColor.pipeline.CreatePipeline();
	s_singleColor.pipeline.LoadShaders("shaders/vs_stencil.glsl", "shaders/fs_stencil.glsl");

	shaders[s_singleColor.ShaderID] = s_singleColor;

	// Basic light bulb / lit object texture
	ShaderObject s_lightSource = ShaderObject("s_lightSource");
	s_lightSource.pipeline.CreatePipeline();
	s_lightSource.pipeline.LoadShaders("shaders/vs_light_basic.glsl", "shaders/fs_light_basic.glsl");

	shaders[s_lightSource.ShaderID] = s_lightSource;
}

void ContentInitialisation::InitialiseShaders(map<string, ShaderObject> &shaders)
{
	//Set single colour shader colour
	shaders["s_singleColor"].Use();
	shaders["s_singleColor"].setVec4("singleColor", glm::vec4(0.94, 0.62, 0.373, 1.0));
}


void ContentInitialisation::LoadModels(map<string, ModelObject> &models, vector<string> &modelSelectableID)
{
    // Overall scale factor for items imported directly from kitchen scene.
	// Note that changing this won't change positions, so those have to be changed individually!
    glm::vec3 gScale = glm::vec3(0.3, 0.3, 0.3);

	/* Syntax for loading an object:
		Create a ModelObject with ModelObject(unique_id, path_to_asset_gltf, position, rotation, scale, shader to use)
		Optionally set the material properties with SetMaterialProperties()
		Add the model to the models dictionary.
		If the model should be selectable to be rotated/moved, add the ID to modelSelectableID (NOTE: Currently everything is selectable for debugging)
	*/

	// Outside image
	/*
	ModelObject objOutside = ModelObject(
						"outside_box", 
						"assets/background_image.gltf",
						glm::vec3(23.5f, 1.9f, 2.4f),
						glm::vec3(0.0f, 1.52f, 0.0f),
						glm::vec3(2.0f, 2.0f, 2.0f),
						"s_shadow"
						);

	objOutside.castShadow = false;
	objOutside.SetMaterialProperties(0);
	models[objOutside.ModelID] = objOutside;
	//modelSelectableID.push_back(objOutside.ModelID);
	*/

	// Floor
    ModelObject floor = ModelObject(
						"floor", 
						"assets/floor.gltf",
						glm::vec3(2.0f, 0.0f, 1.3f),
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(12.0f, 1.0f, 12.0f),
						"s_shadow"
						);

	floor.SetMaterialProperties(64);

	models[floor.ModelID] = floor;
	//modelSelectableID.push_back(floor.ModelID);

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
	//modelSelectableID.push_back(wall_window.ModelID);
	
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
	//modelSelectableID.push_back(wall_door.ModelID);

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
	//modelSelectableID.push_back(wall_back.ModelID);

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
	//modelSelectableID.push_back(wall_front.ModelID);

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
	//modelSelectableID.push_back(roof.ModelID);

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
	//modelSelectableID.push_back(window_frame.ModelID);


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
	//modelSelectableID.push_back(ceiling_light_1.ModelID);

    ModelObject ceiling_light_bulb_1 = ModelObject(
                                    "ceiling_light_bulb_1", 
                                    "assets/ceiling_light_bulb.gltf",
                                    glm::vec3(1.25f, 0.0f, 0.0f),
                                    glm::vec3(0.0f, 0.0f, 0.0f),
                                    gScale,
                                    "s_lightSource"
							    );

	ceiling_light_bulb_1.SetMaterialProperties(64);
    ceiling_light_bulb_1.castShadow = false;

	models[ceiling_light_bulb_1.ModelID] = ceiling_light_bulb_1;
	//modelSelectableID.push_back(ceiling_light_bulb_1.ModelID);
    

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
	//modelSelectableID.push_back(ceiling_light_2.ModelID);

    ModelObject ceiling_light_bulb_2 = ModelObject(
                                        "ceiling_light_bulb_2", 
                                        "assets/ceiling_light_bulb.gltf",
                                        glm::vec3(-4.0f, 0.0f, 0.0f),
                                        glm::vec3(0.0f, 0.0f, 0.0f),
                                        gScale,
                                        "s_lightSource"
                                    );

	ceiling_light_bulb_2.SetMaterialProperties(64);
    ceiling_light_bulb_2.castShadow = false;

	models[ceiling_light_bulb_2.ModelID] = ceiling_light_bulb_2;
	//modelSelectableID.push_back(ceiling_light_bulb_2.ModelID);


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
	//modelSelectableID.push_back(obj_bCab.ModelID);

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
	//modelSelectableID.push_back(obj_sink.ModelID);


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

	/*
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
	*/

	ModelObject obj_toast_1 = ModelObject(
								"toast_1", 
								"assets/toast_gl3.gltf",
								glm::vec3(-3.47, 2.20, -3.03),
								glm::vec3(0.0f, 0.1f, 0.0f),
								glm::vec3(1.0f, 1.0f, 1.0f),
								"s_shadow"
							);

	obj_toast_1.SetMaterialProperties(4);

	models[obj_toast_1.ModelID] = obj_toast_1;
	modelSelectableID.push_back(obj_toast_1.ModelID);

	
	ModelObject obj_toast_2 = ModelObject(
								"toast_2", 
								"assets/toast_gl3.gltf",
								glm::vec3(-3.33, 2.20, -3.05),
								glm::vec3(0.0f, 0.1f, 0.0f),
								glm::vec3(1.0f, 1.0f, 1.0f),
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

	// Storage jar (silver) - Body
	ModelObject obj_sj = ModelObject(
								"sj_silver_body", 
								"assets/storageJar_1_body.gltf",
								glm::vec3(-3.51f, 1.65f, 2.17f),
								glm::vec3(0.0f, -0.45f, 0.0f),
								glm::vec3(0.3f, 0.3f, 0.3f),
								"s_shadow"
							);

	obj_sj.SetMaterialProperties(128);
		
	models[obj_sj.ModelID] = obj_sj;
	modelSelectableID.push_back(obj_sj.ModelID);

	// Storage jar (silver) - Lid
	ModelObject obj_sjL = ModelObject(
								"sj_silver_lid", 
								"assets/storageJar_1_lid.gltf",
								glm::vec3(-3.51f, 2.135f, 2.17f),
								glm::vec3(0.0f, -0.45f, 0.0f),
								glm::vec3(0.3f, 0.3f, 0.3f),
								"s_shadow"
							);

	obj_sjL.SetMaterialProperties(128);
		
	models[obj_sjL.ModelID] = obj_sjL;
	modelSelectableID.push_back(obj_sjL.ModelID);

	// Storage jar (black) - Body
	ModelObject obj_sj2 = ModelObject(
								"sj_black_body", 
								"assets/storageJar_2_body.gltf",
								glm::vec3(-3.575f, 1.65f, 1.80f),
								glm::vec3(0.0f, 0.2f, 0.0f),
								glm::vec3(0.3f, 0.3f, 0.3f),
								"s_shadow"
							);

	obj_sj2.SetMaterialProperties(128);
		
	models[obj_sj2.ModelID] = obj_sj2;
	modelSelectableID.push_back(obj_sj2.ModelID);

	// Storage jar (black) - Lid
	ModelObject obj_sjL2 = ModelObject(
								"sj_black_lid", 
								"assets/storageJar_1_lid.gltf",
								glm::vec3(-3.575f, 2.135f, 1.80f),
								glm::vec3(0.0f, 0.2f, 0.0f),
								glm::vec3(0.3f, 0.3f, 0.3f),
								"s_shadow"
							);

	obj_sjL2.SetMaterialProperties(128);
		
	models[obj_sjL2.ModelID] = obj_sjL2;
	modelSelectableID.push_back(obj_sjL2.ModelID);

	// Model - Cup
	ModelObject cup = ModelObject(
						"cup", 
						"assets/cup.gltf",
						glm::vec3(1.169f, 1.692f, 2.099f),
						//glm::vec3(25.0f, 12.0f, 3.0f),
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(0.11f, 0.11f, 0.11f),
						"s_shadow"
						);
					
	cup.SetMaterialProperties(16);
	
	// This is really terrible
	models[cup.ModelID] = cup;
	modelSelectableID.push_back(cup.ModelID);

	// Model - TABLE
	ModelObject table = ModelObject(
						"table", 
						"assets/table.gltf",
						glm::vec3(3.047f, 1.441f, 2.204f),
						glm::vec3(0.0f, -1.6f, 0.0f),
						glm::vec3(1.0f, 1.0f, 1.0f),
						"s_shadow"
						);
					
	table.SetMaterialProperties(16);
	models[table.ModelID] = table;
	modelSelectableID.push_back(table.ModelID);

	// Model - FRIDGE-DOOR
	ModelObject fridgeDoor = ModelObject(
						"fridgeDoor", 
						"assets/fridge_door.gltf",
						glm::vec3(9.947f, -0.035f, -1.297f),
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(1.0f, 0.8f, 1.0f),
						"s_shadow"
						);
					
	fridgeDoor.SetMaterialProperties(16);
	models[fridgeDoor.ModelID] = fridgeDoor;
	modelSelectableID.push_back(fridgeDoor.ModelID);

	// Model - FRIDGE-Body
	ModelObject fridgeBody = ModelObject(
						"fridgeBody", 
						"assets/fridge_body.gltf",
						glm::vec3(8.829f, -0.104f, -2.445f),
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(1.0f, 0.8f, 1.0f),
						"s_shadow"
						);
					
	fridgeBody.SetMaterialProperties(16);
	models[fridgeBody.ModelID] = fridgeBody;
	modelSelectableID.push_back(fridgeBody.ModelID);

	// Model - Chair
	ModelObject chairs = ModelObject(
						"chairs", 
						"assets/chairs.gltf",
						glm::vec3(1.731f, -0.0f, 3.788f),
						glm::vec3(0.0f, 3.1f, 0.0f),
						glm::vec3(0.5f, 0.6f, 0.5f),
						"s_shadow"
						);
					
	chairs.SetMaterialProperties(16);
	models[chairs.ModelID] = chairs;
	modelSelectableID.push_back(chairs.ModelID);

	// Model - Dish
	ModelObject dish = ModelObject(
						"dish", 
						"assets/Dish.gltf",
						glm::vec3(1.661f, 1.643f, 2.651f),
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(0.4f, 0.4f, 0.4f),
						"s_shadow"
						);
					
	dish.SetMaterialProperties(16);
	models[dish.ModelID] = dish;
	modelSelectableID.push_back(dish.ModelID);















    // Model - Dog
	ModelObject obj1 = ModelObject(
						"Dog", 
						"assets/dog.gltf",
						glm::vec3(9.0f, 0.0f, 7.68f),
						//glm::vec3(25.0f, 12.0f, 3.0f),
						glm::vec3(0.0f, -2.7f, 0.0f),
						glm::vec3(1.0f, 1.0f, 1.0f),
						"s_shadow"
						);

	obj1.SetMaterialProperties(16);
	// This is really terrible
	models[obj1.ModelID] = obj1;
	modelSelectableID.push_back(obj1.ModelID);
	// End of dog

	
	// Upper cabinet
	ModelObject obj_cab = ModelObject(
		"cabin", 
		"assets/cabinv5.gltf",
		glm::vec3(7.624f, 3.783f, -3.066f), 	// New position, placed above the bottom cabinet
		glm::vec3(0.0f, 0.0f, 0.0f), 	// Rotation
		glm::vec3(0.8f, 0.8f, 0.8f),  			// Scale
		"s_shadow"
	);

	obj_cab.SetMaterialProperties(64);
			
	models[obj_cab.ModelID] = obj_cab;
	modelSelectableID.push_back(obj_cab.ModelID);

	// front cabinet
	ModelObject obj_cabfront = ModelObject(
		"cabinfront", 
		"assets/cabinfrontv2.gltf",
		glm::vec3(5.228, 3.773f, -2.055f), 	// New position, placed above the bottom cabinet
		glm::vec3(0.002f, 0.0f, 0.0f), 	// Rotation
		glm::vec3(0.8f, 0.8f, 0.8f),			// Scale
		"s_shadow"
	);

	obj_cabfront.SetMaterialProperties(64);
			
	models[obj_cabfront.ModelID] = obj_cabfront;
	modelSelectableID.push_back(obj_cabfront.ModelID);

}

void ContentInitialisation::LoadLightS(vector<LightObject> &lights_s)
{   
    
    LightObject light_sun = LightObject(
								"sun",
								glm::vec3(22.0f, 13.0f, 3.0f),
								glm::vec3(0.0f),
								glm::vec3(0.0, 1.0, 0.0),
								5.0f,
								35.0f, // 45.0f, //55.0f,
								true,
								glm::vec3(0.3),
								0.3f,
								1.0f, 0.007f, 0.0002f
							);
	// light_sun.orth_left = -20.0f;
	// light_sun.orth_right = 20.0f;
	// light_sun.orth_bottom = -20.0f;
	// light_sun.orth_top = 20.0f;
	light_sun.orth_left = -15.0f;
	light_sun.orth_right = 10.0f;
	light_sun.orth_bottom = -10.0f;
	light_sun.orth_top = 15.0f;

	lights_s.push_back(light_sun);


	LightObject light1 = LightObject(
								"ceiling_1",
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
								"ceiling_2",
								glm::vec3(0.03f, 7.1, 0.0f),
								glm::vec3(0.03f, 0.0f, 0.0f),
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