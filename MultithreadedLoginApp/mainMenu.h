#pragma once

#ifndef MULTITHREADEDLOGINSYS_MAINMENU_H
#define MULTITHREADEDLOGINSYS_MAINMENU_H

#include "loginFunctions.h"

class mainMenu : userAccount
{
public:
	auto showMainMenu() -> void;
	auto executeUserInput(std::function<int()> const&) -> void;
	auto executeCreateAccount(std::function<std::string()> const&, std::function<std::string()> const&) -> void;
	auto executeLogin(std::function<std::string()> const&, std::function<std::string()> const&) -> void;
private:
	bool loggedIn = false;
	std::string menu = "Welcome user, would you like to create an account or log into an existing account?\n1) Create an account\n2) Login in\n";
};

#endif
