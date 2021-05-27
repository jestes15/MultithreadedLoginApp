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
	std::fstream file("shadow", std::ios::in | std::ios::out | std::ios::app);
	std::vector<std::pair<std::any, std::any>> accountData;
	auto username_data = username();
	auto password_data = password();
	accountData.push_back(std::pair<std::string, int>(username_data, username_data.length()));
	accountData.push_back(std::pair<std::string, int>(password_data, password_data.length()));
	accountData.push_back(std::pair<std::string, std::string>(sha256(username_data), sha256(password_data)));

	if (!file.is_open()) {
		accountError_t::CouldNotOpenFile;
	}
	
	file << usernameHeader << std::any_cast<std::string>(accountData[2].first) << std::endl;
	file << passwordHeader << std::any_cast<std::string>(accountData[2].second) << std::endl;

	return accountError_t::AccountCreationSuccessful;
}

userAccount::accountError_t userAccount::parseUserAccountInfo(std::string username, std::string password)
{
	std::vector<std::pair<std::string, std::string>> userData = {};
	std::thread grepPasswordsAndUsernames(
		[](std::vector<std::pair<std::string, std::string>>& userData, std::string& usernameHeader, std::string& passwordHeader)
		{
			std::string* data = new std::string[2];
			std::string fileData;
			std::fstream file("shadow", std::ios::in | std::ios::out | std::ios::app);
			int i = 0;
			while (!file.eof())
			{
				file >> fileData;
				std::string temp_data = fileData;
				if (fileData.erase(8, fileData.size()) == usernameHeader)
				{
					data[0] = temp_data.erase(0, 8);
				}
				if (fileData.erase(8, fileData.size()) == passwordHeader)
				{
					data[1] = temp_data.erase(0, 8);
				}
				i++;

				if (i % 2 == 0) {
					userData.push_back(std::pair<std::string, std::string>(data[0], data[1]));
				}
			}
		}, std::ref(userData), std::ref(usernameHeader), std::ref(passwordHeader));

	grepPasswordsAndUsernames.join();
	for (int i = 0; i < userData.size(); i++) {
		std::cout << "Iteration " << i << std::endl;
		std::cout << std::any_cast<std::string>(userData[i].first) << std::endl << std::any_cast<std::string>(userData[i].second) << std::endl << std::endl;

	}
	return accountError_t::AccountCredentialsFound;
}