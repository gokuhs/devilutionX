#include "devilution.h"
#include "miniwin/ddraw.h"
#include "stubs.h"
#ifdef VITA
#ifdef USE_SDL1
#include <SDL/SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include "../../vita/vita_aux_util.h"
#else
#include <SDL.h>
#endif
#include <string>

#include "DiabloUI/diabloui.h"
#include "DiabloUI/dialogs.h"

#ifdef _MSC_VER
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#endif

namespace dvl {

DWORD last_error;

DWORD GetLastError()
{
	return last_error;
}

void SetLastError(DWORD dwErrCode)
{
	last_error = dwErrCode;
}

int wsprintfA(LPSTR dest, LPCSTR format, ...)
{
	va_list args;
	va_start(args, format);
	return vsprintf(dest, format, args);
}

int wvsprintfA(LPSTR dest, LPCSTR format, va_list arglist)
{
	return vsnprintf(dest, 256, format, arglist);
}

int _strcmpi(const char *_Str1, const char *_Str2)
{
	return strcasecmp(_Str1, _Str2);
}

int _strnicmp(const char *_Str1, const char *_Str2, size_t n)
{
	return strncasecmp(_Str1, _Str2, n);
}

char *_itoa(int _Value, char *_Dest, int _Radix)
{
	switch (_Radix) {
	case 8:
		sprintf(_Dest, "%o", _Value);
		break;
	case 10:
		sprintf(_Dest, "%d", _Value);
		break;
	case 16:
		sprintf(_Dest, "%x", _Value);
		break;
	default:
		UNIMPLEMENTED();
		break;
	}

	return _Dest;
}

DWORD GetTickCount()
{
	return SDL_GetTicks();
}

void Sleep(DWORD dwMilliseconds)
{
	SDL_Delay(dwMilliseconds);
}

HANDLE FindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData)
{
	DUMMY();
	return (HANDLE)-1;
}

WINBOOL FindClose(HANDLE hFindFile)
{
	UNIMPLEMENTED();
	return true;
}

WINBOOL GetComputerNameA(LPSTR lpBuffer, LPDWORD nSize)
{
	DUMMY();
	strncpy(lpBuffer, "localhost", *nSize);
	*nSize = strlen(lpBuffer);
	return true;
}

WINBOOL DeleteFileA(LPCSTR lpFileName)
{
	char name[DVL_MAX_PATH];
	TranslateFileName(name, sizeof(name), lpFileName);

	FILE *f = fopen(name, "r+");
	if (f) {
		fclose(f);
		remove(name);
		f = NULL;
		eprintf("Removed file: %s\n", name);
	} else {
		eprintf("Failed to remove file: %s\n", name);
	}

	return true;
}

bool SpawnWindow(LPCSTR lpWindowName, int nWidth, int nHeight)
{
#ifdef VITA
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) <= -1) {
		SDL_Log(SDL_GetError());
	}
#else
	if (SDL_Init(SDL_INIT_EVERYTHING & ~SDL_INIT_HAPTIC) <= -1) {
		ErrSdl();
	}
#endif

	atexit(SDL_Quit);

#ifdef USE_SDL1
	SDL_EnableUNICODE(1);
#endif
	if (SDL_JoystickOpen(0) == NULL) {
		SDL_Log(SDL_GetError());
	}
#ifndef USE_SDL1
	if (SDL_GameControllerOpen(0) == NULL) {
		SDL_Log(SDL_GetError());
	}
#endif

	int upscale = 1;
	DvlIntSetting("upscale", &upscale);
	DvlIntSetting("fullscreen", (int *)&fullscreen);

	int grabInput = 1;
	DvlIntSetting("grab input", &grabInput);

#ifdef USE_SDL1
	int flags = SDL_SWSURFACE | SDL_HWPALETTE;
	if (fullscreen)
		flags |= SDL_FULLSCREEN;
	SDL_WM_SetCaption(lpWindowName, WINDOW_ICON_NAME);
	SDL_SetVideoMode(nWidth, nHeight, /*bpp=*/0, flags);
#ifdef VITA
	int scalingMode = 2;
	DvlVitaIntSetting("scaling mode", &scalingMode, false);
	switch (scalingMode) {
	case 2:
		SDL_SetVideoModeScaling(0, 0, 960, 544);
		break;
	case 1: {
		SDL_SetVideoModeScaling(118, 0, 724, 544);
		break;
	}
	default:
		SDL_SetVideoModeScaling(160, 32, 640, 480);
		break;
	}
	SDL_SetVideoModeBilinear(1);
#endif
	window = SDL_GetVideoSurface();
	if (grabInput)
		SDL_WM_GrabInput(SDL_GRAB_ON);
	atexit(SDL_VideoQuit); // Without this video mode is not restored after fullscreen.
#else
	int flags = 0;
	if (upscale) {
		flags |= fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_RESIZABLE;

		char scaleQuality[2] = "2";
		DvlStringSetting("scaling quality", scaleQuality, 2);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, scaleQuality);
	} else if (fullscreen) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	if (grabInput) {
		flags |= SDL_WINDOW_INPUT_GRABBED;
	}

	window = SDL_CreateWindow(lpWindowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, nWidth, nHeight, flags);
#endif
	if (window == NULL) {
		ErrSdl();
	}

	if (upscale) {
#ifndef USE_SDL1
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
		if (renderer == NULL) {
			ErrSdl();
		}

		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, nWidth, nHeight);
		if (texture == NULL) {
			ErrSdl();
		}
#ifdef VITA
		int scalingMode = 2;
		DvlVitaIntSetting("scaling mode", &scalingMode, false);
		switch (scalingMode) {
		case 2:
			if (!SDL_RenderSetLogicalSize(renderer, 960, 544) <= -1) {
				ErrSdl();
			}
			break;
		case 1: {
			if (!SDL_RenderSetLogicalSize(renderer, 724, 544) <= -1) {
				ErrSdl();
			}
			break;
		}
		default:
			if (!SDL_RenderSetLogicalSize(renderer, 640, 480) <= -1) {
				ErrSdl();
			}
			break;
		}
#else
		if (SDL_RenderSetLogicalSize(renderer, nWidth, nHeight) <= -1) {
			ErrSdl();
		}
#endif
#endif
	}

	return window != NULL;
}
} // namespace dvl
