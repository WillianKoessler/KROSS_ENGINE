#include "Kross_pch.h"
#include "VertexArrays.h"
#include "GLErrors.h"

namespace Kross::OpenGL {

	unsigned int convertion_to_GLTYPE(const Kross::Buffer::ShaderDataType type)
	{
		if (type == Kross::Buffer::ShaderDataType::Float)	return GL_FLOAT;
		else if (type == Kross::Buffer::ShaderDataType::Float2)	return GL_FLOAT;
		else if (type == Kross::Buffer::ShaderDataType::Float3)	return GL_FLOAT;
		else if (type == Kross::Buffer::ShaderDataType::Float4)	return GL_FLOAT;
		else if (type == Kross::Buffer::ShaderDataType::Mat3)	return GL_FLOAT;
		else if (type == Kross::Buffer::ShaderDataType::Mat4)	return GL_FLOAT;
		else if (type == Kross::Buffer::ShaderDataType::Int)	return GL_INT;
		else if (type == Kross::Buffer::ShaderDataType::Int2)	return GL_INT;
		else if (type == Kross::Buffer::ShaderDataType::Int3)	return GL_INT;
		else if (type == Kross::Buffer::ShaderDataType::Int4)	return GL_INT;
		else if (type == Kross::Buffer::ShaderDataType::uInt)	return GL_UNSIGNED_INT;
		else if (type == Kross::Buffer::ShaderDataType::uInt2)	return GL_UNSIGNED_INT;
		else if (type == Kross::Buffer::ShaderDataType::uInt3)	return GL_UNSIGNED_INT;
		else if (type == Kross::Buffer::ShaderDataType::uInt4)	return GL_UNSIGNED_INT;
		else if (type == Kross::Buffer::ShaderDataType::Bool)	return GL_BOOL;
		return NULL;
	}

	VertexArray::VertexArray()
	{
		KROSS_PROFILE_FUNC();
		glCall(glGenVertexArrays(1, &m_RendererID));
		Bind();
		KROSS_CORE_INFO("[Kross::OpenGL::VertexArray] Vertex Array Created");
	}

	VertexArray::~VertexArray()
	{
		KROSS_PROFILE_FUNC();
		glCall(glDeleteVertexArrays(1, &m_RendererID));
		KROSS_CORE_INFO("[Kross::OpenGL::VertexArray] Vertex Array Deleted");
	}

	void VertexArray::Bind() const
	{
		KROSS_PROFILE_FUNC();
		glCall(glBindVertexArray(m_RendererID));
	}

	void VertexArray::unBind() const
	{
		KROSS_PROFILE_FUNC();
		glCall(glBindVertexArray(0));
	}

	void VertexArray::AddVoxel(const Ref<Kross::Buffer::Vertex>& voxel)
	{
		KROSS_PROFILE_FUNC();
		this->Bind();
		voxel->Bind();

		if (voxel->GetLayout().GetElements().size() == 0)
		{
			KROSS_CORE_WARN("[{0}] Voxel Buffer has no layout. Aborting.", __FUNCTION__);
			return;
		}

		uint32_t index = 0;
		const Buffer::Layout& layout = voxel->GetLayout();

		glCall(glEnableVertexAttribArray(0));
		glCall(glVertexAttribIPointer(0, 2, GL_UNSIGNED_INT, 8, nullptr));

		m_vecVertex.push_back(voxel);
		KROSS_CORE_TRACE("[{0}] Voxel Buffer Added", __FUNCTION__);
		//if ((layout.begin()->Type == Buffer::ShaderDataType::Int) ||
		//	(layout.begin()->Type == Buffer::ShaderDataType::Int2) ||
		//	(layout.begin()->Type == Buffer::ShaderDataType::Int3) ||
		//	(layout.begin()->Type == Buffer::ShaderDataType::uInt) ||
		//	(layout.begin()->Type == Buffer::ShaderDataType::uInt2) ||
		//	(layout.begin()->Type == Buffer::ShaderDataType::uInt3))
		//{
		//	for (const Buffer::Element& element : layout)
		//	{
		//		glCall(glEnableVertexAttribArray(index));
		//		glCall(glVertexAttribIPointer(
		//			index,
		//			element.GetComponentCount(),
		//			convertion_to_GLTYPE(element.Type),
		//			layout.GetStride(),
		//			(const void*)element.OffSet
		//		));
		//		index++;
		//	}
		//}
	}

	void VertexArray::AddVertex(const Ref<Kross::Buffer::Vertex>& vertex)
	{
		KROSS_PROFILE_FUNC();
		this->Bind();
		vertex->Bind();

		if (vertex->GetLayout().GetElements().size() == 0)
			KROSS_CORE_WARN("[{0}] Vertex Buffer has no layout", __FUNCTION__);

		uint32_t index = 0;
		Buffer::Layout layout = vertex->GetLayout();
		if ((layout.begin()->Type == Buffer::ShaderDataType::Int) ||
			(layout.begin()->Type == Buffer::ShaderDataType::Int2) ||
			(layout.begin()->Type == Buffer::ShaderDataType::Int3) ||
			(layout.begin()->Type == Buffer::ShaderDataType::uInt) ||
			(layout.begin()->Type == Buffer::ShaderDataType::uInt2) ||
			(layout.begin()->Type == Buffer::ShaderDataType::uInt3))
		{
			for (const Buffer::Element& element : layout)
			{
				glCall(glEnableVertexAttribArray(index));
				glCall(glVertexAttribIPointer(
					index,
					element.GetComponentCount(),
					convertion_to_GLTYPE(element.Type),
					layout.GetStride(),
					(const void*)element.OffSet
				));
				index++;
			}
		} else {
			for (const Buffer::Element& element : layout)
			{
				glCall(glEnableVertexAttribArray(index));
				glCall(glVertexAttribPointer(
					index,
					element.GetComponentCount(),
					convertion_to_GLTYPE(element.Type),
					element.Normalized,
					layout.GetStride(),
					(const void*)element.OffSet
				));
				index++;
			}
		}

		m_vecVertex.push_back(vertex);
		KROSS_CORE_TRACE("[{0}] Vertex Buffer Added", __FUNCTION__);
	}

	void VertexArray::SetIndex(const Ref<Kross::Buffer::Index>& index)
	{
		KROSS_PROFILE_FUNC();
		this->Bind();
		index->Bind();
		m_Index = index;
		KROSS_CORE_TRACE("[{0}] Index Buffer Setted", __FUNCTION__);
	}


}