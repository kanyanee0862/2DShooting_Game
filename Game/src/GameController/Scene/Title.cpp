
#include "Title.h"
#include "../../Input/Input.hpp"
#include "SceneManager.hpp"
#include "../GameController.h"
#include "../src/Utility/Parameter.hpp"
#include "../src/Components/BackGround.hpp"
#include "../src/ArcheType/CharacterArcheType.hpp"
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
		ResourceManager::GetGraph().load("Resource/image/enemy01.png", "enemy");
	}

	void Title::initialize()
	{
		ECS::CharacterArcheType::CreatePlayer(*entityManager_);
		ECS::CharacterArcheType::CreateEnemy(*entityManager_);

		background = &entityManager_->addEntity(ENTITY_GROUP::BACKGROUND);
		background->addComponent<ECS::Transform>();
		background->addComponent<ECS::SpriteDraw>("BG");
		background->getComponent<ECS::SpriteDraw>().setPivot(Vec2{ 0.0f, 0.0f });
		background->addComponent<ECS::BGMove>();

		auto background2 = &entityManager_->addEntity(ENTITY_GROUP::BACKGROUND);
		background2->addComponent<ECS::Transform>();
		background2->addComponent<ECS::SpriteDraw>("BG");
		background2->getComponent<ECS::SpriteDraw>().setPivot(Vec2{ 0.0f, 0.0f });
		background2->getComponent<ECS::Position>().val.y = -System::SCREEN_HEIGHT;
		background2->addComponent<ECS::BGMove>();

	

		
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