#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string> 

using namespace std;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

bool quitMin = false;
bool startMin = false;
bool playing = true;
bool onMap = false;
bool onQuestion = false;

int charFlagX;
int charFlagY;
int charFixY = 0;

int money = 0;

SDL_Event eventImage; 

SDL_Window* window = SDL_CreateWindow("Europe trip", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

SDL_Surface* background = SDL_LoadBMP("./Graphics/background.bmp");

SDL_Surface* quit = SDL_LoadBMP("./Graphics/Buttons/ButtonQuit.bmp");

SDL_Surface* start = SDL_LoadBMP("./Graphics/Buttons/ButtonPlay.bmp");

SDL_Surface* arrow = SDL_LoadBMP("./Graphics/ArrowNotHovered.bmp");

SDL_Surface* character = SDL_LoadBMP("./Graphics/carOne.bmp");

SDL_Surface* visit = SDL_LoadBMP("./Graphics/MapModes/EnteredVisit.bmp");

SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);

SDL_Texture* characterTexture = SDL_CreateTextureFromSurface(renderer, character);

SDL_Texture* quitTexture = SDL_CreateTextureFromSurface(renderer, quit);

SDL_Texture* startTexture = SDL_CreateTextureFromSurface(renderer, start);

SDL_Texture* arrowTexture = SDL_CreateTextureFromSurface(renderer, arrow);  

SDL_Texture* visitTexture = SDL_CreateTextureFromSurface(renderer, visit);

int carOnCountry(SDL_Rect CharRect)
{
	if (CharRect.x >= 865 and CharRect.x <= 1370 and charFixY + 980 <= 801 and charFixY + 980 >= 439)
	{
		return 1;
	}
	else if (CharRect.x >= 619 and CharRect.x <= 840 and charFixY + 980 <= 830 and charFixY + 980 >= 701)
	{
		return 2;
	}
	else if (CharRect.x >= 584 and CharRect.x <= 701 and charFixY + 980 <= 658 and charFixY + 980 >= 579)
	{
		return 3; 
	}
	else if (CharRect.x >= 401 and CharRect.x  <= 513 and charFixY + 980 <= 639 and charFixY + 980 >= 545)
	{
		return 4;
	}
	else if (CharRect.x >= 487 and CharRect.x  <= 586 and charFixY + 980 <= 1016 and charFixY + 980 >= 667)
	{
		return 5;
	}
	else
	{
		return 0;
	}
}

void quiting(SDL_Rect quitRect)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= quitRect.x and x <= quitRect.w + quitRect.x and y >= quitRect.y and y <= quitRect.h + quitRect.y)
	{ 
		playing = false;
	}
}

void quitButtonOnHoverCheck(SDL_Rect quitRect)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= quitRect.x and x <= quitRect.w + quitRect.x and y >= quitRect.y and y <= quitRect.h + quitRect.y)
	{
		quit = SDL_LoadBMP("./Graphics/Buttons/ButtonQuitHovered.bmp");
		quitTexture = SDL_CreateTextureFromSurface(renderer, quit);
	}
	else
	{
		quit = SDL_LoadBMP("./Graphics/Buttons/ButtonQuit.bmp");
		quitTexture = SDL_CreateTextureFromSurface(renderer, quit);
	}
}

void arrowButtonOnHoverCheck(SDL_Rect arrowRect)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= arrowRect.x and x <= arrowRect.w + arrowRect.x and y >= arrowRect.y and y <= arrowRect.h + arrowRect.y)
	{
		arrow = SDL_LoadBMP("./Graphics/ArrowHovered.bmp");
		arrowTexture = SDL_CreateTextureFromSurface(renderer, arrow);
	}
	else
	{
		arrow = SDL_LoadBMP("./Graphics/ArrowNotHovered.bmp");
		arrowTexture = SDL_CreateTextureFromSurface(renderer, arrow);
	}
}

void playButtonOnHoverCheck(SDL_Rect startRect, bool startMin)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= startRect.x and x <= startRect.w + startRect.x and y >= startRect.y and y <= startRect.h + startRect.y)
	{
		start = SDL_LoadBMP("./Graphics/Buttons/ButtonPlayHovered.bmp");
		startTexture = SDL_CreateTextureFromSurface(renderer, start);

		return void();
	}
	else
	{
		start = SDL_LoadBMP("./Graphics/Buttons/ButtonPlay.bmp");
		startTexture = SDL_CreateTextureFromSurface(renderer, start);

		if (startMin == true)
		{
			startRect.w = startRect.w - 20;
			startRect.h = startRect.h - 20;
			startMin = false;
			return void();
		}
	}
}

void quitButtonEnlarge(SDL_Rect quitRect, bool quitMin)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= quitRect.x and x <= quitRect.w + quitRect.x and y >= quitRect.y and y <= quitRect.h + quitRect.y)
	{
		if (quitMin == false)
		{
			quitRect.w = quitRect.w + 20;
			quitRect.h = quitRect.h + 20;
			quitMin = true;
			return void(quitMin);
		}
	}
}

