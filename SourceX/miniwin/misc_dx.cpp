#include "devilution.h"
#include "miniwin/ddraw.h"
#include "stubs.h"
#ifdef VITA
#ifdef USE_SDL1
#include <SDL/SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#else
#include <SDL.h>
#endif

namespace dvl {

WINBOOL SetCursorPos(int X, int Y)
{
	assert(window);

#ifndef VITA

#ifndef USE_SDL1
	if (renderer) {
		SDL_Rect view;
		SDL_RenderGetViewport(renderer, &view);
		X += view.x;
		Y += view.y;

		float scaleX;
		SDL_RenderGetScale(renderer, &scaleX, NULL);
		X *= scaleX;
		Y *= scaleX;
	}
#endif
#endif

	SDL_WarpMouseInWindow(window, X, Y);
	return true;
}

WINBOOL TextOutA(HDC hdc, int x, int y, LPCSTR lpString, int c)
{
	DUMMY_ONCE();

	assert(window);
#ifdef USE_SDL1
	SDL_WM_SetCaption(lpString, WINDOW_ICON_NAME);
#else
	SDL_SetWindowTitle(window, lpString);
#endif

	return true;
}

} // namespace dvl
