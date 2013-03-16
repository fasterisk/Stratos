#include "RTRS_IModel.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "glm/gtc/matrix_transform.hpp"



/**************************************************************************************************
 **************************************************************************************************/
RTRS::IModel::IModel()
{
	m_pLogger	= new RTRS::Logger("RTRS_IModel.cpp");

	//m_pEnvironmentMapGenerator = NULL;
	m_pbEnvironmentMappedFlags = NULL;
	m_v3EnvironmentMapPosition = glm::vec3(0, 0, 0);

	m_v3Color		= glm::vec3(1.0f, 1.0f, 1.0f);

	m_m4Translation	= glm::mat4(1.0);
	m_m4Scale		= glm::mat4(1.0);
	m_m4Rotation	= glm::mat4(1.0);
	m_v3Position	= glm::vec3(0,0,0);
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::IModel::~IModel()
{
	if(m_pLogger != NULL)
	{
		delete m_pLogger;
		m_pLogger = NULL;
	}

	if(m_pbEnvironmentMappedFlags != NULL)
	{
		delete[] m_pbEnvironmentMappedFlags;
		m_pbEnvironmentMappedFlags = NULL;
	}
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::IModel::LoadMesh(const char* pcMeshFileName)
{
	GLuint	glnBuffer;

	Mesh	stMesh;

	Assimp::Importer Importer;

	std::string sFile(pcMeshFileName);
	const aiScene* pScene = Importer.ReadFile(sFile, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);
	assert(pScene != NULL);

	for (unsigned int n = 0; n < pScene->mNumMeshes; ++n)
	{
		const struct aiMesh* pMesh = pScene->mMeshes[n];

		unsigned int *faceArray;
		faceArray = (unsigned int *)malloc(sizeof(unsigned int) * pMesh->mNumFaces * 3);
		unsigned int faceIndex = 0;

		for (unsigned int t = 0; t < pMesh->mNumFaces; ++t) {
			const struct aiFace* face = &pMesh->mFaces[t];

			memcpy(&faceArray[faceIndex], face->mIndices,3 * sizeof(float));
			faceIndex += 3;
		}
		stMesh.nNumFaces = pScene->mMeshes[n]->mNumFaces;

		glGenVertexArrays(1, &stMesh.nVAOID);
		glBindVertexArray(stMesh.nVAOID);

		// buffer for faces
		glGenBuffers(1, &glnBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glnBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * pMesh->mNumFaces * 3, faceArray, GL_STATIC_DRAW);

		// buffer for vertex positions
		if (pMesh->HasPositions()) {
			glGenBuffers(1, &glnBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, glnBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*pMesh->mNumVertices, pMesh->mVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
		}

		// buffer for vertex texture coordinates
		if (pMesh->HasTextureCoords(0)) {
			float *texCoords = (float *)malloc(sizeof(float)*2*pMesh->mNumVertices);
			for (unsigned int k = 0; k < pMesh->mNumVertices; ++k) {

				texCoords[k*2]   = pMesh->mTextureCoords[0][k].x;
				texCoords[k*2+1] = pMesh->mTextureCoords[0][k].y; 

			}
			glGenBuffers(1, &glnBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, glnBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*2*pMesh->mNumVertices, texCoords, GL_STATIC_DRAW);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, 0);
		}

		// buffer for vertex normals
		if (pMesh->HasNormals()) {
			glGenBuffers(1, &glnBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, glnBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*pMesh->mNumVertices, pMesh->mNormals, GL_STATIC_DRAW);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, 0, 0, 0);
		}

		//buffer for the tangents and bitangents
		if (pMesh->HasTangentsAndBitangents())
		{
			glGenBuffers(1, &glnBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, glnBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*pMesh->mNumVertices, pMesh->mTangents, GL_STATIC_DRAW);
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, 0, 0, 0);

			glGenBuffers(1, &glnBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, glnBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*pMesh->mNumVertices, pMesh->mBitangents, GL_STATIC_DRAW);
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 3, GL_FLOAT, 0, 0, 0);
		}

		// unbind buffers
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER,0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

		m_vMeshes.push_back(stMesh);
	}

	if(m_pbEnvironmentMappedFlags != NULL)
	{
		delete[] m_pbEnvironmentMappedFlags;
		m_pbEnvironmentMappedFlags = NULL;
	}

	m_pbEnvironmentMappedFlags = new bool[m_vMeshes.size()];

	for(unsigned int i = 0; i < m_vMeshes.size(); i++)
		m_pbEnvironmentMappedFlags[i] = false;

	ItlInitialize();
}

