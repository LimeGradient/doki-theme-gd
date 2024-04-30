#include <Geode/Geode.hpp>

#include <Geode/modify/CCDirector.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>

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

CCNode* getDoki() {
	return CCDirector::get()->getRunningScene()->getChildByIDRecursive("doki-theme-gd"_spr);
}

std::string getBackground() {
	auto value = Mod::get()->getSettingValue<int64_t>("BackgroundSlider");
	switch (value) {
		case 1:
			return "aqua_dark.png"_spr;
		case 2:
			return "astolfo_dark.png"_spr;
		case 3:
			return "asuna_dark.png"_spr;
		case 4:
			return "azuki_dark.png"_spr;
		case 5:
		 	return "beatrice.png"_spr;
		case 6:
			return "cinnamon_dark.png"_spr;
		case 7:
			return "coconut_dark.png"_spr;
		case 8:
			return "darkness_dark.png"_spr;
		case 9:
			return "echidna_dark.png"_spr;
		case 10:
			return "gray_dark.png"_spr;
		case 11:
			return "rias_dark.png"_spr;
		case 12:
			return "rin_dark.png"_spr;
		case 13:
			return "ryuko_light.png"_spr;
		case 14:
			return "sayori_dark_normal.png"_spr;
		case 15:
			return "soma_dark.png"_spr;
		case 16:
			return "tohru_light.png"_spr;
		case 17:
			return "umi_dark.png"_spr;
		case 18:
			return "v8_girls.png"_spr;
		case 19:
			return "yuri_joy.png"_spr;
		case 20:
			return "zero_two_dark.png"_spr;
		default:
			return "blank.png"_spr;
	}
}

std::string getSticker() {
	auto value = Mod::get()->getSettingValue<int64_t>("StickerSlider");
	switch (value) {
		case 1:
			return "essex_dark.png"_spr;
		case 2:
			return "kanna_dark_secondary.png"_spr;
		case 3:
			return "kanna_dark.png"_spr;
		case 4:
			return "mai_dark.png"_spr;
		case 5:
			return "ram.png"_spr;
		case 6:
			return "rem.png"_spr;
		case 7:
			return "rias_dark.png"_spr;
		case 8:
			return "yuno_dark.png"_spr;
		case 9:
			return "ryuko.png"_spr;
		case 10:
			return "nagatoro_dark.png"_spr;
		default:
			return "blank.png"_spr;
	}
}

class $modify(EditorPauseLayer) {
	void onExitNoSave(CCObject* sender) {
		if (auto dokiTheme = getDoki()) {
			dokiTheme->setVisible(true);
		}
		EditorPauseLayer::onExitNoSave(sender);
	}
	void onSaveAndExit(CCObject* sender) {
		if (auto dokiTheme = getDoki()) {
			dokiTheme->setVisible(true);
		}
		EditorPauseLayer::onSaveAndExit(sender);
	}
	void onSaveAndPlay(CCObject* sender) {
		if (auto dokiTheme = getDoki()) {
			dokiTheme->setVisible(Mod::get()->getSettingValue<bool>("ShowStickerInLevel"));
		}
		EditorPauseLayer::onSaveAndPlay(sender);
	}
	void onResume(CCObject* sender) {
		if (auto dokiTheme = getDoki()) {
			dokiTheme->setVisible(Mod::get()->getSettingValue<bool>("ShowStickerInEditor"));
		}
		EditorPauseLayer::onResume(sender);
	}
};

class $modify(LevelEditorLayer) {
	bool init(GJGameLevel* p0, bool p1) {
		if (!LevelEditorLayer::init(p0, p1)) {
			return false;
		}

		auto sceneManager = SceneManager::get();
		auto scene = CCScene::get();

		if (!Mod::get()->getSettingValue<bool>("ShowStickerInEditor")) {
			getDoki()->setVisible(false);
		}

		if (!Mod::get()->getSettingValue<bool>("ShowBackgroundInEditor")) {
			return true;
		}

		if (Mod::get()->getSettingValue<bool>("ShowBackgroundInEditor")) {
			auto mainNode = this->getChildByID("EditorUI");
			auto sticker = CCSprite::createWithSpriteFrameName(getBackground().c_str());
	
			sticker->setPosition(ccp(mainNode->getScaledContentSize().width / 2.f, mainNode->getScaledContentSize().height / 1.5f));
			sticker->setContentSize(mainNode->getScaledContentSize()); // fucking idk if this works but look at it
			sticker->setZOrder(-60);
			sticker->setOpacity(Mod::get()->getSettingValue<int64_t>("TransparencySliderEditor"));
			sticker->setID("doki-background"_spr);
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
			mainNode->addChild(sticker);
		}
		
		if (!Mod::get()->getSettingValue<bool>("ShowStickerInEditor") && getDoki()) {
			getDoki()->setVisible(false);
		}
		
		return true;
	}
};

class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		auto sceneManager = SceneManager::get();

		if (CCScene::get()->getChildByID("doki-theme-gd"_spr)) {
			sceneManager->forget(CCScene::get()->getChildByID("doki-theme-gd"_spr));
			CCScene::get()->removeChildByID("doki-theme-gd"_spr);
		}

		auto director = CCDirector::get();

		auto menu = CCMenu::create();
		menu->setID("doki-theme-gd"_spr);
		menu->setPosition({.0f, .0f});

		auto stickerNode = CCNode::create();
		stickerNode->setID("sticker-node"_spr);

		auto sticker = CCSprite::createWithSpriteFrameName(getSticker().c_str());
		sticker->setOpacity(Mod::get()->getSettingValue<int64_t>("TransparencySliderLevel") * 5);
		sticker->setID("doki-sticker"_spr);
		sticker->setPosition({director->getWinSize().width * (Mod::get()->getSettingValue<int64_t>("xPosPercent") / 100.f), director->getWinSize().height * (Mod::get()->getSettingValue<int64_t>("yPosPercent") / 100.f)});
		sticker->setScale(Mod::get()->getSettingValue<double>("Scale"));
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

		stickerNode->addChild(sticker);
		menu->addChild(stickerNode);
		this->addChild(menu);

		sceneManager->keepAcrossScenes(menu);
		return true;
	}
};

class $modify(PlayLayer) {
	bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
		if (!PlayLayer::init(level, useReplay, dontCreateObjects)) { return false; }
		if (!Mod::get()->getSettingValue<bool>("ShowStickerInLevel") && getDoki()) {
			getDoki()->setVisible(false);
		}
		return true;
	}
	void onQuit() {
		if (auto dokiTheme = getDoki()) {
			dokiTheme->setVisible(true);
		}
		PlayLayer::onQuit();
	}
};
