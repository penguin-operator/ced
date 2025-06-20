#include <ced.h>
#include <mods/win.h>

int main(int argc, char **argv, char **envp) {
	ced.argc = argc;
	ced.argv = argv;
	ced.envp = envp;
	ced.mods = (mod_t[]){
		MOD_PRELOAD(win),
		(mod_t){0}
	};
	for (int i = 0; ced.mods[i].data; i++) {
		((void(*)())ced.mods[i].data)();
	}
	return 0;
}
