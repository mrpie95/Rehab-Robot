#include "KInectStream.h"
#include <iostream>
#include <GL/glew.h>
#define TEXTURE_SIZE 512

#define log(x) std::cout << x << std::endl
#define NUM_OF_CHUNCKS(dataSize, chunksize) ((((dataSize)-1)/(chunksize)+1))
#define CHUNCK_SIZE(dataSize, chunksize) (NUM_OF_CHUNCKS(dataSize, chunksize)*(chunksize))

#define COLORSTREAM true
#define DEPTHSTREAM true
#define DRAWSKELETON false

#define colorCount = 3

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

#if (COLORSTREAM && !DEPTHSTREAM)
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

#elif (DEPTHSTREAM && !COLORSTREAM)
	if (depthStream.isValid())
	{
		depthMode = depthStream.getVideoMode();
		depthResolutionX = depthMode.getResolutionX();
		depthResolutionY = depthMode.getResolutionY();

		streamWidth = depthResolutionX;
		streamHeight = depthResolutionY;
	}
	else
	{
		log("no depth streams found");
		exit(1);
	}

	streams[0] = &depthStream;
#else
	if (depthStream.isValid() && colourStream.isValid())
	{
		depthMode = depthStream.getVideoMode();
		colourMode = colourStream.getVideoMode();

		colourResolutionX = colourMode.getResolutionX();
		colourResolutionY = colourMode.getResolutionY();
		depthResolutionX = depthMode.getResolutionX();
		depthResolutionY = depthMode.getResolutionY();

		streamWidth = depthResolutionX;
		streamHeight = depthResolutionY;
	}
	else
	{
		log("no streams found");
		exit(1);
	}

	streams[0] = &colourStream;
	streams[1] = &depthStream;

#endif


	colorTextureMapX = CHUNCK_SIZE(streamWidth, 512);
	colorTextureMapY = CHUNCK_SIZE(streamHeight, 512);
	colorTextureMap = new openni::RGB888Pixel[colorTextureMapX * colorTextureMapY];
	depthTextureMap = new openni::RGB888Pixel[colorTextureMapX * colorTextureMapY];

}

// TODO: this probably contains so many memory leaks idk
// TODO: this can probalbt be done in a fragment and vertext shader program and will scale properly and remove that stutter
// this might not be thread safe
void KinectStream::run()
{
	int index = -1;
	int streamCount = 0;
	

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
	if (index == 0)
	{
		colourStream.readFrame(&colourFrame);
	}
	else if (index == 1)
	{
		depthStream.readFrame(&depthFrame);
	}
	else
	{
		log("failed to read frame, how did you get here?");
	}

#elif (COLORSTREAM && !DEPTHSTREAM)
	if (index == 0)
		colourStream.readFrame(&colourFrame);
	else
		log("failed to read frame, how did you get here?");

#elif (!COLORSTREAM && DEPTHSTREAM)
	if (index == 0)
		depthStream.readFrame(&depthFrame);
	else
		log("failed to read depth frame, how did you get here?");
#endif
	
	
}

//
// NOTE: Swap opengl contexts before drawing
//

void KinectStream::drawDepthFrame()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, -1.0f, 1.0f);

	//file texture map with 0s
	memset(depthTextureMap, 0, colorTextureMapX*colorTextureMapY * sizeof(openni::Grayscale16Pixel));

	// draw texture from frame
	if (depthFrame.isValid())
	{
		const openni::DepthPixel* depthRow = (const openni::DepthPixel*)depthFrame.getData();
		openni::RGB888Pixel* textureRow = depthTextureMap + depthFrame.getCropOriginY() * colorTextureMapX;

		int rowBufferSize = depthFrame.getStrideInBytes() / sizeof(openni::DepthPixel);

		for (size_t i = 0; i < depthFrame.getHeight(); i++)
		{
			const openni::DepthPixel* depthPixel = depthRow;
			openni::RGB888Pixel* pixelTexture = textureRow + depthFrame.getCropOriginX();

			for (size_t j = 0; j < depthFrame.getWidth(); j++, depthPixel++, pixelTexture++)
			{
				// TODO: fix this 
				pixelTexture->r = *depthPixel / 0xff;
				pixelTexture->g = (*depthPixel << 8)/0xff;
				pixelTexture->b = 0;
			}
			depthRow += rowBufferSize;
			textureRow += colorTextureMapX;
		}

		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //what type of varible name is GL_LINEAR_MIPMAP_LINEAR
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, colorTextureMapX, colorTextureMapY, 0, GL_RGB, GL_UNSIGNED_BYTE, depthTextureMap);

		glColor4f(1, 1, 1, 1);

		// TODO: this needs to be 2 triangles instead for shaders to work
		glBegin(GL_QUADS);

		//topleft vertex
		glTexCoord2f(0, 0);
		glVertex2f(0, 0);

		//topright 
		glTexCoord2f((float)streamWidth / (float)colorTextureMapX, 0);
		glVertex2f(800, 0);

		//bottomright
		glTexCoord2f((float)streamWidth / (float)colorTextureMapX, (float)streamHeight / (float)colorTextureMapY);
		glVertex2f(800, 600);


		//bottomleft
		glTexCoord2f(0, (float)streamHeight / (float)colorTextureMapY);
		glVertex2f(0, 600);

		glEnd();
	}
}

