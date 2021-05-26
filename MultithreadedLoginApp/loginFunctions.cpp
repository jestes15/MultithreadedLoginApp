#include "loginFunctions.h"

userAccount::accountError_t userAccount::createAccount(std::string username, std::string password)
{
	try {
		std::initializer_list<std::function<void(std::string)>> len = {
			[](const std::string username)
			{
				return username.length();
			},
			[](const std::string password)
			{
				return password.length();
			}
		};
	} catch (...)
	{
		return accountError_t::CouldNotCreateAccount;
	}

	std::cout << path << std::endl;
	return accountError_t::AccountCreationSuccessful;
}

userAccount::accountError_t userAccount::createAccount(std::function<std::string()> username, std::function<std::string()> password)
{
	std::vector<std::pair<std::any, std::any>> accountData;
	auto username_data = username();
	auto password_data = password();
	accountData.push_back(std::pair<std::string, int>(username_data, username_data.length()));
	accountData.push_back(std::pair<std::string, int>(password_data, password_data.length()));
	accountData.push_back(std::pair<std::string, std::string>(sha256(username_data), sha256(password_data)));

	std::fstream file("shadow", std::ios::in | std::ios::out | std::ios::app);

	file << "";

	if (!file.is_open()) {
		std::cout << "error" << std::endl;
		accountError_t::CouldNotOpenFile;
	}
	
	file << usernameHeader << std::any_cast<std::string>(accountData[2].first) << std::endl;
	file << passwordHeader << std::any_cast<std::string>(accountData[2].second) << std::endl;

	return accountError_t::AccountCreationSuccessful;
}