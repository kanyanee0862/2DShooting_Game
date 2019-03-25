/**
* @file Game.hpp
* @brief ゲームシーンでの動作を記述します
* @author 
* @date 
*/
#pragma once
#include "../../ECS/ECS.hpp"
#include "../Scene/SceneManager.hpp"

namespace Scene
{
	class Game : public AbstractScene
	{
	private:
		ECS::EntityManager* entityManager_;
	public:
		Game(IOnSceneChangeCallback* sceneTitleChange, ECS::EntityManager* entityManager);
		~Game();
		virtual void initialize() override;
		virtual void update() override;
		virtual void draw() override;
	
	};
}