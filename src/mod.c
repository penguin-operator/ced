#include <mod.h>

struct mod mod = {
	.load = mod_load,
	.drop = mod_drop,
	.len = mod_len,
};

void mod_load(mod_t *self, char *path, char *name) {
	char mod[64], *err;
	memset(mod, 0, 64);
	sprintf(mod, "%s/lib%s.so", path, name);
	self->dl = dlopen(mod, RTLD_NOW | RTLD_GLOBAL);
	if ((err = dlerror())) {
		fprintf(stderr, "%s\n", err);
		exit(1);
	}
	self->name = name;
	self->data = *(void**)dlsym(self->dl, name);
}

void mod_drop(mod_t *self) {
	dlclose(self->dl);
	self->dl = self->name = self->data = NULL;
}

int mod_len(mod_t *self) {
	int c = 0;
	while (self[c].dl) c++;
	return c;
}
