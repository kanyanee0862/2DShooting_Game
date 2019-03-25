/**
* @file Title.hpp
* @brief タイトルシーンでの動作を記述します
* @author 
* @date 
*/
#pragma once
#include "../../ECS/ECS.hpp"
#include "../Scene/SceneManager.hpp"
#include "../../Utility//Easing.hpp"
#include "../../System/System.hpp"
#include "../../ArcheType/ArcheType.hpp"
#include "../../ArcheType/Primitive2D.hpp"
#include "../../Utility/Parameter.hpp"
#include "../../Utility/String.hpp"
#include "../../Utility/JsonIO.hpp"

namespace Scene
{
	class Title : public AbstractScene
	{
	private:
		ECS::EntityManager* entityManager_{};
		Easing easing;
		ECS::Entity* entity;

		ECS::Entity* box;
		ECS::Entity* redBox;
	public:
		~Title();
		Title(IOnSceneChangeCallback* sceneTitleChange, ECS::EntityManager* entityManager);
		virtual void initialize() override;
		virtual void update() override;
		virtual void draw() override;
	};

}