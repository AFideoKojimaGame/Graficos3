#ifndef MESH_H
#define MESH_H

#include"Renderer.h"
#include"Entity3D.h"
#include <math.h>
#include "Node.h"

using namespace std;

class Mesh : public Entity3D{

public:
	DllExport Mesh();
	DllExport Mesh(Renderer& rkRenderer);
	DllExport ~Mesh();

	DllExport void setRenderer(Renderer& rkRenderer);

	DllExport void setMeshData(const ColorVertex* pakVertices, D3DPRIMITIVETYPE ePrimitive,
							   size_t uiVertexCount, const unsigned short* pusIndices, size_t uiIndexCount);

	DllExport void setMeshData(const TexVertex* pakVertices, D3DPRIMITIVETYPE ePrimitive,						//Revisar proviene 
							   size_t uiVertexCount, const unsigned short* pusIndices, size_t uiIndexCount);	//de Renderer

	DllExport void draw(vector<string>& vec);
	DllExport void drawColored();
	DllExport void draw(Renderer& rkRenderer, CollisionResult eParentResult, const Frustum& rkFrustum, vector<string>& vec);

	DllExport void createBV(float x, float y, float z);
	DllExport void updateBV();

	DllExport void setTextureId(int iTextureId, Texture blah);

	DllExport D3DXVECTOR3 getMin();
	DllExport D3DXVECTOR3 getMax();

protected:
	Renderer* meshRenderer;

	VertexBuffer* meshVB;
	IndexBuffer* meshIB;
	VertexBuffer* meshVBnotex;
	D3DPRIMITIVETYPE meshPrimitive;

	const TexVertex* myVerts;
	size_t vertsSize;

	Texture text;

	int textureID;
};

#endif