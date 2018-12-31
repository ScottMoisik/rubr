#include <Rubr.h>


class ExampleLayer : public Rubr::Layer {
public: 
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		RUBR_INFO("ExampleLayer::Update");
	}

	void OnEvent(Rubr::Event& event) override {
		RUBR_TRACE("{0}", event);
	}
};






class Sandbox : public Rubr::App {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {}
};

Rubr::App* Rubr::CreateApp() {
	return new Sandbox();
}




