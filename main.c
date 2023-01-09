/**
 * ===========================================================
 * Name: David Petzold
 * Section: M3
 * Project: Practice debugging lab.
 * ===========================================================
 */

/****************************************************************
 * COMPLETION INSTRUCTIONS:
 *
 * This program should read data from the number.dat file
 * and store in an array of integers.  It should prompt the
 * user to enter a value, then use binary search to determine
 * if the value is in the array.
 *
 * There are errors present in this code you should fix them.
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX_NUMBERS 1000 /* Max numbers in file */

const char DATA_FILE[] = "numbers.dat"; /* File with numbers */

int data[MAX_NUMBERS]; /* Array of numbers to search */
int max_count;         /* Number of valid elements in data */

int main() {
    FILE *in_file; /* Input file */
    int middle;    /* Middle of our search range */
    int low, high; /* Upper/lower bound */
    int search;    /* number to search for */
    char line[80]; /* Input line */

    in_file = fopen(DATA_FILE, "r");
    if (in_file == NULL) {
        fprintf(stderr, "Error:Unable to open %s\n", DATA_FILE);
        exit(8);
    }

    /*
     * Read in data
     */

    max_count = 0;
    while (1) {
        if (fgets(line, sizeof(line), in_file) == NULL) {
            break;  /* End of file */
        }

        /* convert number */
        sscanf(line, "%d", &data[max_count]);
        ++max_count;
    }

    while (1) {
        printf("Enter number to search for or -1 to quit:");
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%d", &search);

        if (search == -1) {
            break;
        }

        low = 0;
        high = max_count;
        while (1) {
            middle = (low + high) / 2;

            if (search == data[middle]) {
                printf("Found at index %d\n", middle);
                break;
            } else if (search > data[middle]) { // Search is on the right side of middle
                low = middle;   // Move low to be middle
            } else {    // Search is on the left side of middle
                high = middle;  // Move high to be middle
            }

            if (low == high || low < 0 || high < 0) {
                printf("Not found\n");
                break;
            }
        }
    }
    return 0;
}