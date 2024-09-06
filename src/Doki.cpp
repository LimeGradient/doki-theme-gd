#include <filesystem>

#include <Geode/Geode.hpp>

#include "Doki.h"

CCNode *getDoki() {
  return CCDirector::get()-> getRunningScene()->getChildByIDRecursive("doki-theme-gd"_spr);
}

std::string getBackground() {
  long long value = Mod::get() -> getSettingValue<int64_t>("BackgroundSlider");
  switch ( value ) {
    case 1: return "aqua_dark.png"_spr;
    case 2: return "astolfo_dark.png"_spr;
    case 3: return "asuna_dark.png"_spr;
    case 4: return "azuki_dark.png"_spr;
    case 5: return "beatrice.png"_spr;
    case 6: return "cinnamon_dark.png"_spr;
    case 7: return "coconut_dark.png"_spr;
    case 8: return "darkness_dark.png"_spr;
    case 9: return "echidna_dark.png"_spr;
    case 10: return "gray_dark.png"_spr;
    case 11: return "rias_dark.png"_spr;
    case 12: return "rin_dark.png"_spr;
    case 13: return "ryuko_light.png"_spr;
    case 14: return "sayori_dark_normal.png"_spr;
    case 15: return "soma_dark.png"_spr;
    case 16: return "tohru_light.png"_spr;
    case 17: return "umi_dark.png"_spr;
    case 18: return "v8_girls.png"_spr;
    case 19: return "yuri_joy.png"_spr;
    case 20: return "zero_two_dark.png"_spr;
    default: return "blank.png"_spr;
  }
}

std::string getSticker() {
  long long value = Mod::get() -> getSettingValue<int64_t>("StickerSlider");
  switch ( value ) {
    case 1: return "essex_dark.png"_spr;
    case 2: return "kanna_dark_secondary.png"_spr;
    case 3: return "kanna_dark.png"_spr;
    case 4: return "mai_dark.png"_spr;
    case 5: return "ram.png"_spr;
    case 6: return "rem.png"_spr;
    case 7: return "rias_dark.png"_spr;
    case 8: return "yuno_dark.png"_spr;
    case 9: return "ryuko.png"_spr;
    case 10: return "nagatoro_dark.png"_spr;
    case 11: return "reggie.png"_spr;
    case 12: return Mod::get()->getSettingValue<std::filesystem::path>("CustomStickerPath").string();
    default: return "blank.png"_spr;
  }
}