# F21GA - Interaction

## Contents

- [Model Exporting and Importing](#model-exporting-and-importing)

- [Scene Setup](#scene-setup)

- [Shaders and Lighting](#shaders-and-lighting)

    - [Phong lighting model](#phong-lighting-model)
    - [Attenuation](#attenuation)
    - [Shadows](#shadows)
    - [Multiple lights and shadows](#multiple-lights-and-shadows)

- [Additional Effects](#additional-effects)

- [Interaction](#interaction)
    
    - [Mouse](#mouse)
    - [Keyboard](#keyboard)
    - [UI](#ui)

- [References](#references)


## Model Exporting and Importing


The basic steps to import most of the models are as follows.

First, if any parts of a model are very thin or made out of a plane, they are solidified to avoid issues with culling.

<img src="Readme_Images/models/model_solidify.png" alt="Solifiy" height="400"/>

Next, since the light model used ([Phong lighting model](#phong-lighting-model)) does not support the complex material types possible in blender, any complex materials are made into a more simple version.

<img src="Readme_Images/models/materials_1.png" alt="Complex materials" width="1000"/>

Here the glass and metal have been changed into more basic colours.

<img src="Readme_Images/models/materials_2_basic_replacement.png" alt="Basic materials" width="800"/>

Now, all the materials for the object are baked into one texture for exporting. This is first done by adding an overall texture to each of the materials for the model.

<img src="Readme_Images/models/materials_3_add_overall_texture.png" alt="Texture bake 1" width="800"/>

Then the model is UV unwrapped to this texture, and any overlapping parts are fixed.

<img src="Readme_Images/models/materials_4_uv_unwrap.png" alt="Texture bake 2" width="800"/>

Then the texture is baked, without the overall lighting

<img src="Readme_Images/models/materials_5_texture_bake.png" alt="Texture bake 3" height="400"/>

Then this texture is applied to the model as a single material.

<img src="Readme_Images/models/materials_6_apply_texture.png" alt="Single material" width="600"/>


Next, any transformations are applied to the object.

<img src="Readme_Images/models/apply_all_transforms.png" alt="Apply transformations" height="500"/>

Then the object is exported as a glTF file using the following settings.

<img src="Readme_Images/models/kettle_export_settings.png" alt="Export settings" height="600"/>



<br /><br />

## Scene Setup

Model placement, light placement?




<br /><br />

## Shaders and Lighting

### Phong lighting model

### Attenuation

### Shadows

### Multiple lights and shadows



<br /><br />

## Additional Effects

Other framebuffer effects or techniques?


<br /><br />

## Interaction

### Mouse

### Keyboard

### UI


<br /><br />

## References

Any other references / reference summary