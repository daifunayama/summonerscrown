#include "BattleScene.h"
#include "../Input/Input.h"
#include "../Effekseer/AnimationController.h"
#include "../Player/Character/Ein.h"
#include "../Player/Character/Ria.h"
#include "../Player/Character/Carol.h"
#include "../Player/Character/Kare-meshi.h"
#include "../Arms/FollowerArms.h"
#include "../SSEffect/SSEffectController.h"
#include "../Camera/Camera.h"


/*リソースのロードと初期化*/
void BattleScene::Load() {
	int loadGraph;
	loadGraph = LoadGraph("Data/graphic/game/loading.png");

	mPlayer[0] = new Ein();
	mPlayer[1] = new Carol();

	SetUseASyncLoadFlag(true);

	for (int p= 0; p < 2; p++) {
		//プレイヤーのロード
		mPlayer[p]->setPlayerId(p);
		mPlayer[p]->LoadGraphic();//グラフィックのロード
		mPlayer[p]->LoadCommonSound();//共通SEのロード
		mPlayer[p]->LoadSound();//固有SEのロード
		mPlayer[p]->LoadVoice();//ボイスのロード
		mPlayer[p]->LoadData();//ボックスデータのロード
		mPlayer[p]->LoadAtack();//攻撃データのロード
		mPlayer[p]->Init(p);//プレイヤーの初期化

		//魔具のロード
		mPlayer[p]->LoadArms(p);

		//HPゲージの設定
		mHPGauge[p].setPlayerId(p);
		mHPGauge[p].Load(*mPlayer[p]);

		//EXゲージの設定
		mEXGauge[p].setPlayerId(p);
		mEXGauge[p].Load();

		//チェーンの設定
		mChain[p].setPlayerId(p);
		mChain[p].Load();

		//契約陣の設定
		mContractCircle[p].setPlayerId(p);
		mContractCircle[p].Load(*mPlayer[p]);
	}
	//背景のロード
	BackGround::get().LoadGraphic();

	mBGM = LoadSoundMem("Data/bgm/night2.mp3");
	
	int n = 0;
	while(CheckHandleASyncLoad(mBGM) != FALSE){
		ProcessMessage();
		n++;

		ClearDrawScreen();

		DrawRotaGraph(1100, 500, 1.3, (Parameter::PI / 360)*n, loadGraph, true, false);
		DrawFormatString(10, 10, Parameter::COLOR_WHITE, "%d", n);

		ScreenFlip();
	}
	SetUseASyncLoadFlag(false);
	
	//エフェクトのロードと初期化
	SSEffectController::getInstance().Load();

	//カメラの初期化
	Camera::getInstance().Init();

	//音量の初期化
	mPlayer[0]->InitVolume();
	mPlayer[1]->InitVolume();

	ChangeVolumeSoundMem(100, mBGM);
	//PlaySoundMem(mBGM, DX_PLAYTYPE_LOOP);
	
}

