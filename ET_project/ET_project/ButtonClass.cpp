#include "ButtonClass.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include <string>

using namespace std;

ButtonClass::ButtonClass()
{
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

}

ButtonClass::ButtonClass()
{
}
