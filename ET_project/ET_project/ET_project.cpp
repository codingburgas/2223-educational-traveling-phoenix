#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

bool QuitMin = false;
bool StartMin = false;
bool playing = true;
bool OnMap = false;

int CharFlagX;
int CharFlagY;
int CharFixY = 0;

SDL_Event eventImage;

SDL_Window* window = SDL_CreateWindow("Europe trip", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

SDL_Surface* background = SDL_LoadBMP("./Graphics/background.bmp");

SDL_Surface* quit = SDL_LoadBMP("./Graphics/ButtonQuit.bmp");

SDL_Surface* start = SDL_LoadBMP("./Graphics/ButtonPlay.bmp");

SDL_Surface* Arrow = SDL_LoadBMP("./Graphics/ArrowNotHovered.bmp");

SDL_Surface* blackCloset1 = SDL_LoadBMP("./Graphics/ButtonPlay.bmp");

SDL_Surface* character = SDL_LoadBMP("./Graphics/character.bmp");

SDL_Texture* BackgroundTexture = SDL_CreateTextureFromSurface(renderer, background);

SDL_Texture* characterTexture = SDL_CreateTextureFromSurface(renderer, character);

SDL_Texture* QuitTexture = SDL_CreateTextureFromSurface(renderer, quit);

SDL_Texture* StartTexture = SDL_CreateTextureFromSurface(renderer, start);

SDL_Texture* ArrowTexture = SDL_CreateTextureFromSurface(renderer, Arrow);

SDL_Texture* blackCloset1Texture = SDL_CreateTextureFromSurface(renderer, blackCloset1);

void Quiting(SDL_Rect QuitRect)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= QuitRect.x and x <= QuitRect.w + QuitRect.x and y >= QuitRect.y and y <= QuitRect.h + QuitRect.y)
	{ 
		playing = false;
	}
}

void QuitButtonOnHoverCheck(SDL_Rect QuitRect)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= QuitRect.x and x <= QuitRect.w + QuitRect.x and y >= QuitRect.y and y <= QuitRect.h + QuitRect.y)
	{
		quit = SDL_LoadBMP("./Graphics/ButtonQuitHovered.bmp");
		QuitTexture = SDL_CreateTextureFromSurface(renderer, quit);
	}
	else
	{
		quit = SDL_LoadBMP("./Graphics/ButtonQuit.bmp");
		QuitTexture = SDL_CreateTextureFromSurface(renderer, quit);
	}
}

void ArrowButtonOnHoverCheck(SDL_Rect ArrowRect)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= ArrowRect.x and x <= ArrowRect.w + ArrowRect.x and y >= ArrowRect.y and y <= ArrowRect.h + ArrowRect.y)
	{
		Arrow = SDL_LoadBMP("./Graphics/ArrowHovered.bmp");
		ArrowTexture = SDL_CreateTextureFromSurface(renderer, Arrow);
	}
	else
	{
		Arrow = SDL_LoadBMP("./Graphics/ArrowNotHovered.bmp");
		ArrowTexture = SDL_CreateTextureFromSurface(renderer, Arrow);
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
		
		OnMap = true;
		background = SDL_LoadBMP("./Graphics/mode_1.bmp");
		BackgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
	}
}

void CharPosEvent()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (OnMap == true)
	{
		CharFlagX = x;
		CharFlagY = y;
	}
}
	
void BackToMenu(SDL_Rect ArrowRect)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= ArrowRect.x and x <= ArrowRect.w + ArrowRect.x and y >= ArrowRect.y and y <= ArrowRect.h + ArrowRect.y)
	{
		
		OnMap = false;
		background = SDL_LoadBMP("./Graphics/background.bmp");
		BackgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
	}
}

