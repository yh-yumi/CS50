#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0;
            image[i][j].rgbtRed = (int)(average + 0.5);
            image[i][j].rgbtGreen = (int)(average + 0.5);
            image[i][j].rgbtBlue = (int)(average + 0.5);
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
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float sepiaBlue = .272 * image[i][j].rgbtRed + .131 * image[i][j].rgbtBlue + .534 * image[i][j].rgbtGreen;
            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            if ((int)(sepiaRed + 0.5) > 255) //check if the number is out of 255
            {
                sepiaRed = 255.0;
            }
            if ((int)(sepiaBlue + 0.5) > 255)
            {
                sepiaBlue = 255.0;
            }
            if ((int)(sepiaGreen + 0.5) > 255)
            {
                sepiaGreen = 255.0;
            }
            image[i][j].rgbtBlue = (int)(sepiaBlue + 0.5);
            image[i][j].rgbtRed = (int)(sepiaRed + 0.5);
            image[i][j].rgbtGreen = (int)(sepiaGreen + 0.5);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        if (width % 2 == 0)
        {
            for (int j = 0; j < width / 2; j++) //for number that can be diveded by 2, only do the half part
            {
                RGBTRIPLE temp = image[i][j];
                image[i][j] = image[i][width - 1 - j];
                image[i][width - 1 - j] = temp;
            }
        }
        else
            for (int j = 0; j < width / 2 + 1; j++) //for the odd width number
            {
                RGBTRIPLE temp = image[i][j];
                image[i][j] = image[i][width - 1 - j];
                image[i][width - 1 - j] = temp;
            }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) //image is a pointer to  one dimension array
{
    RGBTRIPLE copy[height][width]; // create a copy array to assin not to change the original number
    copy[0][0].rgbtRed = (int)((image[0][0].rgbtRed + image[0][1].rgbtRed + //the corner average
                                image[1][0].rgbtRed + image[1][1].rgbtRed) / 4.0 + 0.5);
    copy[0][0].rgbtBlue = (int)((image[0][0].rgbtBlue + image [0][1].rgbtBlue +
                                 image[1][0].rgbtBlue + image[1][1].rgbtBlue) / 4.0 + 0.5);
    copy[0][0].rgbtGreen = (int)((image[0][0].rgbtGreen + image [0][1].rgbtGreen +
                                  image[1][0].rgbtGreen + image[1][1].rgbtGreen) / 4.0 + 0.5);

    copy[0][width - 1].rgbtRed = (int)((image[0][width - 1].rgbtRed + image[0][width - 2].rgbtRed +
                                        image[1][width - 1].rgbtRed + image[1][width - 2].rgbtRed) / 4.0 + 0.5);
    copy[0][width - 1].rgbtBlue = (int)((image[0][width - 1].rgbtBlue + image[0][width - 2].rgbtBlue +
                                         image[1][width - 1].rgbtBlue + image[1][width - 2].rgbtBlue) / 4.0 + 0.5);
    copy[0][width - 1].rgbtGreen = (int)((image[0][width - 1].rgbtGreen + image[0][width - 2].rgbtGreen +
                                          image[1][width - 1].rgbtGreen + image[1][width - 2].rgbtGreen) / 4.0 + 0.5);

    copy[height - 1][0].rgbtRed = (int)((image[height - 2][0].rgbtRed + image[height - 2][1].rgbtRed +
                                         image[height - 1][0].rgbtRed + image[height - 1][1].rgbtRed) / 4.0 + 0.5);
    copy[height - 1][0].rgbtBlue = (int)((image[height - 2][0].rgbtBlue + image[height - 2][1].rgbtBlue +
                                          image[height - 1][0].rgbtBlue + image[height - 1][1].rgbtBlue) / 4.0 + 0.5);
    copy[height - 1][0].rgbtGreen = (int)((image[height - 2][0].rgbtGreen + image[height - 2][1].rgbtGreen +
                                           image[height - 1][0].rgbtGreen + image[height - 1][1].rgbtGreen) / 4.0 + 0.5);

    copy[height - 1][width - 1].rgbtRed = (int)((image[height - 2][width - 2].rgbtRed + image[height - 2][width - 1].rgbtRed +
                                          image[height - 1][width - 2].rgbtRed + image[height - 1][width - 1].rgbtRed) / 4.0 + 0.5);
    copy[height - 1][width - 1].rgbtBlue = (int)((image[height - 2][width - 2].rgbtBlue + image[height - 2][width - 1].rgbtBlue +
                                           image[height - 1][width - 2].rgbtBlue + image[height - 1][width - 1].rgbtBlue) / 4.0 + 0.5);
    copy[height - 1][width - 1].rgbtGreen = (int)((image[height - 2][width - 2].rgbtGreen + image[height - 2][width - 1].rgbtGreen +
                                            image[height - 1][width - 2].rgbtGreen + image[height - 1][width - 1].rgbtGreen) / 4.0 + 0.5);
    for (int i = 0, j = 1; j < width - 1; j++) // for the top edge
    {
        copy[i][j].rgbtRed = (int)((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                    image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0 + 0.5);
        copy[i][j].rgbtBlue = (int)((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                     image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0 + 0.5);
        copy[i][j].rgbtGreen = (int)((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                      image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0 + 0.5);
    }
    for (int i = height - 1, j = 1; j < width - 1; j++) // for the bottom edge
    {
        copy[i][j].rgbtRed = (int)((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                    image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed) / 6.0 + 0.5);
        copy[i][j].rgbtBlue = (int)((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                     image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue) / 6.0 + 0.5);
        copy[i][j].rgbtGreen = (int)((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                      image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen) / 6.0 + 0.5);
    }
    for (int i = 1, j = 0; i < height - 1; i++) //for the left edge
    {
        copy[i][j].rgbtRed = (int)((image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed +
                                    image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0 + 0.5);
        copy[i][j].rgbtBlue = (int)((image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue +
                                     image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0 + 0.5);
        copy[i][j].rgbtGreen = (int)((image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j].rgbtGreen +
                                      image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0 + 0.5);
    }
    for (int i = 1, j = width - 1; i < height - 1; i++) // for the right edge
    {
        copy[i][j].rgbtRed = (int)((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed +
                                    image[i][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) / 6.0 + 0.5);
        copy[i][j].rgbtBlue = (int)((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                                     image[i][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 6.0 + 0.5);
        copy[i][j].rgbtGreen = (int)((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                                      image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 6.0 + 0.5);
    }
    for (int i = 1; i < height - 1; i++) // for the middle
    {
        for (int j = 1; j < width - 1; j++)
        {
            copy[i][j].rgbtRed = (int)((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                        image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                        image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9.0 + 0.5);
            copy[i][j].rgbtBlue = (int)((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                         image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                         image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9.0 + 0.5);
            copy[i][j].rgbtGreen = (int)((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                          image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + 
                                          image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9.0 + 0.5);
        }
    }
    for (int i = 0; i < height; i++) // assin the value to image
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
        }
    }
    return;
}
