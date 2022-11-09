#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

bool QuitMin = false;
bool StartMin = false;

bool playing = true;

SDL_Event eventImage;

SDL_Window* window = SDL_CreateWindow("Hello SDL WORLD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

SDL_Surface* background = SDL_LoadBMP("./Graphics/background.bmp");

SDL_Surface* quit = SDL_LoadBMP("./Graphics/ButtonQuit.bmp");

SDL_Surface* start = SDL_LoadBMP("./Graphics/ButtonPlay.bmp");

SDL_Texture* BackgroundTexture = SDL_CreateTextureFromSurface(renderer, background);

SDL_Texture* QuitTexture = SDL_CreateTextureFromSurface(renderer, quit);

SDL_Texture* StartTexture = SDL_CreateTextureFromSurface(renderer, start);

void Quiting(SDL_Rect QuitRect)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= QuitRect.x and x <= QuitRect.w + QuitRect.x and y >= QuitRect.y and y <= QuitRect.h + QuitRect.y)
	{
		playing = false;
		return void();
	}
}

void QuitButtonOnHoverCheck(SDL_Rect QuitRect, bool QuitMin)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= QuitRect.x and x <= QuitRect.w + QuitRect.x and y >= QuitRect.y and y <= QuitRect.h + QuitRect.y)
	{
		quit = SDL_LoadBMP("./Graphics/ButtonQuitHovered.bmp");
		QuitTexture = SDL_CreateTextureFromSurface(renderer, quit);
		return void(QuitMin);
	}
	else
	{
		quit = SDL_LoadBMP("./Graphics/ButtonQuit.bmp");
		QuitTexture = SDL_CreateTextureFromSurface(renderer, quit);
		if (QuitMin == true)
		{
			QuitRect.w = QuitRect.w - 20;
			QuitRect.h = QuitRect.h - 20;
			QuitMin = false;
			return void(QuitMin);
		}
	}
}

void PlayButtonOnHoverCheck(SDL_Rect StartRect, bool StartMin)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= StartRect.x and x <= StartRect.w + StartRect.x and y >= StartRect.y and y <= StartRect.h + StartRect.y)
	{
		start = SDL_LoadBMP("./Graphics/ButtonPlayHovered.bmp");
		StartTexture = SDL_CreateTextureFromSurface(renderer, start);
		return void();
	}
	else
	{
		start = SDL_LoadBMP("./Graphics/ButtonPlay.bmp");
		StartTexture = SDL_CreateTextureFromSurface(renderer, start);
		if (StartMin == true)
		{
			StartRect.w = StartRect.w - 20;
			StartRect.h = StartRect.h - 20;
			StartMin = false;
			return void();
		}
	}
}

void QuitButtonEnlarge(SDL_Rect QuitRect, bool QuitMin)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= QuitRect.x and x <= QuitRect.w + QuitRect.x and y >= QuitRect.y and y <= QuitRect.h + QuitRect.y)
	{
		if (QuitMin == false)
		{
			QuitRect.w = QuitRect.w + 20;
			QuitRect.h = QuitRect.h + 20;
			QuitMin = true;
			return void(QuitMin);
		}
	}
}

void PlayButtonEvent(SDL_Rect StartRect)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= StartRect.x and x <= StartRect.w + StartRect.x and y >= StartRect.y and y <= StartRect.h + StartRect.y)
	{
		background = SDL_LoadBMP("./Graphics/mode_1.bmp");
		BackgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
	}
}

void ButtonEvents(SDL_Rect QuitRect, SDL_Rect StartRect, SDL_Rect background, bool QuitMin, bool StartMin)
{
	if (SDL_PollEvent(&eventImage))
	{
		if (SDL_MOUSEMOTION == eventImage.type)
		{
			QuitButtonOnHoverCheck(QuitRect, QuitMin);
			PlayButtonOnHoverCheck(StartRect, StartMin);
		}
		if (SDL_MOUSEBUTTONUP == eventImage.type)
		{
			Quiting(QuitRect);
			PlayButtonEvent(StartRect);
		}
		if (SDL_MOUSEBUTTONDOWN == eventImage.type)
		{
			QuitButtonEnlarge(QuitRect, QuitMin);
		}


		if (SDL_MOUSEBUTTONDOWN == eventImage.type)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (x >= StartRect.x and x <= StartRect.w + StartRect.x and y >= StartRect.y and y <= StartRect.h + StartRect.y)
			{
				if (StartMin == false)
				{
					StartRect.w = StartRect.w + 20;
					StartRect.h = StartRect.h + 20;
					StartMin = true;
				}
			}
		}

	}
}

int main(int argc, char* args[])
{
	SDL_FreeSurface(background);
	SDL_FreeSurface(quit);
	SDL_FreeSurface(start);

	SDL_Rect BackRect;
	BackRect.w = SCREEN_WIDTH;
	BackRect.h = SCREEN_HEIGHT;
	BackRect.x = 0;
	BackRect.y = 0;

	SDL_Rect QuitRect;
	QuitRect.w = 215;
	QuitRect.h = 129;
	QuitRect.x = SCREEN_WIDTH / 2 - QuitRect.w / 2;
	QuitRect.y = SCREEN_HEIGHT - SCREEN_HEIGHT / 2 + 200;

	SDL_Rect MouseRect;
	MouseRect.x = 0;
	MouseRect.y = 0;
	MouseRect.w = 50;
	MouseRect.h = 50;

	SDL_Rect StartRect;
	StartRect.w = 215;
	StartRect.h = 129;
	StartRect.x = SCREEN_WIDTH / 2 - StartRect.w / 2;
	StartRect.y = SCREEN_HEIGHT / 2;

	SDL_SetWindowFullscreen(window, SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN ? 0 : SDL_WINDOW_FULLSCREEN);
	while (playing == true)
	{
		ButtonEvents(QuitRect, StartRect, BackRect, QuitMin, StartMin);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0xff, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

		SDL_RenderCopy(renderer, BackgroundTexture, NULL, &BackRect);
		SDL_RenderCopy(renderer, QuitTexture, NULL, &QuitRect);
		SDL_RenderCopy(renderer, StartTexture, NULL, &StartRect);
		SDL_RenderPresent(renderer);
	}
	return 0;
}
