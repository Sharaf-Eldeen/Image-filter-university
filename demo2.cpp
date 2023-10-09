#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

unsigned char image[SIZE][SIZE];

void load_image();
void save_image();
void choose_filter_to_do();
void apply_black_and_white_filter();
void apply_invert_filter();
void apply_merge_filter();
void apply_flip_image();
void apply_darken_and_lighten_image();
void apply_rotate_image();

int main()
{
    load_image();
    choose_filter_to_do();
    save_image();
    return 0;
}

void load_image()
{
    char image_file_name[100];

    cout << "Ahlan ya user ya habibi" << "\n";
    cout << "Please enter file name of the image to process:" << "\n";
    cin >> image_file_name;
    strcat(image_file_name, ".bmp");
    readGSBMP(image_file_name, image);
}

void save_image()
{
    char image_file_name[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> image_file_name;

    // Add .bmp extension and save image
    strcat(image_file_name, ".bmp");
    writeGSBMP(image_file_name, image);
}

void choose_filter_to_do()
{
    int number_of_filter;
    cout << "1- Black & White Filter" << "\n";
    cout << "2- Invert Filter" << "\n";
    cout << "3- Merge Filter" << "\n";
    cout << "4- Flip Image" << "\n";
    cout << "5- Darken and Lighten Image" << "\n";
    cout << "6- Rotate Image" << "\n";
    cout << "0- Exit" << "\n";
    cin >> number_of_filter;

    switch (number_of_filter)
    {
    case 1:
        apply_black_and_white_filter();
        break;
    case 2:
        apply_invert_filter();
        break;
    case 3:
        apply_merge_filter();
        break;
    case 4:
        apply_flip_image();
        break;
    case 5:
        apply_darken_and_lighten_image();
        break;
    case 6:
        apply_rotate_image();
        break;
    case 0:
        cout << "Exiting program." << "\n";
        break;
    default:
        cout << "Invalid selection." << "\n";
    }
}

// Function to apply the black and white filter
void apply_black_and_white_filter()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}

// Function to apply the invert filter
void apply_invert_filter()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // Invert the color of each pixel by subtracting its value from 255
            image[i][j] = 255 - image[i][j];
        }
    }
    cout << "Invert filter applied." << "\n";
}

// Function to apply the merge filter by averaging two images
void apply_merge_filter()
{
    char second_image_file_name[100];

    cout << "Enter the second image file name (without extension): ";
    cin >> second_image_file_name;

    // Load the second image
    strcat(second_image_file_name, ".bmp");
    unsigned char second_image[SIZE][SIZE];
    readGSBMP(second_image_file_name, second_image);

    unsigned char merged_image[SIZE][SIZE]; // Create a new image to store the merged result

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // Calculate the average of pixel values from both images
            merged_image[i][j] = (image[i][j] + second_image[i][j]) / 2;
        }
    }

    // Copy the merged image back to the original image array
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = merged_image[i][j];
        }
    }

    cout << "Images merged." << "\n";

// Function to apply the flip image operation
void apply_flip_image()
{
    int flip_choice;
    unsigned char flipped_image[SIZE][SIZE];

    cout << "Choose flip direction:" << "\n";
    cout << "1 - Vertical flip" << "\n";
    cout << "2 - Horizontal flip" << "\n";
    cin >> flip_choice;

    if (flip_choice == 1)
    {
        // Vertical flip
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                flipped_image[i][j] = image[SIZE-i][j];
            }
        }
        cout << "Vertical flip applied." << "\n";
    }
    else if (flip_choice == 2)
    {
        // Horizontal flip
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                flipped_image[i][j] = image[i][SIZE- j];
            }
        }
         cout << "Horizontal flip applied." << "\n";
    }


    else
    {
        cout << "Invalid choice. No flip applied." << "\n";
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = flipped_image[i][j];
        }
    }
}

// Function to apply the darken and lighten image operation (by 50%)
void apply_darken_and_lighten_image()
{
    int darken_lighten_choice;

    cout << "Choose an option:" << "\n";
    cout << "1 - Darken Image by 50%" << "\n";
    cout << "2 - Lighten Image by 50%" << "\n";
    cin >> darken_lighten_choice;

    if (darken_lighten_choice == 1)
    {
        // Darken Image by 50%
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                // Reduce each pixel's value by half (divide by 2)
                image[i][j] = image[i][j] / 2;
            }
        }
        cout << "Image darkened by 50%." << "\n";
    }
    else if (darken_lighten_choice == 2)
    {
        // Lighten Image by 50%
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                // Increase each pixel's value by half (multiply by 1.5)
                image[i][j] = static_cast<unsigned char>(min(255, static_cast<int>(1.5 * image[i][j])));
            }
        }
        cout << "Image lightened by 50%." << "\n";
    }
    else
    {
        cout << "Invalid choice. No operation applied." << "\n";
    }
}

// Function to apply the rotate image operation
void apply_rotate_image()
{
    int rotate_choice;

    cout << "Choose rotation angle:" << "\n";
    cout << "1 - 90 degrees clockwise" << "\n";
    cout << "2 - 180 degrees clockwise" << "\n";
    cout << "3 - 270 degrees clockwise" << "\n";
    cin >> rotate_choice;

    unsigned char rotated_image[SIZE][SIZE];

    if (rotate_choice == 1)
    {
        // Rotate 90 degrees clockwise
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                rotated_image[i][j] = image[SIZE - 1 - j][i];
            }
        }
        cout << "90-degree clockwise rotation applied." << "\n";
    }
    else if (rotate_choice == 2)
    {
        // Rotate 180 degrees clockwise
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                rotated_image[i][j] = image[SIZE - 1 - i][SIZE - 1 - j];
            }
        }
        cout << "180-degree clockwise rotation applied." << "\n";
    }
    else if (rotate_choice == 3)
    {
        // Rotate 270 degrees clockwise
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                rotated_image[i][j] = image[j][SIZE - 1 - i];
            }
        }
        cout << "270-degree clockwise rotation applied." << "\n";
    }
    else
    {
        cout << "Invalid choice. No rotation applied." << "\n";
        return;
    }

    // Copy the rotated image back to the original image array
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = rotated_image[i][j];
        }
    }
}
