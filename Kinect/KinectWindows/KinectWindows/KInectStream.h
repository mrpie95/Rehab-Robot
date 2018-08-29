#pragma once
#include <OpenNI.h>
#include <NiTE.h>
#include <vector>
#include <memory>
#include "gestureInterface.h"
#include <FTGL/FTGLPixmapFont.h>
struct QuadData
{
	int topLeftX, topLeftY;
	int topRightX, topRightY;
	int bottomLeftX, bottomLeftY;
	int bottomRightX, bottomRightY;
	int width, height;

	QuadData(int topLeftX, int topLeftY, int height, int width) : topLeftX(topLeftX), topLeftY(topLeftY), width(width), height(height)
	{
		topRightX = topLeftX + width;
		topRightY = topLeftY;

		bottomLeftX = topLeftX;
		bottomLeftY = topLeftY + height;

		bottomRightX = topLeftX + width;
		bottomRightY = topLeftY + height;
	}
};

class KinectStream
{
private:
	openni::VideoFrameRef depthFrame;
	openni::VideoFrameRef colourFrame;
	openni::VideoStream& colourStream;
	openni::VideoStream& depthStream;
	openni::Device& kinect;

	openni::VideoStream** streams;

	int colorTextureMapX;
	int colorTextureMapY;
	openni::RGB888Pixel* colorTextureMap;
	openni::RGB888Pixel* depthTextureMap;

	int streamWidth;
	int streamHeight;

	nite::UserTracker& tracker;
	nite::UserTrackerFrameRef trackerFrame;
	nite::UserData PrimeUser;
	std::vector<nite::UserData> users;
	nite::SkeletonState userSkeltonState = nite::SKELETON_NONE;

	
	FTGLPixmapFont font;
	
	void DrawLimb(nite::UserTracker* pUserTracker, const nite::SkeletonJoint& joint1, const nite::SkeletonJoint& joint2, const nite::UserData& user, const QuadData&);
	void DrawSkeleton(nite::UserTracker* pUserTracker, const nite::UserData& userData, const QuadData&);
	void updateUserState(const nite::UserData& user, uint64_t delta);




public:
	KinectStream(openni::Device& device, openni::VideoStream& depthStream, openni::VideoStream& colourStream, nite::UserTracker& tracker);
	~KinectStream();

	void init();
	void run();

	void runTracker(const QuadData& pos);
	void drawDepthFrame(const QuadData&);
	void drawColorFrame(const QuadData&, int, int);
	void drawString(const char*, float x, float y, float z, int size);

	nite::Skeleton* getUserSkeleton()
	{
		if (&PrimeUser != NULL)
		{
			if (!PrimeUser.isLost())
			{
				if (PrimeUser.getSkeleton().getState() == nite::SKELETON_TRACKED)
				{
					return (const_cast<nite::Skeleton*>(&PrimeUser.getSkeleton()));
				}
			}
			
		}
		return nullptr;
	}

	bool isUserLost()
	{
		return !PrimeUser.isVisible();
	}

};

