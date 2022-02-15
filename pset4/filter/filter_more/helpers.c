#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for each row
    for (int i = 0; i < height; i++)
    {
        // for each column
        for (int j = 0; j < width; j++)
        {
            BYTE buffer = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen
                + image[i][j].rgbtRed) / 3.0);

            // make all values = buffer
            image[i][j].rgbtBlue = image[i][j].rgbtGreen
                = image[i][j].rgbtRed = buffer;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // for each row
    for (int i = 0; i < height; i++)
    {
        // copy row
        RGBTRIPLE buffer[width];
        for (int k = 0; k < width; k++)
        {
            buffer[k] = image[i][k];
        }

        // reverse the rows
        for (int j = 0; j < width; j++)
        {
            image[i][j] = buffer[width - (j + 1)];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create copy
    RGBTRIPLE blurred[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blurred[i][j] = image[i][j];
        }
    }

    // loop through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red, green, blue;
            red = green = blue = 0;
            float counter = 0.0;


            // go through the surrounding pixels
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    // if value exists
                    if (((k < height && k >= 0) && (l < width && l >= 0)))
                    {
                        counter++;
                        red += image[k][l].rgbtRed;
                        green += image[k][l].rgbtGreen;
                        blue += image[k][l].rgbtBlue;
                    }
                }
            }

            // divide the whole thing by the amount of surrounding pixels
            blurred[i][j].rgbtRed = round(red / counter);
            blurred[i][j].rgbtGreen = round(green / counter);
            blurred[i][j].rgbtBlue = round(blue / counter);
        }
    }

    // move copy to ori array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blurred[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    return;
}
