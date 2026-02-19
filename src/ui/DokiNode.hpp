#pragma once

#include <Geode/Geode.hpp>

#include "managers/DokiManager.hpp"

class DokiNode : public cocos2d::CCNode {
public:
    static DokiNode* create(DokiManager::DokiAsset asset);
protected:
    bool init(DokiManager::DokiAsset asset);
};