#include "helpers.h"
#include <math.h>


void swap(RGBTRIPLE *x, RGBTRIPLE *y);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int row = 0; row < height ; row++)
    {
        for(int column = 0 ; column < width ;column++)
        {
          int graypixel=round((image[row][column].rgbtRed+image[row][column].rgbtBlue+image[row][column].rgbtGreen)/3);  
          image[row][column].rgbtRed = graypixel;
          image[row][column].rgbtBlue = graypixel;
          image[row][column].rgbtGreen = graypixel;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int row = 0; row < height ; row++)
    {
        for(int column = 0 ; column < width ;column++)
        {
          int sepiaRed = round(.393 * image[row][column].rgbtRed + .769 * image[row][column].rgbtGreen + .189 *image[row][column].rgbtBlue);
          int sepiaGreen = round(.349 * image[row][column].rgbtRed + .686 * image[row][column].rgbtGreen + .168 * image[row][column].rgbtBlue);
          int sepiaBlue = round(.272 *  image[row][column].rgbtRed + .534 * image[row][column].rgbtGreen + .131 * image[row][column].rgbtBlue);
          
          
          image[row][column].rgbtRed = fmin(255,sepiaRed);
          image[row][column].rgbtBlue = fmin(255 ,sepiaBlue);
          image[row][column].rgbtGreen = fmin(255,sepiaGreen);
        } 
    }    

    return;
}


//convert to Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int row=0 ;row<height ;row++)
    {
        for(int column=0 ;column<width/2 ;column++)
        {
            swap(&image[row][column],&image[row][width - 1 - column]);
        }
    }
    return;
}

//convert to Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int row=0;row<height;row++)
    {
        for (int column=0;column<width;column++)
        {
            temp[row][column] = image[row][column];
        }
    }
    
    
    
    for (int row=0;row<height;row++)
    {
        for (int column=0;column<width;column++)
        {
            int Red;
            int Blue;
            int Green;
            
            // corner pixels
            if ( (row==0 && column==0) || (row==0 && column==(width - 1)) || (row==(height - 1) && column==0) || (row==(height - 1) && column==(width - 1)) )
            {
                Red = fmin(255,round((temp[row][column].rgbtRed + temp[row][column + 1].rgbtRed + temp[row + 1][column].rgbtRed + temp[row + 1][column + 1].rgbtRed)/4));
                Blue = fmin(255,round((temp[row][column].rgbtBlue + temp[row][column + 1].rgbtBlue + temp[row + 1][column].rgbtBlue + temp[row + 1][column + 1].rgbtBlue)/4));
                Green = fmin(255,round((temp[row][column].rgbtGreen + temp[row][column + 1].rgbtGreen + temp[row + 1][column].rgbtGreen + temp[row + 1][column + 1].rgbtGreen)/4));
            }
            
            //edge pixels
            else if (row==0 || column==0 || row==(height - 1) || column==(width - 1)) 
            {
                  Red = fmin(255,round((temp[row][column].rgbtRed + temp[row - 1][column].rgbtRed + temp[row + 1][column].rgbtRed + temp[row][column + 1].rgbtRed + temp[row + 1][column].rgbtRed + temp[row + 1][column + 1].rgbtRed)/6));
                  Blue = fmin(255,round((temp[row][column].rgbtBlue + temp[row - 1][column].rgbtBlue + temp[row + 1][column].rgbtBlue + temp[row][column + 1].rgbtBlue + temp[row + 1][column].rgbtBlue + temp[row + 1][column + 1].rgbtBlue)/6));
                  Green = fmin(255,round((temp[row][column].rgbtGreen + temp[row - 1][column].rgbtGreen + temp[row + 1][column].rgbtGreen + temp[row][column + 1].rgbtGreen + temp[row + 1][column].rgbtGreen + temp[row + 1][column + 1].rgbtGreen)/6));
            }
            
            //middle pixel
            else
            {
               Red = fmin(255,round((temp[row][column].rgbtRed + temp[row][column - 1].rgbtRed + temp[row][column + 1].rgbtRed + temp[row - 1][column - 1].rgbtRed + temp[row - 1][column].rgbtRed + temp[row - 1][column + 1].rgbtRed + temp[row + 1][column - 1].rgbtRed + temp[row + 1][column].rgbtRed + temp[row + 1][column + 1].rgbtRed )/9)); 
               Blue = fmin(255,round((temp[row][column].rgbtBlue + temp[row][column - 1].rgbtBlue + temp[row][column + 1].rgbtBlue + temp[row - 1][column - 1].rgbtBlue + temp[row - 1][column].rgbtBlue + temp[row - 1][column + 1].rgbtBlue + temp[row + 1][column - 1].rgbtBlue + temp[row + 1][column].rgbtBlue + temp[row + 1][column + 1].rgbtBlue )/9)); 
               Green = fmin(255,round((temp[row][column].rgbtGreen + temp[row][column - 1].rgbtGreen + temp[row][column + 1].rgbtGreen + temp[row - 1][column - 1].rgbtGreen + temp[row - 1][column].rgbtGreen + temp[row - 1][column + 1].rgbtGreen + temp[row + 1][column - 1].rgbtGreen + temp[row + 1][column].rgbtGreen + temp[row + 1][column + 1].rgbtGreen )/9));  
            }
            
            image[row][column].rgbtRed = Red;
            image[row][column].rgbtBlue = Blue;
            image[row][column].rgbtGreen = Green;
            
        }
    }
    return;
}





void swap(RGBTRIPLE *x, RGBTRIPLE *y)
{
    RGBTRIPLE temp = *x;
    *x = *y;
    *y = temp;
}
