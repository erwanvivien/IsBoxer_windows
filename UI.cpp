#include "UI.h"
#include "resources.h"

#include "GLOBALS.h"

HWND createMain (HWND desktop, HINSTANCE instance, LPCSTR name)
{
    return ::CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           name,         /* Classname */
           name,//_T("Code::Blocks Template Windows App"),       /* Title Text */
           (WS_OVERLAPPED  | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX), /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           desktop,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           instance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
       );
}

HWND createToggle (HINSTANCE instance)
{
    return ::CreateWindow(
        "BUTTON",  // Predefined class; Unicode assumed
        "It's OFF",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        10,         // x position
        10,         // y position
        100,        // Button width
        100,        // Button height
        hwndALL,       // Parent window
        (HMENU)ID_TOGGLE,       // No menu.
        instance,
        NULL);      // Pointer not needed.
}

HWND createRegister (HINSTANCE instance)
{
    return ::CreateWindow(
        "BUTTON",  // Predefined class; Unicode assumed
        "Register",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_MULTILINE,  // Styles
        10,         // x position
        120,         // y position
        100,        // Button width
        100,        // Button height
        hwndALL,       // Parent window
        (HMENU)ID_REGISTER,       // No menu.
        instance,
        NULL);      // Pointer not needed.
}


HWND createRepeatTimer (HINSTANCE instance)
{
    return ::CreateWindow(
        "EDIT",  // Predefined class; Unicode assumed
        "500\0",      // Button text
        ES_NUMBER | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        115,         // x position
        45,         // y position
        60,        // Button width
        18,        // Button height
        hwndALL,       // Parent window
        (HMENU)ID_TIMER,       // No menu.
        instance,
        NULL);      // Pointer not needed.
}

//HWND createWindowNb (HINSTANCE instance)
//{
//    return ::CreateWindow(
//        "EDIT",  // Predefined class; Unicode assumed
//        valSelectedWC,      // Button text
//        ES_NUMBER | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
//        325,         // x position
//        45,         // y position
//        60,        // Button width
//        18,        // Button height
//        hwndALL,       // Parent window
//        (HMENU)ID_SELECTW,       // No menu.
//        instance,
//        NULL);      // Pointer not needed.
//}

//HWND createWindowClickNb (HINSTANCE instance)
//{
//    return ::CreateWindow(
//        "EDIT",  // Predefined class; Unicode assumed
//        valNbAddC,      // Button text
//        ES_NUMBER | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
//        325,         // x position
//        85,         // y position
//        60,        // Button width
//        18,        // Button height
//        hwndALL,       // Parent window
//        (HMENU) ID_ADDCLICK,       // No menu.
//        instance,
//        NULL);      // Pointer not needed.
//}

//HWND createAddClicks (HINSTANCE instance)
//{
//    return ::CreateWindow(
//        "BUTTON",  // Predefined class; Unicode assumed
//        "AddClicks",      // Button text
//        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_MULTILINE,  // Styles
//        325,         // x position
//        120,         // y position
//        100,        // Button width
//        100,        // Button height
//        hwndALL,       // Parent window
//        (HMENU)ID_ADDCLICK,       // No menu.
//        instance,
//        NULL);      // Pointer not needed.
//}

HWND createNumberWindow (HINSTANCE instance)
{
    return ::CreateWindow(
        "EDIT",  // Predefined class; Unicode assumed
        "4",      // Button text
        ES_NUMBER | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        115,         // x position
        155,         // y position
        30,        // Button width
        18,        // Button height
        hwndALL,       // Parent window
        (HMENU)ID_NUMBER,       // No menu.
        instance,
        NULL);      // Pointer not needed.
}

//HWND createText1 (HINSTANCE instance)
//{
//    return ::CreateWindow(
//        "STATIC",  // Predefined class; Unicode assumed
//        "The number of windows you wanna handle :",      // Button text
//        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
//        115,         // x position
//        145,         // y position
//        100,        // Button width
//        50,        // Button height
//        hwndALL,       // Parent window
//        NULL,       // No menu.
//        instance,
//        NULL);      // Pointer not needed.
//}

//HWND createText2 (HINSTANCE instance)
//{
//    return ::CreateWindow(
//        "STATIC",  // Predefined class; Unicode assumed
//        "The timer between each action\n(\'0\' to disable)",      // Button text
//        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
//        115,         // x position
//        25,         // y position
//        100,        // Button width
//        70,        // Button height
//        hwndALL,       // Parent window
//        NULL,       // No menu.
//        instance,
//        NULL);      // Pointer not needed.
//}

HWND createTextTime (HINSTANCE instance)
{
    return ::CreateWindow(
        "STATIC",  // Predefined class; Unicode assumed
        "0",      // Button text
        WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        35,         // x position
        230,         // y position
        50,        // Button width
        18,        // Button height
        hwndALL,       // Parent window
        NULL,       // No menu.
        instance,
        NULL);      // Pointer not needed.
}

HWND createChangeKey (HINSTANCE instance)
{
    return ::CreateWindow(
        "BUTTON",  // Predefined class; Unicode assumed
        "F6",      // Button text
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        200,         // x position
        60,         // y position
        100,        // Button width
        50,        // Button height
        hwndALL,       // Parent window
        (HMENU)ID_CHANGEKEY,       // No menu.
        instance,
        NULL);      // Pointer not needed.
}

HWND createIsMimic (HINSTANCE instance)
{
    return ::CreateWindow(
        "BUTTON",  // Predefined class; Unicode assumed
        "Mimic",      // Button text
        BS_CHECKBOX | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        200,         // x position
        10,         // y position
        100+16,        // Button width
        45,        // Button height
        hwndALL,       // Parent window
        (HMENU)ID_MIMIC,       // No menu.
        instance,
        NULL);      // Pointer not needed.
}

HWND createIsMimicMovement (HINSTANCE instance)
{
    return ::CreateWindow(
        "BUTTON",  // Predefined class; Unicode assumed
        "Mov. Keys",      // Button text
        BS_CHECKBOX | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        200,         // x position
        60,         // y position
        100+16,        // Button width
        45,        // Button height
        hwndALL,       // Parent window
        (HMENU)ID_MIMIC_MOVEMENT,       // No menu.
        instance,
        NULL);      // Pointer not needed.
}

HWND createIsPlaceWindow (HINSTANCE instance)
{
    return ::CreateWindow(
        "BUTTON",  // Predefined class; Unicode assumed
        "Place window",      // Button text
        BS_CHECKBOX | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        200,         // x position
        110,         // y position
        100+16,        // Button width
        45,        // Button height
        hwndALL,       // Parent window
        (HMENU)ID_PLACE_WINDOW,       // No menu.
        instance,
        NULL);      // Pointer not needed.
}

HWND createHandleTextField (HINSTANCE instance)
{
    return ::CreateWindow(
        "EDIT",
        "",
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
        200, 120,
        100+16, 100,
        hwndALL,
        (HMENU) ID_HANDLE_FIELD,
        instance,
        NULL);
}

HWND createBordersToggle (HINSTANCE instance)
{
    return ::CreateWindow(
        "BUTTON",  // Predefined class; Unicode assumed
        "Toggle borders",      // Button text
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        200,         // x position
        160,         // y position
        100+16,        // Button width
        45,        // Button height
        hwndALL,       // Parent window
        (HMENU)ID_TOGGLE_BORDERS,       // No menu.
        instance,
        NULL);      // Pointer not needed.
}
