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
#include <string>
#include "library/Image_Class.h"

using namespace std;
Image uimage;

string imginput;

void Invert_Image()
{
    for (int i = 0; i < uimage.width; i++)
    {
        for (int j = 0; j < uimage.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                uimage(i, j, k) = 255 - (uimage(i, j, k));
            }
        }
    }
}


void greyscale()
{
    for (int i = 0; i < uimage.width; i++)
    {
        for (int j = 0; j < uimage.height; j++)
        {
            int av = 0;
            for (int k = 0; k < 3; k++)
            {
                av += uimage(i, j, k);
            }
            av /= 3;
            for (int k = 0; k < 3; k++)
            {
                uimage(i, j, k) = av;
            }
        }
    }
}

void black_and_white()
{
    for (int i = 0; i < uimage.width; i++)
    {
        for (int j = 0; j < uimage.height; j++)
        {
            int av = 0;
            for (int k = 0; k < 3; k++)
            {
                av += uimage(i, j, k);
            }
            av /= 3;
            for (int k = 0; k < 3; k++)
            {
                uimage(i, j, k) = av;
            }
            if (uimage(i, j, 0) < 128)
            {
                uimage(i, j, 0) = 0;
                uimage(i, j, 1) = 0;
                uimage(i, j, 2) = 0;
            }
            else
            {
                uimage(i, j, 0) = 255;
                uimage(i, j, 1) = 255;
                uimage(i, j, 2) = 255;
            }
        }
    }
}

Image Rotate_Image()
{
    Image img(uimage.height, uimage.width);
    for (int i = 0; i < uimage.width; i++)
    {
        for (int j = 0; j < uimage.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                img(i, j, k) = uimage(i, j, k);
            }
        }
    }
    return img;
}

void flip_image(){
    Image flipped (uimage.width, uimage.height);
    
    // Flip the image in x direction
    for (int i = 0; i < uimage.width; i++){
        for (int j = 0; j < uimage.height; j++){
            for (int k=0 ; k<3 ; k++){
                flipped(i,j,k) = uimage(uimage.width-i,j,k);
            }
        }
    }
    // Flip the image in y direction
    for (int i = 0; i < uimage.width; i++){
        for (int j = 0; j < uimage.height; j++){
            for (int k=0 ; k<3 ; k++){
                flipped(i,j,k) = uimage(i,uimage.height-j,k);
            }
        }
    }
    uimage = flipped;
    uimage.saveImage("m.png");
}

int insert_image()
{
    while (true)
    {
        cout << "Please enter image name with it's extension: ";
        cin >> imginput;
        try
        {
            uimage.loadNewImage(imginput);
            break;
        }
        catch (invalid_argument)
        {
            continue;
        }
    }
    return 0;
}

int save_image(Image img)
{
    string savechoice;
    while (true)
    {
        cout << "\n*** How do you want to save your image? ***\n";
        cout << "===========================================\n";
        cout << "A) Save as a new image\n";
        cout << "B) Replace the existing image\n";
        cout << "C) Back to the Main menu\n";
        cout << "===========================================\n";
        cout << "Enter your choice: ";
        cin >> savechoice;
        transform(savechoice.begin(), savechoice.end(), savechoice.begin(), ::toupper);
        if (savechoice == "A")
        {
            string outimg;
            while (true)
            {
                try
                {
                    cout << "\nPlease enter image name with it's extension: ";
                    cin >> outimg;
                    img.saveImage(outimg);
                    break;
                }
                catch (invalid_argument)
                {
                    continue;
                }
            }
            return 0;
        }
        else if (savechoice == "B")
        {
            while (true)
            {
                try
                {
                    img.saveImage(imginput);
                    break;
                }
                catch (invalid_argument)
                {
                    continue;
                }
            }
            return 0;
        }
        else if (savechoice == "C")
        {
            return 0;
        }
        else
        {
            cout << "\nPlease enter a valid choice\n";
        }
    }
}

int filters_menu()
{
    string filterschoice;
    while (true)
    {
        cout << "\n***filters Menu***\n";
        cout << "===================\n";
        cout << "A) Greyscale\n";
        cout << "B) Black and White\n";
        cout << "C) Invert image\n";
        cout << "D) Filter 4\n";
        cout << "E) Flip\n";
        cout << "F) Rotate image\n";
        cout << "G) Clear All Filters\n";
        cout << "H) Back to the Main\n";
        cout << "===================\n";
        cout << "Enter your choice: ";
        cin >> filterschoice;
        transform(filterschoice.begin(), filterschoice.end(), filterschoice.begin(), ::toupper);
        if (filterschoice == "A")
        {
            greyscale();
            return 0;
        }
        else if (filterschoice == "B")
        {
            black_and_white();
            return 0;
        }
        else if (filterschoice == "C")
        {
            Invert_Image();
            return 0;
        }
        else if (filterschoice == "D")
        {
            return 0;
        }
        else if (filterschoice == "E")
        {
            flip_image();
            return 0;
        }
        else if (filterschoice == "F")
        {
            int deg;
            cout << "enter degree: ";
            cin >> deg;
            deg /= 90;
            deg %= 4;
            deg++;
            Image a(uimage.height, uimage.width), b(uimage.width, uimage.height), c(uimage.height, uimage.width), d(uimage.width, uimage.height);
            for (int i = 1; i <= deg; i++)
            {
                if (i == 1)
                    a = Rotate_Image();
                else if (i == 2)
                    b = Rotate_Image();
                else if (i == 3)
                    c = Rotate_Image();
                else
                    d = Rotate_Image();
            }
            if (deg == 1)
                a.saveImage("new.jpg");
            else if (deg == 2)
                b.saveImage("new.jpg");
            else if (deg == 3)
                c.saveImage("new.jpg");
            else if (deg == 4)
                d.saveImage("new.jpg");
            return 0;
        }
        else if (filterschoice == "G")
        {
            uimage.loadNewImage(imginput);
            cout << "All filters has been cleared";
        }
        else if (filterschoice == "H")
        {
            return 0;
        }
        else
        {
            cout << "\nPlease enter a valid choice\n";
        }
    }
}

int main()
{
    cout << "           \n******Welcome to baby photoshop program******\n";
    string choice;
    while (true)
    {
        cout << "\n***Main Menu***\n";
        cout << "===================\n";
        cout << "A) Insert image\n";
        cout << "B) Apply filters\n";
        cout << "C) Save image\n";
        cout << "D) Exit the program\n";
        cout << "===================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        transform(choice.begin(), choice.end(), choice.begin(), ::toupper);
        if (choice == "A")
        {
            insert_image();
        }
        else if (choice == "B")
        {
            filters_menu();
        }
        else if (choice == "C")
        {
            save_image(uimage);
        }
        else if (choice == "D")
        {
            return 0;
        }
        else
        {
            cout << "\nPlease enter a valid choice\n";
        }
    }
}