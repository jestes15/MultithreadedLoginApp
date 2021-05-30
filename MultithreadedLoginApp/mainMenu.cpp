#include "mainMenu.h"

auto mainMenu::showMainMenu() -> void
{
	std::cout << menu;
	executeUserInput([]()
	{
		int userInput;
		std::cin >> userInput;
		return userInput;
	});
}

auto mainMenu::executeUserInput(std::function<int()> const& function) -> void
{
	switch (function())
	{
	case 1:
		executeCreateAccount([]() -> std::string
		{
			std::string input;
			std::cout << "What would you like your username to be?" << std::endl;
			std::cin >> input;
			return input;
		}, []() -> std::string
		{
			std::string input;
			std::cout << "What would you like your password to be?" << std::endl;
			std::cin >> input;
			return input;
		});
		break;
	case 2:
		executeLogin([]() -> std::string
		{
			std::string input;
			std::cout << "What is your username?" << std::endl;
			std::cin >> input;
			return input;
		}, []() -> std::string
		{
			std::string input;
			std::cout << "what is your password?" << std::endl;
			std::cin >> input;
			return input;
		});
		break;
	default:
		std::cout << "Option not valid" << std::endl;
	}
}

auto mainMenu::executeCreateAccount(std::function<std::string()> const& username, std::function<std::string()> const& password) -> void
{
	if (createAccount(username, password) == accountError_t::AccountCreationSuccessful)
	{
		std::cout << "Account creation successful" << std::endl;
		loggedIn = true;
	}
	else
		std::cout << "Could not create account" << std::endl;
}

auto mainMenu::executeLogin(std::function<std::string()> const& username, std::function<std::string()> const& password) -> void
{
	if (loggedIn)
		return;
	if (parseUserAccountInfo(username, password) == accountError_t::AccountCredentialsNotFound)
		std::cout << "Could not login" << std::endl;
}
