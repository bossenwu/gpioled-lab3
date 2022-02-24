// SPDX-License-Identifier: GPL-3.0+
// SPDX-FileCopyrightText: 2022 Bossen WU <bossen.wu@st.com>
/*
 * gpiolab.c
 *
 *  Created on: Feb 24, 2022
 *      Author: Bossen Wu
 */

#include <errno.h>
#include <gpiod.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define GPIOA   "/dev/gpiochip0"
#define PA14    14

int main(void)
{
	struct gpiod_line *line;
	struct gpiod_chip *gpiochip;
	unsigned int count = 0;
	int i, value = 0, ret = 0;

	gpiochip = gpiod_chip_open(GPIOA);
	line = gpiod_chip_get_line(gpiochip, PA14);
	if (line == NULL)
		goto EXIT_CHIP;

	ret = gpiod_line_request_output(line, "gpiolab", 0);
	if (ret)
	{
		printf("gpiod_line_request_output failed \n");
		goto EXIT_LINE;
	}

	do {
		count++;
		for (i=0; i < 6; i++)
		{
			value = (value) ? 0 : 1;
			ret = gpiod_line_set_value(line, value);
			if (ret)
				goto EXIT_LINE;

			usleep(200000);
		}
		sleep(1);
	} while (count < 5);

	EXIT_LINE:
	gpiod_line_release(line);

	EXIT_CHIP:
	gpiod_chip_close(gpiochip);

	printf("gpiolab is completed \n");
	return 0;
}
