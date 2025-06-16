#pragma one

#include <stdio.h>
#include <stdint.h>
#include <ced.h>

struct win {
	void (*main)(struct ced *);
	struct win *children;
};

void win_main(struct ced *ced);

extern struct win win;