/*更新*/
void BattleScene::Process() {
	if (Input::getInstance().GetKey(KEY_INPUT_F) == 1) {
		mPlayer[0]->LoadAtack();//攻撃データのロード
		mPlayer[1]->LoadAtack();//攻撃データのロード
		mPlayer[0]->LoadData();
		mPlayer[1]->LoadData();
		mPlayer[0]->LoadArms(0);
		mPlayer[1]->LoadArms(1);
	}

	if (Input::getInstance().GetKey(KEY_INPUT_A) == 1 || Input::getInstance().GetKey(PAD_INPUT_10) == 1) {
		mPlayer[0]->Init(0);
		mPlayer[1]->Init(1);
		mPlayer[0]->getArms(mPlayer[0]->getArmsId())->setPositionX(mPlayer[0]->getPositionX());
		mPlayer[0]->getArms(mPlayer[0]->getArmsId())->setPositionY(mPlayer[0]->getPositionY());
		mPlayer[1]->getArms(mPlayer[1]->getArmsId())->setPositionX(mPlayer[1]->getPositionX());
		mPlayer[1]->getArms(mPlayer[1]->getArmsId())->setPositionY(mPlayer[1]->getPositionY());

		mPlayer[0]->getArms(mPlayer[0]->getArmsId())->ResetPosition();
		mPlayer[1]->getArms(mPlayer[1]->getArmsId())->ResetPosition();

		mPlayer[0]->setEX(100);
	}

	if (mPlayer[0]->getHitStop() == 0) {

		//プレイヤーの動作
		mPlayer[0]->Move(*mPlayer[1]);
		mPlayer[1]->Move(*mPlayer[0]);

		//魔具の動作
		mPlayer[0]->MoveArms();
		mPlayer[1]->MoveArms();

		
		//プレイヤー同士の当たり判定
		mPlayer[0]->CheckPlayersHit(*mPlayer[1]);

		//仮想壁との接触判定
		mPlayer[0]->CheckVirtualWallHit(*mPlayer[1]);

		//魔具の攻撃の当たり判定
		mPlayer[0]->getArms(mPlayer[0]->getArmsId())->CheckArmsAtackHit(*mPlayer[1]);
		mPlayer[1]->getArms(mPlayer[1]->getArmsId())->CheckArmsAtackHit(*mPlayer[0]);

		if (mPlayer[0]->getBlaze() != nullptr) {
			if (mPlayer[0]->getBlaze()->getState() == Parameter::S_ARMS_SUMMON) {

				mPlayer[0]->getBlaze()->Move();
				mPlayer[0]->getBlaze()->UpdateArmsAnimation();
				mPlayer[0]->getBlaze()->CheckArmsAtackHit(*mPlayer[1]);
			}
		}

		//プレイヤーの攻撃の当たり判定
		mPlayer[0]->CheckPlayersAtackHit(*mPlayer[1]);
		mPlayer[1]->CheckPlayersAtackHit(*mPlayer[0]);

		//振り向き
		mPlayer[0]->ChangeDirection(*mPlayer[1]);
		mPlayer[1]->ChangeDirection(*mPlayer[0]);

		//プレイヤーが攻撃を食らったときの処理
		mPlayer[0]->EatDamage(*mPlayer[1]);
		mPlayer[1]->EatDamage(*mPlayer[0]);

		//プレイヤーのアニメーションの更新
		if (mPlayer[0]->getHitStop() == 0)mPlayer[0]->UpdateAnimation();
		if (mPlayer[1]->getHitStop() == 0)mPlayer[1]->UpdateAnimation();

		//HPゲージへ反映
		mHPGauge[0].Process(*mPlayer[0], *mPlayer[1]);
		mHPGauge[1].Process(*mPlayer[1], *mPlayer[0]);

		//EXゲージへ反映
		mEXGauge[0].Process(*mPlayer[0]);
		mEXGauge[1].Process(*mPlayer[1]);

		//チェーンへ反映
		mChain[0].Process(*mPlayer[0]);
		mChain[1].Process(*mPlayer[1]);

		//契約陣へ反映
		mContractCircle[0].Process(*mPlayer[0]);
		mContractCircle[1].Process(*mPlayer[1]);

		mPlayer[0]->DecrementHitStop();
		mPlayer[1]->DecrementHitStop();
	}
	else mPlayer[0]->DecrementHitStop();

	//背景にプレイヤー情報を渡す
	BackGround::get().Process(*mPlayer[0], *mPlayer[1]);

	//アニメーションのプロセス
	AnimationController::getInstance().Process();

	SSEffectController::getInstance().Process();

	//カメラのアップデート
	Camera::getInstance().Update(*mPlayer[0], *mPlayer[1]);
}

