#include <mods/win.h>

struct win win = {
	.main = win_main,
};

void win_main(struct ced *ced) {
	printf("{ ");
	for (int i = 0; i < ced->argc; ++i) {
		printf("\"%s\", ", ced->argv[i]);
	}
	printf("}\n");
}
