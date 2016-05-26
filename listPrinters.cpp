#include <stdio.h>
#include <cups/cups.h>

void listPrinters()
{
    int i;
    int j;
    cups_dest_t *dests, *dest;

    // Must call cupsFreeDests(), below
    int num_dests = cupsGetDests(&dests);

    for (i = num_dests, dest = dests; i > 0; i --, dest ++)
    {
        // List common info
        printf("%15s%20s%7s%4d\n",
               dest->name,
               dest->instance ? dest->instance : "NULL",
               dest->is_default ? "True" : "False",
               dest->num_options);

        // Must unlink() the ppdName file when done, do not free() the ppdName buffer
        const char *ppdName = cupsGetPPD(dest->name);

        // Must free() the realPpdName buffer when done
        char *realPpdName = realpath(ppdName, NULL);

        printf("\tppd file = %s --> %s\n", ppdName, realPpdName);
        unlink(ppdName);
        free(realPpdName);

        // List options
        cups_option_t *option;
        for (j = dest->num_options, option = dest->options; j > 0; j--, option++) {
            printf("%30s = %s\n", option->name, option->value);
        }
        printf("\n");
    }

    cupsFreeDests(num_dests, dests);

    return;
}

