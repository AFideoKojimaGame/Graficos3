#include "Quad.h"

Quad::Quad(){
	q_vertices[0] = { -0.5, 0.5f, 0.0f, D3DCOLOR_ARGB(255, 0, 0, 255) };
	q_vertices[1] = { 0.5f, 0.5f, 0.0f, D3DCOLOR_ARGB(255, 0, 255, 0) };
	q_vertices[2] = { -0.5f, -0.5f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 0) };
	q_vertices[3] = { 0.5f, -0.5f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 255) };

	updateTransformation();
}

Quad::~Quad(){
	delete m_pkTransformationMatrix;
	m_pkTransformationMatrix = NULL;
}

void Quad::draw(Renderer& rkRenderer){
	rkRenderer.setCurrentTexture(NoTexture);
	rkRenderer.setMatrix(m_pkTransformationMatrix);
	rkRenderer.draw(q_vertices, D3DPT_TRIANGLESTRIP, 4);
}
