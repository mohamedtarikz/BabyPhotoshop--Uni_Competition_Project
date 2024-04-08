//  FCAI – Structured Programming – 2024 - Assignment 3
//  File: CS112_A3_Part1_S3_20230309_S4_20230381_20230554.cpp
//  Purpose: Baby Photoshop for Image Processing
//  Flow map link: https://drive.google.com/file/d/1efY7Dc3V8tU-0ygiAyMTlVMV-9hApo94/view?usp=sharing
//  *********************************************************************************Authors*********************************************************************************
//  Mazen nasser >> Group A >> S3 >> 20230309 >> mazen.nasser143@gmail.com >> greyscale, merge
//  Marwan Hussein Galal >> Group A >> S4 >> 20230381 >> marwanhussein@gmail.com >> black and white, Flip, Crop, infera red, menus, error handling
//  Mohamed tarek >> Group A >> S4 >> 20230554 >> mohamedtarik06@gmail.com >> Invert, rotate
//  ********************************************************************************End Authors******************************************************************************
//  TA: Ahmed Fouad
//  Version: 2.0
//  Last Modification Date: 08/04/2024
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
#include <random>
#include "library/Image_Class.h"

using namespace std;
Image img_in;
string imginput;

bool isNumeric(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (isdigit(str[i]) == false)
            return false; //when one non numeric value is found, return false
    }
    return true;
}

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
                // Convert to black and white based on threshold (128)
                if (img_in(i, j, k) < 128) {
                    img_in(i, j, k) = 0;
                } else {
                    img_in(i, j, k) = 255;
                }
            }
        }
    }
}

// Function to crop an image
void crop_image() {
    // Declare variables to store user input for coordinates and dimensions
    string X, Y, W, H;
    // Continue prompting for input until valid values are provided
    while (true) {
        // Prompt user to enter starting X coordinate
        cout << "Enter starting X coordinate: ";
        cin >> X;
        // Prompt user to enter starting Y coordinate
        cout << "Enter starting Y Coordinate: ";
        cin >> Y;
        // Prompt user to enter the width of the crop area
        cout << "Enter the width of the cropped picture: ";
        cin >> W;
        // Prompt user to enter the height of the crop area
        cout << "Enter the height of the cropped picture: ";
        cin >> H;
        // Check if any input is not numeric
        if (!isNumeric(X) || !isNumeric(Y) || !isNumeric(W) || !isNumeric(H)) {
            cout << "Invalid input! Please enter positive integer values." << endl;
            continue;
        }
        // Convert input strings to integers
        int x = stoi(X), y = stoi(Y), w = stoi(W), h = stoi(H);
        // Check if the specified crop area is within the bounds of the image
        if (x > img_in.width || y > img_in.height || w > img_in.width - x || h > img_in.height - y) {
            cout << "Coordinates are out of bounds." << endl;
            continue;
        } else {
            // Break out of the loop if input is valid
            break;
        }
    }
    // Convert input strings to integers after validation
    int x = stoi(X), y = stoi(Y), w = stoi(W), h = stoi(H);
    // Initialize variables for iterating through cropped image
    int M = 0, N = 0;
    // Create a new image to store the cropped region
    Image img_cropped(w, h);
    // Iterate over the specified region of the input image and copy pixels to cropped image
    for (int i = x; i < w + x; i++) {
        for (int j = y; j < h + y; j++) {
            for (int k = 0; k < 3; k++) {
                // Copy pixel values from input image to cropped image
                img_cropped(M, N, k) = img_in(i, j, k);
            }
            N++;
        }
        M++;
        N = 0;
    }
    img_in = img_cropped;
}

int Darken_and_Lighten_Image() {
    string DorL_choice;
    while (true) {
        cout << "\n*** What do you want to do with your image? ***\n";
        cout << "================================================\n";
        cout << "A) Darknen\n";
        cout << "B) Brightnen\n";
        cout << "C) Back to filters menu\n";
        cout << "================================================\n";
        cout << "Enter your choice: ";
        cin >> DorL_choice;
        transform(DorL_choice.begin(), DorL_choice.end(), DorL_choice.begin(), ::toupper); // Convert filter choice to uppercase
        if (DorL_choice != "A" && DorL_choice != "B" && DorL_choice != "C") {
            cout << "Please enter a valid choice" << endl;
            continue;
        }
        if (DorL_choice == "C") {
            return 0;
        }
        break;
    }
    for (int i = 0; i < img_in.width; i++) {
        for (int j = 0; j < img_in.height; j++) {
            for (int k = 0; k < 3; k++) {
                if (DorL_choice == "A") {
                    img_in(i, j, k) /= 2;
                } else if (DorL_choice == "B") {
                    if (img_in(i, j, k) <= 170) {
                        img_in(i, j, k) *= 1.5;
                    } else {
                        img_in(i, j, k) = 255;
                    }
                }
            }
        }
    }
    cout << "Operation completed successfully!" << endl;
    return 0;
}

