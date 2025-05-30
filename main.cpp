//  FCAI – Structured Programming – 2024 - Assignment 3
//  File: CS112_A3_Part1_S3_20230309_S4_20230381_20230554.cpp
//  Purpose: Baby Photoshop for Image Processing
//  app map link: https://drive.google.com/file/d/1efY7Dc3V8tU-0ygiAyMTlVMV-9hApo94/view?usp=sharing
//  Github Repo: https://github.com/mohamedtarikz/Assignment-3-Little-photoshop-
//  ****************************************************************************************Authors****************************************************************************************
//  Mazen nasser >> Group A >> S3 >> 20230309 >> mazen.nasser143@gmail.com >> greyscale, merge, Edit Brightness, Detect image edges, Channel Swap, Wano Day.
//  Marwan Hussein Galal >> Group A >> S4 >> 20230381 >> marwanhussein@gmail.com >> black and white, Flip, Crop, infera red, wano TV-NIGHT, Skew, menus, saving system, error handling.
//  Mohamed tarek >> Group A >> S4 >> 20230554 >> mohamedtarik06@gmail.com >> Invert, rotate, resize, blur, pixelate, frames, Oil Painting.
//  ***************************************************************************************End Authors*************************************************************************************
//  TA: Ahmed Fouad
//  Version: 2.0
//  Last Modification Date: 17/04/2024
//  =================================================================================================================================================================================   //
#include "Src\encryption-decryption.h"

Image img_in;
Image img_filter;
string imginput = "NULL";
string saveindicator = "N";

// Function to check if a string is numeric
bool isNumeric(string str) {
    for (int i = 0; i < str.length(); i++) {
        // Check each character of the string
        if (isdigit(str[i]) == false)
            return false; // Return false if a non-numeric character is found
    }
    // Return true if all characters are numeric
    return true;
}

// Function to convert the input image to grayscale
void greyscale() {
    // Iterate through each pixel in the image
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            int av = 0; // Initialize average value
            // Calculate average pixel value across RGB channels
            for (int k = 0; k < 3; k++) {
                av += img_filter(i, j, k);
            }
            av /= 3; // Compute the average
            // Set each RGB channel to the average value to convert to grayscale
            for (int k = 0; k < 3; k++) {
                img_filter(i, j, k) = av;
            }
        }
    }
}

// Function to convert the input image to black and white
void black_and_white() {
    // Convert the input image to grayscale
    greyscale();
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            // Set the color of the pixel to max white or black
            for (int k = 0; k < 3; k++) {
                if (img_filter(i, j, k) < 128) {
                    img_filter(i, j, k) = 0;
                } else {
                    img_filter(i, j, k) = 255;
                }
            }
        }
    }
}

// Function to crop an image
void crop_image() {
    // Declare variables to store user input for coordinates and dimensions
    string X, Y, W, H;
    int x, y, w, h;
    // Continue prompting for input until valid values are provided
    while (true) {
        cout << "\ncurrent possetion is: ( 0 , 0 )" << endl;
        cout << "current Image Size is: " << img_filter.width << " X " << img_filter.height << endl;
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
        try {
            x = stoi(X), y = stoi(Y), w = stoi(W), h = stoi(H);
        } catch (out_of_range) {
            cout << "Coordinates are out of bounds." << endl;
        }
        // Check if the specified crop area is within the bounds of the image
        if (x > img_filter.width || y > img_filter.height || w > img_filter.width - x || h > img_filter.height - y) {
            cout << "Coordinates are out of bounds." << endl;
            continue;
        } else {
            // Break out of the loop if input is valid
            break;
        }
    }
    // Initialize variables for iterating through cropped image
    int M = 0, N = 0;
    // Create a new image to store the cropped region
    Image img_cropped(w, h);
    // Iterate over the specified region of the input image and copy pixels to cropped image
    for (int i = x; i < w + x; i++) {
        for (int j = y; j < h + y; j++) {
            for (int k = 0; k < 3; k++) {
                // Copy pixel values from input image to cropped image
                img_cropped(M, N, k) = img_filter(i, j, k);
            }
            N++;
        }
        M++;
        N = 0;
    }
    img_filter = img_cropped;
}

// Function to darken or lighten an image based on user choice
int edit_brightness() {
    string DorL_choice;
    // Loop until a valid choice is entered
    while (true) {
        // Display menu options to the user
        cout << "\n*** What do you want to do with your image? ***\n";
        cout << "================================================\n";
        cout << "A) Darken\n";
        cout << "B) Brighten\n";
        cout << "C) Back to filters menu\n";
        cout << "================================================\n";
        cout << "Enter your choice: ";
        cin >> DorL_choice;
        // Check if the choice is valid, if not, prompt the user to enter a valid choice
        transform(DorL_choice.begin(), DorL_choice.end(), DorL_choice.begin(), ::toupper);
        if (DorL_choice != "A" && DorL_choice != "B" && DorL_choice != "C") {
            cout << "Please enter a valid choice" << endl;
            continue;
        }
        // If the user chooses to go back to the filters menu, return 0 to exit the function
        if (DorL_choice == "C") {
            return 0;
        }
        break;
    }
    // Loop through each pixel in the image
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            for (int k = 0; k < 3; k++) {
                if (DorL_choice == "A") {
                    img_filter(i, j, k) /= 2; // Divide pixel value by 2 to darken
                } else if (DorL_choice == "B") {
                    img_filter(i, j, k) = min(int(img_filter(i, j, k) * 1.5), 255); // Multiply pixel value by 1.5 to brighten
                }
            }
        }
    }
    saveindicator = "N";
    cout << "Operation completed successfully!" << endl;
    return 0;
}

