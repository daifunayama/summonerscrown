#pragma once

/*
�Փ˔���p�{�b�N�X�̒�`�N���X
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
	bool mExist;		//�q�b�g�{�b�N�X�����݂��邩�̃t���O
	int mBoxId;			//�{�b�N�X��ID
	int mPositionX;		//X���W
	int mPositionY;		//Y���W
	int mWidth;			//��
	int mHeight;		//����
};