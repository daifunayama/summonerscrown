#include "Application.h"
#include "Input/Input.h"
#include "SSPlayer\SS5Player.h"
#include "Effekseer\AnimationController.h"
#include "DxLib.h"

int Application::mOldSceneId = Parameter::SCENE_TITLE;
int Application::mNextSceneId = Parameter::SCENE_TITLE;

ss::ResourceManager* Application::resman = nullptr;

/*�Q�[���̃��C�����[�v�̏���*/
void Application::MainLoop() {
	Input::getInstance().Update();

	//�V�[��ID���قȂ�ꍇ�̓V�[���؂�ւ�
	if (mNextSceneId != mOldSceneId) {

		delete mScene;
		AnimationController::getInstance().Reset();

		switch (mNextSceneId) {

		case Parameter::SCENE_TITLE:
			mScene = new TitleScene();
			break;
		
		case Parameter::SCENE_CHARASELECT :
			mScene = new CharaSelectScene();
			break;

		case Parameter::SCENE_BATTLE :
			mScene = new BattleScene();
			break;
		}

		mOldSceneId = mNextSceneId;
		
	}
	
	mScene->Process();
	mScene->Drawing();
}

/*�L�����X�v���C�g�̃��\�[�X�ǉ�*/
void  Application::AddSpriteResource() {
	Application::resman->addData("Data/sprite_ein/ein.ssbp");
	Application::resman->addData("Data/sprite_ria/ria.ssbp");
	Application::resman->addData("Data/sprite_kureha/kureha.ssbp");
	Application::resman->addData("Data/sprite_carol/carol.ssbp");
	Application::resman->addData("Data/sprite_remnant/remnant.ssbp");

	Application::resman->addData("Data/kare-meshi/kare-messhi.ssbp");
}