/**************************************************************************************************
**************************************************************************************************/
 void	RTRS::IModel::Rotate(float fX, float fY, float fZ)
 {
	 RotateX(fX);
	 RotateY(fY);
	 RotateZ(fZ);
 }

 /**************************************************************************************************
 **************************************************************************************************/
void	RTRS::IModel::RotateX(float fX)
{
	glm::vec3 v3OldPosition = m_v3Position;
	MoveTo(0, 0, 0);

	m_m4Rotation = glm::rotate(m_m4Rotation, fX, glm::vec3(1, 0, 0));

	MoveTo(v3OldPosition);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::IModel::RotateY(float fY)
{	
	m_m4Rotation = glm::rotate(m_m4Rotation, fY, glm::vec3(0, 1, 0));
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::IModel::RotateZ(float fZ)
{
	m_m4Rotation = glm::rotate(m_m4Rotation, fZ, glm::vec3(0, 0, 1));
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::IModel::MoveBy(float fX, float fY, float fZ)
{
	m_v3Position += glm::vec3(fX, fY, fZ);
	m_m4Translation = glm::translate(m_m4Translation, glm::vec3(fX, fY, fZ));
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::IModel::MoveTo(float fX, float fY, float fZ)
{
	MoveTo(glm::vec3(fX, fY, fZ));
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::IModel::MoveTo(glm::vec3 v3NewPosition)
{
	glm::vec3 v3Diff = v3NewPosition - m_v3Position;

	MoveBy(v3Diff.x, v3Diff.y, v3Diff.z);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::IModel::Scale(float fX, float fY, float fZ)
{
	m_m4Scale = glm::scale(m_m4Scale, glm::vec3(fX, fY, fZ));
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::IModel::Scale(float fScale)
{
	Scale(fScale, fScale, fScale);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::IModel::Render()
{
	for(unsigned int i = 0; i < m_vMeshes.size(); i++)
	{
		glBindVertexArray(m_vMeshes[i].nVAOID);
				
		glDrawElements(GL_TRIANGLES, m_vMeshes[i].nNumFaces*3, GL_UNSIGNED_INT, 0);
		
		glBindVertexArray(0);
	}
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::IModel::Render(unsigned int nMeshID)
{
	assert(nMeshID < m_vMeshes.size());

	glBindVertexArray(m_vMeshes[nMeshID].nVAOID);
	
	glDrawElements(GL_TRIANGLES, m_vMeshes[nMeshID].nNumFaces*3, GL_UNSIGNED_INT, 0);
		
	glBindVertexArray(0);
}

/**************************************************************************************************
 **************************************************************************************************/
glm::mat4	RTRS::IModel::GetModelMatrix() const
{
	return m_m4Translation * m_m4Rotation * m_m4Scale;
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::IModel::SetColor(glm::vec3 v3Color)
{
	m_v3Color = v3Color;
}

/**************************************************************************************************
 **************************************************************************************************/
bool	RTRS::IModel::SetEnvironmentMappedFlag(unsigned int nMeshID, bool bIsEnvironmentMapped)
{
	bool bOk = false;
	if(nMeshID < m_vMeshes.size())
	{
		assert(m_pbEnvironmentMappedFlags != NULL);
		m_pbEnvironmentMappedFlags[nMeshID] = bIsEnvironmentMapped;
		bOk = true;
	}

	return bOk;
}

/**************************************************************************************************
 **************************************************************************************************/
bool	RTRS::IModel::SetEnvironmentMappedFlag(bool bAllMeshesEnvironmentMapped)
{
	assert(m_pbEnvironmentMappedFlags != NULL);
	
	for(unsigned int n = 0; n < m_vMeshes.size(); n++)
		m_pbEnvironmentMappedFlags[n] = bAllMeshesEnvironmentMapped;

	return true;
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::IModel::SetEnvironmentMapPosition(float fX, float fY, float fZ)
{
	m_v3EnvironmentMapPosition = glm::vec3(fX, fY, fZ);
}

/**************************************************************************************************
 **************************************************************************************************/
bool	RTRS::IModel::IsEnvironmentMapped(unsigned int nMeshID)
{
	assert(nMeshID < m_vMeshes.size());

	return m_pbEnvironmentMappedFlags[nMeshID];
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::IModel::ItlInitialize()
{
}