#include <ced.h>

#define MODS 1

const char* MODFILES[MODS] = {
	"./mods/test.so",
};
struct mod* mods;

int main(int argc, char** argv) {
	curwin = newwin();
	mods = malloc(sizeof(struct mod) * MODS);
	for (int i = 0; i < MODS; i++)
		load(mods+i*sizeof(struct mod), MODFILES[i]);
	while (curwin) {
		wrefresh(curwin);
	}
	return 0;
}
