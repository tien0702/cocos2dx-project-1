#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    std::map<std::string, Layer*>* _callbackLayers;
    virtual bool init();

    CREATE_FUNC(MainMenuScene);
protected:
    void startCallback(Ref* sender);
    void highScoreCallback(Ref* sender);
    void optionsCallback(Ref* sender);
    void quitCallback(Ref* sender);

    void onEnter();
    void onExit();
};

#endif // !__MAIN_MENU_SCENE_H__
