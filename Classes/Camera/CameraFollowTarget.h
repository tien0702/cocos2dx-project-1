#ifndef __CAMERA_FOLLOW_TARGET_H__
#define __CAMERA_FOLLOW_TARGET_H__

#include "cocos2d.h"

USING_NS_CC;

class CameraFollowTarget : public Node
{
public:
	static CameraFollowTarget* create(Camera* tagetCam, Node* target, float smoothRate);
	virtual bool init(Camera* targetCam, Node* target, float smoothRate);

protected:
	Camera* _camFollow;
	Node* _target;
	Rect _fieldOfView;
	float _smoothRate;

	Size _winSize;
	virtual void update(float dt);

	virtual void onEnter();
};

#endif // !__CAMERA_FOLLOW_TARGET_H__
