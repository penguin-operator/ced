#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct win {
	uint16_t h, w, y, x, r, c;
	struct win *parent, *next, *prev, *left, *right, *bottom, *top;
	struct { struct win** mem; size_t cap, len; } children;
	void* shared;
	void (*func)(struct win*);
};

struct win* newwin();
void wchild(struct win*, struct win*);
void wrefresh(struct win*);
void delwin(struct win*);
