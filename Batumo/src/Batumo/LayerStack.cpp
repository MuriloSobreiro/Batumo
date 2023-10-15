#include "btpch.h"
#include "LayerStack.h"


namespace Batumo {
	LayerStack::LayerStack() {
		m_LayerInsert = m_layers.begin();
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : m_layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer) {
		m_layers.emplace(m_LayerInsert,layer);
	}

	void LayerStack::PushOverlay(Layer* layer) {
		m_layers.push_back(layer);
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end()) {
			m_layers.erase(it);
			m_LayerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* layer) {
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end()) {
			m_layers.erase(it);
		}
	}
}