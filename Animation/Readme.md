# F21GA - Animation

## Contents

- [Object Importing](#object-importing)
    - [Kettle and Toaster](#kettle-and-toaster)
    - [Sink](#sink)
    - [Storage Jars](#storage-jars)
    - [Cups & Dishes](#cups-&-dishes)
    - [Table & Fridge](#table-&-fridge)


- [Animations](#animations)
    - [Cooker Animation](#cooker-animation)
    - [Toaster Animation](#toaster-animation)
    - [Sink Animation](#sink-animation)
    - [Stove/Cooker Animation](#cooker-animation)
    - [Door Animation](#door-animation)
    - [Steam Animation](#steam-animation)

- [World](#world)
    - [Interior](#interior)
    - [Landscape](#landscape)


## Object Importing

### Kettle and Toaster

Before exporting, some parts of the model were joined together, for example the toaster was joined into two parts: the body and the lever. This is it make the object a bit easier to deal with in Unreal Engine.

<img src="ReadmeImages/screenshots_n/Toaster_blender_prejoined.png" alt="Toaster Joining" width="300"/> <img src="ReadmeImages/screenshots_n/Toaster_blender_joined.png" alt="FBX settings" width="300"/>

To move the kettle and toaster from Blender into Unreal, they are exported as an FBX file using Blender's `File>Export>FBX` option.

<img src="ReadmeImages/screenshots_n/N_fbx_export_options.png" alt="FBX settings" height="800"/>

Then the kettle and toaster are imported into Unreal using the `Content Drawer>Import` menu.

<img src="ReadmeImages/screenshots_n/Kettle_1_initial_import.png" alt="Kettle initial import" width="600"/> <img src="ReadmeImages/screenshots_n/Toaster_1_initial_import.png" alt="Toaster initial import" width="400"/>

The initial kettle and toaster import only has the basic black texture. The texture is without its roughness set. The kettle and toaster are missing the metal texture. The kettle also does not have its glass texture.

Although the kettle had the right texture for the control panel, the toaster did not. 

<img src="ReadmeImages/screenshots_n/toaster_kettle_detail.png" alt="Toaster and Kettle detail" width="600"/>

Attempts were made to bake the texture in blender but were unsuccessful in moving the texture into Unreal.

Fixing the plastic texture involved adding a constant for the roughness in Unreal's material editor.

<img src="ReadmeImages/screenshots_n/plastic_texture_fix.png" alt="Plastic material" width="600"/>

For basic metallic materials the same process can be followed, adding in values for metallic and roughness. For more complex materials, a base material provided by Unreal's `StarterContent` was used. For metals `M_Metal_Brushed_Nickel` and `M_Metal_Chrome` are used. For the glass Unreal's glass material `M_Glass` was used.

<img src="ReadmeImages/screenshots_n/M_metal_chrome_cust_texture.png" alt="Chrome material" width="600"/>

Once the materials have been fixed, the kettle and toaster are then ready to be added to the kitchen scene.

<img src="ReadmeImages/screenshots_n/Kettle_2_textures_fixed.png" alt="Kettle fixed" width="500"/><img src="ReadmeImages/screenshots_n/Toaster_2_textures_fixed.png" alt="Toaster fixed" width="400"/>


#### Kettle and Toaster References

- Unreal Engine's StarterContent
 - Clear plastic tutorial https://www.youtube.com/watch?v=CEBwUx-7xZQ
 - Brushed metal tutorial https://www.youtube.com/watch?v=POwYQtq-1jU
 - Metallic texture https://www.behance.net/gallery/60064327/20-Seamless-Brushed-Metal-Background-Textures-DOWNLOAD/modules/353093609


<br /><br />

### Sink

The sink is imported using the same FBX options as shown in the [Kettle and Toaster](#kettle-and-toaster) section.

<img src="ReadmeImages/screenshots_n/Sink_1_initial.png" alt="Sink initial import" width="600"/>

The sink has no initial textures as they are metallic and have not been exported/imported correctly. The textures are fixed in a similar way to the [Kettle and Toaster](#kettle-and-toaster), where the materials are either basic metallic ones or built on a provided Unreal material.

<img src="ReadmeImages/screenshots_n/Sink_2_textures_fixed.png" alt="Sink fixed" width="600"/>


<br /><br />

### Storage Jars

The storage jars are imported using the same FBX options as shown in the [Kettle and Toaster](#kettle-and-toaster) section.

<img src="ReadmeImages/screenshots_n/SJ_1_initial_import.png" alt="Storage jar initial import" width="600"/>

The oval window in the storage jars should be transparent, however setting this to a transparent material results in being able to see through the entire jar rather than to inside it.

<img src="ReadmeImages/screenshots_n/SJ_2_Seethrough_example.png" alt="Storage jar see through problem" width="600"/>

To fix this, in Blender a Solidify modified was added to increase the thickness of the walls of the jar. Then exported/imported back into Unreal.

The metal texture are fixed in a similar way to the [Kettle and Toaster](#kettle-and-toaster). Then a `Material Instance` is used for the different body colour.

<img src="ReadmeImages/screenshots_n/SJ_Material_Instance.png" alt="Material Instance example" width="400"/>

The models are then ready to use.

<img src="ReadmeImages/screenshots_n/SJ_3_textures_fixed.png" alt="Storage fixed" width="600"/>


<br /><br />

<br /><br />

### Cups & Dishes

<br /><br />

<br /><br />

### Table & Fridge

<br /><br />


## Animations

### Cooker Animation

A flame is created inside the cooker/stove and is animated using Blender 

<img src="https://github.com/devJudah/F21GA-Kitchen-Scene/blob/7c981a15f2f168b38a8d6cdac298939a6c29695b/Animation/ReadmeImages/Fire/Fire%201.png" alt="Fire animation 1" width="600"/> 

Nodes are created my mapping the texture in the blender and is shown below 

<img src="https://github.com/devJudah/F21GA-Kitchen-Scene/blob/63baaf0bc04c768bd371fa4484fe8e67537c7dbb/Animation/ReadmeImages/Fire/Fire%20Texture.png" alt="Fire animation 2" width="600"/> 

After creating a single flame it is multiplied in to several and is kept in a rotational axis created a round image

<img src="https://github.com/devJudah/F21GA-Kitchen-Scene/blob/63baaf0bc04c768bd371fa4484fe8e67537c7dbb/Animation/ReadmeImages/Fire/Fire%20complete%20flame%20.png" alt="Fire animation 3" width="600"/> 

Then the flame is fixed in to the stove 

<img src="https://github.com/devJudah/F21GA-Kitchen-Scene/blob/63baaf0bc04c768bd371fa4484fe8e67537c7dbb/Animation/ReadmeImages/Fire/Fire%20Image.png" alt="Fire animation 3" width="600"/> 

#### Rendered image of the flame 

<img src="https://github.com/devJudah/F21GA-Kitchen-Scene/blob/e1e22afadc34f6411d3a0c8695248abf3d306e94/Animation/ReadmeImages/Fire/STOVE.gif" alt="Fire animation 3" width="600"/> 

<br /><br />


### Toaster Animation

For the toaster animation, a toast model was made in Blender.

<img src="ReadmeImages/screenshots_n/toast_model.png" alt="Toast model" width="600"/>

 Then exported/imported to Unreal Engine using the same method as in the [Kettle and Toaster](#kettle-and-toaster) section.

<img src="ReadmeImages/screenshots_n/toast_imported.png" alt="Toast Imported" width="600"/>

As the texture is simple, it only needs roughness adding to fix the material.

To create the toast popping animation, sequencer is used to keyframe in the transformation positions.

<img src="ReadmeImages/screenshots_n/toaster_sequencer_1.png" alt="Toaster Sequencer" width="1000"/>

The toaster lever and toast are first moved down. Then after some time the toast and lever are moved back up, with the toast popping further out of the toaster. More key frames were added for the rotation of the toast and moving it back down into the toaster.

Camera movement and focus is done in a similar way, using Sequencer.


#### Toaster Animation References

- Toast https://www.youtube.com/watch?v=ohmidMxrKPI
- Sequencer https://docs.unrealengine.com/4.26/en-US/AnimatingObjects/Sequencer/QuickStart/


<br /><br />

### Sink Animation

The water animation is done in Blender using Blender's Fluid Simulation.

<img src="ReadmeImages/screenshots_n/sink_fluidsim_1.png" alt="Sink Fluid Simulation 1" width="600"/> <img src="ReadmeImages/screenshots_n/sink_fluidsim_2.png" alt="Sink Fluid Simulation 2" width="300"/>

This is then baked and exported into an `Alembic (.abc)` file. Which can then be imported into Unreal Engine as a geometry cache.

Once in Unreal the Sequencer is used in a similar way to the [Toaster Animation](#toaster-animation). Where the camera is moved through the scene using key frames. The tap top on/off animation is also done by using the transformation key frames.

<img src="ReadmeImages/screenshots_n/sink_sequencer_1.png" alt="Sink Sequencer" width="1000"/>

For the water animation, the key frames for the animation running are used to start and stop it at the correct time.

<img src="ReadmeImages/screenshots_n/sink_sequencer_water_opt.png" alt="Sink Sequencer water options" width="400"/>

The water is also set to "Keep State" once the animation is done so that some water remains in the sink.

<img src="ReadmeImages/screenshots_n/sink_sequencer_water_persistant.png" alt="Sink Sequencer water keep state" width="1200"/>


#### Sink Animation References

- Creating a Simple Fluid Simulation in Blender and Prepping for Unreal Engine https://www.youtube.com/watch?v=YdWHMD3VhrE
- Importing Alembic Geometry Cache [Fluid Simulation] into Unreal Engine 4 and 5 https://www.youtube.com/watch?v=qbaoRjjlul8
- Quick Water Animation in Blender 3.0 https://www.youtube.com/watch?v=6dCcwAUQGC0

<br /><br />



### Walkthrough Animation

The walkthrough animation is consist of 5 small shorts in sequence master. First rendering was done using Premier Pro but due to size issue it was decided to use legacy.
I

<img src="Early Animation\KitchenScene.mp4" alt="Early Rendering" width="400"/>

#### Walkthrough Shots

- Importing blender export to FBX and importing in unreal https://www.youtube.com/watch?v=KtPYTaCcCNU
- Adding keyframes, adjusting camera, creating shots https://www.youtube.com/watch?v=5jHhIah8H7U

<br /><br />


### Door animation
First I followed a tutorial to animate the door:
https://www.youtube.com/watch?v=O7vmp73ue4Y&t=63s

<img src="ReadmeImages/screenshots_n/door_bp_door.png" alt="Bluprint" width="400"/>
<img src="ReadmeImages/screenshots_n/door_bp_tp.png" alt="Bluprint" width="400"/>

But it didn't work, so I made an animation on Blender, following this tutorial:

https://www.youtube.com/watch?v=8-p7JPtk6n0&t=87s

<img src="ReadmeImages/screenshots_n/door_blender.png" alt="Blender" width="400"/>

The animation worked but when I imported it in Unreal Engine, the software crashed.

So I managed to do an animation with the sequencer, following these tutorials:

https://www.youtube.com/watch?v=-aApmzxl874
https://www.youtube.com/watch?v=vOfncpXxRh8

<img src="https://github.com/devJudah/F21GA-Kitchen-Scene/blob/main/Animation/ReadmeImages/screenshots_n/door_sequence.png" alt="Sequencer" width="400"/>


<br /><br />

### Steam Animation

<br /><br />

## World

### Interior

Additional objects in the scene were extracted from some unreal marketplace projects:

 - _Twinmotion Materials for Unreal Engine_ by Epic Games - https://www.unrealengine.com/marketplace/en-US/product/twinmotion-materials

 - _Triplex House Villa_ by 1D.STUDIO - https://www.unrealengine.com/marketplace/en-US/product/big-triplex-house-villa


### Landscape

#### Landscape references

- Ground, water and mountains are from _Unreal Engine 5 Beginner Tutorial - UE5 Starter Course_ by Unreal Sensei
    - https://www.youtube.com/watch?v=k-zMkzmduqI
    - https://www.unrealsensei.com/asset/ue5beginner

- Trees are from _Stylized Nature Pack_ by Tiny Talisman Games - https://www.unrealengine.com/marketplace/en-US/product/stylized-pbr-nature-pack

