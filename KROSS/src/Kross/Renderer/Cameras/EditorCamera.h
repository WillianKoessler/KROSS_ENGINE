#pragma once

#include "Kross/Core/Core.h"
#include "Kross/Core/Timestep.h"
#include "Kross/Events/Event.h"
#include "Kross/Events/MouseEvent.h"
#include "Kross/Events/KeyEvent.h"

#include <glm/glm.hpp>

namespace Kross::Camera {

	class Editor
	{
	public:
		Editor() = default;
		Editor(float fov, float aspectRatio, float nearClip, float farClip);

		void OnUpdate(double ts);
		void OnEvent(Event &e);

		inline float GetDistance() const { return m_Distance; }
		inline void SetDistance(float distance) { m_Distance = distance; }

		inline void SetViewportSize(float width, float height) { m_ViewportWidth = width; m_ViewportHeight = height; UpdateProj(); }
		inline void SetViewportSize(const glm::vec2& size) { m_ViewportWidth = size.x; m_ViewportHeight = size.y; UpdateProj(); }

		const glm::mat4 &GetProjMat() const { return m_ProjMat; }
		glm::mat4 &GetViewMat() { return m_ViewMat; }
		const glm::mat4 &GetViewMat() const { return m_ViewMat; }
		glm::mat4 GetVPM() const { return m_ProjMat * m_ViewMat; }

		glm::vec3 GetUpDir() const;
		glm::vec3 GetRightDir() const;
		glm::vec3 GetForwardDir() const;
		const glm::vec3 &GetPosition() const { return m_Position; }
		glm::quat GetOrientation() const;

		float GetPitch() const { return m_Pitch; }
		float GetYaw() const { return m_Yaw; }
	private:
		void UpdateProj();
		void UpdateView();

		bool OnMouseMoved(MouseMovedEvent &e);
		bool OnMouseScroll(MouseScrolledEvent &e);

		void MousePan(const glm::vec2 &delta);
		void MouseRotate(const glm::vec2 &delta);
		void MouseZoom(float delta);

		glm::vec3 CalculatePosition() const;

		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;
	private:
		float m_FOV = 45.0f, m_AspectRatio = 16.0f / 9.0f, m_NearClip = 0.1f, m_FarClip = 1000.0f;

		glm::mat4 m_ProjMat = glm::mat4(1.0f);
		glm::mat4 m_ViewMat = glm::mat4(1.0f);
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };

		glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };
		glm::vec2 m_Delta = glm::vec2(0.0f);
		glm::vec2 m_MousePosition = glm::vec2(0.0f);

		float m_Distance = 10.0f;
		float m_Pitch = 0.0f, m_Yaw = 0.0f;

		float m_ViewportWidth = 600, m_ViewportHeight = 400;

		bool m_bMouseMiddle = false;
		bool m_bLeftShift = false;
		bool m_bLeftCtrl = false;
	};

}
