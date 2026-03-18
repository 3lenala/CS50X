#include "helpers.h"
#include <math.h>

#define UCHAR_MAX 255

int correct_overflow(int value);

// Convert image to grayscale
// Each pixel's red, green, and blue values are averaged
// and then assigned equally to all three channels.
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = (int) round(
                (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            // the average can be > UCHAR_MAX
            // if it is, we correct it
            average = correct_overflow(average);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
// Each pixel's new R, G, B is a weighted sum of the old R, G, B.
// Coefficients chosen to emulate warm tones of old photographs.
// Values are clamped to 255 (max byte) using correct_overflow.
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepia_red;
    int sepia_green;
    int sepia_blue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Coefficients for the standard sepia filter
            // Derive the weighted R, G, B values to simulate the warm tone
            // from old pictures
            sepia_red = (int) round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen +
                                    0.189 * image[i][j].rgbtBlue); // weighting for red channel
            sepia_green = (int) round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen +
                                      0.168 * image[i][j].rgbtBlue); // weighting for green channel
            sepia_blue = (int) round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen +
                                     0.131 * image[i][j].rgbtBlue); // weighting for blue channel
            image[i][j].rgbtRed = correct_overflow(sepia_red);
            image[i][j].rgbtGreen = correct_overflow(sepia_green);
            image[i][j].rgbtBlue = correct_overflow(sepia_blue);
        }
    }
    return;
}

// Reflect image horizontally
// Each pixel at (i, j) is swapped with its symmetric counterpart (i, width - j - 1).
// Only loop over half of the row (width/2) to avoid undoing swaps.
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE auxiliar;
    int reflct;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++) // width/2 so that we don't reverse a change
        {
            auxiliar = image[i][j];
            reflct = width - j - 1;
            image[i][j] = image[i][reflct];
            image[i][reflct] = auxiliar;
        }
    }
    return;
}

// Blur image
// For each pixel, compute the average of the RGB values of all neighboring pixels (3x3 box).
// A copy of the original image is used to avoid mixing already-modified values.
// Edge pixels naturally consider fewer neighbors (skip out-of-bound indices).
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j]; // we make a copy so that we don't contaminate the
            // calculations through already modified values
        }
    }

    int avg_red;
    int avg_green;
    int avg_blue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            int sum_red = 0;
            int sum_green = 0;
            int sum_blue = 0;

            for (int k = i - 1; k <= i + 1; k++)
            {
                if (k < 0 || k >= height)
                {
                    continue; // skip if the pixel doesn't exit
                }
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (l < 0 || l >= width)
                    {
                        continue; // skip if the pixel doesn't exit
                    }
                    count += 1;
                    sum_red += copy[k][l].rgbtRed;
                    sum_green += copy[k][l].rgbtGreen;
                    sum_blue += copy[k][l].rgbtBlue;
                }
            }

            avg_red = (int) round(sum_red / (float) count);
            avg_green = (int) round(sum_green / (float) count);
            avg_blue = (int) round(sum_blue / (float) count);

            image[i][j].rgbtRed = correct_overflow(avg_red);
            image[i][j].rgbtGreen = correct_overflow(avg_green);
            image[i][j].rgbtBlue = correct_overflow(avg_blue);
        }
    }
    return;
}
// Clamp a value to the maximum allowed by one byte (0–255).
// if a value is greater than a byte (255)
// it gets corrected to equal a byte
int correct_overflow(int value)
{
    if (value > UCHAR_MAX)
    {
        return UCHAR_MAX;
    }
    return value;
}
