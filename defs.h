// some global definitions, found in debug release

#define DMAXX 40
#define DMAXY 40

#define LIGHTSIZE 6912 // 27 * 256

#define GMENU_SLIDER 0x40000000
#define GMENU_ENABLED 0x80000000

// must be unsigned to generate unsigned comparisons with pnum
#define MAX_PLRS 4

#define MAX_CHARACTERS 10
#define MAX_LVLMTYPES 16
// #define MAX_PATH				260
#define MAX_SEND_STR_LEN 80
#define MAX_SPELLS 37

#define MAXDEAD 31
#define MAXDUNX 112
#define MAXDUNY 112
#define MAXITEMS 127
#define MAXBELTITEMS 8
#define MAXLIGHTS 32
#define MAXMISSILES 125
#define MAXMONSTERS 200
#define MAXMULTIQUESTS 4
#define MAXOBJECTS 127
#define MAXPORTAL 4
#define MAXQUESTS 16
#define MAXTHEMES 50
#define MAXTILES 2048
#define MAXTRIGGERS 5
#define MAXVISION 32
#define MDMAXX 40
#define MDMAXY 40
#define MAXCHARLEVEL 51
#define ITEMTYPES 35

// number of inventory grid cells
#define NUM_INV_GRID_ELEM 40
#define INV_SLOT_SIZE_PX 28

// Item indestructible durability
#define DUR_INDESTRUCTIBLE 255

#define VOLUME_MIN -1600
#define VOLUME_MAX 0

// todo: enums
#define NUMLEVELS 17

// from diablo 2 beta
#define MAXEXP 2000000000

#define GOLD_SMALL_LIMIT 1000
#define GOLD_MEDIUM_LIMIT 2500
#define GOLD_MAX_LIMIT 5000

#define PLR_NAME_LEN 32

#define MAXPATHNODES 300

// 256 kilobytes + 3 bytes (demo leftover) for file magic (262147)
// final game uses 4-byte magic instead of 3
#define FILEBUFF ((256 * 1024) + 3)

#define PMSG_COUNT 8

// Diablo Retail Version Game ID
#define GAME_ID ((int)'DRTL')

// Diablo uses a 256 color palette
// Entry 0-127 (0x00-0x7F) are level specific
// Entry 128-255 (0x80-0xFF) are global

// standard palette for all levels
// 8 or 16 shades per color
// example (dark blue): PAL16_BLUE+14, PAL8_BLUE+7
// example (light red): PAL16_RED+2, PAL8_RED
// example (orange): PAL16_ORANGE+8, PAL8_ORANGE+4
#define PAL8_BLUE 128
#define PAL8_RED 136
#define PAL8_YELLOW 144
#define PAL8_ORANGE 152
#define PAL16_BEIGE 160
#define PAL16_BLUE 176
#define PAL16_YELLOW 192
#define PAL16_ORANGE 208
#define PAL16_RED 224
#define PAL16_GRAY 240

#ifdef VITA
#define SCREEN_WIDTH 724 //960
#define SCREEN_HEIGHT 544
#define ZOOM_WIDTH 434
#define ZOOM_HEIGHT 253
#else
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define ZOOM_WIDTH 384
#define ZOOM_HEIGHT 224
#endif

#define ZOOM_WIDTH 384
#define ZOOM_HEIGHT 224

// If defined, use 32-bit colors instead of 8-bit [Default -> Undefined]
//#define RGBMODE

#ifndef RGBMODE
#define SCREEN_BPP 8
#else
#define SCREEN_BPP 32
#endif

#define BORDER_LEFT 64
#define BORDER_TOP 160
#define BORDER_RIGHT 64
#define BORDER_BOTTOM 0

#define SCREEN_X BORDER_LEFT
#define SCREEN_Y BORDER_TOP

#define BUFFER_WIDTH (BORDER_LEFT + SCREEN_WIDTH + BORDER_RIGHT)
#define BUFFER_HEIGHT (BORDER_TOP + SCREEN_HEIGHT + BORDER_BOTTOM)
#define TILE_SIZE 32

#ifdef VITA
#define PANEL_WIDTH 724
#define PANEL_HEIGHT 145
#define PANEL_TOP (SCREEN_HEIGHT - PANEL_HEIGHT)
#define PANEL_Y (PANEL_TOP + SCREEN_Y)
#define PANEL_RIGHT (SCREEN_X + SCREEN_WIDTH - 362)
#else
#define PANEL_WIDTH 640
#define PANEL_HEIGHT 128
#define PANEL_TOP (SCREEN_HEIGHT - PANEL_HEIGHT)
#define PANEL_Y (PANEL_TOP + SCREEN_Y)
#define PANEL_RIGHT (SCREEN_X + SCREEN_WIDTH - 320)
#endif

#if SCREEN_WIDTH == PANEL_WIDTH
#define VIEWPORT_HEIGHT (SCREEN_HEIGHT - PANEL_HEIGHT)
#else
#define VIEWPORT_HEIGHT SCREEN_HEIGHT
#endif

#define SCREENXY(x, y) ((x) + SCREEN_X + ((y) + SCREEN_Y) * BUFFER_WIDTH)

#define MemFreeDbg(p)       \
	{                       \
		void *p__p;         \
		p__p = p;           \
		p    = NULL;        \
		mem_free_dbg(p__p); \
	}

#undef assert

#ifndef _DEBUG
#define assert(exp) ((void)0)
#else
#define assert(exp) (void)((exp) || (assert_fail(__LINE__, __FILE__, #exp), 0))
#endif

#define ERR_DLG(title, text) ErrDlg(title, text, __FILE__, __LINE__)

#ifndef INVALID_FILE_ATTRIBUTES
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)
#endif

// To apply to certain functions which have local variables aligned by 1 for unknown yet reason
#if (_MSC_VER == 1200)
#define ALIGN_BY_1 __declspec(align(1))
#else
#define ALIGN_BY_1
#endif

#define SwapLE32 SDL_SwapLE32
#define SwapLE16 SDL_SwapLE16

#define ErrSdl() ErrDlg("SDL Error", SDL_GetError(), __FILE__, __LINE__)
