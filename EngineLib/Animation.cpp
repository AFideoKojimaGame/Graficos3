#include "Animation.h"

Animation::Animation(){
	currentTime = 0;
	currentFrame = 0;
	length = 1;
}

void Animation::addFrame(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, float textureHeight){
	addFrame(frameX, frameY, frameWidth, frameHeight, textureWidth, textureHeight, 1);
}

void Animation::addFrame(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, float textureHeight,
						 float durationInMili){
	addFrame(frameX, frameY, frameWidth, frameHeight, textureWidth, textureHeight, durationInMili, 1);
	addFrame(frameX, frameY, frameWidth, frameHeight, textureWidth, textureHeight, durationInMili, 1);
}

void Animation::addFrame(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, float textureHeight,
						 float durationInMili, int frameCount){

	for (int i = 0; i < frameCount; i++){
		Frame frame;

		frame.u1 = (frameX + (frameWidth * i)) / textureWidth;
		frame.v1 = frameY / textureHeight;

		frame.u2 = (frameX + frameWidth * (i + 1)) / textureWidth;
		frame.v2 = frameY / textureHeight;

		frame.u3 = (frameX + (frameWidth * i)) / textureWidth;
		frame.v3 = (frameY + frameHeight) / textureHeight;

		frame.u4 = (frameX + frameWidth * (i + 1)) / textureWidth;
		frame.v4 = (frameY + frameHeight) / textureHeight;

		frames.push_back(frame);
	}

	length = durationInMili;
}

vector<Frame>& Animation::getFrames(){
	return frames;
}

int Animation::getCurrentFrame(){
	return currentFrame;
}

void Animation::update(Timer& timer){
	currentTime += timer.timeBetweenFrames();
	while (currentTime > length) {
		currentTime -= length;
	}

	float frameLength = length / frames.size();
	currentFrame = static_cast<unsigned int>(currentTime / frameLength);
}
