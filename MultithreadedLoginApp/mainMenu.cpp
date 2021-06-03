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

	if (!loggedIn)
	{
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
	}
	while (continueShowingMenu) {
		showLoginMenu();
		system(clear_msg);
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
	std::cout << "Login successful, welcome" << std::endl;
	loggedIn = true;
}

auto mainMenu::getSHA256Hash(std::function<std::string()> const& userInput) -> std::string
{
	return sha256(userInput());
}

auto mainMenu::getSHA256Hash(std::function<std::string()> const& userInput, std::string* dest) -> void
{
	(*dest) = sha256(userInput());
}

auto mainMenu::getSHA256Hash(std::string const& source) -> std::string
{
	return sha256(source);
}

auto mainMenu::getSHA256Hash(std::string const& source, std::string* dest) -> void
{
	(*dest) = sha256(source);
}

auto mainMenu::getSHA512Hash(std::function<std::string()> const& func) -> std::string
{
	return sha512(func());
}

auto mainMenu::getSHA512Hash(std::function<std::string()> const& func, std::string* dest) -> void
{
	(*dest) = sha512(func());
}

auto mainMenu::getSHA512Hash(std::string const& source) -> std::string
{
	return sha512(source);
}

auto mainMenu::getSHA512Hash(std::string const& source, std::string* dest) -> void
{
	(*dest) = sha512(source);
}S

auto mainMenu::showLoginMenu() -> void
{
	std::cout << "What would you like to do?" << std::endl;
	std::cout << "0: Quite\nm1: Create 256 Hash\n2: Create 512 Hash" << std::endl;
	int val;
	std::cin >> val;

	switch (val)
	{
	case 0:
		{
			continueShowingMenu = false;
			break;
		}
	case 1:
		{
			std::string userInput;
			std::cout << "Enter the string you wish to get the 256 hash for" << std::endl;
			std::cin >> userInput;
			std::cout << sha256(userInput) << std::endl;
			break;
		}
	case 2:
		{
			std::string userInput;
			std::cout << "Enter the string you wish to get the 512 hash for" << std::endl;
			std::cin >> userInput;
			std::cout << sha512(userInput) << std::endl;
			break;
		}
	default:
		break;
	}
}