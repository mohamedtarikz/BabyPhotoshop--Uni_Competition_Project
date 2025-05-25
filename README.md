# Baby Photoshop for Image Processing

This project is a simplified image processing application inspired by Photoshop, allowing users to load images and apply a wide range of filters and effects.

## Features

### Filter 1: Grayscale Conversion
Converts the image to grayscale, removing all color and leaving only shades of gray.

### Filter 2: Black and White
Converts the image to pure black and white, with no intermediate shades.

### Filter 3: Invert Image
Inverts the colors of the image, producing a photographic negative effect.

### Filter 4: Merge Images
Combines two images into one. Handles different image sizes by resizing or cropping as needed.

### Filter 5: Flip Image
Mirrors the image horizontally, vertically, or both.

### Filter 6: Rotate Image
Rotates the image clockwise by 90°, 180°, or 270°.

### Filter 7: Darken and Lighten Image
Adjusts brightness, allowing the user to darken or lighten the image by 50%.

### Filter 8: Crop Images
Removes portions of the image to focus on a specific area.

### Filter 9: Add Frame
Adds a simple or fancy frame in a requested color or style.

### Filter 10: Detect Image Edges
Highlights the edges within the image for edge detection effects.

### Filter 11: Resize Image
Changes the dimensions of the image, either by specifying new dimensions or a scaling ratio.

### Filter 12: Blur Image
Applies a blur effect to reduce detail and smooth the image.

### Filter 13: Pixelate Image
Applies a pixelation effect, making the image appear blocky.

### Filter 14: Oil Painting Effect
Applies an oil painting artistic effect.

### Filter 15: Channel Swap
Swaps the color channels (e.g., RGB to BGR) for creative effects.

### Filter 16: Infrared/Wano TV/Wano Day
Special artistic or themed filters.

### Filter 17: Skew Image
Skews the image along an axis.

### Filter 18: Clear All Filters
Resets the image to its original state.

### Image Steganography (Text Hiding)

This application includes a feature for hiding and retrieving secret text messages within images, also known as image steganography. Unlike the standard filters, this feature allows you to embed a message into the image by subtly manipulating pixel values, making the text invisible to the naked eye but retrievable by the program.

- **Encrypt (Hide Text):**
  - Select the 'Encrypt' option from the menu.
  - Enter the secret message you wish to hide.
  - The program encodes the message into the image's pixel data.

- **Decrypt (Reveal Text):**
  - Select the 'Decrypt' option from the menu.
  - The program scans the image and extracts any hidden message, displaying it if present.

This feature is implemented in the `library/encryption-decryption.h` file and is accessible from the main menu. It is useful for watermarking, copyright marking, or securely sharing hidden information within an image.

## Installation

### Prerequisites
- C++ compiler (e.g., g++, clang++)
- stb_image and stb_image_write libraries (included in `library/`)
- Windows OS (tested)

## Troubleshooting
- Ensure your images are in a supported format.
- If you encounter build errors, verify that all required libraries are present in the `library/` folder.
- For large images or complex filters, processing may take longer.

## Contributors
- Mohamed Tarek
- Marwan Hussein
- Mazen Nasser

## Additional Notes
- Test with various images for best results.
- Report bugs or issues to the development team.
- Some advanced filters (Pixelate, Oil Painting, Channel Swap, Infrared, Wano TV, Skew) may be experimental or optional depending on your version.
