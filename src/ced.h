#pragma once

#include <dirent.h>
#include <string.h>
#include <mod.h>

struct ced {
	int argc;
	char **argv;
	char **envp;
	mod_t *mods;
	void (*preload)(char *modspath);
};

void ced_preload(char *modspath);

extern struct ced ced;
