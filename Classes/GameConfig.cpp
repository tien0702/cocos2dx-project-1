#include "GameConfig.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

std::string GameConfig::_path = cocos2d::FileUtils::getInstance()->getWritablePath() + "config.txt";
float GameConfig::_sfxVolume = 0.0f;
float GameConfig::_bgmVolume = 0.0f;
TTFConfig GameConfig::_font;

bool GameConfig::save()
{
	auto fileInstance = cocos2d::FileUtils::getInstance();
	rapidjson::Document document;

	document.SetObject();
	document.AddMember("BGM", GameConfig::_bgmVolume, document.GetAllocator());
	document.AddMember("SFX", GameConfig::_sfxVolume, document.GetAllocator());
	cocos2d::log(_path.c_str());
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	fileInstance->writeStringToFile(buffer.GetString(), _path);
	return true;
}

bool GameConfig::load()
{
	if (!cocos2d::FileUtils::getInstance()->isFileExist(_path))
	{
		GameConfig::save();
	}

	_font.fontFilePath = "fonts/Marker Felt.ttf";
	_font.fontSize = 30;
	_font.glyphs = GlyphCollection::DYNAMIC;
	_font.outlineSize = 1;
	_font.customGlyphs = nullptr;
	_font.distanceFieldEnabled = false;
	rapidjson::Document document;

	std::string fileData = cocos2d::FileUtils::getInstance()->getStringFromFile(_path);
	document.Parse(fileData.c_str());
	if (document.HasParseError())
	{
		cocos2d::log("Parse Error!");
		return false;
	}
	else
	{
		GameConfig::_bgmVolume = document["BGM"].GetFloat();
		GameConfig::_sfxVolume = document["SFX"].GetFloat();
	}

	return true;
}
