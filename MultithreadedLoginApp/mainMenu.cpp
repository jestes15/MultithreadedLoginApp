#include "mainMenu.h"

void mainMenu::showMainMenu()
{
	std::cout << menu;
	executeUserInput([]()
	{
		int userInput;
		std::cin >> userInput;
		return userInput;
	});
}

void mainMenu::executeUserInput(std::function<int()> function)
{
	switch (function())
	{
	case 1:
		executeCreateAccount([]()
		{
			std::string input;
			std::cout << "What would you like your username to be?" << std::endl;
			std::cin >> input;
			return input;
		}, []()
		{
			std::string input;
			std::cout << "What would you like your password to be?" << std::endl;
			std::cin >> input;
			return input;
		});
		break;
	case 2:
		executeLogin([]()
		{
			std::string input;
			std::cout << "What is your username?" << std::endl;
			std::cin >> input;
			return input;
		}, []()
		{
			std::string input;
			std::cout << "what is your password?" << std::endl;
			std::cin >> input;
			return input;
		});
		break;
	}
}

void mainMenu::executeCreateAccount(std::function<std::string()> username, std::function<std::string()> password)
{
	if (createAccount(username, password) == accountError_t::AccountCreationSuccessful)
	{
		std::cout << "Account creation successful" << std::endl;
		loggedIn = true;
	}
	else
	{
		std::cout << "Could not create account" << std::endl;
	}
	
}

void mainMenu::executeLogin(std::function<std::string()> username, std::function<std::string()> password)
{
	if (loggedIn)
		return;
	parseUserAccountInfo(username(), password());
}
