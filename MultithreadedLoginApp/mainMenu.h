#pragma once

#ifndef MULTITHREADEDLOGINSYS_MAINMENU_H
#define MULTITHREADEDLOGINSYS_MAINMENU_H
#include "loginFunctions.h"
class mainMenu : userAccount
{
public:
	void showMainMenu();
	void executeCreateAccount();
	void executeLogin();
private:
	bool loggedIn = false;
	std::string menu = "Welcome user, would you like to create an account or log into an existing account?\n1) Create an account\n2) Login in\n";
};

#endif