// Function to invert the colors of the input image
void invert_image() {
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

// Filter to detect image edges
void detect_image_edge() {
    // Convert input image to black and white
    black_and_white();
    Image Detected_edges(img_in.width, img_in.height);
    for (int i = 0; i < img_in.width; i++) {
        for (int j = 0; j < img_in.height; j++) {
            for (int k = 0; k < 3; k++) {
                // Check if the current pixel is not on the image border
                if (i != 0 && i != img_in.width - 1 && j != 0 && j != img_in.height - 1) {
                    // Check if the current pixel is black and any of its neighboring pixels are white
                    if ((img_in(i, j, k) == 0 && img_in(i - 1, j, k) == 255) ||
                        (img_in(i, j, k) == 0 && img_in(i + 1, j, k) == 255) ||
                        (img_in(i, j, k) == 0 && img_in(i, j - 1, k) == 255) ||
                        (img_in(i, j, k) == 0 && img_in(i, j + 1, k) == 255)) {
                        // If any of the neighboring pixels are white, set the corresponding pixel in Detected_edges to black
                        Detected_edges(i, j, k) = 0;
                    } else {
                        // If none of the neighboring pixels are white, set the corresponding pixel in Detected_edges to white
                        Detected_edges(i, j, k) = 255;
                    }
                } else {
                    // If the pixel is on the image border, retain its original color in Detected_edges
                    Detected_edges(i, j, k) = img_in(i, j, k);
                }
            }
        }
    }
    img_in = Detected_edges;
}

void blur() {
    // Declare variables
    int r, sum, sr, er, sc, ec, area;
    // Create a new image for the blurred result with the same dimensions as the input image
    Image blur_img(img_in.width, img_in.height);
    // Prompt the user to enter the blur radius
    cout << "Enter the radius of the blur (the higher the stronger the effect is): ";
    cin >> r;
    // Store the width and height of the input image
    int w = img_in.width;
    int h = img_in.height;
    // Initialize cumulative arrays for each color channel
    int cmlt[w + 1][h + 1][3], row[w + 1][h + 1][3];
    memset(cmlt, 0, sizeof cmlt); // Initialize cumulative arrays with zeros
    memset(row, 0, sizeof row);    // Initialize row arrays with zeros
    // Copy pixel values from input image to cumulative and row arrays
    for (int i = 1; i <= w; ++i) {
        for (int j = 1; j <= h; ++j) {
            for (int k = 0; k < 3; ++k) {
                cmlt[i][j][k] = row[i][j][k] = img_in(i, j, k); // Copy pixel values
            }
        }
    }
    // Calculate cumulative sum for each row
    for (int i = 1; i <= w; i++) {
        for (int j = 1; j <= h; j++) {
            for (int k = 0; k < 3; k++) {
                row[i][j][k] += row[i - 1][j][k]; // Add previous pixel value in row
            }
        }
    }
    // Calculate cumulative sum for each column
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            for (int k = 0; k < 3; k++) {
                if (!i)
                    cmlt[j][i][k] = row[j][i][k]; // First row cumulative sum is same as row value
                else if (!j) {
                    cmlt[j][i][k] += cmlt[j][i - 1][k]; // Add previous column value
                } else {
                    cmlt[j][i][k] = cmlt[j][i - 1][k] + row[j][i][k]; // Add previous row and column value
                }
            }
        }
    }
    // Calculate area of the blur kernel
    area = (2 * r + 1) * (2 * r + 1);
    // Apply blur to each pixel
    for (int i = 1; i <= w; i++) {
        for (int j = 1; j <= h; j++) {
            for (int k = 0; k < 3; k++) {
                // Define region of pixels to be blurred
                sc = max(i - r + 1, 1); ec = min(i + r + 1, w);
                sr = max(j - r + 1, 1); er = min(j + r + 1, h);
                
                // Calculate sum of pixel values within the region
                sum = cmlt[ec][er][k] - cmlt[ec][sr - 1][k] - cmlt[sc - 1][er][k] + cmlt[sc - 1][sr - 1][k];
                
                // Calculate average pixel value within the region
                sum /= area;
                
                // Set blurred pixel value in the output image
                blur_img(i - 1, j - 1, k) = min(sum, 255); // Clamp to maximum pixel value (255)
            }
        }
    }
    // Update the input image with the blurred image
    img_in = blur_img;
}


