// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE]; //To create an array of spaces to store the data when reading from the file
    // uint8_t is a type that stores an 8-bit unsigned (i.e. not negative) integer
    fread(header, sizeof(uint8_t), 44, input); //the first parameter is the pointer to the location in
    // the memory to store the data when reading from the file
    fwrite(header, HEADER_SIZE, 1, output);
    int16_t buffer; //No need to store 44 bytes data, just 2 bytes, for a type stores an integer with 16 bits
    while (fread(&buffer, sizeof(int16_t), 1, input))
        //fread function returns the number of items of data successfully read. By this to check if it is the end of file.
    {
        buffer = factor * buffer;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    // TODO: Read samples from input file and write updated data to output file

    // Close files
    fclose(input);
    fclose(output);
}