// Function to invert the colors of the input image
void invert_image() {
    // Iterate through each pixel in the image
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            // Invert each RGB channel by subtracting from 255
            for (int k = 0; k < 3; k++) {
                img_filter(i, j, k) = 255 - (img_filter(i, j, k));
            }
        }
    }
}

// Filter to detect image edges
void detect_edge() {
    // Convert input image to black and white
    black_and_white();
    Image img_Detected_edges(img_filter.width, img_filter.height);
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            for (int k = 0; k < 3; k++) {
                // Check if the current pixel is not on the image border
                if (i != 0 && i != img_filter.width - 1 && j != 0 && j != img_filter.height - 1) {
                    // Check if the current pixel is black and any of its neighboring pixels are white
                    if ((img_filter(i, j, k) == 0 && img_filter(i - 1, j, k) == 255) ||
                        (img_filter(i, j, k) == 0 && img_filter(i + 1, j, k) == 255) ||
                        (img_filter(i, j, k) == 0 && img_filter(i, j - 1, k) == 255) ||
                        (img_filter(i, j, k) == 0 && img_filter(i, j + 1, k) == 255)) {
                        // If any of the neighboring pixels are white, set the corresponding pixel in Detected_edges to black
                        img_Detected_edges(i, j, k) = 0;
                    } else {
                        // If none of the neighboring pixels are white, set the corresponding pixel in Detected_edges to white
                        img_Detected_edges(i, j, k) = 255;
                    }
                } else {
                    // If the pixel is on the image border, retain its original color in Detected_edges
                    img_Detected_edges(i, j, k) = img_filter(i, j, k);
                }
            }
        }
    }
    img_filter = img_Detected_edges;
}

