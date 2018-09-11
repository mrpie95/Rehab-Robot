<h1>Kinect Memes</h1>
<h2>Windows Build</h2>
<p>Run the  x86 build in Visual Studio it has the all the dependcies linked. Kinect only code used for development of gestures or kinect modules.</p>

<h2>Tracking</h2>
<p>NiTE 2 is used for tracking user skeletons, only one skeleton currently checks for gestures called prime user</p>
<ul>
<li>White Skeleton: User is being picked up by NiTE and can be tracked</li>
<li>Green Skeleton: Prime User, there gestures are being recognized and tracked</li>
<li>Yellow Skeleton: Prime User, but there position is somewhat uncertain</li>
</ul>
<p>To become a prime user cross your arms, your skeleton should turn yellow-green</p>

<h2>Adding Gestures</h2>
<p>Gestures are created by implementing the Gesture class and its virtual functions</p>

<pre><code>
class SomeGesture :public Gesture
{
  //The function that you implement to check whether conditions have been meet that the gesture has happened
  bool checkForGesture() override;

  //The function that you implement to check whether conditions have been the meet that the user is trying to do the gesture
  bool checkForDoingGesture() override;

  //The Function you can implement that will return useful information about the gesture
  std::string print() override;
}
</code></pre>

<p>I recommend checking out the hands on heads class for a simple gesture implementation, and wave gesture for a more complex gesture implementation. Use the functions to get x,y,z position of different body parts to build your gestures.</p>
<p>The Gestures are currently manually inserted into the User class with the init function</p>


<h2>Dependencies</h2>
<ul>
<li>SDL2</li>
<li>GLEW</li>
<li>OPENNI2</li>
<li>NiTE2</li>
<li>FTLG</li>
</ul>

<h2>Bugs I can't be bothered fixing</h2>
<ul>
<li><p>Text Colour: drawString function using FTGLPixmap to draw text to screen, colours don't change correctly e.g. Cyan is Red, red is yellow.
Could be fixed by using FTGLTexture or FTGLPolygon, but then posisitions are off, because of how glortho is set up will need to translate position before drawing.</p></li>
<li><p>Depth drawing: drawDepthFrame function, i don't how to pass 16bit monochrome texture data to opengl</p></li>
</ul>
