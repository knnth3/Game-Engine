#include <glm\gtx\transform.hpp>
#include "Model3D.h"
#include "MeshLoader.h"



Graphics::Model::Model3D::Model3D()
{
	m_outRotation = glm::mat4();
	m_inRotation = glm::mat4();
	m_scaleMatrix = glm::mat4();
	m_translation = glm::mat4();
	m_localToWorld = glm::mat4();
	m_position = glm::vec3();
	m_offset = glm::vec3();
	m_texture = -1;
	m_mesh = nullptr;
	m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_bDraw = false;
}

Graphics::Model::Model3D::Model3D(const MeshID id) :
	Model3D()
{
	m_meshID = id;
	AddMesh(id);
}

void Graphics::Model::Model3D::Draw()
{
	m_bDraw = true;
}

void Graphics::Model::Model3D::Scale(const float x, const float y, const float z)
{
	Scale(glm::vec3(x, y, z));
}

void Graphics::Model::Model3D::Scale(glm::vec3 scale)
{
	m_scale = scale;
	m_offset.x *= m_scale.x;
	m_offset.y *= m_scale.y;
	m_offset.z *= m_scale.z;
	m_scaleMatrix = glm::scale(m_scale);
}

void Graphics::Model::Model3D::SetPosition(const float x, const float y, const float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void Graphics::Model::Model3D::SetPosition(glm::vec3 pos)
{
	m_position = pos;
}

void Graphics::Model::Model3D::Rotate(float x, float y, float z)
{
	RotateMatrix(m_outRotation, glm::vec3(x, y, z));
}

void Graphics::Model::Model3D::Rotate(glm::vec3 rotation)
{
	RotateMatrix(m_outRotation, rotation);
}

void Graphics::Model::Model3D::RotateAtOrigin(float x, float y, float z)
{
	RotateMatrix(m_inRotation, glm::vec3(x, y, z));
}

void Graphics::Model::Model3D::SetColor(float r, float g, float b)
{
	m_color = glm::vec4(r, g, b, 1.0f);
}

void Graphics::Model::Model3D::SetColor(float r, float g, float b, float a)
{
	m_color = glm::vec4(r, g, b, a);
}

void Graphics::Model::Model3D::SetColor(glm::vec4 color)
{
	m_color = color;
}

void Graphics::Model::Model3D::SetOpacity(float alpha)
{
	m_color.a = alpha;
}

void Graphics::Model::Model3D::SetOffset(float offset)
{
	m_offset = glm::vec3(offset * m_scale.x, 0.0f, 0.0f);
}

void Graphics::Model::Model3D::SetTexture(TextureID tex)
{
	m_texture = tex;
}

void Graphics::Model::Model3D::AddMesh(MeshID id)
{
	MeshLoader::GrabMeshData(id, m_mesh);
	m_meshType = TRIANGLE;
	if (id != -1)
	{
		MeshLoader::GetDefaulMeshInfo(id, *this);
	}
}

glm::vec3 Graphics::Model::Model3D::GetPosition() const
{
	return m_position - m_offset;
}

glm::vec3 Graphics::Model::Model3D::GetScale() const
{
	return m_scale;
}

glm::mat4 Graphics::Model::Model3D::GetModelMatrix()
{
	CreateLocalToWorld();
	return m_localToWorld;
}

glm::vec4 Graphics::Model::Model3D::GetColor()
{
	return m_color;
}

Graphics::TextureID Graphics::Model::Model3D::GetTexture()
{
	return m_texture;
}

Graphics::MeshID Graphics::Model::Model3D::GetMesh()
{
	return m_meshID;
}

float Graphics::Model::Model3D::GetHeight() const
{
	return m_mesh->GetHeight();
}

void Graphics::Model::Model3D::GetMeshData(std::vector<Graphics::Model::Vertex>& vertices, std::vector<uint32_t>& indices) const
{
	m_mesh->GetBuffers(vertices, indices);
}

void Graphics::Model::Model3D::operator=(MeshID id)
{
	m_meshID = id;
	AddMesh(id);
}

void Graphics::Model::Model3D::CreateLocalToWorld()
{
	glm::vec3 pos = m_position - m_offset;
	m_translation = glm::translate(glm::mat4(), glm::vec3(pos.x, pos.y, pos.z));
	m_localToWorld = m_inRotation * m_translation * m_outRotation * m_scaleMatrix;
}

void Graphics::Model::Model3D::RotateMatrix(glm::mat4 & matrix, glm::vec3 rot)
{
	matrix = glm::mat4();
	if (rot.x != 0.0f)
	{
		glm::vec3 rotaxis(1.0f, 0.0f, 0.0f);
		matrix = glm::rotate(matrix, rot.x, rotaxis);
	}
	if (rot.y != 0.0f)
	{
		glm::vec3 rotaxis(0.0f, 1.0f, 0.0f);
		matrix = glm::rotate(matrix, rot.y, rotaxis);
	}
	if (rot.z != 0.0f)
	{
		glm::vec3 rotaxis(0.0f, 0.0f, 1.0f);
		matrix = glm::rotate(matrix, rot.z, rotaxis);
	}
}