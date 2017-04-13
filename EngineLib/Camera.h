#ifndef CAMERA_H
#define CAMERA_H

#include"Renderer.h"
#include"BoundingVolumes.h"

#define DllExport __declspec( dllexport )

class Camera{
	public:
		DllExport Camera(Renderer& rkRenderer);
		DllExport ~Camera();

		DllExport void roll(float angle);
		DllExport void pitch(float angle);
		DllExport void yaw(float angle);

		DllExport void walk(float dist);
		DllExport void strafe(float dist);
		DllExport void fly(float dist);

		DllExport void setPos(float fPosX, float fPosY, float fPosZ);
		DllExport void setForward(float fX, float fY, float fZ);
		DllExport const Matrix& viewMatrix() const;

		DllExport const Frustum& getFrustum() const;
		DllExport void updateFrustum();

		DllExport void UpdateCam();

		DllExport D3DXVECTOR3 getPos();

	private:
		Renderer& r;

		Matrix m_view;

		D3DXVECTOR3 m_right;
		D3DXVECTOR3 m_up;
		D3DXVECTOR3 m_forward;
		D3DXVECTOR3 m_position;
		D3DXVECTOR3 m_lookAt;

		float m_pitch;

		float m_maxPitch;
		BOOL  m_invertY;
		BOOL  m_enableYMovement;

		D3DXVECTOR3 m_velocity;
		float m_maxVelocity;

		float maxYAngle = 90.0f;
		float YAngle = 0.0f;

		Frustum camFrustum;
};

#endif