// Filter to apply blur effect
void blur() {
    // Declare variables
    string R;
    int r, sr, er, sc, ec;
    long long int sum, area;
    // Create a new image for the blurred result with the same dimensions as the input image
    Image blur_img(img_filter.width, img_filter.height);
    // Prompt the user to enter the blur radius
    while (true) {
        // Prompt user to enter starting X coordinate
        cout << "Enter the strength of the blur (3 - 100): ";
        cin >> R;
        // Convert input strings to integers
        // Check if any input is not numeric
        if (!isNumeric(R)) {
            cout << "Invalid input! Please enter positive integer values." << endl;
            continue;
        }
        try {
            r = stoi(R);
        } catch (out_of_range) {
            cout << "Invalid input! Please enter a number within the range." << endl;
        }
        if (r > 100 || r < 3) {
            cout << "Invalid input! Please enter a number within the range." << endl;
            continue;
        } else {
            // Break out of the loop if input is valid
            break;
        }
    }
    // Store the width and height of the input image
    int w = img_filter.width;
    int h = img_filter.height;
    // Initialize cumulative arrays for each color channel using dynamic memory allocation
    long long int*** cmlt = new long long int** [w + 1];
    long long int*** row = new long long int** [w + 1];
    for (int i = 0; i <= w; ++i) {
        cmlt[i] = new long long int* [h + 1];
        row[i] = new long long int* [h + 1];
        for (int j = 0; j <= h; ++j) {
            cmlt[i][j] = new long long int[3];
            row[i][j] = new long long int[3];
            memset(cmlt[i][j], 0, sizeof(long long int) * 3); // Initialize cumulative arrays with zeros
            memset(row[i][j], 0, sizeof(long long int) * 3);    // Initialize row arrays with zeros
        }
    }
    // Copy pixel values from input image to cumulative and row arrays
    for (int i = 1; i <= w; ++i) {
        for (int j = 1; j <= h; ++j) {
            for (int k = 0; k < 3; ++k) {
                cmlt[i][j][k] = row[i][j][k] = img_filter(i - 1, j - 1, k); // Copy pixel values
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
    // Apply blur to each pixel
    for (int i = 1; i <= w; i++) {
        for (int j = 1; j <= h; j++) {
            for (int k = 0; k < 3; k++) {
                // Define region of pixels to be blurred
                sc = max(i - r, 1); ec = min(i + r, w);
                sr = max(j - r, 1); er = min(j + r, h);
                area = ((er - sr) * (ec - sc));
                // Calculate sum of pixel values within the region
                sum = cmlt[ec][er][k] - cmlt[ec][sr - 1][k] - cmlt[sc - 1][er][k] + cmlt[sc - 1][sr - 1][k];
                // Calculate average pixel value within the region
                sum /= area;
                // Set blurred pixel value in the output image
                blur_img(i - 1, j - 1, k) = (sum <= 255 ? sum : 255); // Clamp to maximum pixel value (255)
            }
        }
    }
    // Update the input image with the blurred image
    img_filter = blur_img;
    // Deallocate memory
    for (int i = 0; i <= w; ++i) {
        for (int j = 0; j <= h; ++j) {
            delete[] cmlt[i][j];
            delete[] row[i][j];
        }
        delete[] cmlt[i];
        delete[] row[i];
    }
    delete[] cmlt;
    delete[] row;
}

// Function to resize the image
Image resize(Image img_resize, int newWidth, int newHeight) {
    int width = img_resize.width, height = img_resize.height;

    // Calculate scaling factors for width
    int scale1, scale2;
    scale1 = max(width, newWidth) / min(newWidth, width);
    scale2 = scale1 + 1;

    // Calculate division of the new image width into two parts
    int FirstPart = scale2 * min(newWidth, width) - max(width, newWidth);
    int SecondPart = (max(width, newWidth) - scale1 * FirstPart) / scale2;
    int StartofSecondpart = SecondPart * scale2;

    // Create a new image with the desired width and original height
    Image Resized(newWidth, height);

    if (newWidth <= width) {
        // If the new width is less than or equal to the original width
        // Create two images representing the first and second parts of the resized image
        Image FirstImage(FirstPart, height);
        Image SecondImage(SecondPart, height);
        int idx, fixed, avrg;

        // For each row in the image
        for (int j = 0; j < height; j++) {
            idx = 0;
            fixed = StartofSecondpart;

            // Process the first part of the resized image
            for (int h = 0; h < FirstPart; h++) {
                for (int k = 0; k < 3; ++k) {
                    avrg = 0;
                    idx = fixed;

                    // Calculate average pixel value for each channel
                    for (int i = 0; i < scale1; i++) {
                        avrg += img_resize(idx, j, k);
                        idx++;
                        if (idx >= width) {
                            break;
                        }
                    }
                    avrg /= scale1;
                    // Assign the average pixel value to the corresponding position in the FirstImage
                    FirstImage(h, j, k) = min(avrg, 255);
                }
                fixed += scale1;
            }

            // Process the second part of the resized image
            idx = 0;
            fixed = 0;
            for (int h = 0; h < SecondPart; h++) {
                for (int k = 0; k < 3; ++k) {
                    avrg = 0;
                    idx = fixed;
                    for (int i = 0; i < scale2; i++) {
                        avrg += img_resize(idx, j, k);
                        idx++;
                        if (idx >= width) {
                            break;
                        }
                    }
                    avrg /= scale2;
                    // Assign the average pixel value to the corresponding position in the SecondImage
                    SecondImage(h, j, k) = min(avrg, 255);
                }
                fixed += scale2;
            }
        }

        // Merge the two parts into the final resized image
        for (int i = 0; i < Resized.height; i++) {
            for (int j = 0; j < Resized.width; ++j) {
                for (int k = 0; k < 3; ++k) {
                    Resized(j, i, k) = (j >= SecondPart ? FirstImage(j - SecondPart, i, k) : SecondImage(j, i, k));
                }
            }
        }
    } else {
        // If the new width is greater than the original width
        // Process each row and scale the pixels accordingly
        int idx;
        for (int j = 0; j < height; j++) {
            idx = 0;
            for (int i = 0; i < width; i++) {
                if (i >= FirstPart) {
                    // Scale the pixels in the first part
                    for (int h = 0; h < scale2; h++) {
                        for (int k = 0; k < 3; ++k) {
                            Resized(idx, j, k) = img_resize(i, j, k);
                        }
                        idx++;
                    }
                } else {
                    // Scale the pixels in the second part
                    for (int h = 0; h < scale1; h++) {
                        for (int k = 0; k < 3; ++k) {
                            Resized(idx, j, k) = img_resize(i, j, k);
                        }
                        idx++;
                    }
                }
            }
        }
    }

    // Update the input image to the resized image
    img_resize = Resized;
    width = img_resize.width;
    height = img_resize.height;

    // Calculate scaling factors for height
    scale1 = max(height, newHeight) / min(newHeight, height);
    scale2 = scale1 + 1;

    // Calculate division of the new image height into two parts
    FirstPart = scale2 * min(newHeight, height) - max(height, newHeight);
    SecondPart = (max(height, newHeight) - scale1 * FirstPart) / scale2;
    StartofSecondpart = SecondPart * scale2;

    // Create a new image with the resized width and desired height
    Image Resizedall(width, newHeight);

    if (newHeight <= height) {
        // If the new height is less than or equal to the original height
        // Create two images representing the first and second parts of the resized image
        Image FirstImage(width, FirstPart);
        Image SecondImage(width, SecondPart);
        int idx, fixed, avrg;

        // For each column in the image
        for (int j = 0; j < width; j++) {
            idx = 0;
            fixed = StartofSecondpart;

            // Process the first part of the resized image
            for (int h = 0; h < FirstPart; h++) {
                for (int k = 0; k < 3; ++k) {
                    avrg = 0;
                    idx = fixed;

                    // Calculate average pixel value for each channel
                    for (int i = 0; i < scale1; i++) {
                        avrg += img_resize(j, idx, k);
                        idx++;
                        if (idx >= height) {
                            break;
                        }
                    }
                    avrg /= scale1;
                    // Assign the average pixel value to the corresponding position in the FirstImage
                    FirstImage(j, h, k) = min(avrg, 255);
                }
                fixed += scale1;
            }

            // Process the second part of the resized image
            idx = 0;
            fixed = 0;
            for (int h = 0; h < SecondPart; h++) {
                for (int k = 0; k < 3; ++k) {
                    avrg = 0;
                    idx = fixed;
                    for (int i = 0; i < scale2; i++) {
                        avrg += img_resize(j, idx, k);
                        idx++;
                        if (idx >= height) {
                            break;
                        }
                    }
                    avrg /= scale2;
                    // Assign the average pixel value to the corresponding position in the SecondImage
                    SecondImage(j, h, k) = min(avrg, 255);
                }
                fixed += scale2;
            }
        }

        // Merge the two parts into the final resized image
        for (int j = 0; j < Resizedall.width; ++j) {
            for (int i = 0; i < Resizedall.height; i++) {
                for (int k = 0; k < 3; ++k) {
                    Resizedall(j, i, k) = (i >= SecondPart ? FirstImage(j, i - SecondPart, k) : SecondImage(j, i, k));
                }
            }
        }
    } else {
        // If the new height is greater than the original height
        // Process each column and scale the pixels accordingly
        int idx;
        for (int j = 0; j < width; j++) {
            idx = 0;
            for (int i = 0; i < height; i++) {
                if (i >= FirstPart) {
                    // Scale the pixels in the first part
                    for (int h = 0; h < scale2; h++) {
                        for (int k = 0; k < 3; ++k) {
                            Resizedall(j, idx, k) = img_resize(j, i, k);
                        }
                        idx++;
                    }
                } else {
                    // Scale the pixels in the second part
                    for (int h = 0; h < scale1; h++) {
                        for (int k = 0; k < 3; ++k) {
                            Resizedall(j, idx, k) = img_resize(j, i, k);
                        }
                        idx++;
                    }
                }
            }
        }
    }
    // Return the resized image
    return Resizedall;
}

// Function to handle resizing options for the image
void resize_menu() {
    string resizechoice; // Variable to store user's resize menu choice
    int newWidth, newHeight; // Variables to store new dimensions for the image
    Image img_resize = img_filter; // Create a copy of the filtered image to work with
    while (true) {
        cout << "\n*** How do you want to Resize your image? ***\n";
        cout << "==============================================\n";
        cout << "A) Resize by dimensions\n";
        cout << "B) Resize by scale\n";
        cout << "C) Back to filters menu\n";
        cout << "==============================================\n";
        cout << "Enter your choice: ";
        cin >> resizechoice;
        transform(resizechoice.begin(), resizechoice.end(), resizechoice.begin(), ::toupper); // Convert choice to uppercase
        if (resizechoice == "A") { // If user chooses to resize by dimensions
            while (true) {
                cout << "Enter your new desired dimensions(\"Width Height\"): ";
                cin >> newWidth >> newHeight; // Read new dimensions from user input
                if (newWidth <= 0 || newHeight <= 0) {
                    cout << "Please enter a width and hight grater than 0" << endl;
                    continue;
                }
            }
            img_filter = resize(img_filter, newWidth, newHeight); // Resize the image
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
            return;
        } else if (resizechoice == "B") { // If user chooses to resize by scale
            double scalew, scaleh; // Variables to store scaling factors
            while (true) {
                cout << "Enter your desired scale for each dimension(\"ScaleWidth ScaleHeight\"): ";
                cin >> scalew >> scaleh; // Read scaling factors from user input
                if (scalew <= 0 || scaleh <= 0) {
                    cout << "Please enter a scale grater than 0" << endl;
                    continue;
                }
                if (scalew > 10 || scaleh > 10) {
                    cout << "Please enter a scale less than 10" << endl;
                    continue;
                } else {
                    break;
                }
            }
            // Calculate new dimensions based on the scaling factors
            newWidth = (double)(img_resize.width * scalew);
            newHeight = (double)(img_resize.height * scaleh);
            img_filter = resize(img_filter, newWidth, newHeight); // Resize the image
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
            return;
        } else if (resizechoice == "C") { // If user chooses to go back to filters menu
            return;
        } else {
            cout << "Please enter a valid choice" << endl;
        }
    }
}

// Function to merge the input image with another image
void merge_images(Image img_first, Image img_second) {
    // Create a new image for merging with dimensions equal to the minimum of the two input images
    Image img_merged(min(img_first.width, img_second.width), min(img_first.height, img_second.height));
    // Iterate through each pixel in the merged image
    for (int i = 0; i < min(img_first.width, img_second.width); i++) {
        for (int j = 0; j < min(img_first.height, img_second.height); j++) {
            // Average the RGB values of corresponding pixels from both images and assign to the merged image
            for (int k = 0; k < 3; k++) {
                img_merged(i, j, k) = (img_first(i, j, k) + img_second(i, j, k)) / 2;
            }
        }
    }
    img_filter = img_merged;
}

// Function to handle the merging of images and provide options for the user
void merge_images_menu() {
    string mergechoice; // Variable to store user's merge menu choice
    Image img_one, img_two; // Variables to store the two images to be merged
    int max_width, max_height, min_width, min_height; // Variables to store dimensions of the images
    img_one = img_filter; // Set the first image to the filtered image
    while (true) {
        cout << "\n**what do you like to enter?**" << endl;
        cout << "==============================" << endl;
        cout << "A) Resize to the smallest dimension" << endl;
        cout << "B) Resize to the greatest dimension" << endl;
        cout << "C) Merge common area" << endl;
        cout << "D) Back to filters menu" << endl;
        cout << "==============================" << endl;
        cout << "Enter your choice: ";
        cin >> mergechoice;
        transform(mergechoice.begin(), mergechoice.end(), mergechoice.begin(), ::toupper); // Convert choice to uppercase
        if (mergechoice != "D") { // If the user didn't choose to go back to filters menu
            string secinputimage; // Variable to store the name of the second image
            // Loop until a valid second image is loaded
            while (true) {
                cout << "Please enter second image name with its extension: ";
                cin >> secinputimage;
                try {
                    img_two.loadNewImage(secinputimage); // Attempt to load the second image
                    break;
                } catch (invalid_argument) {
                    continue;
                }
            }
        }
        // Determine the maximum and minimum dimensions of the two images
        if (img_one.width > img_two.width) {
            max_width = img_one.width;
            min_width = img_two.width;
        } else {
            max_width = img_two.width;
            min_width = img_one.width;
        }
        if (img_one.height > img_two.height) {
            max_height = img_one.height;
            min_height = img_two.height;
        } else {
            max_height = img_two.height;
            min_height = img_one.height;
        }
        // Process user's merge choice
        if (mergechoice == "A") {
            img_one = resize(img_one, min_width, min_height); // Resize the first image to the smallest dimensions
            img_two = resize(img_two, min_width, min_height); // Resize the second image to the smallest dimensions
            merge_images(img_one, img_two); // Merge the images
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
            return;
        } else if (mergechoice == "B") {
            img_one = resize(img_one, max_width, max_height); // Resize the first image to the greatest dimensions
            img_two = resize(img_two, max_width, max_height); // Resize the second image to the greatest dimensions
            merge_images(img_one, img_two); // Merge the images
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
            return;
        } else if (mergechoice == "C") {
            merge_images(img_one, img_two); // Merge the images without resizing
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
            return;
        } else if (mergechoice == "D") {
            return; // Return to the filters menu
        } else {
            cout << "Please enter a valid choice" << endl;
        }
    }
}

// Function to flip the input image horizontally
void flip_horizontally() {
    // Create a new image to store the horizontally flipped image
    Image img_flipped(img_filter.width, img_filter.height);
    // Iterate through each pixel in the image
    for (int i = img_filter.width - 1; i >= 0; i--) {
        for (int j = 0; j < img_filter.height; j++) {
            // Flip the image in the x-direction
            for (int k = 0; k < 3; k++) {
                img_flipped(img_filter.width - 1 - i, j, k) = img_filter(i, j, k);
            }
        }
    }
    img_filter = img_flipped;
}

// Function to flip the input image vertically
void flip_vertically() {
    // Create a new image to store the vertically flipped image
    Image img_flipped(img_filter.width, img_filter.height);
    // Iterate through each pixel in the image
    for (int j = img_filter.height - 1; j >= 0; j--) {
        for (int i = 0; i < img_filter.width; i++) {
            // Flip the image in the y-direction
            for (int k = 0; k < 3; k++) {
                img_flipped(i, img_filter.height - 1 - j, k) = img_filter(i, j, k);
            }
        }
    }
    img_filter = img_flipped;
}

// flipping an image using user choice of direction menu
void flip_image_menu() {
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
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
            return;
        } else if (flipchoice == "B") {
            flip_vertically();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
            return;
        } else if (flipchoice == "C") {
            flip_horizontally();
            flip_vertically();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
            return;
        } else if (flipchoice == "D") {
            return;
        } else {
            cout << "Please enter a valid choice" << endl;
        }
    }
}

// This function rotates an image 90 degrees clockwise.
void rotate_image_90deg() {
    // Create a new Image object with dimensions swapped to accommodate rotation.
    Image img_rotated(img_filter.height, img_filter.width);
    // Iterate over the pixels of the original image.
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            // Iterate over the color channels (assuming RGB here).
            for (int k = 0; k < 3; k++) {
                // Assign pixel value from original image to the corresponding position
                // in the rotated image, swapping x and y coordinates.
                img_rotated(j, i, k) = img_filter(i, j, k);
            }
        }
    }
    img_filter = img_rotated;
}

