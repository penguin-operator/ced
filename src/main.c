#include <ced.h>

int main(int argc, char **argv, char **envp) {
	ced.argc = argc;
	ced.argv = argv;
	ced.envp = envp;
	ced.mods = malloc(sizeof(mod_t));
	ced.preload("/home/operator/projects/ced/mods");
	((void(*)(struct ced*))ced.mods->data)(&ced);
	return 0;
}
