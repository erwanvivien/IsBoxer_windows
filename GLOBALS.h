#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include "Llist.h"
#include <windows.h>

extern size_t sWidth, sHeight;

extern HWND hwndALL, hwndToggle, hwndText1, hwndText2,
     hwndRepeatTimer, hwndNumberWindow, hwndRegister,
     hwndTextTime, hwndChangeKey, hwndWindowNb, hwndWindowClickNb,
     hwndAddClicks, hwndMimic, hwndMimicMovement, hwndHandleTextField,
     hwndIsPlaceWindow, hwndBordersToggle;               /* This is the handle for our window */

extern size_t valTimer;
extern size_t valNumberWindows;

extern struct Llist maListe;

extern size_t focusedOne;

extern BOOL isMimic, isChangingKey,
    isStarted, canBeStarted,
    isMimicMovement, isBug,
    isPlaceWindow;

extern WPARAM keyToSend;

extern size_t valNumber;

#endif // GLOBALS_H_INCLUDED