// This function provides options to rotate the image based on user input.
void rotate_image_menu() {
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
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
            return;
        } else if (flipchoice == "B") {
            // Rotate the image 180 degrees
            flip_horizontally();
            flip_vertically();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
            return;
        } else if (flipchoice == "C") {
            // Rotate the image 270 degrees clockwise
            flip_horizontally();
            rotate_image_90deg();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
            return;
        } else if (flipchoice == "D") {
            return;
        } else {
            cout << "Please enter a valid choice" << endl;
        }
    }
}

// Function to apply a "Wanno Day" filter to the input image
void Wanno_Day() {
    // Create a new image with the same dimensions as the input image
    Image Wanno_Day_img(img_filter.width, img_filter.height);
    // Loop through each pixel in the input image
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            Wanno_Day_img(i, j, 0) = min((img_filter(i, j, 0) + 20), 255);
            Wanno_Day_img(i, j, 1) = min((img_filter(i, j, 1) + 20), 255);
            Wanno_Day_img(i, j, 2) = max((img_filter(i, j, 2) - 40), 0);
        }
    }
    img_filter = Wanno_Day_img;
}

// Function to apply a "Wanno Night" filter to the input image
void Wanno_Night() {
    // Create a new image with the same dimensions as the input image
    Image Wanno_Night_img(img_filter.width, img_filter.height);
    // Loop through each pixel in the input image
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            Wanno_Night_img(i, j, 0) = min((img_filter(i, j, 0) + 20), 255);
            Wanno_Night_img(i, j, 1) = max((img_filter(i, j, 1) - 40), 0);
            Wanno_Night_img(i, j, 2) = min((img_filter(i, j, 2) + 20), 255);
        }
    }
    img_filter = Wanno_Night_img;
}

