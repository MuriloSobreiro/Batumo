#include "Batumo.h"

class ExampleLayer : public Batumo::Layer {
public:
	ExampleLayer()
		: Layer("Example"){}

	void OnUpdate() override {
		BT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Batumo::Event& event) override {
		BT_TRACE("{0}", event);
	}
};

class SandBox : public Batumo::Application {
public:
	SandBox() {
		PushLayer(new ExampleLayer());
	}
	~SandBox() {

	}
};

Batumo::Application* Batumo::CreateApplication() {
	return new SandBox();
}

