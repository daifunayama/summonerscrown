#pragma once

/*
Effekseer�A�j���[�V�����̃f�[�^�N���X
*/

class EffAnimation {
public:
	inline bool getExist() { return mExist; }
	inline int getKey() { return mKey; }
	inline int getAtackId() { return mAtackId; }
	inline int getState() { return mState; }
	inline int getLayer() { return mLayer; }
	inline int getGraph() { return mGraph; }
	inline int getPositionX() { return mPositionX; }
	inline int getPositionY() { return mPositionY; }
	inline int getWidth() { return mWidth; }
	inline int getHeight() { return mHeight; }
	inline float getExRate() { return mExRate; }
	inline int getDevided() { return mDevided; }
	inline int getSpeed() { return mSpeed; }
	inline int getAngle() { return mAngle; }
	inline int getCounter() { return mCounter; }
	inline int getStartFrame() { return mStartFrame; }
	inline int getEndFrame() { return mEndFrame; }
	inline int getLoopFrame() { return mLoopFrame; }
	inline bool getAddFlag() { return mAddFlag; }
	inline bool getRight(){ return mRight; }
	
	inline void setExist(int exist) { mExist = exist; }
	inline void setKey(int key) { mKey = key; }
	inline void setAtackId(int atackId) { mAtackId = atackId; }
	inline void setState(int state) { mState = state; }
	inline void setLayer(int layer) { mLayer = layer; }
	inline void setGraph(int graph) { mGraph = graph; }
	inline void setPositionX(int positionX) { mPositionX = positionX; }
	inline void setPositionY(int positionY) { mPositionY = positionY; }
	inline void setWidth(int width) { mWidth = width; }
	inline void setHeight(int height) { mHeight = height; }
	inline void setExRate(float exRate) { mExRate = exRate; }
	inline void setDevided(int devided) { mDevided = devided; }
	inline void setSpeed(int speed) { mSpeed = speed; }
	inline void setAngle(int angle) { mAngle = angle; }
	inline void setCounter(int counter) { mCounter = counter; }
	inline void setStartFrame(int startFrame) { mStartFrame = startFrame; }
	inline void setEndFrame(int endFrame) { mEndFrame = endFrame; }
	inline void setLoopFrame(int loopFrame) { mLoopFrame = loopFrame; }
	inline void setAddFlag(bool addFlag) { mAddFlag = addFlag; }
	inline void setRight(bool right) { mRight = right; }

	inline void IncrementCounter() { mCounter++; }

private:
	bool mExist;		//���݃t���O
	int mKey;			//�A�j���[�V�����̃L�[
	int mAtackId;		//�U��ID
	int mLayer;			//���C���[
	int mState;			//��ԕϐ�
	int mGraph;			//�O���t�B�b�N�n���h��
	int mPositionX;		//X���W
	int mPositionY;		//Y���W
	int mWidth;			//����
	int mHeight;		//����
	float mExRate;		//�g�嗦
	int mDevided;		//���摜�̉�������
	int mSpeed;			//�Đ����x
	int mAngle;			//�p�x
	int mCounter;		//�J�E���^�[
	int mStartFrame;	//�Đ��J�n�t���[��
	int mEndFrame;		//�Đ��I���t���[��
	int mLoopFrame;		//���[�v�A�j���̏ꍇ�̃��[�v�t���[��(����ȊO��-1)
	bool mAddFlag;		//���Z�`��t���O
	bool mRight;		//����
};