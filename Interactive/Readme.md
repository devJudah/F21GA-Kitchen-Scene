# F21GA - Interaction

## Contents

- [Basic Interaction and Hotkey guide](#basic-interaction-and-hotkey-guide)

- [Model Exporting and Importing](#model-exporting-and-importing)

- [Scene Setup](#scene-setup)

- [Shaders and Lighting](#shaders-and-lighting)

    - [Phong lighting model](#phong-lighting-model)
    - [Attenuation](#attenuation)
    - [Shadows](#shadows)
    - [Multiple lights and shadows](#multiple-lights-and-shadows)

- [Additional Effects](#additional-effects)

- [Interaction](#interaction)
    
    - [Mouse an Camera](#mouse-and-camera)
    - [Keyboard](#keyboard)
    - [UI](#ui)

- [Animations](#animations)

    - [Toast Popping](#toast-popping)

- [References](#references)


## Basic Interaction and Hotkey Guide

V key : ON/OFF ceiling light
F key : ON/OFF sun

## Model Exporting and Importing


The basic steps to import most of the models are as follows.

First, if there are any overlapping faces that may result in "Z-fighting", they are reduced to one face. Then, if there is any complex geometry, particularly geometry that is not triangles or quads, a triangle modifier is applied.

<img src="Readme_Images/models/toaster_geo_tri_1.png" alt="Complex materials" width="400"/> <img src="Readme_Images/models/toaster_geo_tri_2.png" alt="Complex materials" width="400"/>

Next, if any parts of a model are very thin or made out of a plane, they are solidified to avoid issues with culling.

<img src="Readme_Images/models/model_solidify.png" alt="Solifiy" height="400"/>

If a model had issues that could not be resolved then they were partially remade with more straight forward geometry. For example, the lower cabinets. Any additional models can be found in `Interactive/Additional_blender_models/`.

Then, since the light model used ([Phong lighting model](#phong-lighting-model)) does not support the complex material types possible in blender, any complex materials are made into a more simple version.

<img src="Readme_Images/models/materials_1.png" alt="Complex materials" width="1000"/>

Here the glass and metal have been changed into more basic colours.

<img src="Readme_Images/models/materials_2_basic_replacement.png" alt="Basic materials" width="800"/>

Now, all the materials for the object are baked into one texture for exporting. This is first done by adding an overall texture to each of the materials for the model.

<img src="Readme_Images/models/materials_3_add_overall_texture.png" alt="Texture bake 1" width="800"/>

Then the model is UV unwrapped to this texture, and any overlapping parts are fixed.

<img src="Readme_Images/models/materials_4_uv_unwrap.png" alt="Texture bake 2" width="800"/>

Next the texture is baked, without the overall lighting

<img src="Readme_Images/models/materials_5_texture_bake.png" alt="Texture bake 3" height="400"/>

Then this texture is applied to the model as a single material.

<img src="Readme_Images/models/materials_6_apply_texture.png" alt="Single material" width="600"/>


Next, any transformations are applied to the object.

<img src="Readme_Images/models/apply_all_transforms.png" alt="Apply transformations" height="500"/>

Finally, the object is exported as a glTF file using the following settings.

<img src="Readme_Images/models/kettle_export_settings.png" alt="Export settings" height="600"/>


### References

- Metallic texture - https://www.youtube.com/watch?v=YRKIAdMYcr0

- Texture baking
    - https://www.youtube.com/watch?v=Se8GdHptD4A
    - https://www.youtube.com/watch?v=B2kFeMBBBjc


<br /><br />

## Scene Setup

Model placement, light placement?




<br /><br />

## Shaders and Lighting

### Phong lighting model


#### References
- _Advanced Lighting - Blinn-Phong_ from LearnOpenGL by Joey de Vries -  https://learnopengl.com/Advanced-Lighting/Advanced-Lighting
- Specular highlight fix - https://stackoverflow.com/questions/61166762/opengl-phong-lighting-specular-highlight-is-wrong/61167359#61167359

### Attenuation


#### References
- Lecture 14 - Advanced Lights

### Shadows


#### References

- _Shadow Mapping_ from LearnOpenGL by Joey de Vries - https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping
- _Basic Shadow Mapping // Intermediate OpenGL Series_ from ogldev.org by Etay Meiri - https://www.youtube.com/watch?v=kCCsko29pv0

### Multiple lights and shadows

#### References
- Lab 06 - Lights and materials
- _Shadow Mapping_ from LearnOpenGL by Joey de Vries - https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping
- _Modern OpenGL 08 – Even More Lighting: Directional Lights, Spotlights, & Multiple Lights_ - "Multiple Lights" section by Tom Dalling - https://www.tomdalling.com/blog/modern-opengl/08-even-more-lighting-directional-lights-spotlights-multiple-lights/ 


### Gamma


#### Refrences
- _Gamma Correction_ from Learn OpenGL by Joey de Vries - https://learnopengl.com/Advanced-Lighting/Gamma-Correction

<br /><br />

### Screenshots

<img src="Readme_Images/screenshots/lightoff.png" alt="Light off" height="600"/>
<img src="Readme_Images/screenshots/lighton.png" alt="Light on" height="600"/>

## Additional Effects

### Object highlights/outlines - Stencil Test

To highlight the currently selected object, it is possible to turn on object outlines. This is done by using a stencil test. The implementation for the stencil test heavily uses the code and information from [Stencil testing - learnopengl.com](https://learnopengl.com/Advanced-OpenGL/).


#### References

- _Stencil testing_ from Learn OpenGL by Joey de Vries - https://learnopengl.com/Advanced-OpenGL/Stencil-testing
- _OpenGL Tutorial 15 - Stencil Buffer & Outlining_ by Victor Gordan - https://www.youtube.com/watch?v=ngF9LWWxhd0


<br /><br />

## Interaction


### Mouse and Camera

#### References

- F21GA - Lab 05: Interaction, Cameras, Textures
- _Camera_ from Learn OpenGL by Joey de Vries - https://learnopengl.com/Getting-started/Camera

### Keyboard

### UI

The UI is built using the [Dear ImGui](https://github.com/ocornut/imgui) library.


#### References
- [Dear ImGui](https://github.com/ocornut/imgui) by [@ocornut](https://github.com/ocornut)
- Interactive imgui_manual by Pascal Thomet [@pthom](https://github.com/pthom) - https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html



## Animations

### Toast popping

#### References
- _Chapter 22: Interpolation_ from Graphics Programming Compendium by Ian Dunn and Zoë Wood - https://graphicscompendium.com/opengl/22-interpolation


<br /><br />

## References

Any other references / reference summary



## Upper Cabinet

First I changed the model into three meshes and baked the material for each object,
1: Back frame
2: Front frame with all the doors of cabinet except 1
3: 1 Remaining cabinet door

<img src="Readme_Images/models/cabinfront_1.png"  height="600"/>
<img src="Readme_Images/models/cabinfront_2.png" height="600"/>
<img src="Readme_Images/models/cabin_backframe.png" height="600"/>

Then Exported all three meshes with gltf format and imported in the project and placed the models onto their correct place.
<img src="Readme_Images/models/cabinet_placement.png" height="600"/>


Then added animation and interaction with cabinetfront 1. Upon selecting this object and pressing G will rotate open the door. But I was unable to specify the direction of the animation.
<img src="Readme_Images/models/doorOpen.png" height="600"/>

##References

Baking and openGL documentation: as mentioned above.

## Plate

Used the early made plate from blender and then the texture are baked in for the plate 
the image of baked on is given below 

<img src="https://github.com/devJudah/F21GA-Kitchen-Scene/blob/e9b6432a017ac4e092e3c2ca9f1f47887d081a22/Interactive/Readme_Images/screenshots/Plate/Screenshot%202023-11-22%20at%2020.48.08.png"  height="600"/>

Then the file exported as a .gltf file and then is trasfered to the opengl 
images inside the opengl is given below








