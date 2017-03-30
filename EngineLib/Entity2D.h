#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "Renderer.h"

class Entity2D{
	public:
		DllExport Entity2D();
		DllExport ~Entity2D(){};
		DllExport void setPos(float fPosX, float fPosY);
		DllExport void setRotation(float fRotation);
		DllExport void setScale(float fScaleX, float fScaleY);

		DllExport float posX() const;
		DllExport float posY() const;
		DllExport float rotation() const;
		DllExport float scaleX() const;
		DllExport float scaleY() const;

		DllExport float previousPosX() const;
		DllExport float previousPosY() const;
		DllExport void returnToPos(float fPosX, float fPosY);

		DllExport enum CollisionResult{
			Collision,
			NoCollision
		};

		DllExport CollisionResult checkCollision(Entity2D& otherObject) const;
		DllExport CollisionResult checkCollision(Entity2D& otherObject, float offsetX, float offsetY) const;
		DllExport bool isWalkable() const;

		DllExport void setZ(float z){
			m_fPosZ = z;
		}

		DllExport float getZ(){ return m_fPosZ; };

	protected:
		float m_fPosX, m_fPosY;
		float m_fPosZ;
		float m_fRotation;
		float m_fScaleX, m_fScaleY;
		float m_fPreviousPosX, m_fPreviousPosY;
		float baseScaleX, baseScaleY;
		void updateTransformation();
		Matrix m_pkTransformationMatrix;
		bool tWalkable = false;
};
#endif
