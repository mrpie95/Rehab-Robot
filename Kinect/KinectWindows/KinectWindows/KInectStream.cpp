#include "KInectStream.h"
#include <iostream>
#include <GL/glew.h>
#include <string>
#include <algorithm>
#define TEXTURE_SIZE 512

#define log(x) std::cout << x << std::endl
#define logI(x,i) std::cout << x <<" "<< i << std::endl;
#define NUM_OF_CHUNCKS(dataSize, chunksize) ((((dataSize)-1)/(chunksize)+1))
#define CHUNCK_SIZE(dataSize, chunksize) (NUM_OF_CHUNCKS(dataSize, chunksize)*(chunksize))

#define COLORSTREAM true
#define DEPTHSTREAM false
#define SKELETON true
#define colorCount = 3

KinectStream::KinectStream(openni::Device& device, openni::VideoStream& depthStream, openni::VideoStream& colourStream, nite::UserTracker& tracker): 
	kinect(device), depthStream(depthStream), colourStream(colourStream), tracker(tracker) ,streams(NULL)
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


// TODO: this can probalbt be done in a fragment and vertext shader program and will scale properly and remove that stutter
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
				// TODO: fix this 16bit depthpixel to 24bit rgb
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

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, 800, 600, 0, -1.0f, 1.0f);

		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //what type of varible name is GL_LINEAR_MIPMAP_LINEAR
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, colorTextureMapX, colorTextureMapY, 0, GL_RGB, GL_UNSIGNED_BYTE, colorTextureMap);

		glColor4f(1, 1, 1, 1);

		// TODO: this needs to be 2 triangles instead, i heard thats good practice for graphics apis

		glEnable(GL_TEXTURE_2D);
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
		glDisable(GL_TEXTURE_2D);


	}
}

void KinectStream::DrawLimb(nite::UserTracker* pUserTracker, const nite::SkeletonJoint& joint1, const nite::SkeletonJoint& joint2, const nite::UserData& user)
{
	bool prime = false;
	if (PrimeUser.getId() == user.getId())
		prime = true;


	glDisable(GL_TEXTURE_2D);

	float coordinates[6] = {0};
	pUserTracker->convertJointCoordinatesToDepth(joint1.getPosition().x, joint1.getPosition().y, joint1.getPosition().z, &coordinates[0], &coordinates[1]);
	pUserTracker->convertJointCoordinatesToDepth(joint2.getPosition().x, joint2.getPosition().y, joint2.getPosition().z, &coordinates[3], &coordinates[4]);

	coordinates[0] *= 800.0f/(float)streamWidth;
	coordinates[1] *= 600.0f/(float)streamHeight;
	coordinates[3] *= 800.0f/(float)streamWidth;
	coordinates[4] *= 600.0f/(float)streamHeight;

	if (joint1.getPositionConfidence() == 1 && joint2.getPositionConfidence() == 1)
	{
		if (prime)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (joint1.getPositionConfidence() < 0.5f || joint2.getPositionConfidence() < 0.5f)
	{
		//log("low confidence in joint posisition");
		glColor3f(1.0f, 1.0f, 1.0f);
		return;
	}
	else
	{
		if (prime)
			glColor3f(1.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 1.0f, 1.0f);
	}
	glPointSize(2);
	glVertexPointer(3, GL_FLOAT, 0, coordinates);
	glDrawArrays(GL_LINES, 0, 2);

	glPointSize(10);
	if (joint1.getPositionConfidence() == 1)
	{
		if (prime)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		if (prime)
			glColor3f(1.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 1.0f, 1.0f);
	}
	glVertexPointer(3, GL_FLOAT, 0, coordinates);
	glDrawArrays(GL_POINTS, 0, 1);

	if (joint2.getPositionConfidence() == 1)
	{
		if (prime)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		if (prime)
			glColor3f(1.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 1.0f, 1.0f);
	}
	glVertexPointer(3, GL_FLOAT, 0, coordinates+3);
	glDrawArrays(GL_POINTS, 0, 1);
}

void KinectStream::DrawSkeleton(nite::UserTracker* pUserTracker, const nite::UserData& userData)
{
	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_HEAD), userData.getSkeleton().getJoint(nite::JOINT_NECK), userData);

	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_LEFT_SHOULDER), userData.getSkeleton().getJoint(nite::JOINT_LEFT_ELBOW), userData);
	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_LEFT_ELBOW), userData.getSkeleton().getJoint(nite::JOINT_LEFT_HAND), userData);

	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_RIGHT_SHOULDER), userData.getSkeleton().getJoint(nite::JOINT_RIGHT_ELBOW), userData);
	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_RIGHT_ELBOW), userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HAND), userData);

	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_LEFT_SHOULDER), userData.getSkeleton().getJoint(nite::JOINT_RIGHT_SHOULDER), userData);

	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_LEFT_SHOULDER), userData.getSkeleton().getJoint(nite::JOINT_TORSO), userData);
	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_RIGHT_SHOULDER), userData.getSkeleton().getJoint(nite::JOINT_TORSO), userData);

	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_TORSO), userData.getSkeleton().getJoint(nite::JOINT_LEFT_HIP), userData);
	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_TORSO), userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HIP), userData);

	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_LEFT_HIP), userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HIP), userData);


	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_LEFT_HIP), userData.getSkeleton().getJoint(nite::JOINT_LEFT_KNEE), userData);
	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_LEFT_KNEE), userData.getSkeleton().getJoint(nite::JOINT_LEFT_FOOT), userData);

	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_RIGHT_HIP), userData.getSkeleton().getJoint(nite::JOINT_RIGHT_KNEE), userData);
	DrawLimb(pUserTracker, userData.getSkeleton().getJoint(nite::JOINT_RIGHT_KNEE), userData.getSkeleton().getJoint(nite::JOINT_RIGHT_FOOT), userData);
}


