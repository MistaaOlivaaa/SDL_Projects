#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define GRAVITY 0.5f
#define BOUNCE_DAMPING 0.8f
#define FRICTION 0.99f
#define FPS 60
#define FRAME_DELAY (1000 / FPS)

struct Circle {
    float x;
    float y;
    int radius;
    float v_x;
    float v_y;
};

void DrawFilledCircle(SDL_Surface *surface, struct Circle circle, Uint32 color) {
    if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);

    Uint32 *pixels = (Uint32*)surface->pixels;
    int pitch = surface->pitch / 4;

    int cx = (int)circle.x;
    int cy = (int)circle.y;
    int r = circle.radius;

    int minX = fmax(0, cx - r);
    int maxX = fmin(WIDTH - 1, cx + r);
    int minY = fmax(0, cy - r);
    int maxY = fmin(HEIGHT - 1, cy + r);

    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            int dx = x - cx;
            int dy = y - cy;
            if (dx * dx + dy * dy <= r * r) {
                pixels[y * pitch + x] = color;
            }
        }
    }

    if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
}

void UpdateBall(struct Circle *circle) {
    circle->v_y += GRAVITY;
    circle->v_x *= FRICTION;
    circle->v_y *= FRICTION;

    circle->x += circle->v_x;
    circle->y += circle->v_y;

    // Bounce logic
    if (circle->x - circle->radius < 0) {
        circle->x = circle->radius;
        circle->v_x = -circle->v_x * BOUNCE_DAMPING;
    } else if (circle->x + circle->radius > WIDTH) {
        circle->x = WIDTH - circle->radius;
        circle->v_x = -circle->v_x * BOUNCE_DAMPING;
    }

    if (circle->y - circle->radius < 0) {
        circle->y = circle->radius;
        circle->v_y = -circle->v_y * BOUNCE_DAMPING;
    } else if (circle->y + circle->radius > HEIGHT) {
        circle->y = HEIGHT - circle->radius;
        circle->v_y = -circle->v_y * BOUNCE_DAMPING;
    }
}

int main(int argc, char* argv[]) {
    printf("Bouncy Ball Simulation Starting...\n");

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
    SDL_SetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION, "0");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Bouncy Ball - Software Rendering",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WIDTH, HEIGHT,
                                          SDL_WINDOW_SHOWN);

    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
    if (!screenSurface) {
        printf("Could not get window surface! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Seed RNG
    srand((unsigned int)time(NULL));

    struct Circle ball = {
        .x = WIDTH / 2.0f,
        .y = HEIGHT / 4.0f,
        .radius = 30,
        .v_x = 7.0f,
        .v_y = 3.0f
    };

    Uint32 backgroundColor = SDL_MapRGB(screenSurface->format, 0, 0, 0);
    Uint32 ballColor = SDL_MapRGB(screenSurface->format, 255, 100, 100);

    SDL_Event event;
    int running = 1;

    printf("Starting main loop...\n");
    printf("Controls:\n");
    printf("- Click to move ball to mouse position\n");
    printf("- SPACE to boost ball upward\n");
    printf("- R to reset ball\n");
    printf("- ESC or close window to quit\n");

    while (running) {
        Uint64 frameStart = SDL_GetTicks64();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                ball.x = event.button.x;
                ball.y = event.button.y;
                ball.v_x = ((rand() % 11) - 5) * 2.0f;
                ball.v_y = ((rand() % 11) - 5) * 2.0f;
                if (ball.v_x == 0) ball.v_x = 1.0f;
                if (ball.v_y == 0) ball.v_y = 1.0f;
                printf("Ball moved to (%d, %d)\n", event.button.x, event.button.y);
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        ball.v_y -= 15.0f;
                        printf("Ball boosted upward\n");
                        break;
                    case SDLK_r:
                        ball.x = WIDTH / 2.0f;
                        ball.y = HEIGHT / 4.0f;
                        ball.v_x = 7.0f;
                        ball.v_y = 3.0f;
                        printf("Ball reset\n");
                        break;
                    case SDLK_ESCAPE:
                        running = 0;
                        break;
                }
            }
        }

        UpdateBall(&ball);

        SDL_FillRect(screenSurface, NULL, backgroundColor);
        DrawFilledCircle(screenSurface, ball, ballColor);
        SDL_UpdateWindowSurface(window);

        int frameTime = (int)(SDL_GetTicks64() - frameStart);
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    printf("Simulation ended successfully.\n");
    return 0;
}
