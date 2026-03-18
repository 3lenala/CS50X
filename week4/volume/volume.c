
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int copy_header(FILE *input, FILE *output);
int scale_audio_samples(FILE *input, FILE *output, float factor);

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
        fclose(input);
        return 1;
    }

    float factor = atof(argv[3]);

    // copy the header from input file into output file
    if (copy_header(input, output) != 0)
    {
        fclose(input);
        fclose(output);
        return 1;
    }

    // Read samples from input file and write updated data to output file
    if (scale_audio_samples(input, output, factor) != 0)
    {
        fclose(input);
        fclose(output);
        return 1;
    }

    // Close files
    fclose(input);
    fclosle(output);
    return 0;
}

int copy_header(FILE *input, FILE *output)
{
    uint8_t header[HEADER_SIZE];
    if (fread(header, HEADER_SIZE, 1, input) != 1)
    {
        // if the code can’t read a full header block, report an error
        fprintf(stderr, "Error reading the header from the input file\n");
        return 1; // read error
    }
    if (fwrite(header, HEADER_SIZE, 1, output) != 1)
    {
        // if the code can't write a full header block, report an error
        fprintf(stderr, "Error writing the header into the output file\n");
        return 2; // write error
    }
    return 0; // success
}

int scale_audio_samples(FILE *input, FILE *output, float factor)
{
    // each sample is two byte = 16 bits long
    int16_t sample;

    // returns 0 on success, 1 on read error, 2 on write error
    while (fread(&sample, sizeof(sample), 1, input) != 0)
    {
        float scaled = sample * factor; // Updating each of the two byte samples
        // through the expressed factor

        // performs saturation to avoid overflow outside int16_t range
        if (scaled > INT16_MAX)
        {
            sample = INT16_MAX;
        }
        else if (scaled < INT16_MIN)
        {
            sample = INT16_MIN;
        }
        else
        {
            sample = (int16_t) scaled;
        }

        if (fwrite(&sample, sizeof(sample), 1, output) != 1)
        {
            fprintf(stderr, "Error writing the samples into the output file\n");
            return 2;
        }
    }
    return 0;
}
