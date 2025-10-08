//
// Created by Hayden Beadles on 10/5/25.
//
#include <init.h>

static int throw_sdl_error(const char* fmt);

/**
 *  Helper function to log SDL errors. SDL_LogError should be used instead
 * @param fmt
 * @return int - constant error code (3)
 */
static int throw_sdl_error(const char* fmt){
    SDL_LogError(
        SDL_LOG_CATEGORY_APPLICATION,
        fmt,
        SDL_GetError()
    );
    return 3;
}

bool initAudio() {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    Mix_AllocateChannels(MAX_SND_CHANNELS);
    return true;
}

/**
 * @name initSDL
 * @brief Initializes SDL, creates window and renderer, sets up ImGui context, and initializes SDL_image
 * @param app - Application struct reference
 * @param title  - Title of the window
 * @return boolean - true if successful, false otherwise
 */
bool initSDL(Application &app, const std::string& title){
    bool success= true;
#ifdef __EMSCRIPTEN__
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
        throw_sdl_error("Error initializing SDL");
        success= false;
    }
#else
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        throw_sdl_error("Error initializing video");
        success= false;
    }
#endif
    if (success){
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
            printf("Warning. Linear Texture filtering not enabled!");
        }
        app.window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                        (int) (SCREEN_WIDTH),
                        (int) (SCREEN_HEIGHT),
                        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (app.window == nullptr){
            throw_sdl_error("Create window failed %s");
            success = false;
        }else{
            app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (app.renderer == nullptr){
                throw_sdl_error("Error creating renderer %s");
                success = false;
            }else{

                SDL_SetRenderDrawColor(app.renderer, 0x00, 0x00, 0x00, 255);
                int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
                if (!(IMG_Init(imgFlags) & imgFlags)){
                    printf("SDL_image could not initialize, Error: %s", SDL_GetError());

                }

                if (!initAudio()) {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
            }
        }
    }
    if (success) {
        SDL_ShowCursor(SDL_DISABLE);
    }
    return success;
}

/**
 * Cleanup environment and app struct reference.
 * Cleanup ImGui, SDL renderer, and SDL window.
 * @param app - Application struct reference
 */
void cleanup(Application & app){
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    app.window = nullptr;
    app.renderer = nullptr;
    SDL_Quit();
    Mix_Quit();
}