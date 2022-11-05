#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

SDL_Event eventImage;

SDL_Window* window = SDL_CreateWindow("Hello SDL WORLD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

SDL_Surface* background = SDL_LoadBMP("./Graphics/background.bmp");

SDL_Surface* cursor = SDL_LoadBMP("");

SDL_Surface* quit = SDL_LoadBMP("./Graphics/QuitNotHovered.bmp");

SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);

SDL_Texture* quitTexture = SDL_CreateTextureFromSurface(renderer, quit);

SDL_Texture* cursorTexture = SDL_CreateTextureFromSurface(renderer, cursor);

int main(int argc, char* args[])
{

	SDL_FreeSurface(background);
	SDL_FreeSurface(quit);
	SDL_FreeSurface(cursor);

	SDL_Rect BackRect;
	BackRect.w = SCREEN_WIDTH;
	BackRect.h = SCREEN_HEIGHT;
	BackRect.x = 0;
	BackRect.y = 0;

	SDL_Rect QuitRect;
	QuitRect.w = 215;
	QuitRect.h = 129;
	QuitRect.x = SCREEN_WIDTH / 2 - QuitRect.w / 2;
	QuitRect.y = SCREEN_HEIGHT - SCREEN_HEIGHT / 5;

	SDL_Rect MouseRect;
	MouseRect.x = 0;
	MouseRect.y = 0;
	MouseRect.w = 50;
	MouseRect.h = 50;

	bool playing = true;

	bool QuitMin = false;

	SDL_SetWindowFullscreen(window, SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN ? 0 : SDL_WINDOW_FULLSCREEN);
	while (playing == true)
	{

		if (SDL_PollEvent(&eventImage))
		{
			if (SDL_MOUSEMOTION == eventImage.type)
			{
				int x;
				int y;

				SDL_GetMouseState(&x, &y);

				MouseRect.x = x;
				MouseRect.y = y;

				if (x >= QuitRect.x and x <= QuitRect.w + QuitRect.x and y >= QuitRect.y and y <= QuitRect.h + QuitRect.y)
				{
					quit = SDL_LoadBMP("./Graphics/QuitHovered.bmp");
					quitTexture = SDL_CreateTextureFromSurface(renderer, quit);

				}
				else
				{
					quit = SDL_LoadBMP("./Graphics/QuitNotHovered.bmp");
					quitTexture = SDL_CreateTextureFromSurface(renderer, quit);

					if (QuitMin == true)
					{
						QuitRect.w = QuitRect.w - 20;
						QuitRect.h = QuitRect.h - 20;
						QuitMin = false;
					}
				}

			}
			if (SDL_MOUSEBUTTONUP == eventImage.type)
			{
				int x;
				int y;

				SDL_GetMouseState(&x, &y);

				if (x >= QuitRect.x and x <= QuitRect.w + QuitRect.x and y >= QuitRect.y and y <= QuitRect.h + QuitRect.y)
				{
					playing = false;

				}

			}
			if (SDL_MOUSEBUTTONDOWN == eventImage.type)
			{
				int x;
				int y;

				SDL_GetMouseState(&x, &y);

				if (x >= QuitRect.x and x <= QuitRect.w + QuitRect.x and y >= QuitRect.y and y <= QuitRect.h + QuitRect.y)
				{
					if (QuitMin == false)
					{
						QuitRect.w = QuitRect.w + 20;
						QuitRect.h = QuitRect.h + 20;
						QuitMin = true;
					}
				}
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0xff, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

		SDL_RenderCopy(renderer, backgroundTexture, NULL, &BackRect);
		SDL_RenderCopy(renderer, quitTexture, NULL, &QuitRect);
		SDL_RenderCopy(renderer, cursorTexture, NULL, &MouseRect);
		SDL_RenderPresent(renderer);
	}
	return 0;
}
