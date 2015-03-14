# Blender 2.69 Cycles Ceramic Floor Tutorial #
[return to the Tutorials page](Tutorials.md)<br />
In this tutorial you will learn:<br />
How to make a realistic ceramic floor material<br />
In Blender 2.69 Cycles.<br />
# Blender 2.69 Cycles #
Get a copy of Blender 2.69 Cycles.<br />
Blender Cycles is not yet part of the Blender release.  To get yourself a copy<br />
simply go to GraphicAll and download it.<br />
Go to http://www.graphicall.org/ and get Blender 2.69 + CUDA + Cycles + OSL<br />
or similar for your operating system.

# Original Image #
![https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/CeramicFloor2.png](https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/CeramicFloor2.png)

# Better Texturing #
Instead of just placing a flat image onto your scene, let's create a more realistic result.<br />
We are going to use a displacement map, specular map, ambient occlusion map and a normal map.

# Building More Realistic Texture in Blender #
1) Load the default scene in Blender and delete the cube.<br />
2) Change the engine to use for redering to Blender Cycles.<br />
![https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/EngineRender.png](https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/EngineRender.png)<br />
to<br />
![https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/EngineCycles.png](https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/EngineCycles.png)<br />
3) Place a plane in the scene.<br />
4) Change the default lamp to a sun lamp.<br />
5) Arrane the lamp as shown.<br />
6) Select the Lamp<br />
7) Hold down shift and select the plane.<br />
8) Press Ctrl+T and select "Damped Track Constraint"<br />
![https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/DampedConstraint.png](https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/DampedConstraint.png)<br />
9) Set your Sun Lamp Settings to be:<br />
> a) Size: 0.010<br />
> b) Color: White<br />
> c) Energy: 10.0000<br />
![https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/SunLampSettings.png](https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/SunLampSettings.png)<br />
To get to the Energy Setting you must press the Nodes button under your Sun Lamp.<br />
10) Select the plane and only the plane and Enter Edit Mode.<br />
11) Press the 7 on the number pad to go to the Top View.<br />
12) Press the letter u.  Select Project From View (Bounds) from the popup menu.<br />
![https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/ProjectFromView.png](https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/ProjectFromView.png)<br />
13) Add a new material.<br />
14) Split the view so the top is the edit mode and the bottom is the Nodes view.<br />
![https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/SplitNodesView.png](https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/SplitNodesView.png)<br />
15) In the Nodes window, Make sure the Nodes box is checked.<br />
16) Press Shift+A select Texture->Image Texture.<br />
17) In the Image Texture node, Select the Open button and open CeramicFloor2.png.<br />
18) In the same Image Texture Node, Connect the Color to the Diffuse Color input.<br />
![https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/ImgTexNd100.png](https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/ImgTexNd100.png)<br />

# Using InsaneBump #

1) Go to https://gimp-plugin-insanebump.googlecode.com/git/windows/bin/InsaneBump-Windows-1.0.6.zip<br />
2) Unzip to your Gimp plugins directory.  For example on Windows XP:<br />
> c:\Documents and Settings\YOURUSERNAME\.gimp-2.8\plug-ins<br />
1) Start Gimp.<br />
2) Open the image from here:<br />
![https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/CeramicFloor2.png](https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/CeramicFloor2.png)<br />
3) Save to your hard drive somewhere.  Close and reopen it.<br />
4) Select from the menu:<br />
> Filters->Map->InsaneBump...<br />
5) After the Dialog finishes loading, Select the Execute Button (Keep the defaults).<br />
6) Press Close.  In the folder where you Saved the original drawing you will see these drawings:<br />
![https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/InsaneAll.png](https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/InsaneAll.png)<br />

# Add the Specular Map #

