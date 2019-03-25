#include "GameController.h"
#include "../Class/ResourceManager.hpp"
#include "Scene/SceneManager.hpp"
#include "../Input/Input.hpp"
#include "Scene/Title.h"
#include "Scene/Game.h"
#include "../Class/Sound.hpp"

void GameController::resourceLoad()
{
	
}

GameController::GameController()
{
	//最初に必要なリソースやEntityの生成、ロードを行う
	resourceLoad();
	//初期シーンの設定
	sceneStack_.push(std::make_unique<Scene::Title>(this, &entityManager_));	//タイトルシーンを作成し、プッシュ
	sceneStack_.top()->initialize();
}

void GameController::onSceneChange(const Scene::SceneName& scene, const Scene::StackPopFlag stackClearFlag, const bool isInitialize)
{
	switch (stackClearFlag)
	{
	case Scene::StackPopFlag::NON:
		break;
	case Scene::StackPopFlag::POP:
		DOUT << "poped the scene stack" << std::endl;
		sceneStack_.pop();
		break;
	case Scene::StackPopFlag::ALL_CLEAR:
		DOUT << "scene stack allclear" << std::endl;
		stackClear();
		break;
	default:
		break;
	}
	switch (scene)
	{
	case Scene::SceneName::TITLE:
		sceneStack_.push(std::make_unique<Scene::Title>(this, &entityManager_));
		break;
	case Scene::SceneName::GAME:
		sceneStack_.push(std::make_unique<Scene::Game>(this, &entityManager_));
		break;
	default:
		break;
	}
	MasterSound::Get().update();
	if (isInitialize)
	{
		sceneStack_.top()->initialize();
	}
}

void GameController::stackClear()
{
	while (!sceneStack_.empty())
	{
		sceneStack_.pop();
	}
}

void GameController::update()
{
	MasterSound::Get().update();
	entityManager_.refresh();
	//シーン更新
	sceneStack_.top()->update();
}

void GameController::draw()
{
	//シーン描画
	sceneStack_.top()->draw();
}