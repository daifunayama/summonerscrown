#include "Application.h"
#include "Input/Input.h"
#include "SSPlayer\SS5Player.h"
#include "Effekseer\AnimationController.h"
#include "DxLib.h"

int Application::mOldSceneId = Parameter::SCENE_TITLE;
int Application::mNextSceneId = Parameter::SCENE_TITLE;

ss::ResourceManager* Application::resman = nullptr;

/*ゲームのメインループの処理*/
void Application::MainLoop() {
	Input::getInstance().Update();

	//シーンIDが異なる場合はシーン切り替え
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

		case Parameter::SCENE_CONTRACT :
			mScene = new ContractScene();
			break;

		case Parameter::SCENE_EYECATCH:
			mScene = new EyecatchScene();
			break;

		case Parameter::SCENE_BATTLE :
			mScene = new BattleScene();
			break;


		case Parameter::SCENE_ATACKEDIT:
			mScene = new AtackEditScene();
			break;
		}

		mOldSceneId = mNextSceneId;
		
	}
	
	mScene->Process();
	mScene->Drawing();
}

/*キャラスプライトのリソース追加*/
void  Application::AddSpriteResource() {
	Application::resman->addData("Data/sprite_ein/ein.ssbp");
	Application::resman->addData("Data/sprite_ria/ria.ssbp");
	Application::resman->addData("Data/sprite_kureha/kureha.ssbp");
	Application::resman->addData("Data/sprite_carol/carol.ssbp");
	Application::resman->addData("Data/sprite_remnant/remnant.ssbp");

	Application::resman->addData("Data/kare-meshi/kare-meshi.ssbp");

	Application::resman->addData("Data/arms/HollyKnights/Aries/Aries.ssbp");
	Application::resman->addData("Data/arms/HollyKnights/Southern/Southern.ssbp");
	Application::resman->addData("Data/arms/HollyKnights/Hercules/Hercules.ssbp");
	Application::resman->addData("Data/arms/PrimalSpheres/Cyanos/Cyanos.ssbp");
	
	Application::resman->addData("Data/arms/Comander/Cavalier/cavalier.ssbp");
	Application::resman->addData("Data/arms/ArticArts/Alpha/alpha.ssbp");
	Application::resman->addData("Data/arms/EvilAnima/Enikuma/Enikuma.ssbp");
}