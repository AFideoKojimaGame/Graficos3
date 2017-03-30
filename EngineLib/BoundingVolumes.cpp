#include "BoundingVolumes.h"

AABB::AABB(){
	emptyAABB();
}

AABB::~AABB(){}

void AABB::addPoint(const D3DXVECTOR3 &p){

	//Usado para AABB de Nodo

	if (p.x < min.x) 
		min.x = p.x;
	if (p.x > max.x) 
		max.x = p.x;

	if (p.y < min.y) 
		min.y = p.y;
	if (p.y > max.y) 
		max.y = p.y;

	if (p.z < min.z) 
		min.z = p.z;
	if (p.z > max.z)
		max.z = p.z;
}

void AABB::overwriteMin(const D3DXVECTOR3 &p){

	//Usado para AABB de Mesh

	min.x = p.x;

	min.y = p.y;

	min.z = p.z;

}

void AABB::overwriteMax(const D3DXVECTOR3 &p){

	//Usado para AABB de Mesh

	max.x = p.x;

	max.y = p.y;

	max.z = p.z;
}

void AABB::addBasePoint(const D3DXVECTOR3 &p){

	//Se usa para crear la AABB del Mesh

	if (p.x < basemin.x)
		basemin.x = p.x;
	if (p.x > basemax.x)
		basemax.x = p.x;

	if (p.y < basemin.y)
		basemin.y = p.y;
	if (p.y > basemax.y)
		basemax.y = p.y;

	if (p.z < basemin.z)
		basemin.z = p.z;
	if (p.z > basemax.z)
		basemax.z = p.z;
}

void AABB::emptyAABB(){
	const float kBigNumber = 1e37f;
	min.x = min.y = min.z = kBigNumber;
	max.x = max.y = max.z = -kBigNumber;
	basemin = min;
	basemax = max;
}

Frustum::Frustum(){
	for (unsigned int i = 0; i < 6; i++)
		frustum[i] = new D3DXPLANE();
}

Frustum::~Frustum(){
	for (unsigned int i = 0; i < 6; i++){
		delete frustum[i];
		frustum[i] = NULL;
	}
}

bool Frustum::pointInFrustum(D3DXVECTOR3& p) const{
	for (int i = 0; i < 6; i++){
		if (D3DXPlaneDotCoord(frustum[i], &p) < 0){
			// Outside the frustum, reject it!
			return false;
		}
	}
	return true;
}

const CollisionResult Frustum::aabbInFrustum(const AABB& aabb) const{
	float xPoint = aabb.min.x;
	float yPoint, zPoint;
	int pointsInFrustum = 0;
	for (int x = 0; x < 2; x++){
		yPoint = aabb.min.y;
		for (int y = 0; y < 2; y++){
			zPoint = aabb.min.z;
			for (int z = 0; z < 2; z++){
				D3DXVECTOR3 v;
				v.x = xPoint;
				v.y = yPoint;
				v.z = zPoint;
				if (pointInFrustum(v))
					pointsInFrustum++;
				zPoint = aabb.max.z;
			}
			yPoint = aabb.max.y;
		}
		xPoint = aabb.max.x;
	}

	if (pointsInFrustum == 0)
		return AllOutside;
	else if (pointsInFrustum == 8)
		return AllInside;
	else
		return PartiallyInside;
}

void Frustum::updateFrustum(D3DXMATRIX& view){

	//LEFT
	frustum[0]->a = view._14 + view._11;
	frustum[0]->b = view._24 + view._21;
	frustum[0]->c = view._34 + view._31;
	frustum[0]->d = view._44 + view._41;

	//RIGHT
	frustum[1]->a = view._14 - view._11;
	frustum[1]->b = view._24 - view._21;
	frustum[1]->c = view._34 - view._31;
	frustum[1]->d = view._44 - view._41;

	//TOP
	frustum[2]->a = view._14 - view._12;
	frustum[2]->b = view._24 - view._22;
	frustum[2]->c = view._34 - view._32;
	frustum[2]->d = view._44 - view._42;

	//BOTTOM
	frustum[3]->a = view._14 + view._12;
	frustum[3]->b = view._24 + view._22;
	frustum[3]->c = view._34 + view._32;
	frustum[3]->d = view._44 + view._42;

	//NEAR PLANE
	frustum[4]->a = view._13;
	frustum[4]->b = view._23;
	frustum[4]->c = view._33;
	frustum[4]->d = view._43;

	//FAR PLANE	
	frustum[5]->a = view._14 - view._13;
	frustum[5]->b = view._24 - view._23;
	frustum[5]->c = view._34 - view._33;
	frustum[5]->d = view._44 - view._43;

	for (unsigned int i = 0; i < 6; i++)
		D3DXPlaneNormalize(frustum[i], frustum[i]);
}