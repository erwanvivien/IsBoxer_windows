#ifndef WINDOWING_H_INCLUDED
#define WINDOWING_H_INCLUDED

#include <windows.h>
#include "Llist.h"

void setBorders(HWND hwnd, bool b);
RECT getRect(HWND h);

void postFastMessageForAllK(void);
void mimicFastMessageForAllK(void);
void checkKey(unsigned long long keys[191], size_t KEY, size_t real_key = 0);
void changeWindowPositions(void);


#endif // WINDOWING_H_INCLUDED
