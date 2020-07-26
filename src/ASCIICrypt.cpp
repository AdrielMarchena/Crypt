#include <iostream>
#include <string>
#include <sstream>
#include "ASCIICrypt.h"

//Constructor
ASCIICrypt::ASCIICrypt(){}

std::string ASCIICrypt::encrypt(const std::string& pass, const std::string& key) {

    std::string encryptedPassword;
    int passChar = 0;
    int keyChar = 0;
    int keySizeMax = 0;
    std::stringstream getHex;
    for (int i = 0; i < pass.size(); i++) {

        passChar = pass[i];
        keySizeMax = i % key.size();
        keyChar = key[keySizeMax];
        getHex << std::hex << passChar * keyChar << ":";
        encryptedPassword += getHex.str();
        getHex.str("");
    }
    return encryptedPassword;
}

std::string ASCIICrypt::decrypt(const std::string& key, const std::string& passCrypted) {

    std::string intermediate, decryptedPassword;
    unsigned long getDec = 0;
    int keyCounter = 0;
    int keyChar = 0;
    for (int i = 0; i < passCrypted.size(); i++) {
        if (passCrypted[i] == ':') {
            getDec = hex2dec(intermediate);
            keyChar = key[keyCounter % key.size()];

            decryptedPassword += (getDec / keyChar);
            keyCounter++;
            intermediate = "";
            continue;
        }
        intermediate += passCrypted[i];
    }
    return decryptedPassword;
}

//I got this code in https://stackoverflow.com/questions/11031159/converting-hexadecimal-to-decimal by christos
unsigned long ASCIICrypt::hex2dec(std::string hex)
{
    unsigned long result = 0;
    for (int i = 0; i < hex.length(); i++) {
        if (hex[i] >= 48 && hex[i] <= 57)
        {
            result += (hex[i] - 48) * pow(16, hex.length() - i - 1);
        }
        else if (hex[i] >= 65 && hex[i] <= 70) {
            result += (hex[i] - 55) * pow(16, hex.length() - i - 1);
        }
        else if (hex[i] >= 97 && hex[i] <= 102) {
            result += (hex[i] - 87) * pow(16, hex.length() - i - 1);
        }
    }
    return result;
}
