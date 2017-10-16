#include <glm\gtx\transform.hpp>
#include "Model2D.h"



Lime::Model::Model2D::Model2D()
{
	m_outRotation = glm::mat4();
	m_scaleMatrix = glm::mat4();
	m_translation = glm::mat4();
	m_localToWorld = glm::mat4();
	m_texture = -1;
	m_scale = glm::vec3(1.0f);
	m_mesh = std::make_shared<MeshData2D>();
	m_position = glm::vec2(0.0f);
	m_color = glm::vec4(1.0f);
	m_length = 0.0f;
	m_width = 0.0f;
	m_bDraw = false;
}

Lime::Model::Model2D::Model2D(const glm::vec2 pos, const float length, const float width, const glm::vec4 color)
{
	m_outRotation = glm::mat4();
	m_scaleMatrix = glm::mat4();
	m_translation = glm::mat4();
	m_localToWorld = glm::mat4();
	m_texture = -1;
	m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_mesh = std::make_shared<MeshData2D>();
	m_position = { pos.x, -pos.y };
	m_color = color;
	m_length = length;
	m_width = width;
	m_bDraw = false;
}

void Lime::Model::Model2D::Draw()
{
	m_bDraw = true;
}

void Lime::Model::Model2D::Scale(const float x, const float y, const float z)
{
	m_scale = glm::vec3(x, y, z);
	m_scaleMatrix = glm::scale(m_scale);
}

void Lime::Model::Model2D::Scale(glm::vec3 scale)
{
	m_scale = scale;
}

void Lime::Model::Model2D::SetPosition(const float x, const float y)
{
	m_position = {x,-y};
}

void Lime::Model::Model2D::SetPosition(glm::vec2 pos)
{
	m_position = { pos.x, -pos.y };
}

void Lime::Model::Model2D::Rotate(float rad)
{
	if(rad >= 2.0f * PI)
	{
		float full = (2.0f * PI);
		float revs = truncf( rad / full);
		float remainder = rad - (revs * full);
		RotateMatrix(m_outRotation, glm::vec3(0.0f, 0.0f, remainder));
	}

	RotateMatrix(m_outRotation, glm::vec3(0.0f, 0.0f, rad));
}

void Lime::Model::Model2D::SetColor(float r, float g, float b)
{
	m_color = {r,g,b, 1.0f};
}

void Lime::Model::Model2D::SetColor(float r, float g, float b, float a)
{
	m_color = {r,g,b,a};
}

void Lime::Model::Model2D::SetColor(glm::vec4 color)
{
	m_color = color;
}

void Lime::Model::Model2D::SetOpacity(float alpha)
{
	//m_mesh->m_color.a = alpha;
}

void Lime::Model::Model2D::SetTexture(TextureID tex)
{
	m_texture = tex;
}

void Lime::Model::Model2D::SetLength(const float length)
{
	m_length = length;
}

void Lime::Model::Model2D::SetWidth(const float width)
{
	m_width = width;
}

glm::vec2 Lime::Model::Model2D::GetPosition() const
{
	return { m_position.x, -m_position.y };
}

glm::mat4 Lime::Model::Model2D::GetModelMatrix()
{
	CreateLocalToWorld();
	return m_localToWorld;
}

glm::vec4 Lime::Model::Model2D::GetColor()
{
	return m_color;
}

Lime::TextureID Lime::Model::Model2D::GetTexture()
{
	return m_texture;
}

float Lime::Model::Model2D::GetLength()
{
	return m_length;
}

float Lime::Model::Model2D::GetWidth()
{
	return m_width;
}

void Lime::Model::Model2D::CreateLocalToWorld()
{
	glm::vec3 pos = glm::vec3(m_position, 1.0f);
	m_translation = glm::translate(glm::mat4(), glm::vec3(pos.x, pos.y, pos.z));
	m_localToWorld = m_translation * m_outRotation * m_scaleMatrix;
}

void Lime::Model::Model2D::RotateMatrix(glm::mat4 & matrix, glm::vec3 rotations)
{
	matrix = glm::mat4();
	if (rotations.x != 0.0f)
	{
		glm::vec3 rotaxis(1.0f, 0.0f, 0.0f);
		matrix = glm::rotate(matrix, rotations.x, rotaxis);
	}
	if (rotations.y != 0.0f)
	{
		glm::vec3 rotaxis(0.0f, 1.0f, 0.0f);
		matrix = glm::rotate(matrix, rotations.y, rotaxis);
	}
	if (rotations.z != 0.0f)
	{
		glm::vec3 rotaxis(0.0f, 0.0f, 1.0f);
		matrix = glm::rotate(matrix, rotations.z, rotaxis);
	}
}