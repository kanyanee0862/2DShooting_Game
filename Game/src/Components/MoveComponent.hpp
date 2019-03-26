#pragma once
#include "../Components/BasicComponents.hpp"
namespace ECS
{
	class MoveComponent:public ComponentSystem
	{
	public:
	
		void initialize() override
		{
			if (!owner->hasComponent<ECS::Position>())
			{
				owner->addComponent<ECS::Position>();
			}
			
		}
		void update() override
		{
			owner->update();
		}
	private:
		
		
	};
}
