#ifndef ANIMATION_H
#define ANIMATION_H

#include "Timer.h"
#include <vector>

#define DllExport __declspec( dllexport )

using namespace std;

struct Frame{
	float u1, v1,
		  u2, v2,
		  u3, v3,
		  u4, v4;
};

class Animation{

	public:
		DllExport Animation();

		DllExport void addFrame(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth,
			float textureHeight);

		DllExport void addFrame(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, 
								float textureHeight, float durationInMili);

		DllExport void addFrame(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, 
								float textureHeight, float durationInMili, int frameCount);

		DllExport int getCurrentFrame();

		DllExport vector<Frame>& getFrames();

		DllExport void update(Timer& timer);

	private:
		int currentFrame;
		float currentTime;
		float length;
		vector<Frame> frames;
};
#endif

