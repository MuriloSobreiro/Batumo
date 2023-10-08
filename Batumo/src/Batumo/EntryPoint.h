#pragma once

#ifdef BT_PLATAFORM_WINDOWS

extern Batumo::Application* Batumo::CreateApplication();

int main() {
	auto app = Batumo::CreateApplication();
	app->Run();
	delete app;
}
#endif // BT_PLATAFORM_WINDOWS