// Function to apply noise "Wanno TV" filter to the input image
void Wanno_TV() {
    srand(unsigned(time(0)));
    // Create a new image with the same dimensions as the input image
    Image Wanno_TV_img(img_filter.width, img_filter.height);
    // Loop through each pixel in the input image
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            for (int k = 0; k < 3; k++) {
                int randomvalue = rand() % 21;
                if (img_filter(i, j, k) > 20) { // If pixel has vale more than  225 set it to its original value
                    Wanno_TV_img(i, j, k) = min(int((img_filter(i, j, k) - randomvalue) * 1.07), 255); // subtract a random value  between 1 and 20 to make noise
                } else {
                    Wanno_TV_img(i, j, k) = img_filter(i, j, k) + 1;
                }
            }
        }
    }
    img_filter = Wanno_TV_img;
}

// Function to invert the red channel of the input image
void infera_red() {
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            for (int k = 0; k < 3; k++) {
                // If the current channel is the red channel (k = 0)
                if (k == 0) {
                    // Set the red channel to the maximum value of 255
                    img_filter(i, j, k) = 255;
                } else {
                    // Otherwise, invert the current channel (subtract the value of the current channel from 255)
                    img_filter(i, j, k) = 255 - img_filter(i, j, k);
                }
            }
        }
    }
}

