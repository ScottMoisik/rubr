#pragma once

#include "Core.h"

#include "Window.h"
#include "Rubr/LayerStack.h"
#include "Rubr/Events/Event.h"
#include "Rubr/Events/AppEvents.h"

namespace Rubr {
	class RUBR_API App {
	public:
		App();
		virtual ~App();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static App& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;

	private:
		static App* s_Instance;
	};

	//To be defined in client
	App* CreateApp();
}