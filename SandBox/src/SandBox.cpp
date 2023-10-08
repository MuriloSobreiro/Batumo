#include "Batumo.h"

class SandBox : public Batumo::Application {
public:
	SandBox() {

	}
	~SandBox() {

	}
};

Batumo::Application* Batumo::CreateApplication() {
	return new SandBox();
}

