#include <vector>

class Mod {
public:
    bool back, is, next;
    std::string text;
    int value;
};

class Menu {
public:
    std::string text;
    std::vector<Mod> mods;
    bool go;
};

///Global Variables
const int FRAME_RATE = 60;
JNIEnv *env;

///Part1 Variables
jobject appContext, gameContext;

///Part2 Variables
jobject OverlayView, canvas, paint;
bool icon = true;
int screenWidth, screenHeight, menuWidth, borderSize, iconY, iconX, curMenu, lineHeight, curLine = -1;
std::vector<Menu> menus;

///Menu Variables
PlayerInfo *playerInfo[100];
jobject espView, espCanvas;
void *camera, *oTransform;
float timescale_timer, esp_timer, crouch_timer;
bool blockKills;