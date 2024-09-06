#include <Geode/Geode.hpp>

#include <Geode/modify/CCDirector.hpp>
#include <Doki.h>

using namespace geode::prelude;

/*
$on_mod(Loaded) {
	auto path = (Mod::get()->getConfigDir() / ("custom.txt")).string();
	auto custom = (Mod::get()->getConfigDir() / ("custom.png")).string();
	auto customBG = (Mod::get()->getConfigDir() / ("customBG.png")).string();
	if (!std::filesystem::exists(path)) {
		std::string content = R"(Hey there!
Please supply your own images
(name them "custom.png" for sticker and "customBG.png" for level editor background)
then revisit your mod settings
and tweak the descriptions for the sticker and background slider options
to your linking
- LimeGradient
		)";
		utils::file::writeString(path, content);
	}
}
*/