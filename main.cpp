//  FCAI – Structured Programming – 2024 - Assignment 3
//  File: CS112_A3_T3_S3_20230309_S4_20230381_20230554.cpp
//  Purpose: Baby Photoshop for Image Processing
//  *********************************************************************************Authors*********************************************************************************
//  Mazen nasser >> Group A >> S3 >> 20230309 >> mazen.nasser143@gmail.com >> 
//  Marwan Hussein Galal >> Group A >> S4 >> 20230381 >> marwanhussein@gmail.com >>
//  Mohamed tarek >> Group A >> S4 >> 20230554 >> mohamedtarik06@gmail.com >> 
//  ********************************************************************************End Authors******************************************************************************
//  TA: Ahmed Fouad
//  Version: 1.0
//  Last Modification Date: 19/03/2024
//  ===================================================================================================================================================================   //
#include <iostream>
#include <algorithm>
#include "library/Image_Class.h"
using namespace std;

void insert_image() {

}

int save_image() {
    string savechoice;
    while (true) {
        cout << "\n*** How do you want to save your image? ***\n";
        cout << "A) Save as a new image\n";
        cout << "B) Replace the existing image\n";
        cout << "C) Back to the Main\n";
        cout << "Enter your choice: ";
        cin >> savechoice;
        transform (savechoice.begin(),savechoice.end(),savechoice.begin(),::toupper);
        if (savechoice == "A") {
            return 0;
        }else if (savechoice == "B") {
            return 0;
        }else if (savechoice == "C") {

        }
    }
}

int filters_menu() {
    string filterschoice;
    while (true) {
        cout << "\n***filters Menu***\n";
        cout << "A) Filter 1\n";
        cout << "B) Filter 2\n";
        cout << "C) Filter 3\n";
        cout << "D) Back to the Main\n";
        cout << "Enter your choice: ";
        cin >> filterschoice;
        transform (filterschoice.begin(),filterschoice.end(),filterschoice.begin(),::toupper);
        if (filterschoice == "A") {
            return 0;
        }else if (filterschoice == "B") {
            return 0;
        }else if (filterschoice == "C") {
            return 0;
        }else if (filterschoice == "D") {
            return 0;
        }
    }
}

int main() {
    cout << "           \n******Welcome to baby photoshop program******\n";
    string choice;
    while (true) {
        cout << "\n***Main Menu***\n";
        cout << "===============\n";
        cout << "A) Insert image\n";
        cout << "B) Apply filters\n";
        cout << "C) Save image\n";
        cout << "D) Exit the program\n";
        cout << "Enter your choice: ";
        cin >> choice;
        transform (choice.begin(),choice.end(),choice.begin(),::toupper);
        if (choice == "A") {
            insert_image();
        }else if (choice == "B") {
            filters_menu();
        }else if (choice=="C") {
            save_image();
            return 0;
        }else if (choice=="D") {
            return 0;
        }else{
            cout << "\nPlease enter a valid choice\n";
        }
    }
}