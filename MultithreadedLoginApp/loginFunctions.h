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
#include <thread>
#include <map>
#include <any>

#include "sha256.h"

class userAccount
{
public:
    enum class accountError_t {
        AccountCreationSuccessful [[maybe_unused]] = 0xFF0,
        AccountCredentialsFound [[maybe_unused]] = 0xFFF,
    	AccountCredentialsNotFound [[maybe_unused]] = 0xFFE,
        CouldNotCreateAccount [[maybe_unused]] = 0xFF1,
        ThreadReturnedUnknownValue [[maybe_unused]] = 0xFB1,
        CouldNotOpenFile [[maybe_unused]] = 0xF1,
        CouldNotFindUsername [[maybe_unused]] = 0xFF2,
        CouldNotFindPassword [[maybe_unused]] = 0xFF3
    };
	
    auto createAccount(std::string const& username, std::string const& password) -> accountError_t; 
    auto createAccount(std::function<std::string()> const& username, std::function<std::string()> const& password) -> accountError_t;
    auto parseUserAccountInfo(std::function<std::any()> const& username, std::function<std::any()> const& password) -> accountError_t;

    auto getVector() -> std::vector<std::pair<std::any, std::any>>;
	
    std::filesystem::path const path{ std::filesystem::current_path() };

private:
	struct userData {
        std::string password;
        std::string username;
        accountError_t error;
    };
    std::string const usernameHeader = ":0x8326:";
    std::string const passwordHeader = ":0x8327:";
    std::vector<std::pair<std::any, std::any>> userData = {};
};
#endif
