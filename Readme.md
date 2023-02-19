# Technical documentation description (rendering of large-scale volcano scenes)

# Li Yuan

# The final implementation result (non-stereoscopic version)

<img src="images/技术文档说明0.png" width=500px />

There are 5 different effects

1\. <span style="color:#FF0000">Terrain</span> (based on perlinnoise implementation)

2\. <span style="color:#FF0000">Fireworks</span> (based on the simplest particle system implementation)

3\. <span style="color:#FF0000">Smoke</span> (based on noise\+analytic gradient implementation)

4\. <span style="color:#FF0000">magma</span> (based on physx implementation failed, and finally implemented based on noise\+analytic gradient)

5\. <span style="color:#FF0000">clouds</span> \(based on analytical gradient and noise implementation)

# The difficulty of implementation

1\. Elegant implementation of the math library (after multiple refactorings, util/EigenLidan\,Matrix\.h...\)

2\. Elegant implementation based on opengl pipeline (opengl/\*)

3\. Realization of ray tracing based on glsl (matching of terrain, clouds, etc.)

4\. Support interactive (but only click to set off fireworks)

5\. Simple fireworks particle system (no physics engine, just use shader to simulate the relationship between gravity and speed)

Matching to the teacher's requirements: 1\. <span style="color:#FF0000">5</span> <span style="color:#FF0000">plants</span> <span style="color: #FF0000">\(</span> <span style="color:#FF0000">Match: see previous page),</span> <span style="color:#FF0000">2\.</span> <span style="color:#FF0000">Physics engine (not used, but simulated the simplest fireworks particle system),</span> <span style="color:#FF0000">3\.</span > <span style="color:#FF0000">Interactive (fireworks). </span>

# The final VR effect (because opengl's stereo vision is very simple) (use red and blue eyes to watch)

<img src="images/技术文档说明1.png" width=500px />

# original effect

# stereo vision

# Summarize

1\. In summary, basically fulfill the teacher's requirements

2\. Advantages: I am most satisfied with the elegant implementation of the math library and opengl pipeline. And the first contact, use noise and noise's analytical gradient to construct terrain and other objects, and use path tracing to render these objects. An implementation of stereo vision is provided.

3\. Disadvantages: No physics engine is used, but a particle system is simply implemented. Interactivity is all about setting off fireworks.

# reference

1\.[http://iquilezles\.org/www/articles/morenoise/morenoise\.htm\(noise](http://iquilezles.org/www/articles/morenoise/morenoise.htm(noise) function and Noise analytical gradient calculation, analytical gradient can help to quickly calculate the normal vector)

[2\.](http://iquilezles.org/www/articles/rmshadows/rmshadows.htm)[http://iquilezles\.org/www/articles/rmshadows/rmshadows\.htm](http:// iquilezles.org/www/articles/rmshadows/rmshadows.htm) (Implementation of soft shadows in finite ray tracing)

3\.[http://iquilezles\.org/www/articles/fog/fog\.htm](http://iquilezles.org/www/articles/fog/fog.htm)\(fog calculation, and smoke calculation)

4\. Software noise lab, (provide valued noise, perlinnoise and other 2d noise implementation demos)

5\. Magma noise implementation ([https://www\.shadertoy\.com/view/lslXRS](https://www.shadertoy.com/view/lslXRS))

The above blog posts and software have helped me a lot in my experiments.

# experience

Noise plus analytical gradient can render anything you want, as long as you write the raymatch function.
