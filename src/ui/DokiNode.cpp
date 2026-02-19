#include "DokiNode.hpp"

using namespace geode::prelude;

DokiNode* DokiNode::create(DokiManager::DokiAsset asset) {
    DokiNode* ret = new DokiNode();
    if (ret->init(asset)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool DokiNode::init(DokiManager::DokiAsset asset) {
    if (!CCNode::init()) {
        return false;
    }

    this->setContentSize({200, 200});
    this->setAnchorPoint({0.5f, 0.5f});

    auto layout = ColumnLayout::create()
        ->setDefaultScaleLimits(.1f, 1.f)
        ->setAxisAlignment(AxisAlignment::Start)
        ->setAxisReverse(true)
        ->setAutoScale(false);

    CCMenu* menu = CCMenu::create();
    menu->setLayout(layout);
    menu->setContentSize(CCSize{200, 200});

    this->addChildAtPosition(menu, Anchor::Center);

    LazySprite* spriteAsset = LazySprite::create({200, 200});
    spriteAsset->loadFromUrl(asset.url, LazySprite::Format::kFmtPng, true);
    menu->addChild(spriteAsset);

    CCLabelBMFont* spriteName = CCLabelBMFont::create(asset.name.c_str(), "bigFont.fnt");
    spriteName->setScale(0.65f);
    menu->addChild(spriteName);

    menu->updateLayout();
    spriteAsset->setScale(2.5f);

    return true;
}