bool temp = false;
void KinectStream::updateUserState(const nite::UserData & user, uint64_t delta)
{
	if (user.isNew())
	{
		logI("Found new user ", std::to_string(user.getId()));
	}
	else if (user.isVisible() && !temp)
	{
		logI("Tracking user ", std::to_string(user.getId()));
		temp = true;
	}
	else if (user.isLost())
	{
		logI("Lost user ", std::to_string(user.getId()));
	}


	//skeltons changed
	if (userSkeltonState != user.getSkeleton().getState())
	{
		userSkeltonState = user.getSkeleton().getState();

		switch (userSkeltonState)
		{
		case nite::SKELETON_NONE:
			log("no tracking");
			break;
		case nite::SKELETON_CALIBRATING:
			log("calibrating user");
			break;
		case nite::SKELETON_TRACKED:
			log("Trackingg");
			break;
		default:
			log("error in tracking");
			break;
		}
	}
}

void KinectStream::runTracker()
{
	nite::Status status = tracker.readFrame(&trackerFrame);
	users.clear();
	if (status != nite::STATUS_OK)
	{
		log("failed to get tracker data");
		return;
	}

	

	const nite::UserMap& userLabels = trackerFrame.getUserMap();

	const nite::Array<nite::UserData>& tempUsers = trackerFrame.getUsers();

	if (tempUsers.isEmpty())
		return;
	
	for (size_t i = 0; i < tempUsers.getSize(); i++)
	{
		nite::UserData user = tempUsers[i];

		updateUserState(user, trackerFrame.getTimestamp());

		if (user.isNew())
		{
			tracker.startSkeletonTracking(user.getId());
			tracker.startPoseDetection(user.getId(), nite::POSE_CROSSED_HANDS);
			
		}
		else if (!user.isLost())
		{
			if (user.getSkeleton().getState() == nite::SKELETON_TRACKED)
			{
				glMatrixMode(GL_PROJECTION);
				glPushMatrix();
				glLoadIdentity();

				glOrtho(0, 800, 600, 0, -1.0, 1.0);
				glDisable(GL_TEXTURE_2D);

				if (user.getPose(nite::POSE_CROSSED_HANDS).isEntered())
				{
					PrimeUser = user;
					logI("New prime, user id", user.getId());
				}
				
				//update prime
				if (PrimeUser.getId() == user.getId())
					PrimeUser = user;

				DrawSkeleton(&tracker, user);
				
			}
		}
		
	}
	
}