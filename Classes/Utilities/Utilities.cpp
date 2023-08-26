#include "Utilities.h"
#include "DefaultPath.h"

std::string Utilities::justifyStrings(const std::string& str1, const std::string& str2, int width)
{
	if (width <= 0) {
		return "";
	}

	int totalLength = str1.length() + str2.length();
	int spaceCount = width - totalLength;

	if (spaceCount <= 0) {
		return str1 + str2;
	}

	std::string result = str1;
	result.append(spaceCount, ' ');
	result += str2;

	return result;
}

std::pair<Animation*, int> Utilities::createAnimation(std::string aniName)
{
	Vector<SpriteFrame*> frames;

	int count = 1;
	while (true)
	{
		std::string buffer;
		buffer += "./" + aniName + " (" + std::to_string(count) + ")";
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(buffer);
		if (frame != nullptr)
		{
			frames.pushBack(frame);
			++count;
		}
		else
		{
			break;
		}
	}
	std::pair<Animation*, int> anid;
	float duration = 1.0f / (float)count;
	Animation* animation = Animation::createWithSpriteFrames(frames, duration);
	return std::pair<Animation*, int>(animation, count);
}

Animation* Utilities::createAnimation(std::string fileName, int numberFrames, float duration)
{
	Vector<SpriteFrame*> frames;
	for (int i = 0; i < numberFrames; ++i)
	{
		std::string buffer;
		buffer += "./" + fileName;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(buffer);
		if (frame == nullptr)
		{
			printf("Can't create frame name: %s\n", buffer.c_str());
			break;
		}
		frames.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frames, duration);
	return animation;
}

std::pair<std::string, std::string> Utilities::initSpriteFramesPath(std::string path, std::string fileName)
{
	std::string plist, png;
	plist = path + fileName + ".plist";
	png = path + fileName + ".png";
	return std::pair<std::string, std::string>(plist, png);
}
