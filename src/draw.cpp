#include <draw.h>

void prepareScene(Application & app){
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);
}

void presentScene(Application & app){
    SDL_RenderPresent(app.renderer);
}

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

	SDL_RenderCopyEx(app.renderer, atlasImage->texture, &atlasImage->rect, &dest, angle, NULL, flip);
}