void KinectStream::drawColorFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, -1.0f, 1.0f);

	//file texture map with 0s
	memset(colorTextureMap, 0, colorTextureMapX*colorTextureMapY * sizeof(openni::RGB888Pixel));

	// draw texture from frame
	if (colourFrame.isValid())
	{
		const openni::RGB888Pixel* frameRowTexture = (const openni::RGB888Pixel*)colourFrame.getData();
		openni::RGB888Pixel* textureRow = colorTextureMap + colourFrame.getCropOriginY() * colorTextureMapX;

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
			textureRow += colorTextureMapX;
		}

		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //what type of varible name is GL_LINEAR_MIPMAP_LINEAR
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, colorTextureMapX, colorTextureMapY, 0, GL_RGB, GL_UNSIGNED_BYTE, colorTextureMap);

		glColor4f(1, 1, 1, 1);

		// TODO: this needs to be 2 triangles instead for shaders to work
		glBegin(GL_QUADS);

		//topleft vertex
		glTexCoord2f(0, 0);
		glVertex2f(0, 0);

		//topright 
		glTexCoord2f((float)streamWidth / (float)colorTextureMapX, 0);
		glVertex2f(800, 0);

		//bottomright
		glTexCoord2f((float)streamWidth / (float)colorTextureMapX, (float)streamHeight / (float)colorTextureMapY);
		glVertex2f(800, 600);


		//bottomleft
		glTexCoord2f(0, (float)streamHeight / (float)colorTextureMapY);
		glVertex2f(0, 600);

		glEnd();


	}
}

void KinectStream::DrawLimb(nite::UserTracker* pUserTracker, const nite::SkeletonJoint& joint1, const nite::SkeletonJoint& joint2, int color)
{
	float coordinates[6] = {0};
	pUserTracker->convertJointCoordinatesToDepth(joint1.getPosition().x, joint1.getPosition().y, joint1.getPosition().z, &coordinates[0], &coordinates[1]);
	pUserTracker->convertJointCoordinatesToDepth(joint2.getPosition().x, joint2.getPosition().y, joint2.getPosition().z, &coordinates[3], &coordinates[4]);

	coordinates[0] *= 800.0f/(float)streamWidth;
	coordinates[1] *= 600.0f/(float)streamHeight;
	coordinates[3] *= 800.0f/(float)streamWidth;
	coordinates[4] *= 600.0f/(float)streamHeight;

	if (joint1.getPositionConfidence() == 1 && joint2.getPositionConfidence() == 1)
	{
		glColor3f(1.0f - colors[color][0], 1.0f - colors[color][1], 1.0f - colors[color][2]);
	}
	else if (joint1.getPositionConfidence() < 0.5f || joint2.getPositionConfidence() < 0.5f)
	{
		return;
	}
	else
	{
		glColor3f(.5, .5, .5);
	}
	glPointSize(2);
	glVertexPointer(3, GL_FLOAT, 0, coordinates);
	glDrawArrays(GL_LINES, 0, 2);

	glPointSize(10);
	if (joint1.getPositionConfidence() == 1)
	{
		glColor3f(1.0f - colors[color][0], 1.0f - colors[color][1], 1.0f - colors[color][2]);
	}
	else
	{
		glColor3f(.5, .5, .5);
	}
	glVertexPointer(3, GL_FLOAT, 0, coordinates);
	glDrawArrays(GL_POINTS, 0, 1);

	if (joint2.getPositionConfidence() == 1)
	{
		glColor3f(1.0f - colors[color][0], 1.0f - colors[color][1], 1.0f - colors[color][2]);
	}
	else
	{
		glColor3f(.5, .5, .5);
	}
	glVertexPointer(3, GL_FLOAT, 0, coordinates+3);
	glDrawArrays(GL_POINTS, 0, 1);
}

	