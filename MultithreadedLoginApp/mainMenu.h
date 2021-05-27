#pragma once

#ifdef MULTITHREADEDLOGINSYS_MAINMENU_H
#define MULTITHREADEDLOGINSYS_MAINMENU_H
#include "loginFunctions.h"
class mainMenu
{
public:
	void showMainMenu(userAccount acc);
	void executeCreateAccount();
	void executeLogin();
private:
	bool loggedIn = false;

};

#endif
