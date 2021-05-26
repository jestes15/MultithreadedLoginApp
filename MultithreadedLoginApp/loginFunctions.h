#pragma once
//
// Created by bl4z3 on 5/24/2021.
//

#ifndef MULTITHREADEDLOGINSYS_LOGINFUNCTIONS_H
#define MULTITHREADEDLOGINSYS_LOGINFUNCTIONS_H
#include <iostream>
#include <filesystem>
#include <fstream>
#include <functional>
#include <map>
#include <any>

#include "sha256.h"

class userAccount
{
public:
    enum class accountError_t {
        AccountCreationSuccessful [[maybe_unused]] = 0xFF0,
        CouldNotCreateAccount [[maybe_unused]] = 0xFF1,
        ThreadReturnedUnknownValue [[maybe_unused]] = 0xFB1,
        CouldNotOpenFile [[maybe_unused]] = 0xF1,
        CouldNotFindUsername [[maybe_unused]] = 0xFF2,
        CouldNotFindPassword [[maybe_unused]] = 0xFF3
    };
	
    typedef int (accountError)(accountError_t);
    accountError_t createAccount(std::string username, std::string password);
    accountError_t createAccount(std::function<std::string()> username, std::function<std::string()> password);
    accountError_t parseUserAccountInfo(std::fstream file);
	
    std::filesystem::path path{ std::filesystem::current_path() };

private:
    struct userData {
        std::string password;
        std::string username;
        accountError_t error;
    };
    std::string usernameHeader = ":0x8326:";
    std::string passwordHeader = ":0x8327:";
};
#endif //MULTITHREADEDLOGINSYS_LOGINFUNCTIONS_H
