#ifndef __CONSTANTS
#define __CONSTANTS

#include <string>
using namespace std;

const int MAX_UPGRADES = 10;
const bool DEBUG = false;
const int NUM_OF_TEXTURES = 9;
const string TEXTURE_IMAGES[NUM_OF_TEXTURES] = {"src/config/rocket.png", "src/config/shot.png", "src/config/asteroid_big_w.png", "src/config/asteroid_big_w2.png", "src/config/asteroid_med_w.png", "src/config/asteroid_med_w2.png", "src/config/asteroid_small_w.png", "src/config/asteroid_small_w2.png", "src/config/upgrade.png"};

const int UPGRADE_TYPES = 3;

const int SCREEN_FPS = 50;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

const int LEVELS = 15;

const string ASTEROIDS_INIT = "src/config/asteroidPos.ini";

const string HIGH_SCORE_INIT = "src/config/highScore.ini";

enum MENU_STATE {START, EXIT, GAME};

#endif