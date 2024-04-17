#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CCDirector.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		auto director = CCDirector::get();

		auto menu = CCMenu::create();
		auto stickerNode = CCNode::create();
		auto sticker = CCSprite::createWithSpriteFrameName("mai_dark.png"_spr);
		menu->setPosition(ccp(0.f, 0.f));
		sticker->setPosition(ccp(director->getScreenRight() - 27.f, director->getScreenBottom() + 30.f));
		sticker->setScale(1.5f);
		stickerNode->addChild(sticker);
		menu->addChild(stickerNode);
		this->addChild(menu);

		SceneManager::get()->keepAcrossScenes(menu);
		return true;
	}
};
