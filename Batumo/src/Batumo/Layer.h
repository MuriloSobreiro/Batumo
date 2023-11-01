#pragma once

#include "Batumo/Core.h"
#include "Batumo/Core/DeltaTime.h"
#include "Batumo/Events/Event.h"


namespace Batumo {
	class BATUMO_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void OnDetach(){}
		virtual void OnUpdate(DeltaTime dt){}
		virtual void OnImGuiRender(){}
		virtual void OnEvent(Event& event){}
		
		inline const std::string& GetName() const { return m_DebugName; }
	
	protected:
		std::string m_DebugName;
	};
}


