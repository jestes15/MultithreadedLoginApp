#include "loginFunctions.h"

int main()
{
    userAccount acc;
    acc.createAccount([]{
        std::string username;
        std::cin >> username;
        return username;
    }, []{
		std::string password;
        std::cin >> password;
    	return password;
        });

    acc.parseUserAccountInfo("Bane", "SAM");

    return 0;
}
