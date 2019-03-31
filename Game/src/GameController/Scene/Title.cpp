
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
		//playerを生成
		ECS::CharacterArcheType::CreatePlayer(*entityManager_);
		//enemyを生成
		ECS::CharacterArcheType::CreateEnemy(*entityManager_);
		//BG2枚を生成
		ECS::CharacterArcheType::CreateBG(*entityManager_);
		ECS::CharacterArcheType::CreateBG(*entityManager_)->getComponent<ECS::Position>().val.y = -System::SCREEN_HEIGHT;

		
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