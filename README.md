## More OpenGL demos

The code in this repository is taken from [OpenGL More Code Samples](https://www.opengl.org/archives/resources/code/samples/more_samples/)
and modified to build and run on Windows 10 with MSYS2/MINGW.

# Work in progress

26 March 2021

Downloaded and extracted the following Zip archives:

* [bounce.zip](https://www.opengl.org/archives/resources/code/samples/more_samples/bounce.zip) Program that lets you play around with light attenuation using neat OpenGL-based sliders.
* [chess.zip](https://www.opengl.org/archives/resources/code/samples/more_samples/chess.zip) Classic chessboard with (relatively) complicated pieces (pieces by Randy Brown). Drag the middle mouse button to spin board.
* [csg.zip](https://www.opengl.org/archives/resources/code/samples/more_samples/csg.zip) Constructive Solid Geometry program based on information from the Advanced OpenGL Rendering course at SIGGRAPH '96 by David Blythe and Tom McReynolds. Click right mouse button for menu.
* [cube.zip](https://www.opengl.org/archives/resources/code/samples/more_samples/cube.zip) Very simple Win32 example of drawing a cube.
* [distort.zip](https://www.opengl.org/archives/resources/code/samples/more_samples/distort.zip) Awesome program that causes ripples in the image wherever the mouse button is pressed. Another mode of the program acts like a sheet of rubber and can be pulled by dragging the mouse.
* [drip.zip](https://www.opengl.org/archives/resources/code/samples/more_samples/drip/drip.zip) Neat little program that makes a drip wherever the mouse button is pressed.
* [gliq.zip](https://www.opengl.org/archives/resources/code/samples/more_samples/gliq.zip) An OpenGL version of the pegboard game IQ.
* [lorenz.zip](https://www.opengl.org/archives/resources/code/samples/more_samples/lorenz.zip) This program shows some particles stuck in a Lorenz attractor (the parameters used are r=28, b=8/3, sigma=10). The eye is attracted to the red particle, with a force directly proportionate to distance. A command line puts the whole mess inside a box made of hexagons. I think this helps to maintain the illusion of 3 dimensions, but it can slow things down. Other options allow you to play with the redraw rate and the number of new lines per redraw. So you can customize it to the speed of your machine.
* [maze.zip](https://www.opengl.org/archives/resources/code/samples/more_samples/maze.zip) In this little demo the player navigates through a simple maze using the arrow keys. The maze is defined by a 2D array where each element in the array indicates solid or empty space. This program wraps polygon (quad) walls around the solid space and disallows the player to navigate into solid space during the demo. Note that all the walls are limited to being 90 degrees to each other - there are no "angled" features. The purpose of this sample program is to show a beginning 3D game programmer some things they can do. One other cool thing that this program does is that it constucts a single quad strip to draw all the walls by doing a recursive depth first search on the maze array data.
* [meshview.zip](https://www.opengl.org/archives/resources/code/samples/more_samples/meshview.zip) Simple program to visualize a mesh with a color ramp scale. Press 'h' for a help menu. Specify a data file as a command line argument.
* [rainbow.zip](https://www.opengl.org/archives/resources/code/samples/more_samples/rainbow.zip) Demonstration of palette animation in color index mode. Press 'h' for a help menu, middle button spins.
* [sgiflag.zip](https://www.opengl.org/archives/resources/code/samples/more_samples/sgiflag.zip) This program displays a waving flag with an SGI logo trimmed out of it. The flag is a single nurbs surface (bicubic, bezier). It "waves" by making it control point oscillate on a sine wave. The logo is cut from the flag using a combination of piecewise-linear and bezier trim curves.
* [shadow.zip](https://www.opengl.org/archives/resources/code/samples/more_samples/shadow.zip) Real-time soft shadows. Press 'h' for a help menu. Drag the middle mouse button to rotate the scene.
* [signal.zip](https://www.opengl.org/archives/resources/code/samples/more_samples/signal.zip) Demonstration of picking and rendering luminous objects. Drag the middle mouse button to spin the object. Move the mouse over the bulbs to light them.
* [simplecap.zip](https://www.opengl.org/archives/resources/code/samples/more_samples/simplecap.zip) Simple demonstration of using OpenGL's stencil test to cap clipped objects.
* [simpleci.zip](https://www.opengl.org/archives/resources/code/samples/more_samples/simpleci.zip) Simple program that shows how to do multi-colored material lighting in color index mode.
* [smooth.zip](https://www.opengl.org/archives/resources/code/samples/more_samples/smooth.zip) Wavefront .OBJ file format model reader/writer manipulator. Use the left mouse button to move, middle mouse button to rotate and right mouse button for menu.
* [texenv.zip](https://www.opengl.org/archives/resources/code/samples/more_samples/texenv.zip) Demonstrates texture environment modes and internal image formats.
* [vcull.zip](https://www.opengl.org/archives/resources/code/samples/more_samples/vcull.zip) Simple program that demonstrates the vertex array extension.

Made minimal changes to `bounce` and `chess` to compile and run under MSYS2/MINGW.

27 March 2021

Made minimal changes to enable *all* demos to compile and run on Windows 10 under MSYS2/MINGW.

