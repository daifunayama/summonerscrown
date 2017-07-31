#pragma once
#include "../SSPlayer/SS5Player.h"

/*
SpriteStudioのエフェクトアニメーション制御用シングルトンパターンクラス
*/
class SSEffectController {
public:
	static  SSEffectController& getInstance(void) {
		static  SSEffectController  mSSEffectController;
		return  mSSEffectController;
	}
	SSEffectController(const  SSEffectController&) = delete;
	SSEffectController& operator = (const  SSEffectController&) = delete;
	SSEffectController(SSEffectController&&) = delete;
	SSEffectController operator = (SSEffectController&&) = delete;

	void Load();
	void Play(string pass, int positionX, int positionY, float scaleX, float scaleY,float speed, float angle, int alpha);
	void Process();
	void Draw();

private:
	SSEffectController() { mActive = 0; }
	~SSEffectController() {}

private:
	ss::Player* mSSEffect[5];
	int mActive;
	int mPositionX[5];
	int mPositionY[5];
};