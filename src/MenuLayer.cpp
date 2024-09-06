#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Doki.h>

using namespace geode::prelude;

class $modify(MenuLayer) {
    bool init() {
      if ( ! MenuLayer::init()) {
        return false;
      }

      SceneManager* sceneManager = SceneManager::get();

      if ( CCScene::get() -> getChildByID("doki-theme-gd"_spr)) {
        sceneManager -> forget(CCScene::get() -> getChildByID("doki-theme-gd"_spr));
        CCScene::get() -> removeChildByID("doki-theme-gd"_spr);
      }

      CCDirector* director = CCDirector::get();

      CCMenu* menu = CCMenu::create();
      menu -> setID("doki-theme-gd"_spr);
      menu -> setPosition({.0f, .0f});

      CCNode* stickerNode = CCNode::create();
      stickerNode -> setID("sticker-node"_spr);

      CCSprite* sticker = CCSprite::createWithSpriteFrameName(getSticker() . c_str());
      sticker -> setOpacity(Mod::get() -> getSettingValue<int64_t>("TransparencySliderLevel") * 5);
      sticker -> setID("doki-sticker"_spr);
      sticker -> setPosition({director -> getWinSize()
                                       . width * ( Mod::get() -> getSettingValue<int64_t>("xPosPercent") / 100.f ), director -> getWinSize()
                                                                                                                             . height * ( Mod::get() -> getSettingValue<int64_t>("yPosPercent") / 100.f )});
      sticker -> setScale(Mod::get() -> getSettingValue<double>("Scale"));
      /*
      #ifndef GEODE_IS_MACOS
      if (Mod::get()->getSettingValue<int64_t>("StickerSlider") == 11 && std::filesystem::exists((Mod::get()->getConfigDir() / "custom.png").string())) {
          auto customSticker = (Mod::get()->getConfigDir() / "custom.png").string().c_str();
          auto stickerTexture = CCSprite::create(customSticker);
          auto replacement = stickerTexture->getTexture();
          auto theStickerNode = static_cast<CCSprite*>(sticker);
          theStickerNode->setTexture(replacement);
      }
      #endif
      */

      stickerNode -> addChild(sticker);
      menu -> addChild(stickerNode);
      this -> addChild(menu);

      sceneManager -> keepAcrossScenes(menu);
      return true;
    }
};