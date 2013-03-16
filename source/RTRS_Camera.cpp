#include "RTRS_Common_includes.h"

#include "RTRS_Camera.h"
#include "RTRS_TextureManager.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"


/**************************************************************************************************
 **************************************************************************************************/
RTRS::Camera::Camera(float fFOV, float fAngle, float fNear, float fFar)
{
	ItlInitialize(fFOV, fAngle, fNear, fFar);
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::Camera::~Camera()
{
}

/**************************************************************************************************
 **************************************************************************************************/
glm::mat4	RTRS::Camera::GetViewMatrix()
{
	return m_m4ViewMatrix;
}

/**************************************************************************************************
 **************************************************************************************************/
glm::mat4	RTRS::Camera::GetProjectionMatrix()
{
	return m_m4ProjectionMatrix;
}

/**************************************************************************************************
 **************************************************************************************************/
glm::mat4	RTRS::Camera::GetViewProjectionMatrix()
{
	return  m_m4ProjectionMatrix * m_m4ViewMatrix;
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::Camera::Rotate(float fX, float fY, float fZ)
{
	RotateZ(fZ);
	RotateY(fY);
	RotateX(fX);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::Camera::RotateX(float fX)
{
	glm::vec3 v3LookAt = glm::normalize(glm::rotate(m_v3LookAt, fX, m_v3LookRight));
	float fDot = glm::dot(m_v3LookAt, v3LookAt);
	if(fDot > 0 && v3LookAt.y < 0.95 && v3LookAt.y > -0.95)
	{
		m_v3LookAt = glm::normalize(glm::rotate(m_v3LookAt, fX, m_v3LookRight));
		m_v3LookUp = glm::normalize(glm::rotate(m_v3LookUp, fX, m_v3LookUp));

		m_m4ViewMatrix = glm::lookAt(m_v3Position, m_v3LookAt + m_v3Position, m_v3LookUp);
	}
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::Camera::RotateY(float fY)
{
	m_v3LookRight = glm::normalize(glm::rotate(m_v3LookRight, fY, m_v3LookUp));
	m_v3LookAt = glm::normalize(glm::rotate(m_v3LookAt, fY, m_v3LookUp));

	m_m4ViewMatrix = glm::lookAt(m_v3Position, m_v3LookAt + m_v3Position, m_v3LookUp);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::Camera::RotateZ(float fZ)
{
	m_v3LookUp = glm::normalize(glm::rotate(m_v3LookUp, fZ, m_v3LookAt));
	m_v3LookRight = glm::normalize(glm::rotate(m_v3LookRight, fZ, m_v3LookAt));

	m_m4ViewMatrix = glm::lookAt(m_v3Position, m_v3LookAt + m_v3Position, m_v3LookUp);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::Camera::MoveBy(float fX, float fY, float fZ)
{
	m_v3Position += glm::vec3(fX, fY, fZ);
	m_m4ViewMatrix = glm::lookAt(m_v3Position, m_v3LookAt + m_v3Position, m_v3LookUp);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::Camera::MoveTo(float fX, float fY, float fZ)
{
	m_v3Position = glm::vec3(fX, fY, fZ);

	m_m4ViewMatrix = glm::lookAt(m_v3Position, m_v3LookAt + m_v3Position, m_v3LookUp);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::Camera::MoveTo(glm::vec3 v3NewPosition)
{
	MoveTo(v3NewPosition.x, v3NewPosition.y, v3NewPosition.z);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::Camera::MoveRelativeToView(float fForward, float fRight, float fUp)
{
	glm::vec3 v3Diff = fForward*m_v3LookAt + fRight*m_v3LookRight + fUp*m_v3LookUp;
	m_v3Position += v3Diff;

	m_m4ViewMatrix = glm::lookAt(m_v3Position, m_v3LookAt + m_v3Position, m_v3LookUp);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::Camera::LookTo(float fX, float fY, float fZ)
{
	m_v3LookAt = glm::normalize(glm::vec3(fX, fY, fZ) - m_v3Position);
	m_m4ViewMatrix = glm::lookAt(m_v3Position, m_v3LookAt + m_v3Position, m_v3LookUp);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::Camera::ItlInitialize(float fFOV, float fAngle, float fNear, float fFar)
{
	m_v3Position			= glm::vec3(0, 0, 0);
	m_v3LookAt				= glm::vec3(0, 0, -1);
	m_v3LookRight			= glm::vec3(1, 0, 0);
	m_v3LookUp				= glm::vec3(0, 1, 0);
	m_m4ViewMatrix			= glm::lookAt(m_v3Position, m_v3LookAt + m_v3Position, m_v3LookUp);
	m_m4ProjectionMatrix	= glm::perspective(fFOV, fAngle, fNear, fFar);
}