#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>

#define ASSETS_JSON_URL "https://limegradient.github.io/doki-theme-assets/doki-assets.json"

class DokiManager {
public:
    class DokiAsset {
    public:
        std::string name;
        std::string url;

        DokiAsset(std::string name, std::string url) {
            this->name = name;
            this->url = url;
        }
    };

    static DokiManager* get() {
        static DokiManager instance;
        return &instance;
    }

    std::vector<DokiAsset> getStickers();
    std::vector<DokiAsset> getWallpapers();

    void cacheAssets();

protected:
    void parseJSONResponse(geode::utils::web::WebResponse res, std::string assetType, std::vector<DokiAsset>* parent);

    geode::async::TaskHolder<geode::utils::web::WebResponse> webListener;
    std::vector<DokiAsset> stickerCache;
    std::vector<DokiAsset> wallpaperCache;
};