// Filter to pixelate the image
void pixelate() {
    // Prompt user for pixelation radius
    int r;
    string R;
    while (true) {
        cout << "Enter radius of pixelation (the more the stronger the effect) (0 - 10): ";
        cin >> R;
        if (!isNumeric(R)){
            cout << "Invalid radius. Please enter a value between 0 and 10" << endl;
            continue;
        }
        r = stoi(R);
        if (r < 0 && r > 10) {
            cout << "Invalid radius. Please enter a value between 0 and 10";
            continue;
        }
        else {
            break;
        }
    }
    // Create a new image to store the pixelated result
    Image pixels(img_filter.width, img_filter.height);
    // Iterate through the image pixels with step size of r
    for (int i = 0; i < img_filter.width; i += r) {
        for (int j = 0; j < img_filter.height; j += r) {
            for (int k = 0; k < 3; k++) {
                unsigned char x = img_filter(i, j, k);
                // Find the maximum color value within the pixel block
                for (int l = 0; l < r; ++l) {
                    for (int m = 0; m < r; ++m) {
                        x = max((int)x, (int)img_filter(min(i + l, img_filter.width - 1), min(j + m, img_filter.height - 1), k));
                    }
                }
                // Set the pixel block to the maximum color value
                for (int l = 0; l < r; ++l) {
                    for (int m = 0; m < r; ++m) {
                        pixels(min(i + l, img_filter.width - 1), min(j + m, img_filter.height - 1), k) = x;
                    }
                }
            }
        }
    }
    // Update the input image with the pixelated result
    img_filter = pixels;
}

// Filter to make Oil Painting effect
void oil_painted() {
    // Create a copy of the input image to store the oil-painted effect
    Image img_oil_paint(img_filter);
    // Reduce the color precision of each pixel
    for (int i = 0; i < img_oil_paint.width; i++) {
        for (int j = 0; j < img_oil_paint.height; j++) {
            for (int k = 0; k < 3; k++) {
                // Divide the color value of each channel by 40 to reduce precision
                img_oil_paint(i, j, k) /= 40;
                // Multiply the result by 40 to bring it closer to its original value
                img_oil_paint(i, j, k) *= 40;
            }
        }
    }
    // Update the input image with the oil-painted result
    img_filter = img_oil_paint;
}

void normal_frame() {
    // Prompt user for frame thickness and desired RGB values
    int thck, r, g, b;
    cout << "Enter frame thickness: ";
    cin >> thck;
    cout << "Enter the desired RGB values (\"Rval Gval Bval\"): ";
    cin >> r >> g >> b;
    // Create a new image for the framed result
    Image framed(img_filter.width + 2 * thck, img_filter.height + 2 * thck);
    // Fill the frame area with the desired RGB values
    for (int i = 0; i < framed.width; i++) {
        for (int j = 0; j < framed.height; j++) {
            framed(i, j, 0) = r;
            framed(i, j, 1) = g;
            framed(i, j, 2) = b;
        }
    }
    // Copy the original image into the frame area
    for (int i = thck; i < thck + img_filter.width; i++) {
        for (int j = thck; j < thck + img_filter.height; j++) {
            for (int k = 0; k < 3; k++) {
                framed(i, j, k) = img_filter(i - thck, j - thck, k);
            }
        }
    }
    // Save the framed image and update the input image
    framed.saveImage("framed.png");
    img_filter = framed;
}

void fancy_frame() {
    // Prompt user for frame thickness and desired RGB values for both frames
    int thck, r1, g1, b1, r2, g2, b2;
    cout << "Enter frame Thickness: ";
    cin >> thck;
    cout << "Enter first desired RGB values (\"Rval Gval Bval\"): ";
    cin >> r1 >> g1 >> b1;
    cout << "Enter second desired RGB values (\"Rval Gval Bval\"): ";
    cin >> r2 >> g2 >> b2;
    // Create a new image for the framed result
    Image framed(img_filter.width + 2 * thck, img_filter.height + 2 * thck);
    int y = thck / 2;
    // Fill the outer frame with the first set of RGB values
    for (int i = 0; i < framed.width; i++) {
        for (int j = 0; j < framed.height; j++) {
            framed(i, j, 0) = r1;
            framed(i, j, 1) = g1;
            framed(i, j, 2) = b1;
        }
    }
    // Fill the inner frame with the second set of RGB values
    for (int i = y; i < framed.width - y; i++) {
        for (int j = y; j < framed.height - y; j++) {
            framed(i, j, 0) = r2;
            framed(i, j, 1) = g2;
            framed(i, j, 2) = b2;
        }
    }
    // Copy the original image into the frame area
    for (int i = thck; i < thck + img_filter.width; i++) {
        for (int j = thck; j < thck + img_filter.height; j++) {
            for (int k = 0; k < 3; k++) {
                framed(i, j, k) = img_filter(i - thck, j - thck, k);
            }
        }
    }
    // Update the input image with the framed result
    img_filter = framed;
}

