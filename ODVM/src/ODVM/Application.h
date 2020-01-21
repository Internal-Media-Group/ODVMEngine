#pragma once

#include "Platform/Windows/WindowsInput.h"
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "ODVM/Events/ApplicationEvent.h"
#include "ODVM/LayerStack.h"


namespace ODVM
{
	class ODVM_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void OnEvent(Event& e);
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }

		inline Input& GetInput() { return input; }

		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		#ifdef ODVM_PLATFORM_WINDOWS
		WindowsInput input;
		#endif
	private:
		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateApplication();
}
