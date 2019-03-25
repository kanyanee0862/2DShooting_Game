
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
	
	}

	void Title::initialize()
	{

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