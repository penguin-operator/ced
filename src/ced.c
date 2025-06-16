#include <ced.h>

struct ced ced = {
	.preload = ced_preload,
};

void ced_preload(char *modspath) {
	DIR* mods = opendir(modspath);
	struct dirent *entry;
	char* period;
	for (; (entry = readdir(mods)) ;) {
		period = strchr(entry->d_name, '.');
		if (!period) continue;
		if (!strncmp(entry->d_name, "lib", 3)
			&& !strcmp(period, ".so")) {
			*period = 0;
			int i = mod.len(ced.mods);
			ced.mods = realloc(ced.mods, sizeof(mod_t)*(i+2));
			mod.load(ced.mods+i, entry->d_name+3);
		}
	}
	closedir(mods);
}
