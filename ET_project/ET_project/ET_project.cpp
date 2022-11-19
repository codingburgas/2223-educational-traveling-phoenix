#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string> 

using namespace std;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

bool QuitMin = false;
bool StartMin = false;
bool playing = true;
bool OnMap = false;
bool OnQuestion = false;

int CharFlagX;
int CharFlagY;
int CharFixY = 0;

int money = 0;

SDL_Event eventImage;

SDL_Window* window = SDL_CreateWindow("Europe trip", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

SDL_Surface* background = SDL_LoadBMP("./Graphics/background.bmp");

SDL_Surface* quit = SDL_LoadBMP("./Graphics/Buttons/ButtonQuit.bmp");

SDL_Surface* start = SDL_LoadBMP("./Graphics/Buttons/ButtonPlay.bmp");

SDL_Surface* Arrow = SDL_LoadBMP("./Graphics/ArrowNotHovered.bmp");

SDL_Surface* character = SDL_LoadBMP("./Graphics/carOne.bmp");

SDL_Surface* visit = SDL_LoadBMP("./Graphics/MapModes/EnteredVisit.bmp");

SDL_Texture* BackgroundTexture = SDL_CreateTextureFromSurface(renderer, background);

SDL_Texture* characterTexture = SDL_CreateTextureFromSurface(renderer, character);

SDL_Texture* QuitTexture = SDL_CreateTextureFromSurface(renderer, quit);

SDL_Texture* StartTexture = SDL_CreateTextureFromSurface(renderer, start);

SDL_Texture* ArrowTexture = SDL_CreateTextureFromSurface(renderer, Arrow);  

SDL_Texture* visitTexture = SDL_CreateTextureFromSurface(renderer, visit);

int CarOnCountry(SDL_Rect CharRect)
{
	if (CharRect.x >= 865 and CharRect.x <= 1370 and CharFixY + 980 <= 801 and CharFixY + 980 >= 439)
	{
		return 1;
	}
	else if (CharRect.x >= 619 and CharRect.x <= 840 and CharFixY + 980 <= 830 and CharFixY + 980 >= 701)
	{
		return 2;
	}
	else if (CharRect.x >= 584 and CharRect.x <= 701 and CharFixY + 980 <= 658 and CharFixY + 980 >= 579)
	{
		return 3; 
	}
	else if (CharRect.x >= 401 and CharRect.x  <= 513 and CharFixY + 980 <= 639 and CharFixY + 980 >= 545)
	{
		return 4;
	}
	else if (CharRect.x >= 487 and CharRect.x  <= 586 and CharFixY + 980 <= 1016 and CharFixY + 980 >= 667)
	{
		return 5;
	}
	else
	{
		return 0;
	}
}

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
		quit = SDL_LoadBMP("./Graphics/Buttons/ButtonQuitHovered.bmp");
		QuitTexture = SDL_CreateTextureFromSurface(renderer, quit);
	}
	else
	{
		quit = SDL_LoadBMP("./Graphics/Buttons/ButtonQuit.bmp");
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
		start = SDL_LoadBMP("./Graphics/Buttons/ButtonPlayHovered.bmp");
		StartTexture = SDL_CreateTextureFromSurface(renderer, start);

		return void();
	}
	else
	{
		start = SDL_LoadBMP("./Graphics/Buttons/ButtonPlay.bmp");
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
		background = SDL_LoadBMP("./Graphics/MapModes/Mode1.bmp");
		BackgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
	}
}

