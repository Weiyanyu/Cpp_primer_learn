#include <iostream>
#include "Window.h"


using namespace std;

int main() {
    
    Screen myScreen1(15, 5, 'X'), myScreen2(20, 5, 'Y');

    Window_mgr windowMgr;
    windowMgr.addScreen(myScreen1).addScreen(myScreen2);
    
    windowMgr.display();
    

    return 0;
}