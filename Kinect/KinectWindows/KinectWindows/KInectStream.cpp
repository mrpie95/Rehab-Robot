#include "KInectStream.h"
#include <iostream>
#include <GL/glew.h>
#define TEXTURE_SIZE 512

#define log(x) std::cout << x << std::endl
#define NUM_OF_CHUNCKS(dataSize, chunksize) ((((dataSize)-1)/(chunksize)+1))
#define CHUNCK_SIZE(dataSize, chunksize) (NUM_OF_CHUNCKS(dataSize, chunksize)*(chunksize))

#define COLORSTREAM true
#define DEPTHSTREAM false

KinectStream::KinectStream(openni::Device& device, openni::VideoStream& depthStream, openni::VideoStream& colourStream): 
	kinect(device), depthStream(depthStream), colourStream(colourStream), streams(NULL)
{
}


KinectStream::~KinectStream()
{
}

void KinectStream::init()
{

	streams = new openni::VideoStream*[2];

	openni::VideoMode depthMode;
	openni::VideoMode colourMode;

	int colourResolutionX;
	int colourResolutionY;
	int depthResolutionX;
	int depthResolutionY;

#if COLORSTREAM
	if (colourStream.isValid())
	{
		
		colourMode = colourStream.getVideoMode();

		colourResolutionX = colourMode.getResolutionX();
		colourResolutionY = colourMode.getResolutionY();

		streamWidth = colourResolutionX;
		streamHeight = colourResolutionY;
	}
	else
	{
		log("No color streams found");
		exit(1);
	}

	
	streams[0] = &colourStream;

#endif // COLORSTREAM


#if DEPTHSTREAM
	if (depthStream.isValid())
	{
		depthMode = depthStream.getVideoMode();
		int depthResolutionX = depthMode.getResolutionX();
		int depthResolutionY = depthMode.getResolutionY();

		streamWidth = depthResolutionX;
		streamHeight = depthResolutionY;
	}
	else
	{
		log("no depth streams found");
		exit(1);
	}

	streams[0] = &depthStream;
#endif // DEPTHSTREAM

	textureMapX = CHUNCK_SIZE(streamWidth, 512);
	textureMapY = CHUNCK_SIZE(streamHeight, 512);
	textureMap = new openni::RGB888Pixel[textureMapX * textureMapY];

}

// TODO: this probably contains so many memory leaks idk
// TODO: this can probalbt be done in a fragment and vertext shader program and will scale properly and remove that stutter
// this might not be thread safe
void KinectStream::run()
{
	int index = -1;
	int streamCount = 0;
	//grabs a stream and returns what stream it got with index

#if (COLORSTREAM && DEPTHSTREAM)
	streamCount = 2;
#elif (COLORSTREAM || DEPTHSTREAM)
	streamCount = 1;
#endif
	openni::Status streamStatus = openni::OpenNI::waitForAnyStream(streams, streamCount, &index, openni::TIMEOUT_FOREVER);

	if (streamStatus != openni::Status::STATUS_OK)
	{
		//log("Failed to find stream");
		return;
	}

#if (COLORSTREAM && DEPTHSTREAM)
	
#elif (COLORSTREAM && !DEPTHSTREAM)

#elif (!COLORSTREAM && DEPTHSTREAM)

#endif
	if (index == 0)
	{
		colourStream.readFrame(&colourFrame);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, -1.0f, 1.0f);

	//file texture map with 0s
	memset(textureMap, 0, textureMapX*textureMapY*sizeof(openni::RGB888Pixel));

	// draw texture from frame
	if (colourFrame.isValid())
	{
		const openni::RGB888Pixel* frameRowTexture = (const openni::RGB888Pixel*)colourFrame.getData();
		openni::RGB888Pixel* textureRow = textureMap + colourFrame.getCropOriginY() * textureMapX;

		int rowBufferSize = colourFrame.getStrideInBytes() / sizeof(openni::RGB888Pixel);

		for (size_t i = 0; i < colourFrame.getHeight(); i++)
		{
			const openni::RGB888Pixel* pixelImage = frameRowTexture;
			openni::RGB888Pixel* pixelTexture = textureRow + colourFrame.getCropOriginX();

			for (size_t j = 0; j < colourFrame.getWidth(); j++, pixelImage++, pixelTexture++)
			{
				*pixelTexture = *pixelImage;
			}
			frameRowTexture += rowBufferSize;
			textureRow += textureMapX;
		}

		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //what type of varible name is GL_LINEAR_MIPMAP_LINEAR
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureMapX, textureMapY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureMap);

		glColor4f(1,1,1,1);

		// TODO: this needs to be 2 triangles instead for shaders to work
		glBegin(GL_QUADS);

		//topleft vertex
		glTexCoord2f(0, 0);
		glVertex2f(0, 0);

		//topright 
		glTexCoord2f((float)streamWidth/(float)textureMapX, 0);
		glVertex2f(800, 0);

		//bottomright
		glTexCoord2f((float)streamWidth / (float)textureMapX, (float)streamHeight / (float)textureMapY);
		glVertex2f(800, 600);


		//bottomleft
		glTexCoord2f(0, (float)streamHeight/(float)textureMapY);
		glVertex2f(0, 600);

		glEnd();
		

	}


	
}
