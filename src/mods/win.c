#include <mods/win.h>

struct win win = {
	.main = win_main,
	.reset = win_reset,
	.resize = win_resize,
	.cursor = {
		.y = 0, .x = 0,
		.update = win_cursor_update,
		.setpos = win_cursor_setpos,
		.newpos = win_cursor_newpos,
	},
};

void win_main() {
	atexit(win.reset);
	tcgetattr(0, &win.old);
	signal(SIGWINCH, win.resize);
	win.current = malloc(sizeof(win_t));
	win.current->tc = win.old;
	win.current->tc.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	win.current->tc.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	win.current->tc.c_oflag &= ~(OPOST);
	win.current->tc.c_cflag |= (CS8);
	win.current->tc.c_cc[VMIN] = 0;
	win.current->tc.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &win.current->tc);
	write(1, "\e[?1049h\e[H", 11);
	win.resize(SIGWINCH);
	char c = 0;
	while (1) {
		while (!read(0, &c, 1));
		if (c == 'q') break;
	}
}

void win_reset() {
	write(1, "\e[?1049l", 8);
	tcsetattr(0, TCSAFLUSH, &win.old);
}

void win_resize(int signum) {
	win_t *root = win.current;
	uint16_t y = root->y;
	uint16_t x = root->x;
	uint16_t i = 0;
	ioctl(1, TIOCGWINSZ, (struct winsize*)root);
	root->y = y;
	root->x = x;
	write(1, "\e[2J", 4);
	win.cursor.setpos(0, 0);
	write(1, "\u250c", 3);
	win.cursor.setpos(root->h, 0);
	write(1, "\u2514", 3);
	win.cursor.setpos(0, root->w);
	write(1, "\u2510", 3);
	win.cursor.setpos(root->h, root->w);
	write(1, "\u2518", 3);
	for (i = 0; i < root->w-2; i++) {
		win.cursor.setpos(0, 2+i);
		write(1, "\u2500", 3);
		win.cursor.setpos(root->h, 2+i);
		write(1, "\u2500", 3);
	}
	for (i = 0; i < root->h-2; i++) {
		win.cursor.setpos(2+i, 0);
		write(1, "\u2502", 3);
		win.cursor.setpos(2+i, root->w);
		write(1, "\u2502", 3);
	}
	win.cursor.setpos(2, 2);
}

void win_cursor_update() {
	char cursor[16];
	sprintf(cursor, "\e[%u;%uH", win.cursor.y, win.cursor.x);
	write(1, cursor, strlen(cursor));
}

void win_cursor_setpos(uint16_t y, uint16_t x) {
	win.cursor.y = y;
	win.cursor.x = x;
	win.cursor.update();
}

void win_cursor_newpos() {
	write(1, "\e[6n", 4);
}
