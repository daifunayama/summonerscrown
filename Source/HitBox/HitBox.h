#pragma once

/*
衝突判定用ボックスの定義クラス
*/
class HitBox {
public:
	HitBox() {
		mExist = 0;
	}

	inline bool getExist() { return mExist; }
	inline int getBoxId() { return mBoxId; }
	inline int getPositionX() { return mPositionX; }
	inline int getPositionY() { return mPositionY; }
	inline int getWidth() { return mWidth; }
	inline int getHeight() { return mHeight; }

	inline void setExist(bool exist) { mExist = exist; }
	inline void setBoxId(int boxId) { mBoxId = boxId; }
	inline void setPositionX(int positionX) { mPositionX = positionX; }
	inline void setPositionY(int positionY) { mPositionY = positionY; }
	inline void setWidth(int width) { mWidth = width; }
	inline void setHeight(int height) { mHeight = height; }

private:
	bool mExist;		//ヒットボックスが存在するかのフラグ
	int mBoxId;			//ボックスのID
	int mPositionX;		//X座標
	int mPositionY;		//Y座標
	int mWidth;			//幅
	int mHeight;		//高さ
};