void playButtonEvent(SDL_Rect startRect)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= startRect.x and x <= startRect.w + startRect.x and y >= startRect.y and y <= startRect.h + startRect.y)
	{
		
		onMap = true;
		background = SDL_LoadBMP("./Graphics/MapModes/Mode1.bmp");
		backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
	}
}

void charPosEvent(SDL_Rect charRect, SDL_Rect arrowRect, SDL_Rect visitRect)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (onMap == true)
	{
		charFlagX = x;
		charFlagY = y;
		if (charRect.x < x )
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
	
void backToMenu(SDL_Rect arrowRect)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= arrowRect.x and x <= arrowRect.w + arrowRect.x and y >= arrowRect.y and y <= arrowRect.h + arrowRect.y)
	{
		
		onMap = false;
		background = SDL_LoadBMP("./Graphics/background.bmp");
		backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
	}
}

void backToMap(SDL_Rect arrowRect)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= arrowRect.x and x <= arrowRect.w + arrowRect.x and y >= arrowRect.y and y <= arrowRect.h + arrowRect.y)
	{
		onMap = true;
		onQuestion = false;
	}
}

void visitButtonUp(SDL_Rect visitRect, SDL_Rect charRect)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= visitRect.x and x <= visitRect.w + visitRect.x and y >= visitRect.y and y <= visitRect.h + visitRect.y and carOnCountry(charRect) != 0)
	{
		onMap = false;
		onQuestion = true;
		background = SDL_LoadBMP("./Graphics/");
		backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
	}
}

void hoveredCountry()
{
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x >= 865 and x <= 1370 and y <= 801 and y >= 439 and onMap == 1 and onQuestion == false)
		{
			background = SDL_LoadBMP("./Graphics/MapModes/Mode2.bmp");
			backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
		}
		else if (x >= 619 and x <= 840 and y <= 830 and y >= 701 and onMap == 1 and onQuestion == false)
		{
			background = SDL_LoadBMP("./Graphics/MapModes/Mode3.bmp");
			backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
		}
		else if (x >= 584 and x <= 701 and y <= 658 and y >= 579 and onMap == 1 and onQuestion == false)
		{
			background = SDL_LoadBMP("./Graphics/MapModes/Mode4.bmp");
			backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
		}
		else if (x >= 401 and x <= 513 and y <= 639 and y >= 545 and onMap == 1 and onQuestion == false)
		{
			background = SDL_LoadBMP("./Graphics/MapModes/Mode5.bmp");
			backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
		}
		else if (x >= 487 and x <= 586 and y <= 1016 and y >= 667 and onMap == 1 and onQuestion == false)
		{
			background = SDL_LoadBMP("./Graphics/MapModes/Mode6.bmp");
			backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
		}
		else
		{
			if (onMap == 1 and onQuestion == false)
			{
				background = SDL_LoadBMP("./Graphics/MapModes/Mode1.bmp");
				backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
			}
		}
}

void buttonEvents(SDL_Rect quitRect, SDL_Rect startRect, SDL_Rect background, SDL_Rect arrowRect, SDL_Rect charRect, SDL_Rect visitRect, bool quitMin, bool startMin)
{
	if (SDL_PollEvent(&eventImage))
	{
		if (SDL_MOUSEBUTTONUP == eventImage.type)
		{
			if (onMap == 1 and onQuestion == false)
			{
				backToMenu(arrowRect);
				charPosEvent(charRect, arrowRect, visitRect);
				visitButtonUp(visitRect, charRect);
			}
			else
			{
				if (onQuestion == true)
				{
					backToMap(arrowRect);
				}
				playButtonEvent(startRect);
				quiting(quitRect);
			}  	
		}
		if (SDL_MOUSEMOTION == eventImage.type)
		{
			if (onMap == 1 and onQuestion == false)
			{
				arrowButtonOnHoverCheck(arrowRect);
				hoveredCountry();
			}
			else
			{
				if (onQuestion == true)
				{
					arrowButtonOnHoverCheck(arrowRect);
				}
				quitButtonOnHoverCheck(quitRect);
				playButtonOnHoverCheck(startRect, startMin);
			}
		}
		if (SDL_MOUSEBUTTONDOWN == eventImage.type)
		{
			if (onMap == 1 and onQuestion == false)
			{
				quitButtonEnlarge(quitRect, quitMin);	
			}
		}
		if (SDL_MOUSEBUTTONDOWN == eventImage.type)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (x >= startRect.x and x <= startRect.w + startRect.x and y >= startRect.y and y <= startRect.h + startRect.y)
			{
				if (startMin == false)
				{
					startRect.w = startRect.w + 20;
					startRect.h = startRect.h + 20;
					startMin = true;
				}
			}
		}
	}
}

