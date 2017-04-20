#ifndef NODE_H
#define NODE_H

#include "Entity3D.h"
#include <vector>
#include <list>

using namespace std;

class Node : public Entity3D{
	public:
		DllExport Node();
		DllExport ~Node();

		DllExport const vector<Entity3D*>& childs() const;

		DllExport void addChild(Entity3D* newChild);
		DllExport void removeChild(Entity3D* newChild);
		DllExport Node* getChildNode(string name);
		DllExport Entity3D* getChildMesh(string name);

		DllExport void updateWorldTransformation();
		DllExport void draw(vector<string>& vec, int& vNum, int& pNum);
		DllExport void draw(Renderer& rkRenderer, CollisionResult eParentResult, const Frustum& rkFrustum, vector<string>& vec, int& vNum, int& pNum, D3DXVECTOR3 camPos, BSPTree& bsp);

		DllExport void updateBV();

		DllExport float WorldPosX(){ return worldPosX; };
		DllExport float WorldPosY(){ return worldPosY; };
		DllExport float WorldPosZ(){ return worldPosZ; };

		DllExport float WorldScaleX(){ return worldScaleX; };
		DllExport float WorldScaleY(){ return worldScaleY; };
		DllExport float WorldScaleZ(){ return worldScaleZ; };

	private:
		vector<Entity3D*> children;
		float worldPosX, worldPosY, worldPosZ;
		float worldScaleX, worldScaleY, worldScaleZ;
};

#endif