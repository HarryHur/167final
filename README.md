# **CSE 167 Final project - Shadow Mapping**

Created by Fajar Dirham and Jungwook (Harry) Hur for our CSE 167 Final project. Special thanks to our TA, Baichuan Wu.

## What is shadow mapping?

Shadow mapping is a process used to add shadows to a 3D scene. Shadows add a lot of realism and detail to any 3D scene where light is involved.

In the simplest of terms, it works by **mapping** out the depth / distance of objects from a light source and using the information from said map to add in **shadows** when rendering the scene.

Casting shadows in a 3D scene is usually resource intensive due to all the moving parts involved. That said, there is more than one way to add in shadows to a 3D scene, each with their own pros and cons. Shadow mapping is relatively simple to implement and resource efficient compared to other processes but it usually is just used to create **hard shadows**, a less realistic version of real life shadows.

## The physics

In real life, whenever an object blocks the path of light a shadow is formed. Shadows are just the absence of light. They take the form of the object blocking the light and are distorted based on the position of the light relative to said object.

Shadows contain enough information to tell us a lot about the light source and the object that creates it. Famously, an ancient greek scholar used shadows cast by structures to predict the circumference of the Earth almost 2000 years ago.

There is a bunch of math involved in calculating realistic shadows. Relevant to shadow mapping, all you need to know is that a light source emits a bunch of light particles that an object blocks, thus casting a shadow behind the object relative to the light source.

## The algorithm

At a very high level, our shadow mapping algorithm does two passes when displaying the scene. The first pass is from the light's POV, the second from the main camera's. We store the depth map from the first pass to inform the second pass on where the shadows are.

### More detailed explanation

On the first pass, we draw the scene from the light's POV and color objects on that scene based on the depth. We do this by passing in the light's view, model, and projection matrices and writing our own fragment shader to color based on depth. We store this drawing on a frame buffer object.

On the second pass, we draw the scene from the camera's POV. We modify our fragment shader to compute shadows by referring to the depth map in the FBO. We use both the camera's and light's view, model, and projection matrices to get this information. Then we color in the appropriate pixels with shadows.

### Additional fixes

The core raw implementation might include graphical problems like **shadow acne** and **over sampling**.

In the first case, weird black lines will show up in our scene. This is due to limited resolution and how we take out pixel information from the depth map. To fix, we needed to add a bias in our sampling calculations.

In the second case, pixels outside of the light's projection matrix / frustum (one which we created) are shadowed weirdly. To fix this, we just set all shadows outside of the matrix to 0 using an openGL trick.

## Demo
Go to the demo folder in the repo to see pictures and videos.

## Read more

- [Shadow mapping basics](https://en.wikipedia.org/wiki/Shadow_mapping)
- [Hard and soft shadows](https://www.peachpit.com/articles/article.aspx?p=486505&seqNum=6)
- [Measuring shadows to calculate size of the earth](https://www.nsta.org/science-teacher/science-teacher-february-2020/measuring-shadows-calculate-size-earth)
- [Learn openGL by shadow mapping](https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping)
