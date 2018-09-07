<h1>Kinect Memes</h1>
<h2>Windows Build</h2>
Run the  x86 build in Visual Studio it has the all the dependcies linked, kinect only code used for development of gestures 
or kinect modules.

<h2>Dependencies</h2>
<ul>
<li>SDL2</li>
<li>GLEW</li>
<li>OPENI2</li>
<li>NiTE2</li>
<li>FTLG</li>
</ul>

<h2>Bugs I can't be bothered fixing</h2>
<ul>
<li><p>Text Colour: drawString function using FTGLPixmap to draw text to screen, colours don't change correctly e.g. Cyan is Red, red is yellow. 
Could be fixed by using FTGLTexture or FTGLPolygon, but then posisitions are off, because of how glortho is set up.</p></li>
<li><p>Depth drawing: drawDepthFrame function, i don't how to pass 16bit monochrome texture data to opengl</p></li>
</ul>
