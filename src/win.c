#include <win.h>

struct win* newwin() {
	struct win* self = malloc(sizeof(struct win));
	return self;
}

void wchild(struct win* self, struct win* child) {
	if (self->children.len == self->children.cap) {
		self->children.mem = realloc(self->children.mem, ++self->children.cap*sizeof(void*));
	}
	self->children.mem[self->children.len++] = child;
	child->parent = self;
}

void wrefresh(struct win* self) {
	static uint64_t c;
	c = 0x0000000000000000;
	while (!read(0, &c, sizeof(c)));
	if ((c & 0xff) == 'q') exit(0);
	printf("hello \"%s\"\n", &c);
}

void delwin(struct win* self) {
	if (self->parent) {
		long i = 0;
		for (i = 0; i < self->parent->children.len--; i++)
			if (self->parent->children.mem[i] == self) break;
		memcpy(
			self->parent->children.mem+i, self->parent->children.mem+i+sizeof(void*),
			(self->parent->children.len-i)*sizeof(void*)
		);
	}
	#define dechain(a, b) if (self->a || self->b) {\
		self->a->b = self->b;\
		self->b->a = self->a;\
	}
	dechain(next, prev);
	dechain(right, left);
	dechain(top, bottom);
	#undef dechain
	while (self->children.len) delwin(*self->children.mem);
	free(self);
}