void frame_blur() {
    Image blr(img_filter);
    blur();
    int thck;
    cout << "Enter frame thickness: ";
    cin >> thck;
    int w = img_filter.width, h = img_filter.height;
    img_filter = resize(img_filter, 2 * thck + w, 2 * thck + h);
    for (int i = thck; i < thck + blr.width; i++) {
        for (int j = thck; j < thck + blr.height; j++) {
            for (int k = 0; k < 3; k++) {
                img_filter(i, j, k) = blr(i - thck, j - thck, k);
            }
        }
    }
}

// Menu of Frames
void frame() {
    // Prompt user for frame choice until a valid choice is made
    string framechoice;
    while (true) {
        cout << "\n*** How do you want to frame your image? ***\n";
        cout << "===========================================\n";
        cout << "A) Normal Frame\n";
        cout << "B) Fancy Frame\n";
        cout << "C) Blured Frame\n";
        cout << "D) Back to the Main menu\n";
        cout << "===========================================\n";
        cout << "Enter your choice: ";
        cin >> framechoice;
        transform(framechoice.begin(), framechoice.end(), framechoice.begin(), ::toupper);
        // Process user's frame choice
        if (framechoice == "A") {
            normal_frame();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
            return;
        } else if (framechoice == "B") {
            fancy_frame();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
            return;
        } else if (framechoice == "C") {
            frame_blur();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
            return;
        } else if (framechoice == "D") {
            return;
        } else {
            cout << "Please enter a valid choice" << endl;
        }
    }
}

// Filter to skew image
void Skew() {
    // Prompt user for skew angle until a valid angle is entered
    double angle;
    string ang;
    while (true) {
        cout << "Please enter the angle (0 - 360): ";
        cin >> ang;
        if (!isNumeric(ang)) {
            cout << "Please enter a proper positive numeric value." << endl;
            continue;
        }
        try {
            angle = stod(ang);
        } catch (out_of_range) {
            cout << "Please enter a proper value" << endl;
            continue;
        }
        if (angle == 90.00 || angle == 270) {
            cout << "Invalid Angle. 90 and 270 aren't allowed!" << endl;
            continue;
        }
        if (angle > 360 || angle < 0) {
            cout << "Please enter a proper value" << endl;
            continue;
        } else {
            break;
        }
    }
    // Calculate the width expansion due to skewing
    int w = ceil((img_filter.height) * tan(angle * M_PI / 180.0));
    // Create a new image for the skewed result
    Image img_skewed(img_filter.width + abs(w), img_filter.height);
    // Fill the new image with white color
    for (int i = 0; i < img_skewed.width; i++) {
        for (int j = 0; j < img_skewed.height; j++) {
            for (int k = 0; k < 3; k++) {
                img_skewed(i, j, k) = 255;
            }
        }
    }
    // Skew the original image and copy it to the new image
    int c = 0;
    if ((angle > 90.00 && angle < 180.00) || (angle > 270.00 && angle < 360.00)) {
        for (int i = 0; i < img_filter.width; i++) {
            for (int j = 0; j < img_filter.height; j++) {
                for (int k = 0; k < 3; k++) {
                    // Copy the pixel value from the original image to the skewed image, applying the horizontal offset (c) to the column index (i)
                    img_skewed(i - c, j, k) = img_filter(i, j, k);
                }
                // Calculate the horizontal offset (c) for each row in the skewed image based on the skew angle and current row index (j)
                c = ceil(j * tan(angle * M_PI / 180.0));
            }
            c = 0;
        }
    } else {
        for (int i = w; i < img_skewed.width; i++) { // Iterate through the columns of the skewed image, starting from the width expansion due to skewing (w)
            for (int j = 0; j < img_filter.height; j++) {
                for (int k = 0; k < 3; k++) {
                    // Copy the pixel value from the original image to the skewed image, applying the horizontal offset (c) to the column index (i)
                    img_skewed(i - c, j, k) = img_filter(i - w, j, k);
                }
                // Calculate the horizontal offset (c) for each row in the skewed image based on the skew angle and current row index (j)
                c = ceil(j * tan(angle * M_PI / 180.0));
            }
            c = 0;
        }
    }
    // Update the input image with the skewed result
    img_filter = img_skewed;
}

