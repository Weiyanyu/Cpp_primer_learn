#include "Window.h"

const Screen::pos Window_mgr::DEFAULT_HEIGHT = 24;
const Screen::pos Window_mgr::DEFAULT_WIDTH  = 80;

Window_mgr &Window_mgr::addScreen(Screen &screen)
{
    screens.push_back(screen);
    return *this;
}