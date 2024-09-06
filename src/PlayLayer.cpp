#include <Geode/modify/PlayLayer.hpp>
#include "Doki.h"

using namespace geode::prelude;

class $modify(PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
      if ( ! PlayLayer::init(level, useReplay, dontCreateObjects)) { return false; }
      if ( ! Mod::get() -> getSettingValue<bool>("ShowStickerInLevel") && getDoki()) {
        getDoki() -> setVisible(false);
      }
      return true;
    }

    void onQuit() {
      if ( CCNode* dokiTheme = getDoki()) {
        dokiTheme -> setVisible(true);
      }
      PlayLayer::onQuit();
    }
};
