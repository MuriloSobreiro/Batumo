#pragma once

#ifdef BT_PLATAFORM_WINDOWS

extern Batumo::Application* Batumo::CreateApplication();

int main() {
	Batumo::Log::Init();
	BT_CORE_WARN("Inicializado o Logger!");
	BT_INFO("Inicializado o Logger!");
	auto app = Batumo::CreateApplication();
	app->Run();
	delete app;
}
#endif // BT_PLATAFORM_WINDOWS
