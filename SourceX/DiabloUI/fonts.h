#pragma once

#include "devilution.h"

#ifdef VITA
#ifdef USE_SDL1
#include <SDL/SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif
#else
#include <SDL_ttf.h>
#endif

#include "DiabloUI/art.h"

#ifndef TTF_FONT_PATH
#define TTF_FONT_PATH "CharisSILB.ttf"
#endif

namespace dvl {

enum _artFontTables {
	AFT_SMALL,
	AFT_MED,
	AFT_BIG,
	AFT_HUGE,
};

enum _artFontColors {
	AFC_SILVER,
	AFC_GOLD,
};

extern TTF_Font *font;
extern BYTE *FontTables[4];
extern Art ArtFonts[4][2];

void LoadArtFonts();
void UnloadArtFonts();

void LoadTtfFont();
void UnloadTtfFont();

} // namespace dvl
