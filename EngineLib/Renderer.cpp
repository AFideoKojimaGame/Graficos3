#include "Renderer.h"
#include <d3d9.h>
#pragma comment (lib, "d3d9.lib") 
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib") 
#include "pg2_vertexbuffer.h"
#include "pg2_indexbuffer.h"

using namespace std;

Renderer::Renderer(){
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	projectionMatrix = new D3DXMATRIX();
}

Renderer::~Renderer(){
	d3ddev->Release();
	d3ddev = NULL;
	d3d->Release();
	d3d = NULL;
	delete vb;
	vb = NULL;

	vector<Texture>::iterator iter;
	for (iter = textureList.begin(); iter != textureList.end(); iter++){
		(*iter)->Release();
		(*iter) = NULL;
	}

	textureList.clear();

	delete projectionMatrix;
}

bool Renderer::init(HWND hWnd){
	if (!d3d) return false;

	D3DDISPLAYMODE displayMode;
	HRESULT hr;
	hr = d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);

	if (hr != D3D_OK) return false;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	hr = d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	if (hr != D3D_OK) return false;

	vb = new VertexBuffer2D(d3ddev, sizeof(ColorVertex), CustomFVF);
	texturevb = new VertexBuffer2D(d3ddev, sizeof(TexVertex), TextureFVF);

	D3DVIEWPORT9 viewport;
	d3ddev->GetViewport(&viewport);

	viewportWidth = static_cast<float>(viewport.Width);
	viewportHeight = static_cast<float>(viewport.Height);

	//D3DXMatrixOrthoLH(projectionMatrix, viewportWidth, viewportHeight, -1.0f, 1000.0f);
	setToPerspective();

	d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);
	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	d3ddev->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

	hr = D3DXCreateFont(d3ddev,
		20,
		0,
		FW_NORMAL,
		1,
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		"Arial",
		&text_F);
	return true;


}

void Renderer::beginFrame(){
	d3ddev->BeginScene();
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
}

void Renderer::draw(ColorVertex* gameVertex, D3DPRIMITIVETYPE primiType, int vertexCount){
	vb->bind();
	vb->draw(gameVertex, primiType, vertexCount);
}

void Renderer::draw(TexVertex* gameVertex, D3DPRIMITIVETYPE primiType, int vertexCount){
	texturevb->bind();
	texturevb->draw(gameVertex, primiType, vertexCount);
}

void Renderer::endFrame(){
	d3ddev->EndScene();
	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void Renderer::setMatrix(const Matrix& rkMatrix){
	d3ddev->SetTransform(D3DTS_WORLD, rkMatrix);
}

void Renderer::setMatrix(D3DTRANSFORMSTATETYPE t, const Matrix& rkMatrix){
	d3ddev->SetTransform(t, rkMatrix);
}

const Texture Renderer::loadTexture(const std::string& textureName){
	return loadTexture(textureName, 0);
}

const Texture Renderer::loadTexture(const std::string& textureName, D3DCOLOR ck){
	Texture texture = NULL;

	HRESULT hr = D3DXCreateTextureFromFileEx(d3ddev,
		textureName.c_str(),
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE,
		ck,
		NULL,
		NULL,
		&texture);

	if (hr != D3D_OK){
		return NoTexture;
	}
	else{
		for (size_t i = 0; i < textureList.size(); i++){
			if (texture == textureList[i])
				return texture;
		}

		textureList.push_back(texture);
		return texture;
	}
}

void Renderer::setCurrentTexture(const Texture& texture){
	d3ddev->SetTexture(0, texture);
}

const Matrix& Renderer::getProjectionMatrix() const{
	return projectionMatrix;
}

void Renderer::setToPerspective(){
	D3DXMatrixPerspectiveFovLH(projectionMatrix, D3DX_PI / 3.0f, viewportWidth / viewportHeight, 0.1f, 4000.0f);
	d3ddev->SetTransform(D3DTS_PROJECTION, projectionMatrix);
}

void Renderer::setToOrtho(){
	D3DXMatrixOrthoLH(projectionMatrix, viewportWidth, viewportHeight, -1.0f, 1000.0f);
	d3ddev->SetTransform(D3DTS_PROJECTION, projectionMatrix);
}

void Renderer::setCurrentVertexBuffer(VertexBuffer* VB3d){
	vB3d = VB3d;
}

void Renderer::setCurrentIndexBuffer(IndexBuffer* indexBuffer){
	iB = indexBuffer;
}

void Renderer::drawCurrentBuffers(D3DPRIMITIVETYPE ePrimitive){
	int iPrimitiveCount = 0;

	if (ePrimitive == D3DPT_POINTLIST)
	{
		iPrimitiveCount = iB->indexCount();
	}
	else if (ePrimitive == D3DPT_LINELIST)
	{
		iPrimitiveCount = iB->indexCount() / 2;
	}
	else if (ePrimitive == D3DPT_LINESTRIP)
	{
		iPrimitiveCount = iB->indexCount() - 1;
	}
	else if (ePrimitive == D3DPT_TRIANGLELIST)
	{
		iPrimitiveCount = iB->indexCount() / 3;
	}
	else if (ePrimitive == D3DPT_TRIANGLESTRIP)
	{
		iPrimitiveCount = iB->indexCount() - 2;
	}
	else if (ePrimitive == D3DPT_TRIANGLEFAN)
	{
		iPrimitiveCount = iB->indexCount() - 2;
	}

	HRESULT hr = d3ddev->DrawIndexedPrimitive(ePrimitive, 0, 0, vB3d->vertexCount(), 0, iPrimitiveCount);

	assert(hr == D3D_OK);
}

VertexBuffer* Renderer::createVertexBuffer(size_t uiVertexSize, unsigned int uiFVF){
	return new VertexBuffer(*this, d3ddev, uiVertexSize, uiFVF);
}

IndexBuffer* Renderer::createIndexBuffer(){
	return new IndexBuffer(*this, d3ddev);
}


void Renderer::drawText(string text){

	RECT font_rect;
	SetRect(&font_rect, 0, 0, 800, 600);

	text_F->DrawText(NULL,

		text.c_str(),

		-1,

		&font_rect,

		DT_LEFT | DT_NOCLIP,

		0xFFFFFFFF);
}