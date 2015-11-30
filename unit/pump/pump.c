#include <stdio.h>
#include <stdlib.h>
#include "mraa.h"

int main(int argc, char **argv) {
    int dur;

    if (argc != 2) {
        fprintf(stdout, "usage: pump duration\n");
        return EXIT_FAILURE;
    }

    dur = atoi(argv[1]);

    if (dur > 30) {
        fprintf(stdout, "Duration long\n");
        //return EXIT_FAILURE;
    } else if (dur <= 0) {
        fprintf(stdout, "Duration must be positive\n");
        return EXIT_FAILURE;
    }

    mraa_init();
    fprintf(stdout, "Output HIGH for %d seconds\n", dur);
    fflush(stdout);

    mraa_gpio_context gpio;
    gpio = mraa_gpio_init(6);
    mraa_gpio_dir(gpio, MRAA_GPIO_OUT);
    mraa_gpio_write(gpio, 0);

    mraa_gpio_write(gpio, 1);
    sleep(atoi(argv[1]));
    mraa_gpio_write(gpio, 0);

    mraa_gpio_close(gpio);

    mraa_deinit();
    return MRAA_SUCCESS;
}
