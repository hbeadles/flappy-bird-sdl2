#include <system/atlas.h>
#include <boost/json.hpp>
#include <boost/system/error_code.hpp>

namespace jb = boost::json;
SDL_Texture* texture;
SDL_Texture* textTexture;
static void loadAtlasData(Application & app);
static void loadAtlasData(Application & app, std::string filename, SDL_Texture* texture);
void initAtlas(Application & app) {
    texture = loadTexture(app, ATLAS_PNG_PATH);
    textTexture = loadTexture(app, TEXT_PNG_PATH);
    loadAtlasData(app);

}

AtlasImage* getAtlasImage(Application & app, const std::string& filename, bool required){
    if(app.atlas.find(filename) == app.atlas.end()){
        if(required){
            printf("Error: Atlas image not found: %s\n", filename.c_str());
            throw std::runtime_error("Atlas image not found: " + filename);
        }
        return nullptr;
    }
    return app.atlas[filename];
}



static void loadAtlasData(Application & app){
    std::ifstream infile (ATLAS_FILE_PATH);
    if (!infile.is_open()) {
        printf("Error: Could not open atlas file: %s\n", ATLAS_FILE_PATH);
        return;
    }
    boost::system::error_code ec;
    jb::value parsed = jb::parse(infile, ec);
    if(ec){
        printf("Error parsing atlas file: %s\n", ec.message().c_str());
        return;
    }
    jb::array atlas = parsed.as_array();
    for(const auto& item : atlas){
        jb::object obj = item.as_object();
        std::string filename = static_cast<std::string>(obj["filename"].as_string());
        int x = obj["x"].as_int64();
        int y = obj["y"].as_int64();
        int w = obj["w"].as_int64();
        int h = obj["h"].as_int64();
        int rotated = obj["rotated"].as_int64();
        AtlasImage* atlasImage = new AtlasImage();
        atlasImage->rect = {x, y, w, h};
        atlasImage->rotated = rotated;
        atlasImage->texture = texture;
        app.atlas[filename] = atlasImage;
    }

}

static void loadAtlasData(Application & app, std::string filename, SDL_Texture* texture){
    std::ifstream infile (filename);
    if (!infile.is_open()) {
        printf("Error: Could not open atlas file: %s\n", filename.c_str());
        return;
    }
    boost::system::error_code ec;
    jb::value parsed = jb::parse(infile, ec);
    if(ec){
        printf("Error parsing atlas file: %s\n", ec.message().c_str());
        return;
    }
    jb::array atlas = parsed.as_array();
    for(const auto& item : atlas){
        jb::object obj = item.as_object();
        std::string filename = static_cast<std::string>(obj["filename"].as_string());
        int x = obj["x"].as_int64();
        int y = obj["y"].as_int64();
        int w = obj["w"].as_int64();
        int h = obj["h"].as_int64();
        int rotated = obj["rotated"].as_int64();
        AtlasImage* atlasImage = new AtlasImage();
        atlasImage->rect = {x, y, w, h};
        atlasImage->rotated = rotated;
        atlasImage->texture = texture;
        app.atlas[filename] = atlasImage;
    }
}
