# Wireframe Text Renderer
![exampleGif](https://github.com/rhbourke/wireframe-renderer/assets/3631484/534af99f-042e-4ece-a3ea-5de912105e70)


## About

A C++ program that can take any short English text prompt and render it as a spinning 3D wireframe. I wrote this program at a low level to learn about rendering. It uses nothing but SDL 2.0 to interface with the screen and C++ code!

## Usage Instructions

You will need to compile the application. If you have Visual Studio, it should be as simple as opening the solution and building it. Then run the .exe either from VS or by finding it in the build/configuration/platform/ directory.

The application will open a console menu where you can input some options: what text to render, what size to render it at, what colors to use, what speeds to rotate the text at, the thickness of the letters, etc...

**You can skip the advanced options** and use default values by entering "Y" when prompted, and **this is recommended your first time using the application**.

*Getting **weird/ugly** output? Make sure you didn't*:
* Set a render size that is too extreme - you will almost always want to use a value between 0.5 and 2 or so.
* Choose a prompt that is too long to fit.
* Choose a background color that is the same or very nearly the same as the draw color.

## Understanding the Math

I want to share some resources I liked about rendering in case you are also curious about it and help give you a head start in digesting how this stuff works.

The main mathematical problem we are dealing with for this project is figuring out how to take a point in 3D space and find out where it is in 2D space (your screen) after rotating it around some other point.

In my honest opinion, the best way to understand the math needed for stuff like this at a deep level is to go down the Wikipedia rabbit hole. [This Wikipedia page](https://en.wikipedia.org/wiki/Rotation_matrix) is a good one to dive in at (everything past the first few sections is irrelevant though). 

Wikipedia isn't a friendly place to start for this topic if you aren't very comfortable with linear algebra or aren't used to reading the Wikipedia math pages, however. If you find the Wikipedia page overwhelming, there is good news: at it's core, the math required for this rendering project is built on the simple trigonometry that you probably learned in high school.

Ultimately, all we really need to be able to do for this project is find the positions of the vertices of our shapes after they have been rotated around the origin. If we have the vertices, it is easy to draw lines between them. I'd like to walk you through a simple 2D example on my whiteboard to show how approachable it can be.

Suppose we have a point, p<sub>2</sub>, rotating counterclockwise around the origin (p<sub>1</sub>). It's distance from the origin as it rotates is constant. Let us call it $\ell$ and also say the angle of rotation is $\theta$. Then we can find p<sub>2</sub> with some trig:

![IMG-0805](https://github.com/rhbourke/wireframe-renderer/assets/3631484/5584c375-a714-4ba1-bbe9-811a0e86d9eb)


It really doesn't actually get much more complicated than this. We can always define our origin as the center of rotation, so we will always have one point that hasn't moved. We just perform calculations like this for each vertex and connect them up later. Even in three dimensions, it is conceptually about the same. I recommend breaking out a whiteboard or using scratch paper and working things out in 2D if you run into problems. The Wikipedia page above about rotation matrices just provides a way to streamline those calculations. You might be able to see how the 2D rotation matrix is derived just from the whiteboard example.

For further reading, I really like [this page](https://bvisness.me/desmos/) which details at a high level the process of making a more sophisticated 3D renderer in Desmos, the online graphing calculator.

Here is the part of my code that handles rotating the points. It is a method in a class that keeps track of all of the points in the wireframe. The method takes in the amount in radians to rotate those points by and spits out a rotated copy of the wireframe. You can spot the implementation of the three basic rotation matrices, a few lines of code for each axis:
```
std::vector<point> Frame::generate_rotated_frame(float rX, float rY, float rZ) {

	std::vector<point> newFrame = points;

	for (auto& p : newFrame) {

		// It is mathematically easier to rotate around the origin, so we will shift everything to be centered there then shift back after
		p.x -= center.x;
		p.y -= center.y;
		p.z -= center.z;

		float theta = rX;
		float y1 = p.y;
		p.y = (cos(theta) * p.y) + (-sin(theta) * p.z);
		p.z = (sin(theta) * y1) + (cos(theta) * p.z);

		theta = rY;
		float x1 = p.x;
		p.x = (cos(theta) * p.x) + (sin(theta) * p.z);
		p.z = (-sin(theta) * x1) + (cos(theta) * p.z);

		theta = rZ;
		float x2 = p.x;
		p.x = (cos(theta) * p.x) + (-sin(theta) * p.y);
		p.y = (sin(theta) * x2) + (cos(theta) * p.y);

		p.x += center.x;
		p.y += center.y;
		p.z += center.z;

	}
	return newFrame;
```

## Understanding the Code

The program uses SDL 2.0 in order to open a window and actually output the points that I tell it to onto the screen. Setting up SDL can be a little tricky. [Here is a resource I found helpful](https://www.studyplan.dev/sdl-dev/sdl-setup-windows), though I don't necessarily condone setting up your environment exactly as it describes if you want to distribute your application. I also found [this Stack Overflow answer](https://stackoverflow.com/a/64396980) helpful for understanding some issues I ran into.

If you want to follow along with someone making the basics of a 3D renderer in SDL in video form, I didn't find any perfect options, but I like [this video](https://www.youtube.com/watch?v=kdRJgYO1BJM) which teaches you how to make a spinning cube. I would definitely start with a cube, and I *do* like this person's video and found it helpful to get me started. He is articulate and easy to follow. However, there are some things you should watch out for:

1. In his function that rotates the points, he reuses values that he already changed for previous axes. For example, when he rotates the cube in the X direction, it changes the Y values as it should. However, when he rotates in the Z direction, he is accidentally factoring in this already changed Y value instead of the original. This causes a slight warping of the cube at low rotation speeds (even visible in the video slightly, to my eye) and a very severe warping at high speeds.
1. A floating point error will accumulate over time in his code as the points get rotated around and around, which caused my cube to shrink until it vanishes over time. Again, this is very minor at low speeds, almost unnoticeable, but becomes apparent at high speeds. To fix this, don't rotate the points in place. Instead, keep track of the original positions and make rotated copies of them.
1. Some people in the comments had an error using `emplace_back()` to add the points to the screen. I also had this problem. It can be easily swapped to `push_back()` for our purposes.

Again, despite these warnings, I do recommend the video if you just want to get the ball rolling (cube spinning?) fast, and I am grateful to the author for getting me started.


## Future Improvements and Ideas

If you wanted to iterate on this project and make it your own, I have some ideas for you:
1. Add proper perspective (more distant lines are smaller)
1. Add an option to change the camera's location
1. Fill in the faces of the figures
1. Make an editor for defining the shapes/characters

These steps would all bring the project closer to being a full-fledged renderer suitable for a game or something like that, but of course, if you just want to achieve that end and aren't interested in the challenge, you are certainly better off using something like OpenGL instead of trying to build off of this foundation.

If I were to do this all again, I would normalize the sizes. That would make scaling them easier without cheating by changing the SDL render scale (which doesn't quite work as well as I want anyway), and would make working with the program easier in general.

![nameGif](https://github.com/rhbourke/wireframe-renderer/assets/3631484/b8045582-192f-4f72-96a5-14a59e76d36f)


