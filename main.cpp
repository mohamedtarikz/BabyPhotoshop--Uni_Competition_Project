//  FCAI – Structured Programming – 2024 - Assignment 3
//  File: CS112_A3_Part1_S3_20230309_S4_20230381_20230554.cpp
//  Purpose: Baby Photoshop for Image Processing
//  Flow map link: https://drive.google.com/file/d/1efY7Dc3V8tU-0ygiAyMTlVMV-9hApo94/view?usp=sharing
//  *********************************************************************************Authors*********************************************************************************
//  Mazen nasser >> Group A >> S3 >> 20230309 >> mazen.nasser143@gmail.com >> greyscale, merge
//  Marwan Hussein Galal >> Group A >> S4 >> 20230381 >> marwanhussein@gmail.com >> black and white, Flip, menus, error handling
//  Mohamed tarek >> Group A >> S4 >> 20230554 >> mohamedtarik06@gmail.com >> Invert, rotate
//  ********************************************************************************End Authors******************************************************************************
//  TA: Ahmed Fouad
//  Version: 1.1
//  Last Modification Date: 28/03/2024
//  =============================================================================================================================================================================   //
/*
                                                                \\ Version 1 Notes //
    - "Image_Class.h" V1.0
    - The program can handle only two images at a time and they should be in the same directory as the executable file or absolute path to them.
    - Merging Function works on partial crop of the top right corner image with dimentions of the smaller image (will be fixed in V2-Part 2 inshaalah after making resize).
    - Merging two images and rotating images are saved directly (will be fixed in the next version inshaalah with "temp file creation" saving system).
    - The program can handle images with different sizes (width and height).
    - The program stays at filters menu in case you want to apply more than one filter Notice that you can't apply more than one filter on rotated or merged images (until now).
*/
//  =============================================================================================================================================================================   //
/*
                                                                \\ Version 1.1 Notes //
    - "Image_Class.h" V2.0
    -  V1.0 issues fixed by due to the updated library.
*/
//  =============================================================================================================================================================================   //
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include "library/Image_Class.h" // use V2.0 OR

using namespace std;
Image img_in;
string imginput;

// Function to convert the input image to grayscale
void greyscale() {
    // Iterate through each pixel in the image
    for (int i = 0; i < img_in.width; i++) {
        for (int j = 0; j < img_in.height; j++) {
            int av = 0; // Initialize average value
            // Calculate average pixel value across RGB channels
            for (int k = 0; k < 3; k++) {
                av += img_in(i, j, k);
            }
            av /= 3; // Compute the average
            // Set each RGB channel to the average value to convert to grayscale
            for (int k = 0; k < 3; k++) {
                img_in(i, j, k) = av;
            }
        }
    }
}

// Function to convert the input image to black and white
void black_and_white() {
    // Iterate through each pixel in the image
    for (int i = 0; i < img_in.width; i++) {
        for (int j = 0; j < img_in.height; j++) {
            int av = 0; // Initialize average value
            // Calculate average pixel value across RGB channels
            for (int k = 0; k < 3; k++) {
                av += img_in(i, j, k);
            }
            av /= 3; // Compute the average
            // Set each RGB channel to the average value
            for (int k = 0; k < 3; k++) {
                img_in(i, j, k) = av;
            }
            // Convert to black and white based on threshold (128)
            if (img_in(i, j, 0) < 128) {
                img_in(i, j, 0) = 0;
                img_in(i, j, 1) = 0;
                img_in(i, j, 2) = 0;
            } else {
                img_in(i, j, 0) = 255;
                img_in(i, j, 1) = 255;
                img_in(i, j, 2) = 255;
            }
        }
    }
}

// Function to invert the colors of the input image
void Invert_Image() {
    // Iterate through each pixel in the image
    for (int i = 0; i < img_in.width; i++) {
        for (int j = 0; j < img_in.height; j++) {
            // Invert each RGB channel by subtracting from 255
            for (int k = 0; k < 3; k++) {
                img_in(i, j, k) = 255 - (img_in(i, j, k));
            }
        }
    }
}

