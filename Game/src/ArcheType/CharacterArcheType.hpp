#pragma once
#include <vector>
#include "../GameController/GameController.h"
#include "../Components/Renderer.hpp"
#include "../Components/BackGround.hpp"
#include "../Components/MoveComponent.hpp"
namespace ECS
{
	class CharacterArcheType
	{
	public:
		//ƒvƒŒƒCƒ„[‚ÌEntity
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
		//“G‚ÌEntity
		static Entity* CreateEnemy(ECS::EntityManager &manager)
		{
			auto* enemy = &manager.addEntity(ENTITY_GROUP::ENEMY);
			enemy->addComponent<ECS::Transform>();
			enemy->addComponent<ECS::SpriteDraw>("enemy");
			enemy->getComponent<ECS::SpriteDraw>().setPivot(Vec2{ 0.0f, 0.0f });
			enemy->addComponent<ECS::EasingMove>().SetEasing("ElasticIn", 0.0f, 5.0f, 2.0f);
			
			return enemy;
		}
		//BG‚ÌEntity
		static Entity* CreateBG(ECS::EntityManager &manager)
		{
			auto background = &manager.addEntity(ENTITY_GROUP::BACKGROUND);
			background->addComponent<ECS::Transform>();
			background->addComponent<ECS::SpriteDraw>("BG");
			background->getComponent<ECS::SpriteDraw>().setPivot(Vec2{ 0.0f, 0.0f });
			background->addComponent<ECS::BGMove>();
			

			return background;
		}
	private:
		std::vector<ECS::EntityManager> addBG;
	};
}