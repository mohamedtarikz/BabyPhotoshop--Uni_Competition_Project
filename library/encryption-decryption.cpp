#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <bitset>
#include <unistd.h>
#include <ctime>
#include "Image_Class.h"
#include "encryption-decryption.h"

using namespace std;
Image img_in;
Image img_filter;

string charToBinary(char c) {
    bitset<8> binary(c);
    return binary.to_string();
}

string str_to_binary() {
    string str, binary = "";
    while (true) {
        cout << "Enter a string: ";
        cin.ignore();
        getline(cin, str);
        if (str.length() > floor(img_filter.width * img_filter.height * 3 / 8) - 1) {
            cout << "uh-oh seems like we got a limit Harry, hmmm let me see... " << endl;
            sleep(1);
            cout << "we can write up to " << floor(img_filter.width * img_filter.height * 3 / 8) - 1 << " characters." << endl;
            continue;
        } else {
            break;
        }
    }
    for (int i = 0; i < str.length(); i++) {
        binary += charToBinary(str[i]);
    }
    return binary;
}

char binary_to_char(const std::string& binary_str) {
    char result = 0;
    for (size_t i = 0; i < 8; i++) {
        result <<= 1;
        result |= binary_str[i] - '0';
    }
    return result;
}

void encrypt_image() {
    cout << "Oh you littel devil wizard, you want to encrypt a message in the image? \n";
    cout << "let's do it! \n";
    string binary;
    binary = str_to_binary();
    binary += "00000000";
    int count = 0;
    int mod, binary_cahr;
    for (int j = 0; j < img_filter.height; j++) {
        for (int i = 0; i < img_filter.width; i++) {
            for (int k = 0; k < 3; k++) {
                binary_cahr = stoi(string(1, binary[count]));
                mod = img_filter(i, j, k) % 10;
                if (mod <= 5) {
                    img_filter(i, j, k) = img_filter(i, j, k) - mod;
                } else {
                    img_filter(i, j, k) = min(250, img_filter(i, j, k) + (10 - mod));
                }
                img_filter(i, j, k) = img_filter(i, j, k) + binary_cahr;
                count++;
                if (count == binary.length()) {
                    cout << "Now you have your secret.\n";
                    return;
                }
            }
        }
    }
}

string decrypt_image() {
    cout << "Oh you littel devil wizard, you want to decrypt a message from the image? \n";
    cout << "let's do it! \n";
    int binary_bit;
    string binary = "";
    string temp = "";
    char character;
    string final_string = "";
    for (int j = 0; j < img_filter.height; j++) {
        for (int i = 0; i < img_filter.width; i++) {
            for (int k = 0; k < 3; k++) {
                if ((img_filter(i,j,k)%10 > 1 || img_filter(i,j,k)%10 < 0)  && (binary == "" || binary.length() < 8)) {
                    return "Oh looks like there is nothing to decrypt here.";
                }
                binary_bit = img_filter(i, j, k) % 2;
                binary += to_string(binary_bit);
            }
        }
    }
    for (size_t i = 0; i < binary.length(); i++) {
        temp += binary[i];
        if (temp.length() == 8) {
            if (temp == "00000000") {
                return final_string;
            } else {
                character = binary_to_char(temp);
                final_string += character;
                temp = "";
            }
        }
    }
    return final_string;
}