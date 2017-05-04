#include "Pacman.h"

bool Pacman::init(Renderer& rkRenderer){

	imp = new ImporterPG2(rkRenderer);
	root = new Node();

	if (!imp->importScene("Assets/elmenemovil.3ds", *root, bsp))
		return false;

	camSpeedDivider = 1000.0f;
	gameCamera = new Camera(rkRenderer);
	rkRenderer.setMatrix(D3DTS_VIEW, gameCamera->viewMatrix());

	gameCamera->setPos(0.0f, 0.0f, -200.0f);

	return true;
}

void Pacman::frame(Renderer& pkRenderer, DirectInput& rkInput, Timer& rkTimer){
	showMe = accumulate(begin(*nameVector), end(*nameVector), showMe);
	//D3DXMATRIXROTATIONQUATERNION
	gameCamera->updateFrustum();

	if (!nameVector->empty())
		nameVector->clear();

	root->setPos(0, 0, 0);
	root->updateBV();

	//root->draw(pkRenderer, 
	//		   gameCamera->getFrustum().aabbInFrustum(root->getAABB()),
	//	       gameCamera->getFrustum(),
	//		   *nameVector,
	//		   *vertsNumber,
	//	       *polyNumber,
	//	gameCamera->getPos(),
	//		   bsp);

	root->draw(
		*nameVector,
		*vertsNumber,
		*polyNumber,
		gameCamera->getPos(),
		bsp);

	/*if (rkInput.keyDown(Input::KEY_F)){
		gameCamera->strafe(-fSpeed);;
	}

	if (rkInput.keyDown(Input::KEY_G)){
		gameCamera->walk(-fSpeed);
	}

	if (rkInput.keyDown(Input::KEY_T)){
		gameCamera->walk(fSpeed);
	}

	if (rkInput.keyDown(Input::KEY_H)){
		gameCamera->strafe(fSpeed);
	}*/

	if (rkInput.keyDown(Input::KEY_LCONTROL)){
		gameCamera->fly(-fSpeed);
	}

	if (rkInput.keyDown(Input::KEY_SPACE)){
		gameCamera->fly(fSpeed);
	}

	if (rkInput.keyDown(Input::KEY_K)){
		root->getChildNode("group1")->ScaleAll(-0.05f,-0.05f,-0.05f);
	}

	if (rkInput.keyDown(Input::KEY_L)){
		root->getChildNode("group1")->ScaleAll(0.05f, 0.05f, 0.05f);
	}

	if (!isColliding){

		pkRenderer.drawText(showMe);
		showMe = "";
		if (rkInput.keyDown(Input::KEY_DOWN)){

			gameCamera->walk(-fSpeed);
			//root->getChildNode("group1")->getChildMesh("Teapot001")->ScaleY(-1.00f);
		}

		if (rkInput.keyDown(Input::KEY_UP)){

			gameCamera->walk(fSpeed);

			//root->getChildNode("group1")->getChildMesh("Teapot001")->ScaleY(1.00f);
		}

		if (rkInput.keyDown(Input::KEY_RIGHT)){

			gameCamera->strafe(fSpeed);

			//root->getChildNode("group1")->getChildMesh("Teapot001")->MoveX(1.00f);
		}

		if (rkInput.keyDown(Input::KEY_LEFT)){

			gameCamera->strafe(-fSpeed);

			//root->getChildNode("<3DSRoot>")->getChildMesh("Teapot001")->MoveX(-1.00f);
		}

		if (rkInput.keyDown(Input::KEY_W)){
			//gameCamera->walk(fSpeed);
			root->getChildNode("<3DSRoot>")->getChildMesh("Control")->MoveY(1.00f);
		}

		if (rkInput.keyDown(Input::KEY_S)){
			//gameCamera->walk(-fSpeed);
			root->getChildNode("<3DSRoot>")->getChildMesh("Control")->MoveY(-1.00f);
		}

		if (rkInput.keyDown(Input::KEY_D)){
			//gameCamera->strafe(fSpeed);
			root->getChildNode("<3DSRoot>")->getChildMesh("Control")->MoveX(1.00f);
		}

		if (rkInput.keyDown(Input::KEY_A)){
			//gameCamera->strafe(-fSpeed);
			root->getChildNode("<3DSRoot>")->getChildMesh("Control")->MoveX(-1.00f);
		}

		if (rkInput.keyDown(Input::KEY_Z)) {
			//gameCamera->walk(fSpeed);
			(root->getChildNode("<3DSRoot>")->getChildMesh("Control"))->MoveZ(1.00f);
		}

		if (rkInput.keyDown(Input::KEY_X)) {
			//gameCamera->walk(-fSpeed);
			(root->getChildNode("<3DSRoot>")->getChildMesh("Control"))->MoveZ(-1.00f);
		}

		if (rkInput.keyDown(Input::KEY_Q)){
			gameCamera->roll(0.1f);
		}

		if (rkInput.keyDown(Input::KEY_E)){
			gameCamera->roll(-0.1f);
		}

		gameCamera->pitch(rkInput.mouseRelPosY() / camSpeedDivider);

		gameCamera->yaw(rkInput.mouseRelPosX() / camSpeedDivider);
	}
}

void Pacman::deinit(){
	if (!nameVector->empty())
		nameVector->clear();

	delete vertsNumber;
	vertsNumber = NULL;

	delete polyNumber;
	polyNumber = NULL;
}