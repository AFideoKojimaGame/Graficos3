#include "Entity3D.h"
#include "Node.h"

#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")

Entity3D::Entity3D(){

	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
	m_fPosZ = 0.0f;
	m_fPreviousPosX = m_fPosX;
	m_fPreviousPosY = m_fPosY;
	m_fRotationX = 0.0f;
	m_fRotationY = 0.0f;
	m_fRotationZ = 0.0f;
	m_fScaleX = 1.0f;
	m_fScaleY = 1.0f;
	m_fScaleZ = 1.0f;
	baseScaleX = m_fScaleX;
	baseScaleY = m_fScaleY;
	baseScaleZ = m_fScaleZ;

	m_pkTransformationMatrix = new D3DXMATRIX();
	m_pkWorldMatrix = new D3DXMATRIX();

	m_pkWorldMatrix = m_pkTransformationMatrix;

	updateTransformation();
	updateWorldTransformation();
}

Entity3D::~Entity3D(){
	delete m_pkTransformationMatrix;
	m_pkTransformationMatrix = NULL;

	delete m_pkWorldMatrix;
	m_pkWorldMatrix = NULL;
}

void Entity3D::MoveX(float fPosX){
	m_fPreviousPosX = m_fPosX;
	m_fPosX += fPosX;

	updateWorldTransformation();
}

void Entity3D::MoveY(float fPosY){
	m_fPreviousPosY = m_fPosY;
	m_fPosY += fPosY;

	updateWorldTransformation();
}

void Entity3D::MoveZ(float fPosZ){
	m_fPreviousPosZ = m_fPosZ;
	m_fPosZ += fPosZ;

	updateWorldTransformation();
}

void Entity3D::setPos(float fPosX, float fPosY, float fPosZ){

	m_fPreviousPosX = m_fPosX;
	m_fPreviousPosY = m_fPosY;
	m_fPreviousPosZ = m_fPosZ;

	m_fPosX = fPosX;
	m_fPosY = fPosY;
	m_fPosZ = fPosZ;

	updateWorldTransformation();
}

void Entity3D::setRotation(float fRotationX, float fRotationY, float fRotationZ){
	m_fRotationX = fRotationX;
	m_fRotationY = fRotationY;
	m_fRotationZ = fRotationZ;

	updateWorldTransformation();
}

void Entity3D::setScale(float fScaleX, float fScaleY, float fScaleZ){
	m_fScaleX = fScaleX;
	m_fScaleY = fScaleY;
	m_fScaleZ = fScaleZ;

	updateWorldTransformation();
}

float Entity3D::posX() const{
	return m_fPosX;
}

float Entity3D::posY() const{
	return m_fPosY;
}

float Entity3D::posZ() const{
	return m_fPosZ;
}

float Entity3D::rotationX() const{
	return m_fRotationX;
}

float Entity3D::rotationY() const{
	return m_fRotationY;
}

float Entity3D::rotationZ() const{
	return m_fRotationZ;
}

float Entity3D::scaleX() const{
	return m_fScaleX;
}

float Entity3D::scaleY() const{
	return m_fScaleY;
}

float Entity3D::scaleZ() const{
	return m_fScaleZ;
}

void Entity3D::updateTransformation(){

	D3DXMATRIX traslatrionMat;
	D3DXMatrixTranslation(&traslatrionMat, m_fPosX, m_fPosY, m_fPosZ);

	D3DXMATRIX rotationMatX, rotationMatY, rotationMatZ;
	D3DXMatrixRotationX(&rotationMatX, m_fRotationX);
	D3DXMatrixRotationY(&rotationMatY, m_fRotationY);
	D3DXMatrixRotationZ(&rotationMatZ, m_fRotationZ);

	D3DXMATRIX scaleMat;
	D3DXMatrixScaling(&scaleMat, m_fScaleX, m_fScaleY, m_fScaleZ);

	D3DXMatrixIdentity(m_pkTransformationMatrix);
	D3DXMatrixMultiply(m_pkTransformationMatrix, &traslatrionMat, m_pkTransformationMatrix);
	D3DXMatrixMultiply(m_pkTransformationMatrix, &rotationMatX, m_pkTransformationMatrix);
	D3DXMatrixMultiply(m_pkTransformationMatrix, &rotationMatY, m_pkTransformationMatrix);
	D3DXMatrixMultiply(m_pkTransformationMatrix, &rotationMatZ, m_pkTransformationMatrix);
	D3DXMatrixMultiply(m_pkTransformationMatrix, &scaleMat, m_pkTransformationMatrix);
}

void Entity3D::updateWorldTransformation(){

	updateTransformation();

	if (parent)
		D3DXMatrixMultiply(m_pkWorldMatrix, m_pkTransformationMatrix, parent->worldMatrix());
	else
		m_pkWorldMatrix = m_pkTransformationMatrix;
}

Matrix Entity3D::localMatrix(){
	return m_pkTransformationMatrix;
}

const Matrix& Entity3D::worldMatrix() const{
	return m_pkWorldMatrix;
}

inline float Entity3D::previousPosX() const{
	return m_fPreviousPosX;
}

inline float Entity3D::previousPosY() const{
	return m_fPreviousPosY;
}

inline float Entity3D::previousPosZ() const{
	return m_fPreviousPosZ;
}

void Entity3D::returnToPos(float fPosX, float fPosY, float fPosZ){
	m_fPosX = fPosX;
	m_fPosY = fPosY;
	m_fPosZ = fPosZ;

	updateWorldTransformation();
}

void Entity3D::setParent(Node* newParent){
	parent = newParent;
	updateWorldTransformation();
}

void Entity3D::setName(const string& n){
	name = n;
}

string Entity3D::getName(){
	return name;
}

const AABB& Entity3D::getAABB() const{
	return aabb;
}
