#include <draw/draw.h>

/**
 * @name prepareScene
 * @brief Setups up rendering with a black color
 * @param app Application struct reference
 */
void prepareScene(Application & app){
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);
}

void prepareSceneWithCamera(Application& app) {
    SDL_SetRenderTarget(app.renderer, app.renderTarget);  // ← All rendering now goes to texture
    SDL_SetRenderDrawColor(app.renderer, 0, 255, 0, 255);
    SDL_RenderClear(app.renderer);
}


/**
 * @name` presentScene
 * @brief Presents the rendered scene to the screen
 * @param app Application struct reference
 */
void presentScene(Application & app){
    SDL_RenderPresent(app.renderer);
}

void presentSceneWithCamera(Application& app, float rotation, SDL_Point* center) {
    SDL_SetRenderTarget(app.renderer, nullptr);  // ← Switch back to rendering to screen

    // Now render the texture (which contains everything) to the screen with rotation

    SDL_Rect destRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    int result = SDL_RenderCopyEx(
        app.renderer,
        app.renderTarget,  // The texture containing all your game graphics
        nullptr,
        &destRect,
        rotation,
        center,
        SDL_FLIP_NONE
    );
    if (result != 0) {
        printf("SDL_RenderCopyEx failed: %s\n", SDL_GetError());
    }
    
    SDL_RenderPresent(app.renderer);
}

/**
 * @name blit
 * @brief Renders a texture at the specified (x, y) coordinates with optional rotation and flipping.
 * @param app Application struct reference
 * @param texture Texture to render
 * @param x X coordinate on screen
 * @param y Y coordinate on screen
 * @param angle Rotation angle in degrees (default is 0)
 * @param flip SDL_RendererFlip value for flipping (default is SDL_FLIP_NONE)
 */
void blit(Application & app, SDL_Texture* texture, int x, int y, double angle, SDL_RendererFlip flip) {

    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    if (angle != 0) {
        // Calculate center point for rotation
        SDL_Point center = {dest.w / 2, dest.h / 2};
        // Use RenderCopyEx for rotation
        SDL_RenderCopyEx(app.renderer, texture, NULL, &dest, angle, &center, flip);
    } else {
        // Use standard RenderCopy if no angle
        SDL_RenderCopy(app.renderer, texture, NULL, &dest);
    }

}

void blitEx(Application &app, SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *destRect, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(app.renderer, texture, srcRect, destRect, angle, center, flip);
}

void colorModulate(SDL_Texture *texture, Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetTextureColorMod(texture, r, g, b);
}


/**
 * @name blitAtlasImage
 * @brief Renders an AtlasImage at the specified (x, y) coordinates with optional centering, rotation, and flipping.
 * @param app Application struct reference
 * @param atlasImage AtlasImage to render
 * @param x X coordinate on screen
 * @param y Y coordinate on screen
 * @param center If true, centers the image at (x, y); otherwise, top-left aligns (default is false)
 * @param angle Rotation angle in degrees (default is 0)
 * @param flip SDL_RendererFlip value for flipping (default is SDL_FLIP_NONE)
 */
void blitAtlasImage(Application & app, AtlasImage* atlasImage, int x, int y, int center, double angle, SDL_RendererFlip flip){
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = atlasImage->rect.w;
    dest.h = atlasImage->rect.h;
    if (center)
	{
		dest.x -= dest.w / 2;
		dest.y -= dest.h / 2;
	}

	SDL_RenderCopyEx(app.renderer, atlasImage->texture, &atlasImage->srcRect, &dest, angle, NULL, flip);
}