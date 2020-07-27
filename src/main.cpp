#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "math.h"
#include "ASCIICrypt.h"
#include "HandleFile.h"

#define LOG(x) std::cout<<x<<std::endl;

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


static void menuEncrypt(const std::string filepath) {
    std::string key;
    std::string password;
    std::string type;

    //Ask info to user
    LOG("Attention, don't put accent in any character\nDon't use the character \":\", if used, will break the decryption")
        LOG("Password:")
            std::cin >> password;
        LOG("Key:")
            std::cin >> key;
        LOG("Label(just a label for the password,don't affect the encryption)")
            std::cin >> type;
    
    //Encrypt the password
    std::string cryptedPass = ASCIICrypt::encrypt(password, key);
    LOG("Your Cripted Pass is:")
    LOG(cryptedPass)
    
    //Put the Encrypted pass on a File
    HandleFile files(filepath);
    std::string line = '#' + type + ':' + cryptedPass;
    while (!files.write(line)) { LOG("CREATING DIRECTORY \"pass/passCrypt.pass\"") }
    
    //Exit
    LOG("Your password is Encrypted and saved on \"pass/passCrypt.pass\"!!\nPress any key to go back to menu")
    system("PAUSE");

}

static void showAllDecryptedPass(const std::string& filepath) {
    
    system("cls");
    std::string key;
    LOG("All your password will be decrypted using this key:")
    std::cin >> key;
    
    TypeSeparatePass types;
    HandleFile files(filepath);
    std::string line;
    std::stringstream fileContent = files.read();
    std::string result;

    while (getline(fileContent, line)) {
        if (line.find("#") != std::string::npos) {
            SeparateTypeFromPass(types, line);
            result +=(std::string)types.resType + "\n" + ASCIICrypt::decrypt(key, types.resPass) + "\n\n";
        }
    }
    
    LOG("All tour password decrypted using the key = " << key)
        LOG(result)
        LOG(std::endl << "Press any key to continue")
        system("PAUSE");

}

static void menu() {
    const std::string filepath = "pass/passCrypt.pass";
    ASCIICrypt encrypt;
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