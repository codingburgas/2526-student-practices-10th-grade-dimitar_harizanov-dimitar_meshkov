#include "UserStore.h"
#include <fstream>
using namespace std;

static const char* USERS_FILE = "users.txt";

namespace UserStore {

    bool UserExists(const string& username)
    {
        ifstream file(USERS_FILE);
        if (!file.is_open())
            return false;

        string storedUser, storedPass;
        while (getline(file, storedUser) && getline(file, storedPass))
        {
            if (storedUser == username)
                return true;
        }
        return false;
    }

    bool VerifyCredentials(const string& username, const string& password)
    {
        ifstream file(USERS_FILE);
        if (!file.is_open())
            return false;

        string storedUser, storedPass;
        while (getline(file, storedUser) && getline(file, storedPass))
        {
            if (storedUser == username && storedPass == password)
                return true;
        }
        return false;
    }

    bool CreateUser(const string& username, const string& password)
    {
        if (UserExists(username))
            return false;

        ofstream file(USERS_FILE, ios::app);
        if (!file.is_open())
            return false;

        file << username << "\n" << password << "\n";
        return true;
    }
}
