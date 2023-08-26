#ifndef __TILE_MAP_H__
#define __TILE_MAP_H__

#include "cocos2d.h"

USING_NS_CC;

class TiledMap : public TMXTiledMap
{
public:
	static TiledMap* _mainMap;
	enum MetaType{ OutSide, InsideRed, InsideGreen};
	virtual bool initWithTMXFile(const std::string& tmxFile);

	Vec2 convertPositionTile(Vec2 position);
	MetaType getMetaAt(Vec2 viewPostion);
	ValueMap getObjectInPoint(std::string objName);
protected:
	TMXLayer* _meta;
	Size _tileSize;

	TMXObjectGroup* _pointGroup;
};

#endif // !__TILE_MAP_H__
