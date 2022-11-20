#include "ButtonClass.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include <string>

using namespace std;

buttonClass::buttonClass()
{
	void playButtonOnHoverCheck(SDL_Rect startRect, bool startMin)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x >= startRect.x and x <= startRect.w + startRect.x and y >= startRect.y and y <= startRect.h + startRect.y)
		{
			start = SDL_LoadBMP("./Graphics/ButtonPlayHovered.bmp");
			startTexture = SDL_CreateTextureFromSurface(renderer, start);

			return void();
		}
		else
		{
			start = SDL_LoadBMP("./Graphics/ButtonPlay.bmp");
			startTexture = SDL_CreateTextureFromSurface(renderer, start);

			if (StartMin == true)
			{
				startRect.w = startRect.w - 20;
				startRect.h = startRect.h - 20;
				startMin = false;
				return void();
			}
		}
	}

}

buttonClass::buttonClass()
{
}
