#include "TiledMap.h"

TiledMap* TiledMap::_mainMap;

bool TiledMap::initWithTMXFile(const std::string& tmxFile)
{
	if (!TMXTiledMap::initWithTMXFile(tmxFile)) {
		log("init tile map failed!");
		return false;
	}
	TiledMap::_mainMap = this;

	_meta = this->getLayer("Meta");
	_meta->setVisible(false);
	_tileSize.width = _contentSize.width / _mapSize.width;
	_tileSize.height = _contentSize.height / _mapSize.height;
	_pointGroup = this->getObjectGroup("Point");

	return true;
}

Vec2 TiledMap::convertPositionTile(Vec2 position)
{
	int x = position.x / _tileSize.width;
	int y = (_contentSize.height - position.y) / _tileSize.height;
	return Vec2();
}

TiledMap::MetaType TiledMap::getMetaAt(Vec2 viewPostion)
{
	Vec2 posInMap = convertPositionTile(viewPostion);

	// Check GID
	int tileGid = _meta->getTileGIDAt(posInMap);
	if (tileGid == 0) return TiledMap::MetaType::OutSide;

	// Try get properties of GID
	Value temp = this->getPropertiesForGID(tileGid);
	if(temp.isNull()) return TiledMap::MetaType::OutSide;

	// Get Values from properties
	TiledMap::MetaType result = TiledMap::MetaType::OutSide;
	ValueMap properties = temp.asValueMap();
	auto properName = properties.find("collidable");
	auto properValue = properties.at("collidable").asInt();

	if (properName != properties.end() && properValue == MetaType::InsideRed)
	{
		result = TiledMap::MetaType::InsideRed;
	}
	else if (properName != properties.end() && properValue == MetaType::InsideGreen)
	{
		result = TiledMap::MetaType::InsideGreen;
	}

	return result;
}

ValueMap TiledMap::getObjectInPoint(std::string objName)
{
	return _pointGroup->getObject(objName.c_str());
}
