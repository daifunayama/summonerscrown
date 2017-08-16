#pragma once
#include "Arms.h"
#include "../Effekseer/EffAnimation.h"

/*
–‚‹ï"Blaze"‚ÌƒNƒ‰ƒX
*/
class Blaze : public Arms {
public:
	void InitArms();
	void LoadArmsData();
	void Move();

	virtual void UpdateArmsAnimation() = 0;
	virtual void LoadArmsGraphic() = 0;
	virtual void LoadArmsSound() = 0;

	virtual void Process() = 0;
	void StartAtack();
	void DoAtack();

	void Draw();
	void DrawAtackBox();
	void CheckArmsAtackHit(Player& another);

protected:
	Atack mAtack;
	int mGraphSummonEffect1;
	int mGraphSummonEffect2;
};