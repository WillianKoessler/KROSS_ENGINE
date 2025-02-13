#include "Kross_pch.h"
#include "OrthographicCtrl.h"

#include "Kross/Core/Input.h"
#include "Kross/Events/KeyCodes.h"

namespace Kross::Camera2D {

	OrthographicCtrl::OrthographicCtrl(const char* name, float AR, bool rot)
		: m_fAR(AR), m_bRotation(rot)
	{
		if (camera) KROSS_WARN("WARNING: Overriding previous camera");
		camera = makeRef<Camera::Orthographic>(-AR * m_fZoom, AR * m_fZoom, -m_fZoom, m_fZoom);
		std::string strname(name);
		SetName((strname + "_Controller").c_str());
		KROSS_INFO("'{0}' Constructed", GetName());
	}

	OrthographicCtrl::OrthographicCtrl(const char* name, Ref<Camera::Camera> cam, float AR, bool rot)
		: m_fAR(AR), m_bRotation(rot)
	{
		if (camera) KROSS_WARN("WARNING: Overriding previous camera");
		camera = cam;
		SetName(name);
		KROSS_INFO("Camera Controller Created");
	}

	void OrthographicCtrl::OnUpdate(double ts)
	{
		KROSS_NOT_IMPLEMENTED;
		//KROSS_PROFILE_FUNC();
		//glm::vec3& position = const_cast<glm::vec3&>(camera->GetPosition());
		//float speed = fCameraMoveSpeed * (float)ts;
		//if (Input::IsKeyHeld(Key::W)) position.y += speed;
		//if (Input::IsKeyHeld(Key::S)) position.y -= speed;
		//if (Input::IsKeyHeld(Key::A)) position.x -= speed;
		//if (Input::IsKeyHeld(Key::D)) position.x += speed;
		//camera->SetPosition(position);

		//if (Input::IsKeyHeld(Key::M)) m_fZoomRate *= 1.1f;
		//if (Input::IsKeyHeld(Key::N)) m_fZoomRate *= 0.9f;

		//if (m_fZoomRate > -0.001f) m_fZoomRate = -0.001f;

		//if (Input::IsKeyHeld(Key::I)) m_fZoom += m_fZoomRate;
		//if (Input::IsKeyHeld(Key::O)) m_fZoom -= m_fZoomRate;

		//m_fZoom = std::max(m_fZoom, 0.005f);

		//if (m_bRotation)
		//{
		//	float speed = fCameraRotationSpeed * (float)ts;
		//	if (Input::IsKeyHeld(Key::Q)) fCameraRotation += speed;
		//	if (Input::IsKeyHeld(Key::E)) fCameraRotation -= speed;
		//	camera->SetRotation(fCameraRotation, Kross::Camera::Camera::Axis::Z);
		//}

		//fCameraMoveSpeed = m_fZoom * 1.2f;

		//bounds = { -m_fAR * m_fZoom, m_fAR * m_fZoom, -m_fZoom, m_fZoom };
		//camera->SetProjMat(bounds.left, bounds.right, bounds.bottom, bounds.top);
	}

	void OrthographicCtrl::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(KROSS_BIND_EVENT_FN(OrthographicCtrl::OnWindowResized));
		dispatcher.Dispatch<MouseScrolledEvent>(KROSS_BIND_EVENT_FN(OrthographicCtrl::OnMouseScrolled));
	}

	Ref<Kross::Camera::Camera> OrthographicCtrl::GetCamera() { return camera; }
	const Ref<Kross::Camera::Camera> OrthographicCtrl::GetCamera() const { return camera; }
	void OrthographicCtrl::Zoom(float val)
	{
		m_fZoom = std::clamp<float>(val, 0.05f, 100.0f);
		bounds = { -m_fAR * m_fZoom, m_fAR * m_fZoom, -m_fZoom, m_fZoom };
		camera->SetProjMat(glm::ortho(bounds.left, bounds.right, bounds.bottom, bounds.top));
	}

	bool OrthographicCtrl::OnWindowResized(WindowResizeEvent& e)
	{
		m_fAR = (float)e.GetWidth() / (float)e.GetHeight();
		bounds = { -m_fAR * m_fZoom, m_fAR * m_fZoom, -m_fZoom, m_fZoom };
		camera->SetProjMat(glm::ortho(bounds.left, bounds.right, bounds.bottom, bounds.top));
		return false;
	}

	bool OrthographicCtrl::OnMouseScrolled(MouseScrolledEvent& e)
	{
		Zoom(e.GetYOffSet() * m_fZoom * 0.01f + m_fZoom);
		return false;
	}

	bool OrthographicCtrl::OnMouseMoved(MouseMovedEvent& e)
	{
		return false;
	}
}
