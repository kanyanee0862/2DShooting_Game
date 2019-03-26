#pragma once
#include "../GameController/GameController.h"
#include "../Components/Renderer.hpp"
#include "../Components/MoveComponent.hpp"
namespace ECS
{
	class CharacterArcheType
	{
	public:
		static Entity* CreatePlayer(ECS::EntityManager &manager)
		{
			auto* ship = &manager.addEntity(ENTITY_GROUP::PLAYER);
			ship->addComponent<ECS::Transform>();
			ship->addComponent<ECS::SpriteDraw>("ship");
			ship->getComponent<ECS::SpriteDraw>().setPivot(Vec2{ 0.0f, 0.0f });
			ship->getComponent<ECS::Position>().val.x = static_cast<float>(System::SCREEN_WIDIH /2 - ship->getComponent<ECS::SpriteDraw>().getSize().x/2);
			ship->getComponent<ECS::Position>().val.y = static_cast<float>(System::SCREEN_HEIGHT - ship->getComponent<ECS::SpriteDraw>().getSize().y);
			return ship;
		}
		static Entity* CreateEnemy(ECS::EntityManager &manager)
		{
			auto* enemy = &manager.addEntity(ENTITY_GROUP::ENEMY);
			enemy->addComponent<ECS::Transform>();
			enemy->addComponent<ECS::SpriteDraw>("enemy");
			enemy->getComponent<ECS::SpriteDraw>().setPivot(Vec2{ 0.0f, 0.0f });
			enemy->addComponent<ECS::EasingMove>().SetEasing(EasingFunctions::BounceInOut, 0.0f, 5.0f, 2.0f);
			
			return enemy;
		}
	};
}