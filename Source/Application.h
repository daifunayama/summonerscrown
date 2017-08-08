#pragma once
#include "Arms\ArmsList.h"
#include "Scene/TitleScene.h"
#include "Scene/BattleScene.h"
#include "Scene\/EyecatchScene.h"
#include "Scene/CharaSelectScene.h"
#include "Scene\/\ContractScene.h"
#include "SSPlayer/SS5Player.h"
#include "DxLib.h"

/*
�Q�[�����Ǘ�����N���X
�V�[���̓]���ƑO�̃V�[���̍폜���s��
*/
class Application {
public:
	Application() {
		Parameter::InitFont();
		resman = ss::ResourceManager::getInstance();
		AddSpriteResource();
		ArmsList::get().init();
		WaitKey();
		if (CheckHitKey(KEY_INPUT_B) == 1) {
			mScene = new BattleScene();
			mOldSceneId = Parameter::SCENE_BATTLE;
		}
		else if (CheckHitKey(KEY_INPUT_E) == 1) {
			mScene = new EyecatchScene();
			mOldSceneId = Parameter::SCENE_EYECATCH;
		}
		else if (CheckHitKey(KEY_INPUT_S) == 1) {
			mScene = new CharaSelectScene();
			mOldSceneId = Parameter::SCENE_CHARASELECT;
		}
		else if (CheckHitKey(KEY_INPUT_C) == 1) {
			mScene = new ContractScene();
			mOldSceneId = Parameter::SCENE_CONTRACT;
		}
		else {
			mScene = new TitleScene();
			mOldSceneId = Parameter::SCENE_TITLE;
		}
		mNextSceneId = mOldSceneId;
	}
	~Application(){}

	void MainLoop();

	void AddSpriteResource();
	

public:
	static int mOldSceneId;				//�O�̃V�[��ID
	static int mNextSceneId;			//�V�����V�[��ID
	static ss::ResourceManager *resman; //�X�v���C�g�̃��\�[�X�}�l�[�W���[

private:
	Scene* mScene;						//�V�[��
};