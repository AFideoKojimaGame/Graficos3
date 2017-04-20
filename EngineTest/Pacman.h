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
		//Sprite playerChar;
		//Animation* idle;
		//Animation* walking;
		//Animation* jumping;
		//std::vector<Entity2D*> obstacles;
		//Quad ob1;
		//Quad ob2;
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

		//Mesh meshy;
		//Mesh meshy2;
		//Mesh meshy3;

		Node* root;

		ImporterPG2* imp;
		string showMe;
		vector<string>* nameVector = new vector<string>();
		int* vertsNumber = new int();
		int* polyNumber = new int();
		BSPTree bsp;
		vector<BSPPlane*> planes;
};

#endif
