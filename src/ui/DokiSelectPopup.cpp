#include "DokiSelectPopup.hpp"

using namespace geode::prelude;

#define WIDTH 200.f
#define HEIGHT 200.f

DokiSelectPopup* DokiSelectPopup::create(std::span<geode::Ref<DokiNode>> selections) {
	DokiSelectPopup* ret = new DokiSelectPopup();
	if (ret->init(selections)) {
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}

bool DokiSelectPopup::init(std::span<geode::Ref<DokiNode>> selections) {
    if (!Popup::init(WIDTH * 1.5, HEIGHT * 1.25)) {
        return false;
    }

	m_currentPage = 0;

	this->setTitle("Lily's Totally Epic Paginated Popup");

	m_selectionsContainer = CCNode::create();
	m_selectionsContainer->setContentSize(this->m_mainLayer->getContentSize() * .9f);
	m_selectionsContainer->setAnchorPoint({.5f, .5f});
	m_selectionsContainer->setScale(.9f);

	for (Ref<DokiNode> selection : selections) {
		if (!selection) continue;
		m_totalPages++;
		m_selections.push_back(selection);
		m_selectionsContainer->addChildAtPosition(selection, Anchor::Center);
		selection->setScale(.85f * std::min<float>(WIDTH / selection->getContentWidth(), HEIGHT / selection->getContentHeight()));
		selection->setVisible(false);
	}

	if (m_selections.at(m_currentPage)) m_selections.at(m_currentPage)->setVisible(true);

	this->m_mainLayer->addChildAtPosition(m_selectionsContainer, Anchor::Center);

	m_arrowNavMenu = CCMenu::create();
	m_arrowNavMenu->setContentWidth(WIDTH * 1.45f);

	m_prevArrow = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"), this, menu_selector(DokiSelectPopup::prevPage));
	m_arrowNavMenu->addChild(m_prevArrow);

	CCSprite* nxtArwSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
	nxtArwSpr->setFlipX(true);

	m_nextArrow = CCMenuItemSpriteExtra::create(nxtArwSpr, this, menu_selector(DokiSelectPopup::nextPage));
	m_arrowNavMenu->addChild(m_nextArrow);

	m_arrowNavMenu->setLayout(RowLayout::create()->setAutoScale(true)->setGap(WIDTH * 1.4f)->setDefaultScaleLimits(.0001f, 1.f));
	this->m_mainLayer->addChildAtPosition(m_arrowNavMenu, Anchor::Center);

	this->m_buttonMenu->addChildAtPosition(CCMenuItemSpriteExtra::create(ButtonSprite::create("Select"), this, menu_selector(DokiSelectPopup::selcPage)), Anchor::Bottom, {0.f, 25.f});

	return true;
}

void DokiSelectPopup::prevPage(CCObject*) {
	DokiSelectPopup::goToPage((m_currentPage == 0) ? m_selections.size() - 1 : m_currentPage - 1);
}

void DokiSelectPopup::nextPage(CCObject*) {
	DokiSelectPopup::goToPage((m_currentPage == m_selections.size() - 1) ? 0 : m_currentPage + 1);
}

void DokiSelectPopup::goToPage(const int page) {
	for (CCNode* selection : m_selections) if (selection) selection->setVisible(false);
	if (m_selections.at(page)) m_selections.at(page)->setVisible(true);
	m_currentPage = page;
}

void DokiSelectPopup::selcPage(CCObject *) {
	if (!m_selections.at(m_currentPage)) return;
	Notification::create(fmt::format("Selected page {} of type {}!", m_currentPage, geode::cocos::getObjectName(m_selections.at(m_currentPage))), NotificationIcon::Info)->show();
}

void DokiSelectPopup::keyDown(const cocos2d::enumKeyCodes key, double p1) {
	if (key == enumKeyCodes::KEY_Left || key == enumKeyCodes::KEY_ArrowLeft) return DokiSelectPopup::prevPage(nullptr);
	if (key == enumKeyCodes::KEY_Right || key == enumKeyCodes::KEY_ArrowRight) return DokiSelectPopup::nextPage(nullptr);
	Popup::keyDown(key, p1);
}