#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop over pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            image[i][j].rgbtBlue = round(avg);
            image[i][j].rgbtGreen = round(avg);
            image[i][j].rgbtRed = round(avg);
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sapiaRed = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen +
                             0.189 * image[i][j].rgbtBlue;
            if (sapiaRed > 255)
            {
                sapiaRed = 255;
            }
            float sapiaGreen = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen +
                               0.168 * image[i][j].rgbtBlue;
            if (sapiaGreen > 255)
            {
                sapiaGreen = 255;
            }
            float sapiaBlue = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen +
                              0.131 * image[i][j].rgbtBlue;
            if (sapiaBlue > 255)
            {
                sapiaBlue = 255;
            }

            image[i][j].rgbtRed = round(sapiaRed);
            image[i][j].rgbtGreen = round(sapiaGreen);
            image[i][j].rgbtBlue = round(sapiaBlue);
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width - 1; j < k; j++, k--)
        {
            RGBTRIPLE temp;
            temp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avgRed = 0;
            int avgGreen = 0;
            int avgBlue = 0;
            int cnt = 0;

            for (int n = i - 1; n <= i + 1; n++)
            {
                if (n < 0 || n >= height)
                {
                    continue;
                }
                for (int m = j - 1; m <= j + 1; m++)
                {
                    if (m < 0 || m >= width)
                    {
                        continue;
                    }

                    avgRed += image[n][m].rgbtRed;
                    avgGreen += image[n][m].rgbtGreen;
                    avgBlue += image[n][m].rgbtBlue;

                    cnt++;
                }
            }

            temp[i][j].rgbtRed = round((float) (avgRed) / cnt);
            temp[i][j].rgbtGreen = round((float) (avgGreen) / cnt);
            temp[i][j].rgbtBlue = round((float) (avgBlue) / cnt);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}
