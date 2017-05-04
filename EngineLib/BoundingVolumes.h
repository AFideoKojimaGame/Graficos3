#ifndef BOUNDINGVOLUMES_H
#define BOUNDINGVOLUMES_H

#include "Renderer.h"

enum CollisionResult{
	AllInside,
	AllOutside,
	PartiallyInside
};

struct AABB {
	
	public:
		D3DXVECTOR3 min;
		D3DXVECTOR3 max;
		D3DXVECTOR3 basemin;
		D3DXVECTOR3 basemax;

		DllExport AABB();
		DllExport ~AABB();

		DllExport void addPoint(const D3DXVECTOR3 &p);
		DllExport void overwriteMin(const D3DXVECTOR3 &p);
		DllExport void overwriteMax(const D3DXVECTOR3 &p);
		DllExport void addBasePoint(const D3DXVECTOR3 &p);
		DllExport void emptyAABB();
};

struct Frustum{
	public:
		DllExport Frustum();
		DllExport ~Frustum();
		DllExport void updateFrustum(D3DXMATRIX& view);
		DllExport bool pointInFrustum(D3DXVECTOR3 &p) const;
		DllExport const CollisionResult aabbInFrustum(const AABB& aabb) const;

	private:
		D3DXPLANE* frustum[6];
};

struct BSPPlane {
	public:
		DllExport BSPPlane();
		DllExport ~BSPPlane();
		DllExport void SetPlane(D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3);
		DllExport float Check(D3DXVECTOR3 &p);
	private:
		D3DXPLANE* myPlane;
};

struct BSPTree {
	public:
		DllExport BSPTree();
		DllExport ~BSPTree();
		DllExport void AddChild(D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3);
		DllExport bool CheckTree(D3DXVECTOR3 camPos, D3DXVECTOR3 objMin, D3DXVECTOR3 objMax);
	private:
		vector<BSPPlane*> planes;
};

#endif