#pragma once
#include <string>
using namespace std;

namespace UserStore {
    bool UserExists(const string& username);
    bool VerifyCredentials(const string& username, const string& password);
    bool CreateUser(const string& username, const string& password);
}
