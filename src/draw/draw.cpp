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
    SDL_SetRenderDrawColor(app.renderer, 0, 57, 109, 255);
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
    SDL_SetRenderDrawColor(app.renderer, 0, 57, 109, 255);
    SDL_RenderClear(app.renderer);  // Clear screen with that color

    // Now render the texture (which contains everything) to the screen with rotation

    SDL_Rect destRect = {0, 0, (int)BACKGROUND_WIDTH, (int)BACKGROUND_HEIGHT};
    int offsetX = (app.screenWidth - BACKGROUND_WIDTH) / 2;
    int offsetY = (app.screenHeight - BACKGROUND_HEIGHT) / 2;
    destRect.x = offsetX;
    destRect.y = offsetY;
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

void drawVector(Application& app, float startX, float startY, float dirX, float dirY, float length, SDL_Color color){
    float endX = startX + dirX * length;
    float endY = startY + dirY * length;
    drawArrow(app, startX, startY, endX, endY, color);
}

void drawArrow(Application& app, float startX, float startY, float endX, float endY, SDL_Color color){
    // Draw main line
    SDL_SetRenderDrawColor(app.renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(app.renderer, (Sint16)startX, (Sint16)startY, (Sint16)endX, (Sint16)endY);

    // Calculate arrow head
    float dx = endX - startX;
    float dy = endY - startY;
    float length = sqrt(dx*dx + dy*dy);

    if (length > 0) {
        // Normalize direction
        dx /= length;
        dy /= length;

        // Arrow head size
        float headLength = 10.0f;
        float headAngle = M_PI / 6; // 30 degrees

        // Calculate arrow head points
        float headX1 = endX - headLength * (dx * cos(headAngle) - dy * sin(headAngle));
        float headY1 = endY - headLength * (dy * cos(headAngle) + dx * sin(headAngle));
        float headX2 = endX - headLength * (dx * cos(-headAngle) - dy * sin(-headAngle));
        float headY2 = endY - headLength * (dy * cos(-headAngle) + dx * sin(-headAngle));

        // Draw arrow head
        SDL_SetRenderDrawColor(app.renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(app.renderer, (Sint16)endX, (Sint16)endY, (Sint16)headX1, (Sint16)headY1);
        SDL_RenderDrawLine(app.renderer, (Sint16)endX, (Sint16)endY, (Sint16)headX2, (Sint16)headY2);
    }
}

double evaluateBezier (double *data, int ndata, double t)
{
    double mu, result;
    int n,k,kn,nn,nkn;
    double blend,muk,munk;

    /* Sanity check bounds */
    if (t<0.0) {
        return(data[0]);
    }
    if (t>=(double)ndata) {
        return(data[ndata-1]);
    }

    /* Adjust t to the range 0.0 to 1.0 */
    mu=t/(double)ndata;

    /* Calculate interpolate */
    n=ndata-1;
    result=0.0;
    muk = 1;
    munk = pow(1-mu,(double)n);
    for (k=0;k<=n;k++) {
        nn = n;
        kn = k;
        nkn = n - k;
        blend = muk * munk;
        muk *= mu;
        munk /= (1-mu);
        while (nn >= 1) {
            blend *= nn;
            nn--;
            if (kn > 1) {
                blend /= (double)kn;
                kn--;
            }
            if (nkn > 1) {
                blend /= (double)nkn;
                nkn--;
            }
        }
        result += data[k] * blend;
    }

    return (result);
}

int bezierRGBASDL(SDL_Renderer *renderer, std::vector<SDL_Point> points, int s, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    int n = points.size();

    // Create arrays for x and y coordinates
    std::vector<Sint16> vx(n);
    std::vector<Sint16> vy(n);

    // Extract x and y from SDL_Points
    for (int i = 0; i < n; i++) {
        vx[i] = static_cast<Sint16>(points[i].x);
        vy[i] = static_cast<Sint16>(points[i].y);
    }

    // Call the original function
    return bezierRGBA(renderer, vx.data(), vy.data(), n, s, r, g, b, a);
}


int bezierRGBA(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy, int n, int s, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    int result;
    int i;
    double *x, *y, t, stepsize;
    Sint16 x1, y1, x2, y2;

    /*
    * Sanity check
    */
    if (n < 3) {
        return (-1);
    }
    if (s < 2) {
        return (-1);
    }

    /*
    * Variable setup
    */
    stepsize=(double)1.0/(double)s;

    /* Transfer vertices into float arrays */
    if ((x=(double *)malloc(sizeof(double)*(n+1)))==NULL) {
        return(-1);
    }
    if ((y=(double *)malloc(sizeof(double)*(n+1)))==NULL) {
        free(x);
        return(-1);
    }
    for (i=0; i<n; i++) {
        x[i]=(double)vx[i];
        y[i]=(double)vy[i];
    }
    x[n]=(double)vx[0];
    y[n]=(double)vy[0];

    /*
    * Set color
    */
    result = 0;
    result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
    result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

    /*
    * Draw
    */
    t=0.0;
    x1=(Sint16)lrint(evaluateBezier(x,n+1,t));
    y1=(Sint16)lrint(evaluateBezier(y,n+1,t));
    for (i = 0; i <= (n*s); i++) {
        t += stepsize;
        x2=(Sint16)evaluateBezier(x,n,t);
        y2=(Sint16)evaluateBezier(y,n,t);
        result |= SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        x1 = x2;
        y1 = y2;
    }

    /* Clean up temporary array */
    free(x);
    free(y);

    return (result);
}

