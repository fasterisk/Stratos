#ifndef _RTRS_IMODEL_H_
#define _RTRS_IMODEL_H_

#include "RTRS_Common_includes.h"
#include "RTRS_EnvironmentMapGenerator.h"

#include <vector>

namespace RTRS
{
	class IModel
	{
	public:
		struct Mesh
		{
			unsigned int nNumFaces;
			unsigned int nVAOID;
		};

		IModel();
		virtual ~IModel();

		virtual	void	LoadMesh(const char* pcMeshFileName);

		virtual void	Render();
		virtual void	Render(unsigned int nMeshID);

		virtual void	Rotate(float fX, float fY, float fZ);
		virtual void	RotateX(float fX);
		virtual void	RotateY(float fY);
		virtual void	RotateZ(float fZ);
		virtual void	MoveBy(float fX, float fY, float fZ);
		virtual void	MoveTo(float fX, float fY, float fZ);
		virtual void	MoveTo(glm::vec3 v3NewPosition);
		virtual void	Scale(float fX, float fY, float fZ);
		virtual void	Scale(float fScale);

		virtual void		SetColor(glm::vec3 v3Color);
		virtual glm::vec3	GetColor() const { return m_v3Color; }

		virtual bool		SetEnvironmentMappedFlag(unsigned int nMeshID, bool bIsEnvironmentMapped);
		virtual bool		SetEnvironmentMappedFlag(bool bAllMeshesEnvironmentMapped);
		virtual void		SetEnvironmentMapPosition(float fX, float fY, float fZ);
		virtual glm::vec3	GetEnvironmentMapPosition() const { return m_v3EnvironmentMapPosition; }

		bool			IsEnvironmentMapped(unsigned int nMeshID);

		virtual glm::vec3		GetPosition() const { return m_v3Position; }
		virtual glm::mat4		GetModelMatrix() const;
		virtual unsigned int	GetNumMeshes() const { return m_vMeshes.size(); }

	protected:
		virtual void		ItlInitialize();

		std::vector<Mesh>	m_vMeshes;

		glm::mat4			m_m4Rotation;
		glm::mat4			m_m4Translation;
		glm::mat4			m_m4Scale;

		glm::vec3			m_v3Position;

		bool*				m_pbEnvironmentMappedFlags;
		glm::vec3			m_v3EnvironmentMapPosition;

		glm::vec3			m_v3Color;

		Logger				*m_pLogger;

	};
};

#endif //_RTRS_IMODEL_H_