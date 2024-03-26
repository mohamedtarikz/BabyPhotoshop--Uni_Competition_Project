//  FCAI – Structured Programming – 2024 - Assignment 3
//  File: CS112_A3_S3_20230309_S4_20230381_20230554.cpp
//  Purpose: Baby Photoshop for Image Processing
//  *********************************************************************************Authors*********************************************************************************
//  Mazen nasser >> Group A >> S3 >> 20230309 >> mazen.nasser143@gmail.com >> greyscale, 
//  Marwan Hussein Galal >> Group A >> S4 >> 20230381 >> marwanhussein@gmail.com >> black and white, Flip
//  Mohamed tarek >> Group A >> S4 >> 20230554 >> mohamedtarik06@gmail.com >> Invert, 
//  ********************************************************************************End Authors******************************************************************************
//  TA: Ahmed Fouad
//  Version: 1.0
//  Last Modification Date: 25/03/2024
//  ===================================================================================================================================================================   //
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include "library/Image_Class.h"

using namespace std;
Image uimage;

string imginput;

void greyscale() {
    for (int i = 0; i < uimage.width; i++) {
        for (int j = 0; j < uimage.height; j++) {
            int av = 0;
            for (int k = 0; k < 3; k++) {
                av += uimage(i, j, k);
            }
            av /= 3;
            for (int k = 0; k < 3; k++) {
                uimage(i, j, k) = av;
            }
        }
    }
}

void black_and_white() {
    for (int i = 0; i < uimage.width; i++) {
        for (int j = 0; j < uimage.height; j++) {
            int av = 0;
            for (int k = 0; k < 3; k++) {
                av += uimage(i, j, k);
            }
            av /= 3;
            for (int k = 0; k < 3; k++) {
                uimage(i, j, k) = av;
            }
            if (uimage(i, j, 0) < 128) {
                uimage(i, j, 0) = 0;
                uimage(i, j, 1) = 0;
                uimage(i, j, 2) = 0;
            } else {
                uimage(i, j, 0) = 255;
                uimage(i, j, 1) = 255;
                uimage(i, j, 2) = 255;
            }
        }
    }
}

void Invert_Image() {
    for (int i = 0; i < uimage.width; i++) {
        for (int j = 0; j < uimage.height; j++) {
            for (int k = 0; k < 3; k++) {
                uimage(i, j, k) = 255 - (uimage(i, j, k));
            }
        }
    }
}

void flip_horizontally() {
    // Flip the image in x direction
    Image flipped(uimage.width, uimage.height);
    for (int i = 0; i < uimage.width; i++) {
        for (int j = 0; j < uimage.height; j++) {
            for (int k = 0; k < 3; k++) {
                flipped(i, j, k) = uimage(uimage.width - i, j, k);
            }
        }
    }
    for (int i = 0; i < flipped.width; i++) {
        for (int j = 0; j < flipped.height; j++) {
            for (int k = 0; k < 3; k++) {
                uimage(i, j, k) = flipped(i, j, k);
            }
        }
    }
}

void flip_vertically() {
    // Flip the image in y direction
    Image flipped(uimage.width, uimage.height);
    for (int i = 0; i < uimage.width; i++) {
        for (int j = 0; j < uimage.height; j++) {
            for (int k = 0; k < 3; k++) {
                flipped(i, j, k) = uimage(i, uimage.height - j, k);
            }
        }
    }
    for (int i = 0; i < flipped.width; i++) {
        for (int j = 0; j < flipped.height; j++) {
            for (int k = 0; k < 3; k++) {
                uimage(i, j, k) = flipped(i, j, k);
            }
        }
    }
}

int flip_image() {
    string flipchoice;
    while (true) {
        cout << "\n*** How do you want to save your image? ***\n";
        cout << "===========================================\n";
        cout << "A) Flip horizontally\n";
        cout << "B) Flip vertically\n";
        cout << "C) Flip horizontally and vertically\n";
        cout << "D) Back to filters menu\n";
        cout << "===========================================\n";
        cout << "Enter your choice: ";
        cin >> flipchoice;
        transform(flipchoice.begin(), flipchoice.end(), flipchoice.begin(), ::toupper);
        if (flipchoice == "A") {
            flip_horizontally();
            return 0;
        } else if (flipchoice == "B") {
            flip_vertically();
            return 0;
        } else if (flipchoice == "C") {
            flip_horizontally();
            flip_vertically();
            return 0;
        } else if (flipchoice == "D") {
            return 0;
        } else {
            cout << "\nPlease enter a valid choice\n";
        }
    }
}

