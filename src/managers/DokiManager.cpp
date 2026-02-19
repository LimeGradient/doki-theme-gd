#include "DokiManager.hpp"

using namespace geode::prelude;

std::vector<DokiManager::DokiAsset> DokiManager::getStickers() {
    return this->stickerCache;
}

std::vector<DokiManager::DokiAsset> DokiManager::getWallpapers() {
    return this->wallpaperCache;
}

void DokiManager::parseJSONResponse(web::WebResponse res, std::string assetType, std::vector<DokiManager::DokiAsset>* parent) {
    auto json = res.json();
    if (json.isOk()) {
        auto data = json.ok().value();
        for (auto asset : data[assetType]) {
            parent->push_back(DokiAsset(
                asset.getKey().value(),
                asset.asString().unwrap()
            ));
        }
    }
}

void DokiManager::cacheAssets() {
    this->stickerCache.clear();
    this->wallpaperCache.clear();

    web::WebRequest req = web::WebRequest();
    this->webListener.spawn(
        req.get(ASSETS_JSON_URL),
        [this](web::WebResponse res) mutable {
            this->parseJSONResponse(res, "stickers", &this->stickerCache);
            this->parseJSONResponse(res, "wallpapers", &this->wallpaperCache);
        }
    );
}