#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512
#define NAME_SIZE 8 // the output files will be called "###.jpg"
// so the name string will be made out of 8 characters

bool check_signature(uint8_t *buffer);
bool find_first_signature(uint8_t *buffer, FILE *input);

int main(int argc, char *argv[])
{
    // the first three bytes of JPEGs are: 0xff 0xd8 0xff
    if (argc != 2)
    {
        printf("Usage: ./recover filename \n");
        return 1;
    }

    FILE *input = fopen(argv[1], "rb");

    char output_name[8];
    int output_number = 0;

    if (input == NULL)
    {
        fprintf(stderr, "Could not open file.\n");
        return 1; // open error
    }

    uint8_t buffer[BLOCK_SIZE];
    FILE *output = NULL;

    // to find the first signature
    if (!find_first_signature(buffer, input))
    {
        fclose(input);
        fprintf(stderr, "No signature found\n");
        return 4;
    }

    do
    {
        if (check_signature(buffer))
        {
            if (output != NULL) // close the recovered output file if there is one
            {
                fclose(output);
            }
            sprintf(output_name, "%03d.jpg", output_number); // create a new output file if possible
            output = fopen(output_name, "wb");
            if (output == NULL)
            {
                fclose(input);
                fprintf(stderr, "New output file could not be created\n");
                return 1; // open error
                // if it was not possible, give an error
            }
            output_number += 1;
        }
        if (fwrite(buffer, sizeof(buffer), 1, output) != 1) // write the next block into
        // the output file
        {
            // if it is not possible, return an error
            fclose(input);
            fprintf(stderr, "Error writing the output file\n");
            return 2; // write error
        }
    }
    while (fread(buffer, BLOCK_SIZE * sizeof(uint8_t), 1, input) == 1);
    // do that while there is still a full block to read

    fclose(output);
    fclose(input);
    return 0; // if everything was successful
}

bool check_signature(uint8_t *buffer)
{
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
           (buffer[3] & 0xf0) == 0xe0;
}

bool find_first_signature(uint8_t *buffer, FILE *input)
{
    do
    {
        if (fread(buffer, BLOCK_SIZE * sizeof(uint8_t), 1, input) != 1)
        {
            return false;
        }
    }
    while (!check_signature(buffer));
    return true;
}
