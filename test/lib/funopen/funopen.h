#ifndef FUNOPEN_H
#define FUNOPEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

struct fmem {
  size_t pos;
  size_t size;
  char *buffer;
};

typedef struct fmem fmem_t;

FILE *
funopen(cookie, readfn, writefn, seekfn, closefn)
	const void *cookie;
	int (*readfn)(), (*writefn)();
#if __STDC__
	fpos_t (*seekfn)(void *cookie, fpos_t off, int whence);
#else
	fpos_t (*seekfn)();
#endif
	int (*closefn)();

#endif
