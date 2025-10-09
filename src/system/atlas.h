#ifndef FLAPPY_BIRD_SDL2_ATLAS_H
#define FLAPPY_BIRD_SDL2_ATLAS_H
#include <system/common.h>
#include <draw/textures.h>
#ifndef ATLAS_FILE_PATH
#define ATLAS_FILE_PATH "data/atlas.json"
#endif
#ifndef TEXT_FILE_PATH
#define TEXT_FILE_PATH DATA_DIR "/text.json"
#endif
#ifndef ATLAS_PNG_PATH
#define ATLAS_PNG_PATH GFX_DIR "/atlas.png"
#endif
#ifndef TEXT_PNG_PATH
#define TEXT_PNG_PATH GFX_DIR "/text.png"
#endif

void initAtlas(Application & app);
AtlasImage* getAtlasImage(Application & app, const std::string & filename, bool required = true);

#endif //FLAPPY_BIRD_SDL2_ATLAS_H