void ButtonEvents(SDL_Rect QuitRect, SDL_Rect StartRect, SDL_Rect background, SDL_Rect blackCloset1rect, SDL_Rect ArrowRect, bool QuitMin, bool StartMin)
{
	if (SDL_PollEvent(&eventImage))
	{
		if (SDL_MOUSEBUTTONUP == eventImage.type)
		{
			Quiting(QuitRect);
			PlayButtonEvent(StartRect);
			BackToMenu(ArrowRect);
			CharPosEvent();
		}
		if (SDL_MOUSEMOTION == eventImage.type)
		{
			QuitButtonOnHoverCheck(QuitRect);
			PlayButtonOnHoverCheck(StartRect, StartMin);
			ArrowButtonOnHoverCheck(ArrowRect);
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
	SDL_FreeSurface(Arrow);
	SDL_FreeSurface(character);

	SDL_Rect BackRect;
	BackRect.w = SCREEN_WIDTH;
	BackRect.h = SCREEN_HEIGHT;
	BackRect.x = 0;
	BackRect.y = 0;

	SDL_Rect QuitRect;
	QuitRect.w = 215;
	QuitRect.h = 129;
	QuitRect.x = SCREEN_WIDTH / 2 - QuitRect.w / 2;
	QuitRect.y = SCREEN_HEIGHT - SCREEN_HEIGHT / 2 + 200 - SCREEN_HEIGHT;

	SDL_Rect MouseRect;
	MouseRect.x = 0;
	MouseRect.y = 0;
	MouseRect.w = 50;
	MouseRect.h = 50;

	SDL_Rect StartRect;
	StartRect.w = 215;
	StartRect.h = 129;
	StartRect.x = SCREEN_WIDTH / 2 - StartRect.w / 2;
	StartRect.y = SCREEN_HEIGHT / 2 - SCREEN_HEIGHT;

	SDL_Rect ArrowRect;
	ArrowRect.w = 215;
	ArrowRect.h = 129;
	ArrowRect.x = 0;
	ArrowRect.y = 0 - SCREEN_HEIGHT;

	SDL_Rect CharRect;
	CharRect.w = 50;
	CharRect.h = 100;
	CharRect.x = 500;
	CharRect.y = -100;

	SDL_Rect blackCloset1rect;
	blackCloset1rect.w = SCREEN_WIDTH / 2;
	blackCloset1rect.h = SCREEN_HEIGHT;
	blackCloset1rect.x = 0 - SCREEN_WIDTH / 2;
	blackCloset1rect.y = 0;

	const int StartY = StartRect.y;
	const int QuitY = QuitRect.y;
	const int ArrowY = ArrowRect.y;
	const int CharY = CharRect.y;

	while (playing == true)
	{
		
		ButtonEvents(QuitRect, StartRect, BackRect, blackCloset1rect, ArrowRect, QuitMin, StartMin);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0xff, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

		SDL_RenderCopy(renderer, BackgroundTexture, NULL, &BackRect);
		SDL_RenderCopy(renderer, QuitTexture, NULL, &QuitRect);
		SDL_RenderCopy(renderer, StartTexture, NULL, &StartRect);
		SDL_RenderCopy(renderer, ArrowTexture, NULL, &ArrowRect);
		SDL_RenderCopy(renderer, characterTexture, NULL, &CharRect);
		SDL_RenderCopy(renderer, blackCloset1Texture, NULL, &blackCloset1rect);
		SDL_RenderPresent(renderer);

		if (OnMap == true)
		{	
			StartRect.y = StartY - SCREEN_HEIGHT;
			QuitRect.y = QuitY - SCREEN_HEIGHT;
			ArrowRect.y = ArrowY + SCREEN_HEIGHT;
			CharRect.y = CharY + SCREEN_HEIGHT;
		}
		else
		{
			QuitRect.y = QuitY + SCREEN_HEIGHT;
			StartRect.y = StartY + SCREEN_HEIGHT;
			ArrowRect.y = ArrowY - SCREEN_HEIGHT;
			CharRect.y = CharY - SCREEN_HEIGHT;
		}

		if (CharRect.y + CharFixY > CharFlagY)
		{
			CharFixY = CharFixY - 2;
		}
		else if (CharRect.y + CharFixY < CharFlagY)
		{
			CharFixY = CharFixY + 2;
		}

		CharRect.y = CharRect.y + CharFixY;

		if (CharRect.x > CharFlagX)
		{
			CharRect.x -= 2;
		}
		else if (CharRect.x != CharFlagX)
		{
			CharRect.x += 1;
		}
		else if (CharRect.x < CharFlagX)
		{
			CharRect.x += 2;
		}
		SDL_Delay(2);
	}
	return 0;
}
