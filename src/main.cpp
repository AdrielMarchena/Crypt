#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "math.h"

#define LOG(x) std::cout<<x<<std::endl;

//I got this code in https://stackoverflow.com/questions/11031159/converting-hexadecimal-to-decimal by christos
static unsigned long hex2dec(std::string hex)
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


struct TypeSeparatePass {
    std::string resPass;
    std::string resType;

    void clear() {
        resPass = "";
        resType = "";
    }
};

static void SeparateTypeFromPass(TypeSeparatePass& types,const std::string& line) {
    int position = 0;
    std::string resPass;
    std::string resType;
    
    position = line.find(":");
    resPass = line.substr(position+1,line.size() - position);
    resType = line.substr(0, position);

    types.resPass = resPass;
    types.resType = resType;
}

//Encrypt the pass based on the key passed
//Receive a pointer to the pass, key and the variable to assign into
static void ASCIICrypt(const std::string& pass,const std::string& key, std::string& cryptedPass) {
    int passChar = 0;
    int keyChar = 0;
    int keySizeMax = 0;
    std::stringstream intermediate;
    for (int i = 0; i < pass.size(); i++) {

        passChar = pass[i];
        keySizeMax = i % key.size();
        keyChar = key[keySizeMax];
        intermediate << std::hex << passChar * keyChar<< ":";
        cryptedPass += intermediate.str();
        intermediate.str("");
    }
}


static void Decrypt(const std::string& key,const std::string& passCrypted, std::string& decryptedText) {

    std::string intermediate;
    unsigned long getDec = 0;
    int keyCounter = 0;
    int keyChar = 0;
   for(int i=0;i< passCrypted.size();i++){
       if (passCrypted[i] == ':') {
           getDec = hex2dec(intermediate);
           keyChar = key[keyCounter % key.size()];

           decryptedText += (getDec / keyChar);
           keyCounter++;
           intermediate = "";
           continue;
       }
       intermediate += passCrypted[i];
   }
}

static bool WriteOnFile(const std::string& cryptedPass,const std::string& filepath,const std::string& passType) {

    std::fstream stream (filepath,std::ios::app);
    stream.clear();
    std::string typePass = "#" + passType;
    if (stream.is_open()) {

        stream << '\n' << typePass << ":" << cryptedPass;
        stream.close();
        return true;
    }
    else {
        std::ofstream outFile(filepath.c_str());
        system("mkdir pass");
        outFile << "";
        outFile.close();
        return false;
    }
}

static void menuEncrypt(const std::string filepath) {
    std::string key;
    std::string pass;
    std::string type;
    std::string cryptedPass;
    LOG("Attention, don't put accent in any character\nDon't use the character \":\", if used, will break the decryption")
        LOG("Password:")
        std::cin >> pass;
    LOG("Key:")
        std::cin >> key;
    LOG("Label(just a label for the password,don't affect the encryption)")
        std::cin >> type;

    ASCIICrypt(pass, key, cryptedPass);
    LOG("Your Cripted Pass is:")
        LOG(cryptedPass)

        while (!WriteOnFile(cryptedPass, filepath, type)) { LOG("CREATING DIRECTORY \"pass/passCrypt.pass\"") }

    LOG("Your password is Encrypted and saved on \"pass/passCrypt.pass\"!!\nPress any key to go back to menu")
        system("PAUSE");

}

static void showAllDecryptedPass(const std::string& filepath) {

    TypeSeparatePass types;
    std::string passDecrypted;
    std::string key;
    std::string line;
    std::ifstream stream(filepath);
    int position = 0;

    if (!stream.is_open()) {
        LOG("Any file with password was found, see if the directory \"pass/passCrypted.pass\" exist relative with this .exe")
            return;
    }

    LOG("All your passwords will be decrypted using this key\nSo, the only passwords that will make sense\nIs the ones that was Encrypted using this Key\nKey:")
    std::cin >> key;

    LOG("All your Passwords:")
        while (getline(stream, line)) {
            if (line.find("#") != std::string::npos) {
                SeparateTypeFromPass(types, line);
                Decrypt(key, types.resPass, passDecrypted);
                std::cout << types.resType << " : " << passDecrypted<<std::endl;
                passDecrypted = "";
                types.clear();
            }
        }
    
    stream.close();
    system("PAUSE");
}

static void menu() {
    std::string filepath = "pass/passCrypt.pass";
    char choice;
    while (true) {
        system("cls");
        LOG("====================")
        LOG("=======CRYPT!=======")
        LOG("")
        LOG("1 - Crypt your pass")
        LOG("2 - Decrypt all your pass")
        LOG("3 - exit")
        std::cin >> choice;

        switch (choice) {
            case '1':
                menuEncrypt(filepath);
            break;
            case '2':
                showAllDecryptedPass(filepath);
            break;
            case '3':
                LOG("Thanks for using my program, good Bye :)")
                    std::cin.get();
                return;
            break;
            default:
                system("cls");
                LOG("This option dont exist, select another")
            break;
        }
    }
}

int main(){
    menu();
}