void visitButton(SDL_Rect charRect, SDL_Rect visitRect)
{
	if (onMap == 1 and onQuestion == false)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (carOnCountry(charRect) != 0)
		{
			if (x >= visitRect.x and x <= visitRect.w + visitRect.x and y >= visitRect.y and y <= visitRect.h + visitRect.y)
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
	SDL_Rect backRect;
	backRect.w = SCREEN_WIDTH;
	backRect.h = SCREEN_HEIGHT;
	backRect.x = 0;
	backRect.y = 0;

	SDL_Rect quitRect;
	quitRect.w = 215;
	quitRect.h = 129;
	quitRect.x = SCREEN_WIDTH / 2 - quitRect.w / 2;
	quitRect.y = SCREEN_HEIGHT - SCREEN_HEIGHT / 2 + 200 - SCREEN_HEIGHT;

	SDL_Rect mouseRect;
	mouseRect.x = 0;
	mouseRect.y = 0;
	mouseRect.w = 50;
	mouseRect.h = 50;

	SDL_Rect startRect;
	startRect.w = 215;
	startRect.h = 129;
	startRect.x = SCREEN_WIDTH / 2 - startRect.w / 2;
	startRect.y = SCREEN_HEIGHT / 2 - SCREEN_HEIGHT;

	SDL_Rect arrowRect;
	arrowRect.w = 215;
	arrowRect.h = 129;
	arrowRect.x = 0;
	arrowRect.y = 0 - SCREEN_HEIGHT;

	SDL_Rect charRect;
	charRect.w = 155;
	charRect.h = 67;
	charRect.x = 500;
	charRect.y = -100;

	SDL_Rect moneyRect;
	moneyRect.x = 0;
	moneyRect.y = 0;
	moneyRect.w = 100;
	moneyRect.h = 100;

	SDL_Rect visitRect;
	visitRect.x = SCREEN_WIDTH / 2 - quitRect.w / 2;;
	visitRect.y = -SCREEN_HEIGHT + 900  ;
	visitRect.w = 215;
	visitRect.h = 129;

	const int StartY = startRect.y;
	const int QuitY = quitRect.y;
	const int ArrowY = arrowRect.y;
	const int CharY = charRect.y;
	const int VisitY = visitRect.y;

	while (playing == true)
	{
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 219, 192, 50, SDL_ALPHA_OPAQUE);

		SDL_RenderCopy(renderer, backgroundTexture, NULL, &backRect);
		SDL_RenderCopy(renderer, quitTexture, NULL, &quitRect);
		SDL_RenderCopy(renderer, startTexture, NULL, &startRect);
		SDL_RenderCopy(renderer, arrowTexture, NULL, &arrowRect);
		SDL_RenderCopy(renderer, characterTexture, NULL, &charRect);	
		SDL_RenderCopy(renderer, visitTexture, NULL, &visitRect);
		SDL_RenderPresent(renderer);

		
		
			if (onMap == true and onQuestion == false)
			{

				startRect.y = StartY - SCREEN_HEIGHT;
				quitRect.y = QuitY - SCREEN_HEIGHT;
				arrowRect.y = ArrowY + SCREEN_HEIGHT;
				charRect.y = CharY + SCREEN_HEIGHT;
				visitRect.y = VisitY + SCREEN_HEIGHT;

				visitButton(charRect, visitRect);

			}
			else
			{
				if (onQuestion == false)
				{
					quitRect.y = QuitY + SCREEN_HEIGHT;
					startRect.y = StartY + SCREEN_HEIGHT;
					arrowRect.y = ArrowY - SCREEN_HEIGHT;
					charRect.y = CharY - SCREEN_HEIGHT;
					visitRect.y = VisitY - SCREEN_HEIGHT;
				}
				else
				{
					charRect.y = CharY - SCREEN_HEIGHT;
					visitRect.y = VisitY - SCREEN_HEIGHT;
				}

			}

		if (onMap == 1 and onQuestion == false)
		{
			if (charRect.y + charFixY > charFlagY)
			{
				charFixY = charFixY - 2;
			}
			else if (charRect.y != charFlagY)
			{
				charFixY += 1;
			}
			else if (charRect.y + charFixY < charFlagY)
			{
				charFixY = charFixY + 2;
			}

			charRect.y = charRect.y + charFixY;

			if (charRect.x > charFlagX)
			{
				charRect.x -= 2;
			}
			else if (charRect.x != charFlagX)
			{
				charRect.x += 1;
			}
			else if (charRect.x < charFlagX)
			{
				charRect.x += 2;
			}
		}

		buttonEvents(quitRect, startRect, backRect, arrowRect, charRect, visitRect, quitMin, startMin);

		SDL_Delay(5);
	}
	return 0;
}
