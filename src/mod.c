#include <mod.h>

struct mod mod = {
	.load = mod_load,
	.drop = mod_drop,
	.len = mod_len,
};

void mod_load(mod_t *self, char *name) {
	char mod[256];
	sprintf(mod, "%s/projects/ced/mods/lib%s.so", getenv("HOME"), name);
	self->dl = dlopen(mod, RTLD_LAZY);
	self->name = name;
	self->data = *(void**)dlsym(self->dl, name);
}

void mod_drop(mod_t *self) {
	dlclose(self->dl);
}

int mod_len(mod_t *self) {
	int c = 0;
	while (self[c].dl) c++;
	return c;
}
