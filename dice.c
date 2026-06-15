#include <stdio.h>
#include <stdint.h>
#include <sys/random.h>
#include <unistd.h>
#include <stdlib.h>

#define BAD_ARGS() puts("Usage: [-s sides] [-t throws]"); return 1

int main(int argc, char** argv)
{
    uint64_t sides = 6;
    uint64_t throws = 1;

    int option;

    while ((option = getopt(argc, argv, ":s:t:")) != -1)
    {
        switch (option)
        {
        case 's':
            if (optarg[0] == '-')
            {
                puts("Missing argument for -s");
                BAD_ARGS();
            }
            if (!(optarg[0] > 47 && optarg[0] < 58))
            {
                puts("Argument for -s must be a number");
                BAD_ARGS();
            }
            sides = strtoul(optarg, NULL, 10);
            if (sides == 0) { return 0; }
            break;
        case 't':
            if (optarg[0] == '-')
            {
                puts("Missing argument for -t");
                BAD_ARGS();
            }
            if (!(optarg[0] > 47 && optarg[0] < 58))
            {
                puts("Argument for -t must be a number");
                BAD_ARGS();
            }
            throws = strtoul(optarg, NULL, 10);
            break;
        case ':':
            printf("Missing argument for -%c.\n", optopt);
            BAD_ARGS();
        case '?':
            BAD_ARGS();
        }
    }

    uint64_t randomBuffer;

    for (uint64_t i = 0; i < throws; i++)
    {
        getrandom(&randomBuffer, sizeof(randomBuffer), 0);
        printf("%lu\n", (randomBuffer % sides) + 1);
    }

    return 0;
}