// Function to merge the input image with another image
void merge_Images() {
    string second_image; // Variable to store the name of the second image
    Image img_second; // Object to hold the second image
    // Loop until a valid second image is loaded
    while (true) {
        cout << "Please enter second image name with its extension: ";
        cin >> second_image;
        try {
            img_second.loadNewImage(second_image); // Attempt to load the second image
            break;
        } catch (invalid_argument) {
            continue;
        }
    }
    // Create a new image for merging with dimensions equal to the minimum of the two input images
    Image img_merged(min(img_in.width, img_second.width), min(img_in.height, img_second.height));
    // Iterate through each pixel in the merged image
    for (int i = 0; i < min(img_in.width, img_second.width); i++) {
        for (int j = 0; j < min(img_in.height, img_second.height); j++) {
            // Average the RGB values of corresponding pixels from both images and assign to the merged image
            for (int k = 0; k < 3; k++) {
                img_merged(i, j, k) = (img_in(i, j, k) + img_second(i, j, k)) / 2;
            }
        }
    }
    // Save the merged image with a filename indicating the merge operation
    img_in = img_merged;
}

// Function to flip the input image horizontally
void flip_horizontally() {
    // Create a new image to store the horizontally flipped image
    Image flipped(img_in.width, img_in.height);
    // Iterate through each pixel in the image
    for (int i = img_in.width - 1; i >= 0; i--) {
        for (int j = 0; j < img_in.height; j++) {
            // Flip the image in the x-direction
            for (int k = 0; k < 3; k++) {
                flipped(img_in.width - 1 - i, j, k) = img_in(i, j, k);
            }
        }
    }
    img_in = flipped;
}

// Function to flip the input image vertically
void flip_vertically() {
    // Create a new image to store the vertically flipped image
    Image flipped(img_in.width, img_in.height);
    // Iterate through each pixel in the image
    for (int j = img_in.height - 1; j >= 0; j--) {
        for (int i = 0; i < img_in.width; i++) {
            // Flip the image in the y-direction
            for (int k = 0; k < 3; k++) {
                flipped(i, img_in.height - 1 - j, k) = img_in(i, j, k);
            }
        }
    }
    img_in = flipped;
}

// flipping an image using user choice of direction menu
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

// This function rotates an image 90 degrees clockwise.
void Rotate_Image_90() {
    // Create a new Image object with dimensions swapped to accommodate rotation.
    Image img_rotated(img_in.height, img_in.width);
    // Iterate over the pixels of the original image.
    for (int i = 0; i < img_in.width; i++) {
        for (int j = 0; j < img_in.height; j++) {
            // Iterate over the color channels (assuming RGB here).
            for (int k = 0; k < 3; k++) {
                // Assign pixel value from original image to the corresponding position
                // in the rotated image, swapping x and y coordinates.
                img_rotated(j, i, k) = img_in(i, j, k);
            }
        }
    }
    img_in = img_rotated;
}

// Function to prompt the user to enter an image name with its extension and load the image
int insert_image() {
    while (true) { // Loop until a valid image is loaded
        cout << "Please enter image name with its extension: ";
        cin >> imginput; // Read image name from user input
        try {
            img_in.loadNewImage(imginput); // Attempt to load the image
            break;
        } catch (invalid_argument) { // Catch exception if image loading fails
            continue;
        }
    }
    return 0;
}

// This function provides options to rotate the image based on user input.
int rotate_Image() {
    string flipchoice; // Variable to store user's choice
    while (true) { // Infinite loop to repeatedly prompt the user until a valid choice is made
        // Display menu options
        cout << "\n*** How do you want to rotate your image? ***\n";
        cout << "==============================================\n";
        cout << "A) Rotate 90\n";
        cout << "B) Rotate 180\n";
        cout << "C) Rotate 270\n";
        cout << "D) Back to filters menu\n";
        cout << "==============================================\n";
        cout << "Enter your choice: ";
        cin >> flipchoice; // Read user's choice
        transform(flipchoice.begin(), flipchoice.end(), flipchoice.begin(), ::toupper); // Convert user's choice to uppercase
        // Process user's choice
        if (flipchoice == "A") {
            // Rotate the image 90 degrees clockwise
            flip_vertically();
            Rotate_Image_90();
            return 0;
        } else if (flipchoice == "B") {
            // Rotate the image 180 degrees
            flip_horizontally();
            flip_vertically();
            return 0;
        } else if (flipchoice == "C") {
            // Rotate the image 270 degrees clockwise
            flip_horizontally();
            Rotate_Image_90();
            return 0;
        } else if (flipchoice == "D") {
            return 0;
        } else {
            cout << "\nPlease enter a valid choice\n";
        }
    }
}

