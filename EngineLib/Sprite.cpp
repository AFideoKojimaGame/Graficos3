#include "Sprite.h"

Sprite::Sprite():
texture(NoTexture){
	s_vertices[0] = { -0.5, 0.5f, 1.0f, 0.0f, 0.0f };		//x, y, z, u, v
	s_vertices[1] = { 0.5f, 0.5f, 1.0f, 1.0f, 0.0f };		//x, y, z, u, v
	s_vertices[2] = { -0.5f, -0.5f, 1.0f, 0.0f, 1.0f };		//x, y, z, u, v
	s_vertices[3] = { 0.5f, -0.5f, 1.0f, 1.0f, 1.0f };		//x, y, z, u, v
}

Sprite::~Sprite(){
	m_pkTransformationMatrix = NULL;
	delete m_pkTransformationMatrix;
}

void Sprite::setTexCoords(float fU0, float fV0,
						  float fU1, float fV1,
						  float fU2, float fV2,
						  float fU3, float fV3){

	s_vertices[0].u = fU0;		s_vertices[0].v = fV0;
	s_vertices[1].u = fU1;		s_vertices[1].v = fV1;
	s_vertices[2].u = fU2;		s_vertices[2].v = fV2;
	s_vertices[3].u = fU3;		s_vertices[3].v = fV3;
}

void Sprite::setTexture(const Texture& t){
	texture = t;
}

void Sprite::draw(Renderer& rkRenderer){
	rkRenderer.setCurrentTexture(texture);
	rkRenderer.setMatrix(m_pkTransformationMatrix);
	rkRenderer.draw(s_vertices, D3DPT_TRIANGLESTRIP, 4);
}

void Sprite::setAnimation(Animation* animation){
	sprPreviousFrame = sprCurrentFrame;
	sprAnimation = animation;
}

void Sprite::update(Timer& timer){
	if(!sprAnimation)
		return;

	sprAnimation->update(timer);

	sprCurrentFrame = sprAnimation->getCurrentFrame();

	Frame f = sprAnimation->getFrames()[sprCurrentFrame];

	if(sprCurrentFrame != sprPreviousFrame){
		setTexCoords(f.u1, f.v1,
					 f.u2, f.v2,
					 f.u3, f.v3,
					 f.u4, f.v4);

		sprPreviousFrame = sprCurrentFrame;
	}
}