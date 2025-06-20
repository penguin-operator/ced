#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

#define MOD_PRELOAD(mod) (mod_t){ .dl = NULL, .name = #mod, .data = (void*)mod.main }

typedef struct mod_t {
	void *dl;
	char *name;
	void *data;
} mod_t;

struct mod {
	void (*load)(mod_t *self, char *path, char *name);
	void (*drop)(mod_t *self);
	int (*len)(mod_t *self);
};

void mod_load(mod_t *self, char *path, char *name);
void mod_drop(mod_t *self);
int mod_len(mod_t *self);

extern struct mod mod;
