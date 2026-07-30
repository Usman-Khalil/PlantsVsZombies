#include "main_menu.h"
#include <ctime>
int main()
{
    srand(time(0));

    MainMenu main_menu;
    main_menu.initialize();

    return 0;
}