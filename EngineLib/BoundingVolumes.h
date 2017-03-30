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

#endif