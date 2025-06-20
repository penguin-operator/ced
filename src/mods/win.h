#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <setjmp.h>
#include <signal.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <ced.h>

typedef struct win_t {
	uint16_t h, w, x, y;
	// jmp_buf ctx; // pro futuro
	struct termios tc;
	struct win_t *parent;
	struct win_t *children;
	struct win_t *top;
	struct win_t *bottom;
	struct win_t *right;
	struct win_t *left;
} win_t;

struct win {
	void (*main)();
	void (*reset)();
	void (*resize)(int signum);
	win_t *current;
	struct termios old;
	struct cursor {
		uint16_t x, y;
		void (*update)();
		void (*setpos)(uint16_t y, uint16_t x);
		void (*newpos)();
	} cursor;
};

void win_main();
void win_reset();
void win_resize(int signum);
void win_cursor_update();
void win_cursor_setpos(uint16_t y, uint16_t x);
void win_cursor_newpos();

extern struct win win;