void CharPosEvent(SDL_Rect CharRect, SDL_Rect ArrowRect, SDL_Rect VisitRect)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (OnMap == true)
	{
		CharFlagX = x;
		CharFlagY = y;
		if (CharRect.x < x )
		{
			character = SDL_LoadBMP("./Graphics/carOne.bmp");
			characterTexture = SDL_CreateTextureFromSurface(renderer, character);
		}
		else
		{
			character = SDL_LoadBMP("./Graphics/carTwo.bmp");
			characterTexture = SDL_CreateTextureFromSurface(renderer, character);
		}
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

void BackToMap(SDL_Rect ArrowRect)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= ArrowRect.x and x <= ArrowRect.w + ArrowRect.x and y >= ArrowRect.y and y <= ArrowRect.h + ArrowRect.y)
	{
		OnMap = true;
		OnQuestion = false;
	}
}

void visitButtonUp(SDL_Rect visitRect, SDL_Rect CharRect)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= visitRect.x and x <= visitRect.w + visitRect.x and y >= visitRect.y and y <= visitRect.h + visitRect.y and CarOnCountry(CharRect) != 0)
	{
		OnMap = false;
		OnQuestion = true;
		background = SDL_LoadBMP("./Graphics/");
		BackgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
	}
}

void HoveredCountry()
{
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x >= 865 and x <= 1370 and y <= 801 and y >= 439 and OnMap == 1 and OnQuestion == false)
		{
			background = SDL_LoadBMP("./Graphics/MapModes/Mode2.bmp");
			BackgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
		}
		else if (x >= 619 and x <= 840 and y <= 830 and y >= 701 and OnMap == 1 and OnQuestion == false)
		{
			background = SDL_LoadBMP("./Graphics/MapModes/Mode3.bmp");
			BackgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
		}
		else if (x >= 584 and x <= 701 and y <= 658 and y >= 579 and OnMap == 1 and OnQuestion == false)
		{
			background = SDL_LoadBMP("./Graphics/MapModes/Mode4.bmp");
			BackgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
		}
		else if (x >= 401 and x <= 513 and y <= 639 and y >= 545 and OnMap == 1 and OnQuestion == false)
		{
			background = SDL_LoadBMP("./Graphics/MapModes/Mode5.bmp");
			BackgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
		}
		else if (x >= 487 and x <= 586 and y <= 1016 and y >= 667 and OnMap == 1 and OnQuestion == false)
		{
			background = SDL_LoadBMP("./Graphics/MapModes/Mode6.bmp");
			BackgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
		}
		else
		{
			if (OnMap == 1 and OnQuestion == false)
			{
				background = SDL_LoadBMP("./Graphics/MapModes/Mode1.bmp");
				BackgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
			}
		}
}

