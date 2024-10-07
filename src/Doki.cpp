#include <filesystem>

#include "Doki.h"

CCNode *getDoki() {
  return CCDirector::get()-> getRunningScene()->getChildByIDRecursive("doki-theme-gd"_spr);
}

std::string getBackground() {
  std::string value = Mod::get() -> getSettingValue<std::string>("BackgroundSlider");
  if (value == "Aqua") return "aqua_dark.png"_spr;
  if (value == "Astolfo") return "astolfo_dark.png"_spr;
  if (value == "Asuna") return "asuna_dark.png"_spr;
  if (value == "Azuki") return "azuki_dark.png"_spr;
  if (value == "Beatrice") return "beatrice.png"_spr;
  if (value == "Cinnamon") return "cinnamon_dark.png"_spr;
  if (value == "Coconut") return "coconut_dark.png"_spr;
  if (value == "Darkness") return "darkness_dark.png"_spr;
  if (value == "Echidna") return "echidna_dark.png"_spr;
  if (value == "Gray") return "gray_dark.png"_spr;
  if (value == "Rias") return "rias_dark.png"_spr;
  if (value == "Rin") return "rin_dark.png"_spr;
  if (value == "Ryuko") return "ryuko_light.png"_spr;
  if (value == "Sayori") return "sayori_dark_normal.png"_spr;
  if (value == "Soma") return "soma_dark.png"_spr;
  if (value == "Tohru") return "tohru_light.png"_spr;
  if (value == "Umi") return "umi_dark.png"_spr;
  if (value == "V8 Girls") return "v8_girls.png"_spr;
  if (value == "Yuri") return "yuri_joy.png"_spr;
  if (value == "Zero Two") return "zero_two_dark.png"_spr;

  return "blank.png"_spr;
}

std::string getSticker() {
  std::string value = Mod::get() -> getSettingValue<std::string>("StickerSlider");
  if (value == "Essex") return "essex_dark.png"_spr;
  if (value == "Sleepy Kanna") return "kanna_dark_secondary.png"_spr;
  if (value == "Kanna") return "kanna_dark.png"_spr;
  if (value == "Mai") return "mai_dark.png"_spr;
  if (value == "Ram") return "ram.png"_spr;
  if (value == "Rem") return "rem.png"_spr;
  if (value == "Rias") return "rias_dark.png"_spr;
  if (value == "Yuno") return "yuno_dark.png"_spr;
  if (value == "Ryuko") return "ryuko.png"_spr;
  if (value == "Nagatoro") return "nagatoro_dark.png"_spr;
  if (value == "Reggie") return "reggie.png"_spr;
  
  return "blank.png"_spr;
}