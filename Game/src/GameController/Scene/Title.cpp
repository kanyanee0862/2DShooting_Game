
#include "Title.h"
#include "../../Input/Input.hpp"
#include "SceneManager.hpp"
#include "../GameController.h"
#include "../src/Utility/Parameter.hpp"

namespace Scene
{
	Title::~Title()
	{
		
	}
	Title::Title(IOnSceneChangeCallback* sceneTitleChange, ECS::EntityManager* entityManager)
		: AbstractScene(sceneTitleChange)
		, entityManager_(entityManager)
	{
		ResourceManager::GetGraph().load("Resource/image/back.png", "BG");
		ResourceManager::GetGraph().load("Resource/image/ship.png", "ship");
	}

	void Title::initialize()
	{

		background = &entityManager_->addEntity(ENTITY_GROUP::DEFAULT);
		background->addComponent<ECS::Transform>();
		background->addComponent<ECS::SpriteDraw>("BG");
		background->getComponent<ECS::SpriteDraw>().setPivot(Vec2(0.0f, 0.0f));

		auto ship = &entityManager_->addEntity(ENTITY_GROUP::PLAYER);
		ship->addComponent<ECS::Transform>();
		ship->addComponent<ECS::SpriteDraw>("ship");
		ship->getComponent<ECS::SpriteDraw>().setPivot(Vec2(0.0f, 0.0f));
		
	}

	void Title::update()
	{
		entityManager_->update();
	}

	void Title::draw()
	{
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		//グループ順に描画
		entityManager_->orderByDraw(ENTITY_GROUP::MAX);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}

}