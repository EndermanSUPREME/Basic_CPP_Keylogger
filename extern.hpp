#ifndef LOCKDOWN
#define LOCKDOWN
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <ctime>
#include <Windows.h>
#include <powrprof.h>
#pragma comment(lib, "PowrProf.lib")
/*

For setting up Administrator on Windows:
- powershell.exe as Administrator
- net user Administrator /active:yes
- $pass = ConvertTo-SecureString "adminPassword" -AsPlainText -Force; Set-LocalUser -Name "Administrator" -Password $pass
- net user Administrator :: to review the profile details
- Edit registries to disallow non-admins from running with administrator privilleges
*/

bool testing = false;

std::string emailCmd = "C:/Users/Public/Documents/lockdown/SendEmail.ps1 ";

void SendEmail(std::string);

std::string toLower(const std::string& str);

bool vectorContainsString(const std::vector<std::string>& vec, const std::string& str);

void ParseLine(std::string& line);

void GetKey();

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

std::ofstream outfile;
std::string CurrentSentence = "", logfile = "C:/Users/Public/Documents/lockdown/keys.txt";

std::vector<std::string> blacklistWords = {
    "Collect Words of Choice from online wordlists"
};
#endif