void ButtonEvents(SDL_Rect QuitRect, SDL_Rect StartRect, SDL_Rect background, SDL_Rect ArrowRect, SDL_Rect charRect, SDL_Rect visitRect, bool QuitMin, bool StartMin)
{
	if (SDL_PollEvent(&eventImage))
	{
		if (SDL_MOUSEBUTTONUP == eventImage.type)
		{
			if (OnMap == 1 and OnQuestion == false)
			{
				BackToMenu(ArrowRect);
				CharPosEvent(charRect, ArrowRect, visitRect);
				visitButtonUp(visitRect, charRect);
			}
			else
			{
				if (OnQuestion == true)
				{
					BackToMap(ArrowRect);
				}
				PlayButtonEvent(StartRect);
				Quiting(QuitRect);
			}  	
		}
		if (SDL_MOUSEMOTION == eventImage.type)
		{
			if (OnMap == 1 and OnQuestion == false)
			{
				ArrowButtonOnHoverCheck(ArrowRect);
				HoveredCountry();
			}
			else
			{
				if (OnQuestion == true)
				{
					ArrowButtonOnHoverCheck(ArrowRect);
				}
				QuitButtonOnHoverCheck(QuitRect);
				PlayButtonOnHoverCheck(StartRect, StartMin);
			}
		}
		if (SDL_MOUSEBUTTONDOWN == eventImage.type)
		{
			if (OnMap == 1 and OnQuestion == false)
			{
				QuitButtonEnlarge(QuitRect, QuitMin);	
			}
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

void VisitButton(SDL_Rect CharRect, SDL_Rect VisitRect)
{
	if (OnMap == 1 and OnQuestion == false)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (CarOnCountry(CharRect) != 0)
		{
			if (x >= VisitRect.x and x <= VisitRect.w + VisitRect.x and y >= VisitRect.y and y <= VisitRect.h + VisitRect.y)
			{
				visit = SDL_LoadBMP("./Graphics/Buttons/NormalModeVisit.bmp");
				visitTexture = SDL_CreateTextureFromSurface(renderer, visit);
			}
			else
			{
				visit = SDL_LoadBMP("./Graphics/Buttons/ProcessVisit.bmp");
				visitTexture = SDL_CreateTextureFromSurface(renderer, visit);
			}
		}
		else
		{
			visit = SDL_LoadBMP("./Graphics/Buttons/EnteredVisit.bmp");
			visitTexture = SDL_CreateTextureFromSurface(renderer, visit);
		}
	}
}

int main(int argc, char* args[])
{
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
	CharRect.w = 155;
	CharRect.h = 67;
	CharRect.x = 500;
	CharRect.y = -100;

	SDL_Rect MoneyRect;
	MoneyRect.x = 0;
	MoneyRect.y = 0;
	MoneyRect.w = 100;
	MoneyRect.h = 100;

	SDL_Rect visitRect;
	visitRect.x = SCREEN_WIDTH / 2 - QuitRect.w / 2;;
	visitRect.y = -SCREEN_HEIGHT + 900  ;
	visitRect.w = 215;
	visitRect.h = 129;

	const int StartY = StartRect.y;
	const int QuitY = QuitRect.y;
	const int ArrowY = ArrowRect.y;
	const int CharY = CharRect.y;
	const int VisitY = visitRect.y;

	while (playing == true)
	{
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 219, 192, 50, SDL_ALPHA_OPAQUE);

		SDL_RenderCopy(renderer, BackgroundTexture, NULL, &BackRect);
		SDL_RenderCopy(renderer, QuitTexture, NULL, &QuitRect);
		SDL_RenderCopy(renderer, StartTexture, NULL, &StartRect);
		SDL_RenderCopy(renderer, ArrowTexture, NULL, &ArrowRect);
		SDL_RenderCopy(renderer, characterTexture, NULL, &CharRect);	
		SDL_RenderCopy(renderer, visitTexture, NULL, &visitRect);
		SDL_RenderPresent(renderer);

		
		
			if (OnMap == true and OnQuestion == false)
			{

				StartRect.y = StartY - SCREEN_HEIGHT;
				QuitRect.y = QuitY - SCREEN_HEIGHT;
				ArrowRect.y = ArrowY + SCREEN_HEIGHT;
				CharRect.y = CharY + SCREEN_HEIGHT;
				visitRect.y = VisitY + SCREEN_HEIGHT;

				VisitButton(CharRect, visitRect);

			}
			else
			{
				if (OnQuestion == false)
				{
					QuitRect.y = QuitY + SCREEN_HEIGHT;
					StartRect.y = StartY + SCREEN_HEIGHT;
					ArrowRect.y = ArrowY - SCREEN_HEIGHT;
					CharRect.y = CharY - SCREEN_HEIGHT;
					visitRect.y = VisitY - SCREEN_HEIGHT;
				}
				else
				{
					CharRect.y = CharY - SCREEN_HEIGHT;
					visitRect.y = VisitY - SCREEN_HEIGHT;
				}

			}

		if (OnMap == 1 and OnQuestion == false)
		{
			if (CharRect.y + CharFixY > CharFlagY)
			{
				CharFixY = CharFixY - 2;
			}
			else if (CharRect.y != CharFlagY)
			{
				CharFixY += 1;
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
		}

		ButtonEvents(QuitRect, StartRect, BackRect, ArrowRect, CharRect, visitRect, QuitMin, StartMin);

		SDL_Delay(5);
	}
	return 0;
}
