#ifndef ENTITY3D_H
#define ENTITY3D_H

#include "Renderer.h"
#include "BoundingVolumes.h"

class Node;

using namespace std;

class Entity3D{
	public:
		DllExport Entity3D();
		DllExport ~Entity3D();

		DllExport void MoveX(float fPosX);
		DllExport void MoveY(float fPosY);
		DllExport void MoveZ(float fPosZ);

		DllExport void setPos(float fPosX, float fPosY, float fPosZ);

		DllExport void RotateX(float fRotationX){ setRotation(m_fRotationX + fRotationX, m_fRotationY, m_fRotationZ); };
		DllExport void RotateY(float fRotationY){ setRotation(m_fRotationX, m_fRotationY + fRotationY, m_fRotationZ); };
		DllExport void RotateZ(float fRotationZ){ setRotation(m_fRotationX, m_fRotationY, m_fRotationZ + fRotationZ); };

		DllExport void setRotation(float fRotationX, float fRotationY, float fRotationZ);

		DllExport void ScaleX(float fScaleX){ setScale(m_fScaleX + fScaleX, m_fScaleY, m_fScaleZ); };
		DllExport void ScaleY(float fScaleY){ setScale(m_fScaleX, m_fScaleY + fScaleY, m_fScaleZ); };
		DllExport void ScaleZ(float fScaleZ){ setScale(m_fScaleX, m_fScaleY, m_fScaleZ + fScaleZ); };

		DllExport void ScaleAll(float fScaleX, float fScaleY, float fScaleZ){ setScale(m_fScaleX + fScaleX, 
																					   m_fScaleY + fScaleY, 
																					   m_fScaleZ + fScaleZ); };

		DllExport void setScale(float fScaleX, float fScaleY, float fScaleZ);

		DllExport float posX() const;
		DllExport float posY() const;
		DllExport float posZ() const;
		DllExport float rotationX() const;
		DllExport float rotationY() const;
		DllExport float rotationZ() const;
		DllExport float scaleX() const;
		DllExport float scaleY() const;
		DllExport float scaleZ() const;

		DllExport float previousPosX() const;
		DllExport float previousPosY() const;
		DllExport float previousPosZ() const;
		DllExport void returnToPos(float fPosX, float fPosY, float fPosZ);

		DllExport virtual void draw(vector<string>& vec, int& vNum, int& pNum) = 0;
		DllExport virtual void draw(Renderer& rkRenderer, CollisionResult eParentResult, 
									const Frustum& rkFrustum, vector<string>& vec, int& vNum, int& pNum) = 0;

		DllExport const AABB& getAABB() const;
		DllExport virtual void updateBV() = 0;

		DllExport void importMatrix(float matrix[4][4]);
		DllExport void updateTransformation();
		DllExport virtual void updateWorldTransformation();

		DllExport const Matrix& worldMatrix() const;

		DllExport void setParent(Node* newParent);

		DllExport void setName(const string& n);
		DllExport string getName();

	protected:
		float m_fPosX, m_fPosY, m_fPosZ;
		float m_fRotationX, m_fRotationY, m_fRotationZ;
		float m_fScaleX, m_fScaleY, m_fScaleZ;
		float m_fPreviousPosX, m_fPreviousPosY, m_fPreviousPosZ;
		float baseScaleX, baseScaleY, baseScaleZ;

		Matrix m_pkTransformationMatrix;
		Matrix m_pkWorldMatrix;

		Matrix localMatrix();

		Node* parent = NULL;

		string name;

		AABB aabb;
};
#endif
