#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 300;
void drawing(SDL_Renderer *renderer, TTF_Font *font, struct tm *start_info) {
	SDL_Color textColor = {255, 255, 255, 255};
    SDL_RenderClear(renderer);
    double time_1 = 46;
	double time_2 = 84;
	double time_3 = 113;
	static double x = 0.0;
	char buffer[100];
	int progress;
	SDL_Delay(100);
	printf("Fixed-point (%%f): %.2f\n", x);


    SDL_Rect textRect;
    SDL_Rect bar_bg = { 0, 50, 400, 30 };  // x, y, width, height
	x = x + 0.1;
    if((int)0 < (int)x && (int)x <= (int)time_1) {
    	progress = x * 100 / time_1;  // progress: 0 to 100

    }
    if((int)time_1 < (int)x && (int)x <= (int)time_2) {
    	progress = (x - time_1) * 100 / (time_2 - time_1);  // progress: 0 to 100

    }
    if((int)time_2 < (int)x && (int)x <= (int)time_3) {
    	progress = (x - time_2) * 100 / (time_3 - time_2);  // progress: 0 to 100

    }



    snprintf(buffer, sizeof(buffer), "%d", progress);
	SDL_Rect bar_fg = { 0, 50, progress * 4, 30 };
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &bar_bg);
    SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
    SDL_RenderFillRect(renderer, &bar_fg);
	if((int)x == (int)time_1) {
		printf("Tequilla!!");
		SDL_Surface *textSurface1 = TTF_RenderText_Solid(font, "Tequilla!!", textColor);
	    textRect.x = (WINDOW_WIDTH - textSurface1->w) / 2 - 100; // Center horizontally
	    textRect.y = (WINDOW_HEIGHT - textSurface1->h) / 2 - 200; // Center vertically
	    textRect.w = 200; // Width of the text
	    textRect.h = 200; // Height of the text
	    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface1);
	    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	}
	if((int)x == (int)time_2) {
		printf("Tequilla!!");
		SDL_Surface *textSurface1 = TTF_RenderText_Solid(font, "Tequilla!!", textColor);
	    textRect.x = (WINDOW_WIDTH - textSurface1->w) / 2 - 100; // Center horizontally
	    textRect.y = (WINDOW_HEIGHT - textSurface1->h) / 2 - 200; // Center vertically
	    textRect.w = 200; // Width of the text
	    textRect.h = 200; // Height of the text
	    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface1);
	    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	}
	if((int)x == (int)time_3) {
		printf("Tequilla!!");
		SDL_Surface *textSurface1 = TTF_RenderText_Solid(font, "Tequilla!!1!!1!!", textColor);
	    textRect.x = (WINDOW_WIDTH - textSurface1->w) / 2 - 100; // Center horizontally
	    textRect.y = (WINDOW_HEIGHT - textSurface1->h) / 2 - 200; // Center vertically
	    textRect.w = 200; // Width of the text
	    textRect.h = 200; // Height of the text
	    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface1);
	    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	}
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, buffer, textColor);
    if (!textSurface) {
        printf("Unable to render text surface! TTF_Error: %s\n", TTF_GetError());
        exit(1);
    }
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    textRect.x = (WINDOW_WIDTH - textSurface->w) / 2 - 50; // Center horizontally
    textRect.y = (WINDOW_HEIGHT - textSurface->h) / 2 - 50; // Center vertically
    textRect.w = 200; // Width of the text
    textRect.h = 200; // Height of the text
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderPresent(renderer);




	if((int)x == (int)time_3) {
		SDL_Delay(5000);

		exit(0);
	}
}





int main(int argc, char *argv[]) {
    time_t start_time = time(NULL);
    struct tm *start_info = localtime(&start_time);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0) {
        printf("TTF_Init failed! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! Mix_Error: %s\n", Mix_GetError());
        return 1;
    }
    Mix_Music *bgMusic = Mix_LoadMUS("tequila.mp3");
    if (!bgMusic) {
        printf("Failed to load music! Mix_Error: %s\n", Mix_GetError());
        return 1;
    }
    Mix_PlayMusic(bgMusic,1); // -1 means loop indefinitely


    SDL_Window *window = SDL_CreateWindow("Clock", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 24); // Replace with your font file
    if (!font) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        drawing(renderer, font, start_info); // 1 frame per second
    }

    Mix_FreeMusic(bgMusic);
    Mix_CloseAudio();
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
