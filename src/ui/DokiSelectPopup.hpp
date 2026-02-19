#pragma once

#include <Geode/Geode.hpp>

#include "DokiNode.hpp"

class DokiSelectPopup final : public geode::Popup {
public:
	static DokiSelectPopup* create(std::span<geode::Ref<DokiNode>>);
protected:
	bool init(std::span<geode::Ref<DokiNode>>);
	void selcPage(cocos2d::CCObject*);
	void prevPage(cocos2d::CCObject*);
	void nextPage(cocos2d::CCObject*);
	void goToPage(const int);
	void keyDown(const cocos2d::enumKeyCodes key, double p1) override;

	int m_currentPage = 0;
	int m_totalPages = 0;
	cocos2d::CCMenu* m_arrowNavMenu {};
	CCMenuItemSpriteExtra* m_prevArrow {};
	CCMenuItemSpriteExtra* m_nextArrow {};
	cocos2d::CCNode* m_selectionsContainer {};
	std::vector<geode::Ref<DokiNode>> m_selections;
};