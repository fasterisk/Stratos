#ifndef _RTRS_CAMERA_H_
#define _RTRS_CAMERA_H_

namespace RTRS
{
	class Camera
	{
	public:
		Camera(float fFOV, float fAngle, float fNear, float fFar);
		~Camera();
		
		void		RenderSkyBox();

		glm::mat4	GetViewMatrix();
		glm::mat4	GetProjectionMatrix();
		glm::mat4	GetViewProjectionMatrix();
		glm::vec3	GetPosition() const { return m_v3Position; }

		void		Rotate(float fX, float fY, float fZ);
		void		RotateX(float fX);
		void		RotateY(float fY);
		void		RotateZ(float fZ);
		void		MoveBy(float fX, float fY, float fZ);
		void		MoveTo(float fX, float fY, float fZ);
		void		MoveTo(glm::vec3 v3NewPosition);
		void		MoveRelativeToView(float fForward, float fRight, float fUp);
		void		LookTo(float fX, float fY, float fZ);

	private:
		void		ItlInitialize(float fFOV, float fAngle, float fNear, float fFar);

		glm::vec3	m_v3Position;
		glm::vec3	m_v3LookRight;
		glm::vec3	m_v3LookUp;
		glm::vec3	m_v3LookAt;

		glm::mat4	m_m4ViewMatrix;
		glm::mat4	m_m4ProjectionMatrix;
	};
};

#endif //_RTRS_CAMERA_H_