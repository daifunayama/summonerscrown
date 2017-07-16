#pragma once
#include "Arms.h"
#include "../Atack/FollowerArmsAtack.h"
#include "../Effekseer/EffAnimation.h"

/*
プレイヤーに追従する魔具"Follower"のクラス
*/
class FollowerArms : public Arms {
public:

	void InitArms();
	void LoadArmsData();
	void Move();
	virtual void FollowPlayer(int,int);
	virtual void StartAtack();
	virtual void StartSummon();
	virtual void DoAtack();
	void Draw();
	void DrawAtackBox();
	void CheckArmsAtackHit(Player&);

	virtual void CheckCanSummon(){}
	virtual void Process() {}
	virtual void ProcessAfterAtack(){}

	bool isAtackState();

	virtual void UpdateArmsAnimation() = 0;
	virtual void LoadArmsGraphic() = 0;
	virtual void LoadArmsSound() = 0;

	bool isCanCancelTiming(int atackId);

protected:
	FollowerArmsAtack mAtack[8];
};