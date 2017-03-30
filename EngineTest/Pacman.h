#ifndef PACMAN_H
#define PACMAN_H

#include "Engine.h"
#include "Mesh.h"
#include "ImporterPG2.h"
#include "Node.h"

#include <numeric>
#include <vector>

using namespace std;

class Pacman : public Game{
	public:
		bool init(Renderer& rkRenderer);
		void frame(Renderer& pkRenderer, DirectInput& rkInput, Timer& rkTimer);
		void deinit();

	private:

		bool isColliding = false;
		float Xmove, Ymove;
		bool movingV = false;
		bool movingH = false;
		bool isItSet = false;
		const float fSpeed = 10.1f;
		int itest = 0;
		float scalex, scaley;
		Camera* gameCamera;

		float camSpeedDivider;

		Node* root;

		ImporterPG2* imp;
		string showMe;
		vector<string>* nameVector = new vector<string>();
};

#endif
