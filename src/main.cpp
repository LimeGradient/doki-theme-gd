#include <Geode/Geode.hpp>

#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CCDirector.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>

using namespace geode::prelude;

std::string getSticker() {
	auto value = Mod::get()->getSettingValue<int64_t>("StickerSlider");
	switch (value) {
		case 1:
			return "ishtar_onyx_spicy.png"_spr;
		case 2:
			return "kanna_dark_secondary.png"_spr;
		case 3:
			return "kanna_dark.png"_spr;
		case 4:
			return "mai_dark_spicy.png"_spr;
		case 5:
		 	return "mai_dark.png"_spr;
		case 6:
			return "ram.png"_spr;
		case 7:
			return "rem.png"_spr;
		case 8:
			return "rias_dark.png"_spr;
		case 9:
			return "rias_onyx_spicy.png"_spr;
		case 10:
			return "ryuko.png"_spr;
		default:
			return "ram.png"_spr;
	}
}

class $modify(DokiEditorLayer, LevelEditorLayer) {
	bool init(GJGameLevel* p0, bool p1) {
		if (!LevelEditorLayer::init(p0, p1)) {
			return false;
		}

		auto director = CCDirector::get();

		auto mainNode = this->getChildByID("EditorUI");
		auto sticker = CCSprite::createWithSpriteFrameName(getSticker().c_str());

		sticker->setPosition(ccp(mainNode->getScaledContentSize().width / 2.f, mainNode->getScaledContentSize().height / 1.5f));
		sticker->setOpacity(75);
		sticker->setScale(3.5f);
		sticker->setZOrder(-60);
		sticker->setID("doki-sticker");
		mainNode->addChild(sticker);
		return true;
	}
};

class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		auto sceneManager = SceneManager::get();

		if (CCScene::get()->getChildByID("doki-theme-gd")) {
			sceneManager->forget(CCScene::get()->getChildByID("doki-theme-gd"));
			CCScene::get()->removeChildByID("doki-theme-gd");
		}

		auto director = CCDirector::get();

		auto menu = CCMenu::create();
		menu->setID("doki-theme-gd");

		auto stickerNode = CCNode::create();
		stickerNode->setID("sticker-node");

		auto sticker = CCSprite::createWithSpriteFrameName(getSticker().c_str());
		sticker->setID("doki-sticker");
		menu->setPosition(ccp(0.f, 0.f));
		sticker->setPosition(ccp(director->getScreenRight() - 27.f, director->getScreenBottom() + 46.f));
		sticker->setScale(1.5f);

		stickerNode->addChild(sticker);
		menu->addChild(stickerNode);
		this->addChild(menu);

		sceneManager->keepAcrossScenes(menu);
		return true;
	}
};
