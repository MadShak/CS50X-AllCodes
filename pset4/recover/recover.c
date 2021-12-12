#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define FAT 512

typedef uint8_t BYTE;

int main(int ac, char *av[])
{
    if (ac != 2)

    {
        fprintf(stderr, "Command: ./recover image");
        return 1;
    }

    char *image = av[1];

    // Open file.
    FILE *file = fopen(image, "r");

    if (file == NULL)

    {
        fprintf(stderr, "Something is wrong, try again %s.\n", image);
        return 2;
    }

    BYTE buffer[FAT];

    FILE *img;

    // Warns that the first image was found.
    bool imageF = false;
    int imageN = 0;
    char out[8];



    while (fread(buffer, sizeof(buffer), 1, file) == 1)

    {
        // Warns you when to write a new jpg.
        bool writeJpg = false;


        if (imageF)

        {
            if (buffer[0] == 0xff &&
                buffer[1] == 0xd8 &&
                buffer[2] == 0xff &&
                (buffer[3] & 0xf0) == 0xe0)
            {
                // New JPEG Counter.
                imageN++;
                writeJpg = true;


                fclose(img);
            }

            if (writeJpg)

            {
                // Output file (name).
                sprintf(out, "%03d.jpg", imageN);

                // Open img file (writing).
                img = fopen(out, "w");
            }

            else

            {

                fclose(img);

                // Open img file (attach).
                img = fopen(out, "a");
            }

            // Write.
            fwrite(buffer, sizeof(buffer), 1, img);
        }
        // First JPEG found.
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0 && imageF == false)
        {
            imageF = true;

            // Output file (name).
            sprintf(out, "%03d.jpg", imageN);

            // Open img file (writing).
            img = fopen(out, "w");

            // Write.
            fwrite(buffer, sizeof(buffer), 1, img);
        }
    }

    fclose(file);

    fclose(img);

    return 0;
}