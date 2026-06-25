#pragma once
#include <string>
using namespace std;

// Simple persistent account store backed by a plain-text file (users.txt).
// Each account is saved as two lines: the username, then the password.
// NOTE: this is plain text for simplicity, just like the rest of this app -
// it is not how real, secure account storage should work.
namespace UserStore {
    bool UserExists(const string& username);
    bool VerifyCredentials(const string& username, const string& password);
    bool CreateUser(const string& username, const string& password);
}
