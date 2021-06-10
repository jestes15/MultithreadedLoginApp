#include "loginFunctions.h"

#include <iostream>
#include <fstream>
#include <thread>
#include <map>

#include "sha256.h"

auto userAccount::updateUserData() -> void
{
	userData.erase(userData.begin(), userData.end());

	std::thread grepPasswordsAndUsernames(
		[&]() -> void
		{
				auto* data = new std::string[2];
				std::string fileData;
				std::fstream file("shadow", std::ios::in | std::ios::out | std::ios::app);
				while (!file.eof())
				{
					file >> fileData;
					std::cout << fileData << std::endl;
					if (!fileData.empty())
					{
						std::string tempData = fileData;
						data[0] = fileData.erase(fileData.find(delimiter), fileData.length());
						data[1] = tempData.erase(0, tempData.find(delimiter) + delimiter.length());
						userData.emplace_back(std::pair(data[0], data[1]));
					}
					fileData = "";
				}
		});
	grepPasswordsAndUsernames.join();
}


auto userAccount::createAccount(std::string const& username, std::string const& password) const -> accountError_t
{
	std::fstream file("shadow", std::ios::in | std::ios::out | std::ios::app);
	std::vector<std::pair<std::any, std::any>> accountData;
	accountData.emplace_back(std::pair<std::string, int>(username, username.length()));
	accountData.emplace_back(std::pair<std::string, int>(password, password.length()));
	accountData.emplace_back(std::pair(sha256(username), sha256(password)));

	file << std::any_cast<std::string>(accountData[2].first) << delimiter << std::any_cast<std::string>(accountData[2].second) << std::endl;
	return accountError_t::AccountCreationSuccessful;
}

auto userAccount::createAccount(std::function<std::string()> const& username, std::function<std::string()> const& password) -> accountError_t
{
	std::fstream file("shadow", std::ios::in | std::ios::out | std::ios::app);

	if (!file.is_open())
		return accountError_t::CouldNotCreateAccount;

	auto username_data = username();
	auto password_data = password();
	accountCreationVector.emplace_back(std::pair<std::string, int>(username_data, username_data.length()));
	accountCreationVector.emplace_back(std::pair<std::string, int>(password_data, password_data.length()));
	accountCreationVector.emplace_back(std::pair(sha256(username_data), sha256(password_data)));
	file << std::endl << std::any_cast<std::string>(accountCreationVector[2].first) << delimiter << std::any_cast<std::string>(accountCreationVector[2].second);

	return accountError_t::AccountCreationSuccessful;
}

auto userAccount::parseUserAccountInfo(std::function<std::any()> const& username, std::function<std::any()> const& password) -> accountError_t
{
	for (auto&& [i, d] : userData)
	{	
		if (std::any_cast<std::string>(i) == sha256(std::any_cast<std::string>(username())) && std::any_cast<std::string>(d) == sha256(std::any_cast<std::string>(password())))
			return accountError_t::AccountCredentialsFound;
	}
	
	return accountError_t::AccountCredentialsNotFound;
}

auto userAccount::getVector() const -> std::vector<std::pair<std::any, std::any>> {
	return userData;
}

userAccount::userAccount()
{
	userData.erase(userData.begin(), userData.end());

	std::thread grepPasswordsAndUsernames(
		[&]() -> void
		{
				auto* data = new std::string[2];
				std::string fileData;
				std::fstream file("shadow", std::ios::in | std::ios::out | std::ios::app);
				while (!file.eof())
				{
					file >> fileData;
					std::cout << fileData << std::endl;
					if (!fileData.empty())
					{
						std::string tempData = fileData;
						data[0] = fileData.erase(fileData.find(delimiter), fileData.length());
						data[1] = tempData.erase(0, tempData.find(delimiter) + delimiter.length());
						userData.emplace_back(std::pair(data[0], data[1]));
					}
					fileData = "";
				}
		});
	grepPasswordsAndUsernames.join();
}