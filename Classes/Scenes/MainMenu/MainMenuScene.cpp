#include "MainMenuScene.h"
#include "OptionsLayer.h"
#include "Scenes/MainMenu/HighScoreLayer.h"
#include "GUIs/FollowCursor.h"

#include "GameConfig.h"
#include "Managers/AudioManager.h"
#include "Managers/InputManager.h"
#include "Utilities/DefaultPath.h"
#include "Scenes/GameScene/GameScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

bool MainMenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    GameConfig::load();
    AudioManager::getInstance()->playBGM(DefaultPath::AUDIO_PATH + "bgm.mp3");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // create game name
    auto gameName = Label::createWithTTF("Survivor Game", "fonts/Marker Felt.ttf", 70);
    gameName->setPosition(visibleSize.width / 2, visibleSize.height - 70);

    // Init callback Layers
    _callbackLayers = new std::map<std::string, Layer*>();

    auto optionLayer = OptionsLayer::create();
    auto highScoreLayer = HighScoreLayer::createHighScoreLayer(Size(800, 400), 20.0f, 80);

    optionLayer->retain();
    highScoreLayer->retain();

    _callbackLayers->insert(std::pair<std::string, Layer*>("Options", optionLayer));
    _callbackLayers->insert(std::pair<std::string, Layer*>("HighScore", highScoreLayer));
    // Menu Items
    Menu* menu;
    {
        int fontSize = 40;
        // create labels
        auto startLabel = Label::createWithTTF("Start", "fonts/Marker Felt.ttf", fontSize);
        auto scoreLabel = Label::createWithTTF("High Score", "fonts/Marker Felt.ttf", fontSize);
        auto optionLabel = Label::createWithTTF("Options", "fonts/Marker Felt.ttf", fontSize);
        auto quitLabel = Label::createWithTTF("Quit", "fonts/Marker Felt.ttf", fontSize);

        // create MenuItemLabels
        auto startItem = MenuItemLabel::create(startLabel, CC_CALLBACK_1(MainMenuScene::startCallback, this));
        auto scoreItem = MenuItemLabel::create(scoreLabel, CC_CALLBACK_1(MainMenuScene::highScoreCallback, this));
        auto optionItem = MenuItemLabel::create(optionLabel, CC_CALLBACK_1(MainMenuScene::optionsCallback, this));
        auto quitItem = MenuItemLabel::create(quitLabel, CC_CALLBACK_1(MainMenuScene::quitCallback, this));

        menu = Menu::create(startItem, scoreItem, optionItem, quitItem, nullptr);
        menu->alignItemsVerticallyWithPadding(30);
    }

    menu->setPosition(visibleSize / 2);

    // create background
    auto background = Sprite::create("bg-2.png");
    background->setPosition(visibleSize / 2);
    //
    FollowCursor::getInstance()->initWithFile("cursor.png");
    // add children
    this->addChild(menu, 1);
    this->addChild(gameName, 1);
    this->addChild(background, -1);
    return true;
}

void MainMenuScene::startCallback(Ref* sender)
{
    InputManager::getInstance()->removeFromParent();
    AudioManager::getInstance()->onClickBtn();
    AudioManager::getInstance()->stopBGM();
    auto gameScene = GameScene::create();
    Director::getInstance()->replaceScene(TransitionFade::create(0.75f, gameScene));
}

void MainMenuScene::highScoreCallback(Ref* sender)
{
    this->addChild(_callbackLayers->at("HighScore"), 2);
    AudioManager::getInstance()->onClickBtn();
}

void MainMenuScene::optionsCallback(Ref* sender)
{
    this->addChild(_callbackLayers->at("Options"), 2);
    AudioManager::getInstance()->onClickBtn();
}

void MainMenuScene::quitCallback(Ref* sender)
{
    AudioManager::getInstance()->onClickBtn();
    Director::getInstance()->end();
}

void MainMenuScene::onEnter()
{
    Scene::onEnter();
    InputManager::getInstance()->removeFromParent();
    FollowCursor::getInstance()->removeFromParent();

    FollowCursor::getInstance()->setVisibleCursor(false);
    this->addChild(InputManager::getInstance());
    this->addChild(FollowCursor::getInstance(), 101);
}

void MainMenuScene::onExit()
{
    Scene::onExit();
}
