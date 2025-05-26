#include <ced.h>

struct win* curwin;

int main(int argc, char **argv) {
	curwin = newwin();
	while (curwin) {
		wrefresh(curwin);
	}
	return 0;
}