// Function to provide options for saving an image
int save_image(Image img_save) {
    string savechoice; // Variable to store user's save choice
    while (true) {
        cout << "\n*** How do you want to save your image? ***\n";
        cout << "===========================================\n";
        cout << "A) Save as a new image\n";
        cout << "B) Replace the existing image\n";
        cout << "C) Back to the Main menu\n";
        cout << "===========================================\n";
        cout << "Enter your choice: ";
        cin >> savechoice; // Read user's save choice
        transform(savechoice.begin(), savechoice.end(), savechoice.begin(), ::toupper); // Convert save choice to uppercase
        // Process user's save choice
        if (savechoice == "A") { // Save as a new image
            string outimg; // Variable to store output image name
            while (true) { // Loop until a valid output image name is provided
                try {
                    cout << "\nPlease enter image name with its extension: ";
                    cin >> outimg; // Read output image name from user input
                    img_save.saveImage(outimg); // Attempt to save the image
                    break; // Exit the loop if image saving is successful
                } catch (invalid_argument) { // Catch exception if image saving fails
                    continue; // Continue to prompt the user for a valid output image name
                }
            }
            return 0;
        } else if (savechoice == "B") { // Replace the existing image
            while (true) { // Loop until image saving is successful
                try {
                    img_save.saveImage(imginput); // Attempt to save the image with the original input image name
                    break; // Exit the loop if image saving is successful
                } catch (invalid_argument) { // Catch exception if image saving fails
                    continue; // Continue to attempt image saving
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

// Function to display the filters menu and apply selected filters
int filters_menu() {
    string filterschoice; // Variable to store user's filter choice
    while (true) {
        cout << "\n*** Filters Menu ***\n";
        cout << "========================\n";
        cout << "A) Grey scale\n";
        cout << "B) Black and White\n";
        cout << "C) Invert image\n";
        cout << "D) Merge\n";
        cout << "E) Flip\n";
        cout << "F) Rotate image\n";
        cout << "G) Clear All Filters\n";
        cout << "H) Back to the Main menu\n";
        cout << "========================\n";
        cout << "Enter your choice: ";
        cin >> filterschoice; // Read user's filter choice
        transform(filterschoice.begin(), filterschoice.end(), filterschoice.begin(), ::toupper); // Convert filter choice to uppercase
        // Process user's filter choice
        if (filterschoice == "A") { // Apply Grey scale filter
            greyscale();
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "B") { // Apply Black and White filter
            black_and_white();
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "C") { // Apply Invert image filter
            Invert_Image();
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "D") { // Apply Merge filter
            merge_Images();
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "E") { // Apply Flip filter
            flip_image();
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "F") { // Apply Rotate image filter
            rotate_Image();
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "G") { // Clear All Filters
            img_in.loadNewImage(imginput); // Reload the original image to clear all applied filters
            cout << "All filters have been cleared!" << endl; // Inform the user that all filters have been cleared
        } else if (filterschoice == "H") {
            return 0;
        } else {
            cout << "\nPlease enter a valid choice\n";
        }
    }
}

// Main function of the program
int main() {
    cout << "           \n****** Welcome to baby photoshop program ******\n";
    string choice; // Variable to store user's main menu choice
    while (true) {
        cout << "\n*** Main Menu ***\n";
        cout << "===================\n";
        cout << "A) Insert image\n";
        cout << "B) Apply filters\n";
        cout << "C) Save image\n";
        cout << "D) Exit the program\n";
        cout << "===================\n";
        cout << "Enter your choice: ";
        cin >> choice; // Read user's main menu choice
        transform(choice.begin(), choice.end(), choice.begin(), ::toupper); // Convert main menu choice to uppercase
        // Process user's main menu choice
        if (choice == "A") { // Insert image
            insert_image();
            cout << "Image Inserted!" << endl;
        } else if (choice == "B") { // Apply filters
            filters_menu();
        } else if (choice == "C") { // Save image
            save_image(img_in);
            cout << "Image Saved!" << endl;
        } else if (choice == "D") { // Exit the program
            return 0;
        } else {
            cout << "\nPlease enter a valid choice\n";
        }
    }
}