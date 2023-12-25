#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"

# define RED "\x1b[1m\x1b[38;2;255;0;0m"
# define MB "\x1b[1m\x1b[38;2;25;25;599m"
# define GREEN "\x1b[1m\x1b[38;2;0;128;0m"
# define YELLOW "\x1b[1m\x1b[38;2;205;205;0m"
# define DV "\x1b[1m\x1b[38;2;148;0;211m"
# define C "\x1b[0m"

int main(int ac, char **av) {
	if (ac != 2) {
		printf(RED "Error: " YELLOW "Usage: " C "%s " DV "<file>\n", av[0]);
		return 1;
	}
	FILE *fp = fopen(av[1], "r");
	if (!fp) {
		printf(RED "Error: " YELLOW "Open: " C "Can't open " DV "%s\n", av[1]);
		return 1;
	}

	char	line[1024];
	int		total = 0;
	int		total2 = 0;
	char	*digit[] = {"one\0", "two\0", "three\0", "four\0", "five\0", "six\0", "seven\0", "eight\0", "nine\0", 0};
	while (fgets(line, sizeof(line), fp)) {
		char nb[3] = {0,0,0};
		char nb2[3] = {0,0,0};
		for (int i = 0; line[i]; i++) {
			if (isdigit(line[i])) {
				if (!nb[0])
					nb[0] = line[i];
				if (!nb2[0])
					nb2[0] = line[i];
				nb[1] = line[i];
				nb2[1] = line[i];
			}
			for (int j = 0; digit[j]; j++) {
				if (!strncmp(line + i, digit[j], strlen(digit[j])))
				{
					if (!nb2[0])
						nb2[0] = '0' + j + 1;
					nb2[1] = '0' + j + 1;
				}
			}
		}
		total += atoi(nb);
		total2 += atoi(nb2);
	}
	printf(MB "Total:  " GREEN "%d\n" C, total);
	printf(MB "Total2: " GREEN "%d\n" C, total2);
	fclose(fp);
	return 0;
}