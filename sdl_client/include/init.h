#ifndef INIT
#define INIT

#define SCREEN_WIDTH 480
#define SCREEN_HEIGTH 272
#define BPP 32
#define VIDEO_SDL_FLAGS (SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN)
#define WINDOW_CAPTION "HeggenVille (2018) - Calvin T. Maxwell"

void init (void);
void init_sdl (void);
void init_database (void);

extern SDL_Surface *p_screen;
extern SDL_Surface *map;
extern SDL_Surface *parallax;
extern SDL_Surface *gooble_sprite;
extern int camera_pos;

#endif
