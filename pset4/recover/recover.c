#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    // check usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // open memory card
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        return 1;
    }

    // buffer to contain a chunk from the memory card
    BYTE buffer[512];
    // filename to contain latest filename
    char *filename = malloc(8);
    // jpgs to keep track of how many jpegs created
    int jpgs = 0;
    // pointer to jpegs created
    FILE *output;

    while (fread(&buffer, 512, 1, input) != 0)
    {
        // if it's the beginning of a new jpeg
        if ((buffer[0] == 0xff && buffer[1] == 0xd8) &&
            (buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0))
        {
            jpgs++;
            if (jpgs > 1)
            {
                fclose(output);
            }
            sprintf(filename, "%03i.jpg", jpgs - 1);
            output = fopen(filename, "w");
            fwrite(&buffer, 512, 1, output);
        }
        // if it's a continuation of a jpeg
        else if (jpgs > 0)
        {
            fwrite(&buffer, 512, 1, output);
        }
    }

    fclose(output);
    fclose(input);
    free(filename);
}
