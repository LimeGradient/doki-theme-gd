#include <Geode/modify/LevelEditorLayer.hpp>
#include "Doki.h"

using namespace geode::prelude;

class $modify(LevelEditorLayer) {
    bool init(GJGameLevel* p0, bool p1) {
      if ( ! LevelEditorLayer::init(p0, p1)) {
        return false;
      }

      SceneManager* sceneManager = SceneManager::get();
      CCScene* scene = CCScene::get();

      if ( ! Mod::get() -> getSettingValue<bool>("ShowStickerInEditor")) {
        getDoki() -> setVisible(false);
      }

      if ( ! Mod::get() -> getSettingValue<bool>("ShowBackgroundInEditor")) {
        return true;
      }

      if ( Mod::get() -> getSettingValue<bool>("ShowBackgroundInEditor")) {
        CCNode* mainNode = this -> getChildByID("EditorUI");

        CCSprite* sticker;
        bool isCustomBackground = Mod::get()->getSettingValue<bool>("UseCustomBackground");
        std::filesystem::path customBackgroundPath = Mod::get()->getSettingValue<std::filesystem::path>("CustomBackgroundPath");

        auto backgroundXPos = Mod::get()->getSettingValue<int64_t>("BackgroundXPos");
        auto backgroundYPos = Mod::get()->getSettingValue<int64_t>("BackgroundYPos");
        auto backgroundScale = Mod::get()->getSettingValue<double>("BackgroundScale");

        if (!isCustomBackground) {
          sticker = CCSprite::create(getBackground() . c_str());
          sticker -> setPosition(ccp(mainNode -> getScaledContentSize().width / 2.f + backgroundXPos, mainNode -> getScaledContentSize().height / 1.5f + backgroundYPos));
          sticker -> setContentSize(mainNode -> getScaledContentSize()); // fucking idk if this works but look at it
          sticker -> setZOrder(- 60);
          sticker -> setOpacity(Mod::get() -> getSettingValue<int64_t>("TransparencySliderEditor"));
          sticker->setScale(backgroundScale);
          sticker -> setID("doki-background"_spr);
          sticker->setAnchorPoint({1.0f, 1.0f});
        } else if (!customBackgroundPath.string().empty() && std::filesystem::exists(customBackgroundPath)) {
          CCSprite* testSprite = CCSprite::create(customBackgroundPath.string().c_str());
          if (!testSprite) return true;

          CCImage* image = new CCImage();
          image->initWithImageFile(customBackgroundPath.string().c_str());

          CCTexture2D* texture = new CCTexture2D();
          texture->initWithImage(image);

          sticker = CCSprite::createWithTexture(texture);
          sticker->setPosition({mainNode->getScaledContentWidth() / 2 + backgroundXPos, mainNode->getScaledContentHeight() / 2 + backgroundYPos});
          sticker->setScale(backgroundScale);

          image->release();
          texture->release();

          sticker -> setContentSize(mainNode -> getScaledContentSize()); // fucking idk if this works but look at it
          sticker -> setZOrder(- 60);
          sticker -> setOpacity(Mod::get() -> getSettingValue<int64_t>("TransparencySliderEditor"));
          sticker -> setID("doki-background"_spr);
          sticker->setAnchorPoint({0.5f, 0.5f});
          
        }
        /*
        #ifndef GEODE_IS_MACOS
        if (Mod::get()->getSettingValue<int64_t>("BackgroundSlider") == 19 && std::filesystem::exists((Mod::get()->getConfigDir() / "customBG.png").string())) {
            auto customBG = (Mod::get()->getConfigDir() / "customBG.png").string().c_str();
            auto bgTexture = CCSprite::create(customBG);
            auto replacement = bgTexture->getTexture();
            auto theStickerNode = static_cast<CCSprite*>(sticker);
            theStickerNode->setTexture(replacement);
        }
        #endif
        */
        mainNode -> addChild(sticker);
      }

      if ( ! Mod::get() -> getSettingValue<bool>("ShowStickerInEditor") && getDoki()) {
        getDoki() -> setVisible(false);
      }

      return true;
    }
};