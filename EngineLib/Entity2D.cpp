#include "Entity2D.h"

#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")

Entity2D::Entity2D(){

	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
	m_fPosZ = 1.0f;
	m_fPreviousPosX = m_fPosX;
	m_fPreviousPosY = m_fPosY;
	m_fRotation = 0.0f;
	m_fScaleX = 150.0f;
	m_fScaleY = 150.0f;
	baseScaleX = m_fScaleX;
	baseScaleY = m_fScaleY;

	m_pkTransformationMatrix = new D3DXMATRIX();
}

void Entity2D::setPos(float fPosX, float fPosY){

	m_fPreviousPosX = m_fPosX;
	m_fPreviousPosY = m_fPosY;

	m_fPosX = fPosX;
	m_fPosY = fPosY;

	updateTransformation();
}

void Entity2D::setRotation(float fRotation){
	m_fRotation = fRotation;

	updateTransformation();
}

void Entity2D::setScale(float fScaleX, float fScaleY){
	m_fScaleX = fScaleX;
	m_fScaleY = fScaleY;

	updateTransformation();
}

float Entity2D::posX() const{
	return m_fPosX;
}
float Entity2D::posY() const{
	return m_fPosY;
}

float Entity2D::rotation() const{
	return m_fRotation;
}

float Entity2D::scaleX() const{
	return m_fScaleX;
}
float Entity2D::scaleY() const{
	return m_fScaleY;
}

void Entity2D::updateTransformation(){

	D3DXMATRIX traslatrionMat;
	D3DXMatrixTranslation(&traslatrionMat, m_fPosX, m_fPosY, m_fPosZ);

	D3DXMATRIX rotationMat;
	D3DXMatrixRotationZ(&rotationMat, m_fRotation);

	D3DXMATRIX scaleMat;
	D3DXMatrixScaling(&scaleMat, m_fScaleX, m_fScaleY, 1);

	D3DXMatrixIdentity(m_pkTransformationMatrix);
	D3DXMatrixMultiply(m_pkTransformationMatrix, &traslatrionMat, m_pkTransformationMatrix);
	D3DXMatrixMultiply(m_pkTransformationMatrix, &rotationMat, m_pkTransformationMatrix);
	D3DXMatrixMultiply(m_pkTransformationMatrix, &scaleMat, m_pkTransformationMatrix);
}

bool Entity2D::isWalkable() const{
	return tWalkable;
}

Entity2D::CollisionResult Entity2D::checkCollision(Entity2D& otherObject) const{
	return checkCollision(otherObject, 0, 0);
}

Entity2D::CollisionResult Entity2D::checkCollision(Entity2D& otherObject, float offsetX, float offsetY) const{
	if (!otherObject.isWalkable()){
		bool CollisionX = false;
		bool CollisionY = false;

		float rightXCheck = posX() + std::abs(scaleX() / 2);
		float leftXCheck = posX() - std::abs(scaleX() / 2);

		float otherRightXCheck = otherObject.posX() + std::abs(otherObject.scaleX() / 2) - offsetX;
		float otherLeftXCheck = otherObject.posX() - std::abs(otherObject.scaleX() / 2) + offsetX;

		float upYCheck = posY() + scaleY() / 2;
		float downYCheck = posY() - scaleY() / 2;

		float otherUpYCheck = otherObject.posY() + std::abs(otherObject.scaleY() / 2) - offsetY;
		float otherDownYCheck = otherObject.posY() - std::abs(otherObject.scaleY() / 2) + offsetY;

		if (rightXCheck >= otherLeftXCheck && leftXCheck <= otherRightXCheck)
			CollisionX = true;
		if (upYCheck >= otherDownYCheck && downYCheck <= otherUpYCheck)
			CollisionY = true;

		if (CollisionX && CollisionY)
			return Collision;

		return NoCollision;
	}else{
		return NoCollision;
	}
}

inline float Entity2D::previousPosX() const
{
	return m_fPreviousPosX;
}

inline float Entity2D::previousPosY() const
{
	return m_fPreviousPosY;
}

void Entity2D::returnToPos(float fPosX, float fPosY)
{
	m_fPosX = fPosX;
	m_fPosY = fPosY;

	updateTransformation();
}