// Image Rotate_Image() {
//     Image img(uimage.height, uimage.width);
//     for (int i = 0; i < uimage.width; i++) {
//         for (int j = 0; j < uimage.height; j++) {
//             for (int k = 0; k < 3; k++) {
//                 img(i, j, k) = uimage(i, j, k);
//             }
//         }
//     }
//     int deg;
//     cout << "enter degree: ";
//     cin >> deg;
//     deg /= 90;
//     deg %= 4;
//     deg++;
//     Image a(uimage.height, uimage.width), b(uimage.width, uimage.height), c(uimage.height, uimage.width), d(uimage.width, uimage.height);
//     for (int i = 1; i <= deg; i++) {
//         if (i == 1)
//             a = Rotate_Image();
//         else if (i == 2)
//             b = Rotate_Image();
//         else if (i == 3)
//             c = Rotate_Image();
//         else
//             d = Rotate_Image();
//     }
//     if (deg == 1)
//         a.saveImage("new.jpg");
//     else if (deg == 2)
//         b.saveImage("new.jpg");
//     else if (deg == 3)
//         c.saveImage("new.jpg");
//     else if (deg == 4)
//         d.saveImage("new.jpg");
//     return img;
// }

int insert_image() {
    while (true) {
        cout << "Please enter image name with it's extension: ";
        cin >> imginput;
        try {
            uimage.loadNewImage(imginput);
            break;
        } catch (invalid_argument) {
            continue;
        }
    }
    return 0;
}

// CHat Gpt
// void resize(){
//     int newWidth=0,newHeight=0;
//     cout << "Enter the width of the resized Image : ";
//     cin >> newWidth;
//     cout << "Enter the height of the resized Image : ";
//     cin >> newHeight;
//     Image mimage(newWidth,newHeight);
//     float scaleX = (float)uimage.width / newWidth;
//     float scaleY = (float)uimage.height / newHeight;

//     for (int y = 0; y < newHeight; ++y) {
//         for (int x = 0; x < newWidth; ++x) {
//             // Calculate the position in the original image
//             float srcX = (x + 0.5f) * scaleX - 0.5f;
//             float srcY = (y + 0.5f) * scaleY - 0.5f;

//             // Calculate integer coordinates of the four surrounding pixels
//             int x0 = int(srcX);
//             int y0 = int(srcY);
//             int x1 = min(x0 + 1, uimage.width - 1);
//             int y1 = min(y0 + 1, uimage.height - 1);

//             // Calculate the fractional part of the coordinates
//             float xFraction = srcX - x0;
//             float yFraction = srcY - y0;

//             // Perform bilinear interpolation for each color channel
//             for (int c = 0; c < uimage.channels; ++c) {
//                 float top = (1 - xFraction) * uimage.getPixel(x0, y0, c) + xFraction * uimage.getPixel(x1, y0, c);
//                 float bottom = (1 - xFraction) * uimage.getPixel(x0, y1, c) + xFraction * uimage.getPixel(x1, y1, c);
//                 float newValue = (1 - yFraction) * top + yFraction * bottom;
//                 mimage.setPixel(x, y, c, (unsigned char)newValue);
//             }
//         }
//     }
//     mimage.saveImage("resized.png");
// }

