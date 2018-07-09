#include "KInectStream.h"
#include <iostream>

#define TEXTURE_SIZE 512

#define log(x) std::cout << x << std::endl
#define NUM_OF_CHUNCKS(dataSize, chunksize) ((((dataSize)-1)/(chunksize)+1))
#define CHUNCK_SIZE(dataSize, chunksize) (NUM_OF_CHUNCKS(dataSize, chunksize)*(chunksize))

KinectStream::KinectStream(openni::Device& device, openni::VideoStream& depthStream, openni::VideoStream& colourStream): kinect(device), depthStream(depthStream), colourStream(colourStream)
{
}


KinectStream::~KinectStream()
{
}

void KinectStream::init()
{
	openni::VideoMode depthMode;
	openni::VideoMode colourMode;

	int colourResolutionX;
	int colourResolutionY;

	if (colourStream.isValid())
	{
		//depthMode = depthStream.getVideoMode();
		colourMode = colourStream.getVideoMode();

		//int depthResolutionX = depthMode.getResolutionX();
		//int depthResolutionY = depthMode.getResolutionY();
		colourResolutionX = colourMode.getResolutionX();
		colourResolutionY = colourMode.getResolutionY();
	}
	else
	{
		log("No valid streams found");
		exit(1);
	}

	textureMapX = CHUNCK_SIZE(colourResolutionX, 512);
	textureMapY = CHUNCK_SIZE(colourResolutionY, 512);
	textureMap = new openni::RGB888Pixel[textureMapX * textureMapY];
}

//TODO: this contains so many memory leaks
void KinectStream::run()
{
	int index;
	openni::VideoStream** stream = new openni::VideoStream*[1];
	stream[1] = &colourStream;
	openni::Status streamStatus = openni::OpenNI::waitForAnyStream(stream, 1 &index, new INT(1));

	if (streamStatus != openni::Status::STATUS_OK)
	{
		log("Failed to find stream");
		return;
	}
}
