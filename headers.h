#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <time.h>
#include <cmath>
#include <vector>



#define WINY 512
#define WINX WINY*2
#define MAPSIZE 64
#define TILESIZE WINY/MAPSIZE
#define PSIZE WINY/10


#include "player.h"
#include "map.h"
#include "soundcontrol.h"
#include "controls.h"
#include "dispcontrol.h"