// Function to merge the input image with another image
void merge_images() {
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
    img_in = img_merged;
}

// Function to flip the input image horizontally
void flip_horizontally() {
    // Create a new image to store the horizontally flipped image
    Image img_flipped(img_in.width, img_in.height);
    // Iterate through each pixel in the image
    for (int i = img_in.width - 1; i >= 0; i--) {
        for (int j = 0; j < img_in.height; j++) {
            // Flip the image in the x-direction
            for (int k = 0; k < 3; k++) {
                img_flipped(img_in.width - 1 - i, j, k) = img_in(i, j, k);
            }
        }
    }
    img_in = img_flipped;
}

// Function to flip the input image vertically
void flip_vertically() {
    // Create a new image to store the vertically flipped image
    Image img_flipped(img_in.width, img_in.height);
    // Iterate through each pixel in the image
    for (int j = img_in.height - 1; j >= 0; j--) {
        for (int i = 0; i < img_in.width; i++) {
            // Flip the image in the y-direction
            for (int k = 0; k < 3; k++) {
                img_flipped(i, img_in.height - 1 - j, k) = img_in(i, j, k);
            }
        }
    }
    img_in = img_flipped;
}

// flipping an image using user choice of direction menu
int flip_image_menu() {
    string flipchoice;
    while (true) {
        cout << "\n*** How do you want to flip your image? ***\n";
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
            cout << "Operation completed successfully!" << endl;
            return 0;
        } else if (flipchoice == "B") {
            flip_vertically();
            cout << "Operation completed successfully!" << endl;
            return 0;
        } else if (flipchoice == "C") {
            flip_horizontally();
            flip_vertically();
            cout << "Operation completed successfully!" << endl;
            return 0;
        } else if (flipchoice == "D") {
            return 0;
        } else {
            cout << "Please enter a valid choice" << endl;
        }
    }
}

// This function rotates an image 90 degrees clockwise.
void rotate_image_90deg() {
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

// This function provides options to rotate the image based on user input.
int rotate_image_menu() {
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
            rotate_image_90deg();
            cout << "Operation completed successfully!" << endl;
            return 0;
        } else if (flipchoice == "B") {
            // Rotate the image 180 degrees
            flip_horizontally();
            flip_vertically();
            cout << "Operation completed successfully!" << endl;
            return 0;
        } else if (flipchoice == "C") {
            // Rotate the image 270 degrees clockwise
            flip_horizontally();
            rotate_image_90deg();
            cout << "Operation completed successfully!" << endl;
            return 0;
        } else if (flipchoice == "D") {
            return 0;
        } else {
            cout << "Please enter a valid choice" << endl;
        }
    }
}

// Function to apply a "Wanno Day" filter to the input image
void Wanno_Day() {
    // Create a new image with the same dimensions as the input image
    Image Wanno_Day_img(img_in.width, img_in.height);
    // Loop through each pixel in the input image
    for (int i = 0; i < img_in.width; i++) {
        for (int j = 0; j < img_in.height; j++) {
            Wanno_Day_img(i, j, 0) = min((img_in(i, j, 0) + 20), 255);
            Wanno_Day_img(i, j, 1) = min((img_in(i, j, 1) + 20), 255);
            Wanno_Day_img(i, j, 2) = max((img_in(i, j, 2) - 40), 0);
        }
    }
    img_in = Wanno_Day_img;
}

// Function to apply a "Wanno Night" filter to the input image
void Wanno_Night() {
    // Create a new image with the same dimensions as the input image
    Image Wanno_Night_img(img_in.width, img_in.height);
    // Loop through each pixel in the input image
    for (int i = 0; i < img_in.width; i++) {
        for (int j = 0; j < img_in.height; j++) {
            Wanno_Night_img(i, j, 0) = min((img_in(i, j, 0) + 20), 255);
            Wanno_Night_img(i, j, 1) = max((img_in(i, j, 1) - 40), 0);
            Wanno_Night_img(i, j, 2) = min((img_in(i, j, 2) + 20), 255);
        }
    }
    img_in = Wanno_Night_img;
}

