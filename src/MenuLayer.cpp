#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Doki.h>

using namespace geode::prelude;

class $modify(MenuLayer){
    bool init(){
        if (!MenuLayer::init()){
            return false;
        }

        SceneManager *sceneManager = SceneManager::get();

        if (CCScene::get()->getChildByID("doki-theme-gd"_spr))
        {
            sceneManager->forget(CCScene::get()->getChildByID("doki-theme-gd"_spr));
            CCScene::get()->removeChildByID("doki-theme-gd"_spr);
        }

        CCDirector *director = CCDirector::get();

        CCMenu *menu = CCMenu::create();
        menu->setID("doki-theme-gd"_spr);
        menu->setPosition({.0f, .0f});

        CCNode *stickerNode = CCNode::create();
        stickerNode->setID("sticker-node"_spr);

        CCSprite* sticker;
        bool isCustomSticker = Mod::get()->getSettingValue<bool>("UseCustomSticker");

        if (!isCustomSticker) {
            sticker = CCSprite::createWithSpriteFrameName(getSticker().c_str());
            sticker->setOpacity(Mod::get()->getSettingValue<int64_t>("TransparencySliderLevel") * 5);
            sticker->setID("doki-sticker"_spr);
            sticker->setPosition({director->getWinSize().width * (Mod::get()->getSettingValue<int64_t>("xPosPercent") / 100.f), director->getWinSize().height *(Mod::get()->getSettingValue<int64_t>("yPosPercent") / 100.f)});
            sticker->setScale(Mod::get()->getSettingValue<double>("Scale"));
        } else {
            CCImage* image = new CCImage();
            image->initWithImageFile(Mod::get()->getSettingValue<std::filesystem::path>("CustomStickerPath").c_str());

            CCTexture2D* texture = new CCTexture2D();
            texture->initWithImage(image);

            sticker = CCSprite::createWithTexture(texture);
            sticker->setOpacity(Mod::get()->getSettingValue<int64_t>("TransparencySliderLevel") * 5);
            sticker->setID("doki-sticker"_spr);
            sticker->setPosition({director->getWinSize().width * (Mod::get()->getSettingValue<int64_t>("xPosPercent") / 100.f), director->getWinSize().height *(Mod::get()->getSettingValue<int64_t>("yPosPercent") / 100.f)});
            sticker->setScale(Mod::get()->getSettingValue<double>("Scale"));

            image->release();
            texture->release();
        }

        stickerNode->addChild(sticker);
        menu->addChild(stickerNode);
        this->addChild(menu);

        sceneManager->keepAcrossScenes(menu);
        return true;
    }
};