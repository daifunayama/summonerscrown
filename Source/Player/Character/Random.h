#pragma once
#include "../Player.h"
#include "../Profile.h"

class Random : public Player {
public:

	Profile getProfile() {
		Profile p;
		p.name = "キャラクターがランダムに選択されます";
		p.eName = "Random Select";

		p.size = 1.0f;
		p.speed = 1.0f;
		p.distX = 0;
		p.distY = 0;

		p.cAtack = 0;
		p.lAtack =0;
		p.aut = 0;
		p.pAtack = 0;
		p.sAtack = 0;
		return p;
	}

	void LoadGraphic() {}
	void LoadSound() {}
	void LoadVoice() {}
	void LoadData() {}
	void LoadAtack() {}
	void UpdateAnimation() {}

};