// This function performs a channel swapper.
void channel_swap() {
    // Loop through each column of the image
    for (int i = 0; i < img_filter.width; i++) {
        // Loop through each row of the image
        for (int j = 0; j < img_filter.height; ++j) {
            // Swap the red channel (index 0) with the blue channel (index 2)
            swap(img_filter(i, j, 0), img_filter(i, j, 2));
            // Swap the green channel (index 1) with the blue channel (index 2)
            swap(img_filter(i, j, 1), img_filter(i, j, 2));
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
    img_filter = img_in; // Set the filter image to the loaded image
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
        cout << "C) Exit this menu\n";
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
                    img_save.saveImage(outimg); // Save the image with the provided name
                    break;
                } catch (invalid_argument) { // Catch exception if saving fails
                    continue;
                }
            }
            cout << "Image Saved!" << endl;
            return 0;
        } else if (savechoice == "B") {
            while (true) {
                try {
                    img_save.saveImage(imginput); // Replace the existing image with the same name
                    break;
                } catch (invalid_argument) { // Catch exception if saving fails
                    continue;
                }
            }
            cout << "Image Saved!" << endl;
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
        cout << "G) Skew\n";
        cout << "H) Edit Brightness\n";
        cout << "I) Resize\n";
        cout << "J) Crop\n";
        cout << "K) Blur\n";
        cout << "L) Pixlate\n";
        cout << "M) Detect image edges\n";
        cout << "N) Frame\n";
        cout << "O) Wanno Day\n";
        cout << "P) Wanno Night\n";
        cout << "Q) Wanno TV\n";
        cout << "R) Infera Red\n";
        cout << "S) Oil Painting\n";
        cout << "T) Channel Swap\n";
        cout << "U) Encrypt\n";
        cout << "V) Decrypt\n";
        cout << "W) Clear All Filters\n";
        cout << "X) Back to Main menu\n";
        cout << "Y) Save image\n";
        cout << "Z) Exit\n";
        cout << "========================\n";
        cout << "Enter your choice: ";
        cin >> filterschoice; // Read user's filter choice
        transform(filterschoice.begin(), filterschoice.end(), filterschoice.begin(), ::toupper); // Convert filter choice to uppercase
        if (filterschoice == "A") {
            greyscale();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "B") {
            black_and_white();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "C") {
            invert_image();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "D") {
            merge_images_menu();
        } else if (filterschoice == "E") {
            flip_image_menu();
        } else if (filterschoice == "F") {
            rotate_image_menu();
        } else if (filterschoice == "G") {
            Skew();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "H") {
            edit_brightness();
        } else if (filterschoice == "I") {
            resize_menu();
        } else if (filterschoice == "J") {
            crop_image();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "K") {
            blur();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "L") {
            pixelate();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "M") {
            detect_edge();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "N") {
            frame();
        } else if (filterschoice == "O") {
            Wanno_Day();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "P") {
            Wanno_Night();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "Q") {
            Wanno_TV();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "R") {
            infera_red();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "S") {
            oil_painted();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "T") {
            channel_swap();
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "U") {
            encrypt_image(img_filter);
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "V") {
            decrypt_image(img_filter);
            saveindicator = "N";
            cout << "Operation completed successfully!" << endl;
        } else if (filterschoice == "W") {
            while (true) {
                string clear_choice;
                cout << "are you sure that you want to clear all filters? ( Y / N ): ";
                cin >> clear_choice;
                transform(clear_choice.begin(), clear_choice.end(), clear_choice.begin(), ::toupper);
                if (clear_choice == "Y") {
                    img_filter = img_in;
                    saveindicator = "N";
                    cout << "All filters have been cleared!" << endl;
                    break;
                } else if (clear_choice == "N") {
                    break;
                } else {
                    cout << "Please enter a valid choice" << endl;
                    continue;
                }
            }
        } else if (filterschoice == "X") {
            return 1;
        } else if (filterschoice == "Y") {
            save(img_filter);
            saveindicator = "Y";
        } else if (filterschoice == "Z") {
            string exit_choice;
            if (saveindicator == "N") {
                while (true) {
                    cout << "Do you want to save current image before exiting? (Y / N): ";
                    cin >> exit_choice; // Read user's main menu choice
                    transform(exit_choice.begin(), exit_choice.end(), exit_choice.begin(), ::toupper); // Convert main menu choice to uppercase
                    if (exit_choice == "Y") {
                        save(img_filter);
                        return 0;
                    } else if (exit_choice == "N") {
                        return 0;
                    } else {
                        cout << "Please enter a valid choice" << endl;
                        continue;
                    }
                }
            } else if (saveindicator == "Y") {
                return 0;
            }
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
            saveindicator = "N";
            cout << "Image Inserted!" << endl;
        } else if (choice == "B") {
            if (imginput == "NULL") {
                cout << "Please insert an image first! Use option A." << endl;
                continue;
            } else {
                if (filters_menu() == 0) {
                    return 0;
                }
            }
        } else if (choice == "C") {
            if (imginput == "NULL") {
                cout << "Please insert an image first! Use option A." << endl;
                continue;
            } else {
                save(img_filter);
                saveindicator = "Y";
            }
        } else if (choice == "D") {
            string exit_choice;
            if (imginput == "NULL") {
                return 0;
            } else if (saveindicator == "N") {
                while (true) {
                    cout << "Do you want to save current image before exiting? (Y / N): ";
                    cin >> exit_choice; // Read user's main menu choice
                    transform(exit_choice.begin(), exit_choice.end(), exit_choice.begin(), ::toupper); // Convert main menu choice to uppercase
                    if (exit_choice == "Y") {
                        save(img_filter);
                        return 0;
                    } else if (exit_choice == "N") {
                        return 0;
                    } else {
                        cout << "Please enter a valid choice" << endl;
                        continue;
                    }
                }
            } else if (saveindicator == "Y") {
                return 0;
            }
        } else {
            cout << "Please enter a valid choice" << endl;
        }
    }
}