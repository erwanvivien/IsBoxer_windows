#ifndef LLIST_H_INCLUDED
#define LLIST_H_INCLUDED

#include <iostream>
#include <windows.h>
#include "windowing.h"

struct Llist{
    size_t number; //, *nbclicks;
    HWND *h;
    RECT *r;
    //POINT **p;
};

unsigned long long get_time_ms(void);

void Lfree (struct Llist l);
void updateList(struct Llist *l, HWND main);

#endif // LLIST_H_INCLUDED
