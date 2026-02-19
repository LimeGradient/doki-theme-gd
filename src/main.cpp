#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>

#include "managers/DokiManager.hpp"
#include "ui/DokiSelectPopup.hpp"
#include "ui/DokiNode.hpp"

class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		DokiManager::get()->cacheAssets();

		auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png"),
			this,
			menu_selector(MyMenuLayer::onMyButton)
		);

		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(myButton);

		myButton->setID("my-button"_spr);

		menu->updateLayout();

		return true;
	}

	void onMyButton(CCObject*) {
		auto stickers = DokiManager::get()->getStickers();
		std::vector<geode::Ref<DokiNode>> nodes;
		for (auto sticker : stickers) {
			nodes.push_back(DokiNode::create(sticker));
		}
		DokiSelectPopup::create(nodes)->show();
	}
};
