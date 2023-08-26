#ifndef __HIGH_SCORE_H__
#define __HIGH_SCORE_H__

#include "SwallowTouchLayer.h"

USING_NS_CC;

class HighScoreLayer : public SwallowTouchLayer
{
public:
	static HighScoreLayer* createHighScoreLayer(Size tableSize, float padding, int charNum);
	virtual bool init(Size tableSize, float padding, int charNum);
protected:
	ui::ScrollView* _tableScrollView;
	Size _tableSize;
	float _padding;
	int _charactersNum;
	bool initTableScrollView();
};

#endif // !__HIGH_SCORE_H__