1) Press Shift+A again, this time select Shader->Glossy BSDF and place it down under the Diffuse BSDF.<br />
2) Set the roughness of the Glossy BSDF to 0.1<br />
3) Press Shift+A and place down a Shader->Mix Shader between the Material Output.<br />
4) Place the mix shader so that the Diffuse BSDF and the Glossy BSDF are mixing to the Material Output.<br />
![https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/MixShaderSpecular.png](https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/MixShaderSpecular.png)<br />
5) Press Shift+A and place a Texture->Image Texture.<br />
6) In this new Image Texture Node, Select the Open button and open CeramicFloor2\_s.png, The Specular.<br />
7) Press Shift+A and place a Color->MixRGB next to the Image Texture just placed.<br />
8) Connect Color 1 of the MixRGB to Color of the Image Texture just placed.<br />
9) Connect Color output of the MixRGB to the Fac of the Mix Shader.<br />
![https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/SpecularMix.png](https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/SpecularMix.png)<br />

# Add the Normal Map #

1) Press Shift+A, place down on the left bottom, a Texture->Image Texture.<br />
2) Select the Open button and open CeramicFloor2\_n.png, The Normal.<br />
3) Change, in the Image Texture Node, The Color to Non-Color Data.<br />
4) Press Shift+A, place down the Vector->Normal Map just to the right of the Newest Image Texture.<br />
5) Connect the Color of the Texture output to the Color of the Normal Input.<br />
6) Connect the Normal output of the Normal to the Normal input of the Diffuse BSDF AND the Glossy BSDF.<br />
![https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/NormalNormal.png](https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/NormalNormal.png)<br />

# Add the Displacement Map #

1) In order to do this we need to add more geometry to our plane.  Move your cursor to the edit window.<br />
> You should be in Edit Mode.  Press "t" to activate the toolbar.  Press "a" to select all the vertex.<br />
> In the toolbar at the left Press the Subdivide button.  This will bring up the Subdivide options at<br />
> the bottom of this toolbar window.  Set the number of cuts to 30 by manually entering the value of<br />
> 30 by clicking on the number and changing it to 30.  This value can only be entered manually.<br />
2) Place Blender into Object Mode. (Get out of Edit Mode Now).<br />
![https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/30Cuts.png](https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/30Cuts.png)<br />
3) Go to the Add Modifier menu and add a Generate->Subdivision Surface modifier and set view and render to 2.<br />
![https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/SubSurfLevel2.png](https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/SubSurfLevel2.png)<br />
4) Add a Deform->Displace Modifier and make sure it is below the SubSurf Modifier.<br />
![https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/SubSurfLevel2.png](https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/SubSurfLevel2.png)<br />
5) In the Displace Modifier panel create a new Texture.<br />
6) In the Texture panel (select texture from the type panel at the top right of Blender) Change to the<br />
> New texture just created.  It is listed under Modifiers->Displace-texture Select the Image type<br />
> and select the image CeramicFloor2\_h.png.<br />
7) Now back at the modifier panel set the strength to 0.03 and the direction to Z.<br />

# Add the Ambient Occlusion Map #

The ambient occlusion map will be used to modify any shadows.  This is really hard to see but<br />
the final product will have more realism.<br />
1) Move your cursor back to the Node editor window.<br />
2) Press Shift+A and place down an Image Texture.  Open up the file CeramicFloor2\_a.png.<br />
3) Add another MixRGB.  Press Shift+A and select Color->MixRGB.  Then select the dropdown and select Multiply.<br />
> This turns this mixer into a multiply mixer.  Place this between the image and the Diffuse BSDF from earlier.<br />
> Connect to the Top color box on the Multiply Mixer.<br />
4) Connect the Newest Image Texture to the bottom color box on the Multiply Mixer.<br />
![https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/FinalNodes.png](https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/FinalNodes.png)<br />
Here is the view port render:<br />
![https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/Render10.png](https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/Render10.png)<br />
Here is the render final result:<br />
![https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/Render135.png](https://gimp-plugin-insanebump.googlecode.com/git/images/CeramicTutorial/Render135.png)<br />