#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

typedef struct {
	void *dl;
	char *name;
	void *data;
} mod_t;

struct mod {
	void (*load)(mod_t *self, char *name);
	void (*drop)(mod_t *self);
	int (*len)(mod_t *self);
};

void mod_load(mod_t *self, char *name);
void mod_drop(mod_t *self);
int mod_len(mod_t *self);

extern struct mod mod;
