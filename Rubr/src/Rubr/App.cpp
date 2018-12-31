#include "rubrpch.h"
#include "App.h"

#include "Events/AppEvents.h"
#include "Rubr/Log.h"

#include <GLFW/glfw3.h>



namespace Rubr {

#define BIND_EVENT_FN(x) std::bind(&App::x, this, std::placeholders::_1)

	App::App() {
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}
	
	App::~App() {}

	void App::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void App::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
	}

	void App::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}


	void App::Run() {
		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool App::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
	
}