#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2) //check if the input is legal
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }
    FILE *file = fopen(argv[1], "r"); // open the input file to read
    int imageheader = 512;
    BYTE buffer[imageheader];
    int count = 0;
    FILE *IMG = NULL;
    char jpegfile[10]; //to store the data name
    while (fread(buffer, sizeof(uint8_t), 512, file)) //also can wirte fread(buffer, sizeof(uint8_t), 512, file) == 512
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) //check if it is a jpeg image
        {
            if (count == 0) //the first jpeg
            {
                sprintf(jpegfile, "%03i.jpg", count); //create a jpeg file, use three digits to represent, store nme in char array
                IMG = fopen(jpegfile, "w"); // open the file name you just created (string)
                fwrite(buffer, 512, 1, IMG); //write data from buffer to the output file
                count++;
            }
            else //other jpegs begin (eg.2, 3,...)
            {
                fclose(IMG);
                sprintf(jpegfile, "%03i.jpg", count);
                IMG = fopen(jpegfile, "w");
                fwrite(buffer, 512, 1, IMG);
                count++;
            }
        }
        else
        {
            if (count > 0) //for the contiguous jpeg memory(bigger than 512B) to store
            {
                fwrite(buffer, imageheader, 1, IMG);
            }
        }
    }
    fclose(IMG);
    fclose(file);
}