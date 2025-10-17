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

/**
 * @name` presentScene
 * @brief Presents the rendered scene to the screen
 * @param app Application struct reference
 */
void presentScene(Application & app){
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