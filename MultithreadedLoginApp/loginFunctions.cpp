#include "loginFunctions.h"

userAccount::accountError_t userAccount::createAccount(std::string username, std::string password)
{
	std::fstream file("shadow", std::ios::in | std::ios::out | std::ios::app);
	std::vector<std::pair<std::any, std::any>> accountData;
	accountData.push_back(std::pair<std::string, int>(username, username.length()));
	accountData.push_back(std::pair<std::string, int>(password, password.length()));
	accountData.push_back(std::pair<std::string, std::string>(sha256(username), sha256(password)));

	file << usernameHeader << std::any_cast<std::string>(accountData[2].first) << std::endl << passwordHeader << std::any_cast<std::string>(accountData[2].second) << std::endl;
	return accountError_t::AccountCreationSuccessful;
}

userAccount::accountError_t userAccount::createAccount( std::function<std::string()> username, std::function<std::string()> password)
{
	std::fstream file("shadow", std::ios::in | std::ios::out | std::ios::app);
	std::vector<std::pair<std::any, std::any>> accountData;
	auto username_data = username();
	auto password_data = password();
	accountData.emplace_back(std::pair<std::string, int>(username_data, username_data.length()));
	accountData.emplace_back(std::pair<std::string, int>(password_data, password_data.length()));
	accountData.emplace_back(std::pair<std::string, std::string>(sha256(username_data), sha256(password_data)));
	file << usernameHeader << std::any_cast<std::string>(accountData[2].first) << std::endl << passwordHeader << std::any_cast<std::string>(accountData[2].second) << std::endl;

	return accountError_t::AccountCreationSuccessful;
}

userAccount::accountError_t userAccount::parseUserAccountInfo(std::string username, std::string password)
{
	std::thread grepPasswordsAndUsernames(
		[](std::vector<std::pair<std::string, std::string>>& userData, std::string& usernameHeader, std::string& passwordHeader)
		{
			auto* data = new std::string[2];
			std::string fileData;
			std::fstream file("shadow", std::ios::in | std::ios::out | std::ios::app);
			int i = 0;
			while (!file.eof())
			{
				file >> fileData;
				std::string tempData = fileData;
				if (fileData.erase(8, fileData.size()) == usernameHeader)
				{
					data[0] = tempData.erase(0, 8);
				}
				if (fileData.erase(8, fileData.size()) == passwordHeader)
				{
					data[1] = tempData.erase(0, 8);
				}
				i++;

				if (i % 2 == 0) {
					userData.emplace_back(std::pair<std::string, std::string>(data[0], data[1]));
				}
			}
		}, std::ref(userData), std::ref(usernameHeader), std::ref(passwordHeader));

	grepPasswordsAndUsernames.join();
	return accountError_t::AccountCredentialsFound;
}

std::vector<std::pair<std::string, std::string>> userAccount::getVector() {
	return userData;
}