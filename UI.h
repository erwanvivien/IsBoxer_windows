#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include <windows.h>
#include <tchar.h>

HWND createMain (HWND desktop, HINSTANCE instance, LPCSTR name);
HWND createToggle (HINSTANCE instance);
HWND createRegister (HINSTANCE instance);
HWND createRepeatTimer (HINSTANCE instance);
//HWND createWindowNb (HINSTANCE instance);
//HWND createWindowClickNb (HINSTANCE instance);
//HWND createAddClicks (HINSTANCE instance);
HWND createNumberWindow (HINSTANCE instance);
//HWND createText1 (HINSTANCE instance);
//HWND createText2 (HINSTANCE instance);
HWND createTextTime (HINSTANCE instance);
HWND createChangeKey (HINSTANCE instance);
HWND createIsMimic (HINSTANCE instance);
HWND createIsMimicMovement (HINSTANCE instance);
HWND createHandleTextField (HINSTANCE instance);
HWND createIsPlaceWindow (HINSTANCE instance);
HWND createBordersToggle (HINSTANCE instance);


#endif // UI_H_INCLUDED