// Function to apply noise "Wanno TV" filter to the input image
void Wanno_TV() {
    srand (unsigned (time(0)));
    // Create a new image with the same dimensions as the input image
    Image Wanno_TV_img(img_in.width, img_in.height);
    // Loop through each pixel in the input image
    for (int i = 0; i < img_in.width; i++) {
        for (int j = 0; j < img_in.height; j++) {
            for (int k = 0; k < 3; k++) {
                if (img_in(i, j, k) < 225) { // If pixel has vale more than  225 set it to its original value
                    int randomvalue = rand()%26;
                    Wanno_TV_img(i, j, k) = img_in(i, j, k) + randomvalue; // add a random value  between 0 and 25 to make noise
                } else {
                    Wanno_TV_img(i, j, k) = img_in(i, j, k);
                }
            }
        }
    }
    img_in = Wanno_TV_img;
}

// Function to invert the red channel of the input image
void infera_red() {
    for (int i = 0; i < img_in.width; i++) {
        for (int j = 0; j < img_in.height; j++) {
            for (int k = 0; k < 3; k++) {
                // If the current channel is the red channel (k = 0)
                if (k == 0) {
                    // Set the red channel to the maximum value of 255
                    img_in(i, j, k) = 255;
                } else {
                    // Otherwise, invert the current channel (subtract the value of the current channel from 255)
                    img_in(i, j, k) = 255 - img_in(i, j, k);
                }
            }
        }
    }
}

// Function to prompt the user to enter an image name with its extension and load the image
int insert() {
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

// Function to provide options for saving an image
int save(Image img_save) {
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
        // Process user's save choice
        if (savechoice == "A") {
            string outimg;
            while (true) { // Loop until a valid output image name is provided
                try {
                    cout << "\nPlease enter image name with its extension: ";
                    cin >> outimg;
                    img_save.saveImage(outimg);
                    break;
                } catch (invalid_argument) {
                    continue;
                }
            }
            return 0;
        } else if (savechoice == "B") {
            while (true) {
                try {
                    img_save.saveImage(imginput);
                    break;
                } catch (invalid_argument) {
                    continue;
                }
            }
            return 0;
        } else if (savechoice == "C") {
            return 0;
        } else {
            cout << "Please enter a valid choice" << endl;
        }
    }
}

// Function to display the filters menu and apply selected filters
int filters_menu() {
    string filterschoice;
    while (true) {
        cout << "\n*** Filters Menu ***\n";
        cout << "========================\n";
        cout << "A) Grey scale\n";
        cout << "B) Black and White\n";
        cout << "C) Invert colors\n";
        cout << "D) Merge\n";
        cout << "E) Flip\n";
        cout << "F) Rotate\n";
        cout << "G) Edit Brightness\n";
        cout << "H) Crop\n";
        cout << "I) Blur\n";
        cout << "J) Detect image edges\n";
        cout << "K) Wanno Day\n";
        cout << "L) Wanno Night\n";
        cout << "M) Wanno TV\n";
        cout << "N) Infera red\n";
        cout << "O) Clear All Filters\n";
        cout << "P) Back to the Main menu\n";
        cout << "========================\n";
        cout << "Enter your choice: ";
        cin >> filterschoice; // Read user's filter choice
        transform(filterschoice.begin(), filterschoice.end(), filterschoice.begin(), ::toupper); // Convert filter choice to uppercase
        if (filterschoice == "A") {
            greyscale();
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "B") {
            black_and_white();
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "C") {
            invert_image();
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "D") {
            merge_images();
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "E") {
            flip_image_menu();
        } else if (filterschoice == "F") {
            rotate_image_menu();
        } else if (filterschoice == "G") {
            Darken_and_Lighten_Image();
        } else if (filterschoice == "H") {
            crop_image();
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "I") {
            blur();
            cout << "Operation completed successfully!" << endl;
        }  else if (filterschoice == "J") {
            detect_image_edge();
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "K") {
            Wanno_Day();
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "L") {
            Wanno_Night();
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "M") {
            Wanno_TV();
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "N") {
            infera_red();
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "O") {
            img_in.loadNewImage(imginput); // Reload the original image to clear all applied filters
            cout << "All filters have been cleared!" << endl;
        } else if (filterschoice == "P") {
            return 0;
        } else {
            cout << "Please enter a valid choice" << endl;
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
        if (choice == "A") {
            insert();
            cout << "Image Inserted!" << endl;
        } else if (choice == "B") {
            filters_menu();
        } else if (choice == "C") {
            save(img_in);
            cout << "Image Saved!" << endl;
        } else if (choice == "D") {
            return 0;
        } else {
            cout << "Please enter a valid choice" << endl;
        }
    }
}