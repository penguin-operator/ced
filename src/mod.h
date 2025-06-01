#pragma once

#include <ced.h>

struct mod {
	void (*init)(int, char**);
	void (*loop)();
	void (*quit)();
};

struct mod* load(struct mod*, char*);
