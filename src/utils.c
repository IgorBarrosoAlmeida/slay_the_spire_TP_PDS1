#include "utils.h"
#include "constants.h"

#include <allegro5/allegro5.h>
#include <stdio.h>

void must_init(_Bool test, const char* description)
{
    if (test)
        return;

    fprintf(stderr, "couldn't initialize %s\n", description);
    exit(INITIALIZE_ERROR);
}

void shuffle_array(int* array, int size)
{
    if (size > 1) {
        int i;
        for (i = 0; i < size - 1; i++) {
            int j = i + rand() / (RAND_MAX / (size - i) + 1);
            if (j == i) {
                continue;
            }
            int int_j = array[j];

            array[j] = array[i];

            array[i] = int_j;
        }
    }
}