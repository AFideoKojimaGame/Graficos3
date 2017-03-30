#ifndef RENDERER_H
#define RENDERER_H

#include "VertexBuffer2D.h"
#include "d3dx9math.h"
#include <string>
#include <vector>
#include "pg2_vertexbuffer.h"
#include "pg2_indexbuffer.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define DllExport __declspec( dllexport )

struct IDirect3D9;
struct IDirect3DDevice9;
typedef D3DXMATRIX* Matrix;
struct IDirect3DTexture9;
typedef IDirect3DTexture9* Texture;

static const Texture NoTexture = NULL;

using namespace vb2d;
using namespace std;
class VertexBuffer;
class IndexBuffer;

#define CustomFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define TextureFVF (D3DFVF_XYZ | D3DFVF_TEX1)


struct ColorVertex{
	float x, y, z;
	DWORD color;
};

struct TexVertex{ //Revisar
	float x, y, z;
	float u, v;
};

class Renderer{
public:
	DllExport Renderer();
	DllExport ~Renderer();
	DllExport bool init(HWND hwnd);
	DllExport void beginFrame();
	DllExport void endFrame();
	DllExport void draw(ColorVertex* gameVertex, D3DPRIMITIVETYPE primitive, int vertexCount);
	DllExport void draw(TexVertex* gameVertex, D3DPRIMITIVETYPE primitive, int vertexCount);
	DllExport void setMatrix(const Matrix& rkMatrix);
	DllExport void setMatrix(D3DTRANSFORMSTATETYPE t, const Matrix& rkMatrix);
	DllExport const Texture loadTexture(const std::string& textureName);
	DllExport const Texture loadTexture(const std::string& textureName, D3DCOLOR ck);
	DllExport void setCurrentTexture(const Texture& texture);
	DllExport const Matrix& getProjectionMatrix() const;
	DllExport void setToPerspective();
	DllExport void setToOrtho();

	DllExport VertexBuffer* createVertexBuffer(size_t uiVertexSize, unsigned int uiFVF);
	DllExport IndexBuffer* createIndexBuffer();
	DllExport void setCurrentIndexBuffer(IndexBuffer* pkIndexBuffer);
	DllExport void setCurrentVertexBuffer(VertexBuffer* pkVertexBuffer);
	DllExport void drawCurrentBuffers(D3DPRIMITIVETYPE ePrimitive);
	DllExport void drawText(string text);

private:
	HWND hwnd;

	VertexBuffer2D* vb;
	VertexBuffer2D* texturevb;

	IDirect3D9* d3d;
	IDirect3DDevice9* d3ddev;
	ID3DXFont* text_F;

	std::vector<Texture> textureList;

	Matrix projectionMatrix;
	IndexBuffer* iB;
	VertexBuffer* vB3d;
	float viewportWidth, viewportHeight;
};

#endif