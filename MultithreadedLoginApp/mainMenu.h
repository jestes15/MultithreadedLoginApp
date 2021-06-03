#pragma once

#ifdef _WIN32
#include <Windows.h>
constexpr auto clear_msg = "cls";
#else
#include <unistd.h>
constexpr auto clear_msg = "clear";
#endif

#ifndef MULTITHREADEDLOGINSYS_MAINMENU_H
#define MULTITHREADEDLOGINSYS_MAINMENU_H

#include "loginFunctions.h"
#include "sha256.h"
#include "sha512.h"

class mainMenu : userAccount
{
public:
	auto showMainMenu() -> void;
	auto executeUserInput(std::function<int()> const&) -> void;
	auto executeCreateAccount(std::function<std::string()> const&, std::function<std::string()> const&) -> void;
	auto executeLogin(std::function<std::string()> const&, std::function<std::string()> const&) -> void;
	auto showLoginMenu() -> void;
private:
	static auto getSHA256Hash(std::function<std::string()> const&) -> std::string;
	static auto getSHA256Hash(std::function<std::string()> const&, std::string*) -> void;
	static auto getSHA256Hash(std::string const&) -> std::string;
	static auto getSHA256Hash(std::string const&, std::string*) -> void;
	
	static auto getSHA512Hash(std::function<std::string()> const&) -> std::string;
	static auto getSHA512Hash(std::function<std::string()> const&, std::string*) -> void;
	static auto getSHA512Hash(std::string const&) -> std::string;
	static auto getSHA512Hash(std::string const&, std::string*) -> void;

	
	bool loggedIn = false;
	bool continueShowingMenu = true;
	std::string menu = "Welcome user, would you like to create an account or log into an existing account?\n1) Create an account\n2) Login in\n";
};

#endif