// our
// void resize(){
//     int nwidth,nhight;
//     cout << "enter the width: ";
//     cin >> nwidth;
//     cout << "enter the hight: ";
//     cin >> nhight;
//     Image mimage(nwidth,nhight);
//     int swidth= ((double)uimage.width/(double)nwidth);
//     int sheight= ((double)uimage.height/(double)nhight);
//     int swl=uimage.width%mimage.width,shl=uimage.height%mimage.height;
//     int avgr,avgb,avgg,idx;
//     Image Big(uimage.width+swl,uimage.height+shl);
//     for (int i = 0; i < Big.height; i++) {
//         for (int j = 0; j < Big.width; j++) {
//             for (int k = 0; k < 3; k++) {
//                 if (j >= uimage.width){
//                     Big(j, i, k) = 0;
//                 }else{
//                     Big(j, i, k) = uimage(j,i,k);
//                 }
//             }
//         }
//     }
    // swidth= (Big.width/nwidth);
    // sheight= (Big.height/nhight);
    // for (int i = 0; i < mimage.height; ++i) {
    //     idx=0;
    //     for (int j = 0; j < mimage.width; ++j) {
    //         avgr=avgb=avgg=0;
    //         for (int k = 0; k < swidth; ++k) {
    //             avgr+=Big(idx,i,0);
    //             avgb+=Big(idx,i,1);
    //             avgg+=Big(idx,i,2);
    //             idx++;
    //             if (idx>=uimage.width){
    //                 break;
    //             }
    //         }
    //         avgr/=swidth;
    //         avgb/=swidth;
    //         avgg/=swidth;
    //         mimage(j,i,0) = avgr;
    //         mimage(j,i,1) = avgb;
    //         mimage(j,i,2) = avgg;
    //         if (idx>=uimage.width){
    //                 break;
    //             }
    //     }
    // }
    // for(int i = uimage.width-swl; i <uimage.width;i++) {
    //     for(int j = uimage.height-shl; j <uimage.height;i++){
            
    //     }
    // }
    // for (int i = 0; i < mimage.width; ++i) {
    //     idx=0;
    //     for (int j = 0; j < mimage.height; ++j) {
    //         avgr=avgb=avgg=0;
    //         for (int k = 0; k < sheight; ++k) {
    //             avgr+=uimage(i,idx,0);
    //             avgb+=uimage(i,idx,1);
    //             avgg+=uimage(i,idx,2);
    //             idx++;
    //             if (idx==uimage.height){
    //                 break;
    //             }
    //         }
    //         avgr/=sheight;
    //         avgb/=sheight;
    //         avgg/=sheight;
    //         mimage(i,int(idx/sheight)-1,0) = avgr;
    //         mimage(i,int(idx/sheight)-1,1) = avgb;
    //         mimage(i,int(idx/sheight)-1,2) = avgg;
    //     }
    // }
    // mimage.saveImage("BigBig.jpg");
// }

int save_image(Image img) {
    string savechoice;
    while (true) {
        cout << "\n*** How do you want to save your image? ***\n";
        cout << "===========================================\n";
        cout << "A) Save as a new image\n";
        cout << "B) Replace the existing image\n";
        cout << "C) Back to the Main menu\n";
        cout << "===========================================\n";
        cout << "Enter your choice: ";
        cin >> savechoice;
        transform(savechoice.begin(), savechoice.end(), savechoice.begin(), ::toupper);
        if (savechoice == "A") {
            string outimg;
            while (true) {
                try {
                    cout << "\nPlease enter image name with it's extension: ";
                    cin >> outimg;
                    img.saveImage(outimg);
                    break;
                } catch (invalid_argument) {
                    continue;
                }
            }
            return 0;
        } else if (savechoice == "B") {
            while (true) {
                try {
                    img.saveImage(imginput);
                    break;
                } catch (invalid_argument) {
                    continue;
                }
            }
            return 0;
        } else if (savechoice == "C") {
            return 0;
        } else {
            cout << "\nPlease enter a valid choice\n";
        }
    }
}

int filters_menu() {
    string filterschoice;
    while (true) {
        cout << "\n***filters Menu***\n";
        cout << "===================\n";
        cout << "A) Grey scale\n";
        cout << "B) Black and White\n";
        cout << "C) Invert image\n";
        cout << "D) Merge\n";
        cout << "E) Flip\n";
        cout << "F) Rotate image\n";
        cout << "G) Resize\n";
        cout << "H) Clear All Filters\n";
        cout << "I) Back to the Main\n";
        cout << "===================\n";
        cout << "Enter your choice: ";
        cin >> filterschoice;
        transform(filterschoice.begin(), filterschoice.end(), filterschoice.begin(), ::toupper);
        if (filterschoice == "A") {
            greyscale();
            return 0;
        } else if (filterschoice == "B") {
            black_and_white();
            return 0;
        } else if (filterschoice == "C") {
            Invert_Image();
            return 0;
        } else if (filterschoice == "D") {
            return 0;
        } else if (filterschoice == "E") {
            flip_image();
            return 0;
        } else if (filterschoice == "F") {
            // Rotate_Image();
            return 0;
        } else if (filterschoice == "G") {
            // resize();
            return 0;
        } else if (filterschoice == "H") {
            uimage.loadNewImage(imginput);
            cout << "All filters has been cleared";
        } else if (filterschoice == "I") {
            return 0;
        } else {
            cout << "\nPlease enter a valid choice\n";
        }
    }
}

int main() {
    cout << "           \n******Welcome to baby photoshop program******\n";
    string choice;
    while (true) {
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
        if (choice == "A") {
            insert_image();
        } else if (choice == "B") {
            filters_menu();
        } else if (choice == "C") {
            save_image(uimage);
        } else if (choice == "D") {
            return 0;
        } else {
            cout << "\nPlease enter a valid choice\n";
        }
    }
}