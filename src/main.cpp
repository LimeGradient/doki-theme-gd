#include <Geode/Geode.hpp>

#include <Geode/modify/CCDirector.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>

using namespace geode::prelude;

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
		default:
			return "blank.png"_spr;
	}
}

std::string getSticker() {
	auto value = Mod::get()->getSettingValue<int64_t>("StickerSlider");
	switch (value) {
		case 1:
			return "kanna_dark_secondary.png"_spr;
		case 2:
			return "kanna_dark_secondary.png"_spr;
		case 3:
			return "kanna_dark.png"_spr;
		case 4:
			return "mai_dark_spicy.png"_spr;
		case 5:
			return "ram.png"_spr;
		case 6:
			return "rem.png"_spr;
		case 7:
			return "rias_dark.png"_spr;
		case 9:
			return "yuno_dark.png"_spr;
		case 10:
			return "ryuko.png"_spr;
		case 11:
			if (!std::filesystem::exists((Mod::get()->getConfigDir() / "custom.png").string())) {
				return "blank.png"_spr;
			} else {
				return (Mod::get()->getConfigDir() / "custom.png").string() + ""_spr;
			}
		default:
			return "blank.png"_spr;
	}
}

class $modify(EditorPauseLayer) {
	void onExitEditor(CCObject* sender) {
		EditorPauseLayer::onExitEditor(sender);
		if (auto dokiTheme = getDoki()) {
			dokiTheme->setVisible(true);
		}
	}
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
			dokiTheme->setVisible(false);
		}
		EditorPauseLayer::onResume(sender);
	}
};

class $modify(EditorPauseLayer) {
	void onExitEditor(CCObject* sender) {
		EditorPauseLayer::onExitEditor(sender);
		if (auto dokiTheme = getDoki()) {
			dokiTheme->setVisible(true);
		}
	}
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
			dokiTheme->setVisible(false);
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
			scene->getChildByID("doki-theme-gd")->setVisible(false);
		}

		if (!Mod::get()->getSettingValue<bool>("ShowBackgroundInEditor")) {
			return true;
		}

		if (Mod::get()->getSettingValue<bool>("ShowBackgroundInEditor")) {
			auto mainNode = this->getChildByID("EditorUI");
			auto sticker = CCSprite::createWithSpriteFrameName(getBackground().c_str());
	
			sticker->setPosition(ccp(mainNode->getScaledContentSize().width / 2.f, mainNode->getScaledContentSize().height / 1.5f));
			sticker->setOpacity(Mod::get()->getSettingValue<int64_t>("TransparencySliderEditor"));
			sticker->setScale(0.5f);
			sticker->setZOrder(-60);
			sticker->setOpacity(Mod::get()->getSettingValue<int64_t>("BackgroundSlider") * 5);
			sticker->setID("doki-sticker"_spr);
			mainNode->addChild(sticker);
		}
		
		if (!Mod::get()->getSettingValue<bool>("ShowStickerInEditor") && getDoki()) {
			getDoki()->setVisible(false);
		}
		
		return true;
	}

	void onExit() {
		auto scene = CCScene::get();

		if (!Mod::get()->getSettingValue<bool>("ShowStickerInEditor")) {
			scene->getChildByID("doki-theme-gd")->setVisible(true);
		}

		LevelEditorLayer::onExit();
	}
};

class $modify(PlayLayer) {
	bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
		if (!PlayLayer::init(level, useReplay, dontCreateObjects)) {
			return false;
		}

		auto scene = CCScene::get();

		if (!Mod::get()->getSettingValue<bool>("ShowStickerInLevel")) {
			 scene->getChildByID("doki-theme-gd")->setVisible(false);
		}

		return true;
	}

	void onQuit() {
		auto scene = CCScene::get();

		if (!Mod::get()->getSettingValue<bool>("ShowStickerInLevel")) {
			 scene->getChildByID("doki-theme-gd")->setVisible(true);
		}

		PlayLayer::onQuit();
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

		auto stickerNode = CCNode::create();
		stickerNode->setID("sticker-node"_spr);

		auto sticker = CCSprite::createWithSpriteFrameName(getSticker().c_str());
		sticker->setOpacity(Mod::get()->getSettingValue<int64_t>("TransparencySliderLevel") * 5);
		sticker->setID("doki-sticker"_spr);
		sticker->setPosition(ccp(director->getScreenRight() - 27.f, director->getScreenBottom() + 46.f));
		sticker->setScale(1.5f);
		sticker->setOpacity(Mod::get()->getSettingValue<int64_t>("TransparencySliderLevel") * 5);
		sticker->setID("doki-sticker");

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