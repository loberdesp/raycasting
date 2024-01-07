#include <SDL.h>
#include <SDL_image.h>
// #include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <chrono>

#define WINY 512
#define WINX WINY * 2
#define MAPSIZE 64
#define TILESIZE WINY / MAPSIZE
#define PSIZE WINY / 10
#define SENSITIVITY 0.4
#define FOV MAPSIZE
#define FPSCAP 144

#include "entity.h"
#include "player.h"
#include "map.h"
#include "soundcontrol.h"
#include "controls.h"
#include "dispcontrol.h"
#include "game.h"