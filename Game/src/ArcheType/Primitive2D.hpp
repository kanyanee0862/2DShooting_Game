/**
* @file Primitive2D.hpp
* @brief 基本図形を作る
* @author tonarinohito
* @date 2019/03/14
*/
#pragma once
#include "../GameController/GameController.h"
#include "../Components/Collider.hpp"
namespace ECS
{
	struct Primitive2D
	{
		static Entity* CreateBox(const Vec2& pos, const Vec2& size, EntityManager& entityManager)
		{
			auto* entity = &entityManager.addEntity();
			entity->addComponent<Transform>(pos);
			entity->addComponent<BoxCollider>(size);
			entity->addGroup(ENTITY_GROUP::DEFAULT);
			return entity;
		}

		static Entity* CreateCircle(const Vec2& pos, const float& radius, EntityManager& entityManager)
		{
			auto* entity = &entityManager.addEntity();
			entity->addComponent<Transform>(pos);
			entity->addComponent<CircleCollider>(radius);
			entity->addGroup(ENTITY_GROUP::DEFAULT);
			return entity;
		}
	};
}