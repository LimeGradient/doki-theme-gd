#include <Geode/Geode.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>
#include "Doki.h"

using namespace geode::prelude;

class $modify(EditorPauseLayer) {
    void onExitNoSave(CCObject* sender) {
      if ( CCNode* dokiTheme = getDoki()) {
        dokiTheme -> setVisible(true);
      }
      EditorPauseLayer::onExitNoSave(sender);
    }

    void onSaveAndExit(CCObject* sender) {
      if ( CCNode* dokiTheme = getDoki()) {
        dokiTheme -> setVisible(true);
      }
      EditorPauseLayer::onSaveAndExit(sender);
    }

    void onSaveAndPlay(CCObject* sender) {
      if ( CCNode* dokiTheme = getDoki()) {
        dokiTheme -> setVisible(Mod::get() -> getSettingValue<bool>("ShowStickerInLevel"));
      }
      EditorPauseLayer::onSaveAndPlay(sender);
    }

    void onResume(CCObject* sender) {
      if ( CCNode* dokiTheme = getDoki()) {
        dokiTheme -> setVisible(Mod::get() -> getSettingValue<bool>("ShowStickerInEditor"));
      }
      EditorPauseLayer::onResume(sender);
    }
};