/*描画*/
void BattleScene::Drawing() {
	static bool boxDrawFlag = false;

	if (Input::getInstance().GetKey(KEY_INPUT_G) == 1)boxDrawFlag = !boxDrawFlag;

	//背景の描画
	BackGround::get().Draw();

	//HPゲージを描画
	mHPGauge[0].Draw();
	mHPGauge[1].Draw();

	//契約陣を描画
	mContractCircle[0].Draw();
	mContractCircle[1].Draw();

	AnimationController::getInstance().DrawLayer3();

	mPlayer[0]->DrawArmsBack();
	mPlayer[1]->DrawArmsBack();

	//プレイヤーの描画
	if(CheckDrawPriority(*mPlayer[0],*mPlayer[1]) == 0){
		mPlayer[1]->Draw();
		mPlayer[0]->Draw();
	}
	else {
		mPlayer[0]->Draw();
		mPlayer[1]->Draw();
	}

	AnimationController::getInstance().DrawLayer2();

	mPlayer[0]->DrawArms();
	mPlayer[1]->DrawArms();

	if (mPlayer[0]->getBlaze() != nullptr) {
		if (mPlayer[0]->getBlaze()->getState() == Parameter::S_ARMS_SUMMON) {
			mPlayer[0]->getBlaze()->Draw();
			//mPlayer[0]->getBlaze()->DrawAtackBox();
		}
	}

	//アニメーションの描画
	AnimationController::getInstance().DrawLayer1();

	//エフェクトの描画
	SSEffectController::getInstance().Draw();

	if (mPlayer[0]->getState() == Parameter::S_PLAYER_CATCH)mPlayer[0]->DrawThrowEffect();
	if (mPlayer[1]->getState() == Parameter::S_PLAYER_CATCH)mPlayer[1]->DrawThrowEffect();

	//ヒットボックスを表示する
	if (boxDrawFlag) {
		mPlayer[0]->DrawHitBox();
		mPlayer[0]->DrawDamageBox();
		mPlayer[1]->DrawHitBox();
		mPlayer[1]->DrawDamageBox();

		if (mPlayer[0]->isAtackState())mPlayer[0]->DrawAtackBox();
		if (mPlayer[1]->isAtackState())mPlayer[1]->DrawAtackBox();
		if (mPlayer[0]->getArms(mPlayer[0]->getArmsId())->isAtackState())mPlayer[0]->getArms(mPlayer[0]->getArmsId())->DrawAtackBox();
		if (mPlayer[1]->getArms(mPlayer[1]->getArmsId())->isAtackState())mPlayer[1]->getArms(mPlayer[1]->getArmsId())->DrawAtackBox();
	}

	mPlayer[0]->getArms(mPlayer[0]->getArmsId())->DrawUI();
	mPlayer[1]->getArms(mPlayer[1]->getArmsId())->DrawUI();

	//EXゲージを描画
	mEXGauge[0].Draw();
	mEXGauge[1].Draw();

	//チェーンを描画
	mChain[0].Draw();
	mChain[1].Draw();

	if (mPlayer[1]->isDamageState()) {
		DrawBox(100, 200, mPlayer[1]->getCounter() * 4 + 100, 250, Parameter::COLOR_RED, true);
	}
}

/*描画の優先順位を返す*/
int BattleScene::CheckDrawPriority(Player& p1, Player& p2) {
	//ダメージ中のプレイヤーを後ろに
	if (p1.isDamageState() && !p2.isDamageState())return 1;
	if (p2.isDamageState() && !p1.isDamageState())return 0;
	if (p1.isDamageState() && p2.isDamageState())return 0;

	//掴まれ中のプレイヤーを後ろに
	if (p1.getState() == Parameter::S_PLAYER_CAUGHT && p2.getState() != Parameter::S_PLAYER_CAUGHT)return 1;
	if (p2.getState() == Parameter::S_PLAYER_CAUGHT && p1.getState() != Parameter::S_PLAYER_CAUGHT)return 0;

	//ガード中のプレイヤーを後ろに
	if (p1.isGuardState() && !p2.isGuardState())return 1;
	if (p2.isGuardState() && !p1.isGuardState())return 0;
	if (p1.isGuardState() && p2.isGuardState())return 0;

	//攻撃中のプレイヤーを前に　両方の場合後出しの方を優先
	if (p1.isAtackState() && !p2.isAtackState())return 0;
	if (p2.isAtackState() && !p1.isAtackState())return 1;
	if (p1.isAtackState() && p2.isAtackState()) {
		return p1.getPlayerAtack(p1.getState() - 18).getCounter() <= p2.getPlayerAtack(p1.getState() - 18).getCounter() ?
			0 : 1;
	}

	return 0;
}