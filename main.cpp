#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <time.h>
#include <sstream>
#include <stdlib.h>

#include "UI.h"
#include "windowing.h"
#include "resources.h"
#include "Llist.h"

#define MAX_LEN 1000

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

#include "GLOBALS.h"

size_t sWidth = 0, sHeight = 0;

HWND hwndALL, hwndToggle, hwndText1, hwndText2,
     hwndRepeatTimer, hwndNumberWindow, hwndRegister,
     hwndTextTime, hwndChangeKey, hwndWindowNb, hwndWindowClickNb,
     hwndAddClicks, hwndMimic, hwndMimicMovement, hwndHandleTextField,
     hwndIsPlaceWindow, hwndBordersToggle;               /* This is the handle for our window */

size_t valTimer = 500;

struct Llist maListe;

size_t focusedOne = 0;

BOOL isMimic = true, isChangingKey = false,
    isStarted = false, canBeStarted = false,
    isMimicMovement = false, isBug = false,
    isPlaceWindow = false;

WPARAM keyToSend = VK_F6;

size_t valNumber = 4;

char valTimerC[20] = "500";
char valNumberC[20] = "5";
char valHandleC[1000] = "";


int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = ::LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = ::LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = ::LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    if (!::RegisterClassEx (&wincl))
        return 0;

    /// MAIN WINDOW
    hwndALL = createMain (HWND_DESKTOP, hThisInstance, szClassName);
        /// Shows the application
    ::ShowWindow (hwndALL, nCmdShow);

    /// Toggle
    hwndToggle = createToggle (hThisInstance);

    /// Registers
    hwndRegister = createRegister (hThisInstance);
    hwndNumberWindow = createNumberWindow (hThisInstance);
    hwndTextTime = createTextTime (hThisInstance);

    /// Repeater
    hwndChangeKey = createChangeKey (hThisInstance);
    hwndRepeatTimer = createRepeatTimer (hThisInstance);

    /// Mimics
    hwndMimic = createIsMimic (hThisInstance);
    hwndMimicMovement = createIsMimicMovement (hThisInstance);
    hwndIsPlaceWindow = createIsPlaceWindow (hThisInstance);
    hwndBordersToggle = createBordersToggle (hThisInstance);

        /// This sets the checkbox to be checked by default
    ::SendMessage(hwndMimic, BM_SETCHECK, BST_CHECKED, 0);

    /// Handle text
////////    hwndHandleTextField = createHandleTextField (hThisInstance);


    std::thread t(mimicFastMessageForAllK);
    t.detach();


//    ::ShowWindow (hwndALL, nCmdShow);
//
//    ::Sleep(2000);
//    HWND ttt [4] = { NULL };
//    for(size_t i = 0; i < 4; i ++)
//    {
//        ::Sleep(1000);
//        std::cout << "GO" << std::endl;
//        ttt[i] = ::GetForegroundWindow();
//    }
//    for(size_t i = 0; i < 4; i ++)
//    {
//        changeBorders(ttt[i], false);
//    }
//    return 0;
//
    {    /// Gets the screen size (main monitor AND without taskbar)
//        const HWND hDesktop = ::GetDesktopWindow();
        RECT desktopRect;
        ::SystemParametersInfo(SPI_GETWORKAREA, 0, &desktopRect, 0);

        sWidth = desktopRect.right;
        sHeight = desktopRect.bottom;
    };

    while (::GetMessage (&messages, NULL, 0, 0))
    {
        ::TranslateMessage(&messages);
        ::DispatchMessage(&messages);

        ::ShowWindow (hwndChangeKey, !isMimic);
        ::ShowWindow (hwndMimicMovement, isMimic);
        ::ShowWindow (hwndIsPlaceWindow, isMimic);
        ::EnableWindow (hwndRepeatTimer, !isMimic && !isStarted);
        ::EnableWindow (hwndChangeKey, !isMimic && !isStarted);
        ::EnableWindow (hwndMimic, true);
        ::EnableWindow (hwndRegister, !isStarted);
        ::EnableWindow (hwndNumberWindow, !isStarted);
        ::EnableWindow (hwndToggle, canBeStarted && !isBug);
        ::EnableWindow (hwndIsPlaceWindow, canBeStarted && !isBug);


        char tmp[MAX_LEN] = { 0 };
        GetWindowText(hwndRepeatTimer, tmp, MAX_LEN);
        if(strcmp(tmp, valTimerC) != 0)
        {
            strcpy(valTimerC, tmp);
            valTimer = atoi(valTimerC);
            isBug = strcmp(tmp, "") == 0 || valTimer == 0;
        }


////////        memset(tmp, 0, MAX_LEN * sizeof(char));
////////        GetWindowText(hwndHandleTextField, tmp, MAX_LEN);
////////        if(strcmp(tmp, valHandleC) != 0)
////////        {
////////            strcpy(valHandleC, tmp);
////////
////////            int nbHandle = 0;
////////            size_t newHandle = 0;
////////            size_t i;
////////
////////            if (valHandleC[0] != '0' || valHandleC[1] != 'x') continue;
////////            for(i = 2; valHandleC[i] != '\0' && i < 1000; i++)
////////            {
////////                char c = valHandleC[i];
////////                switch (c)
////////                {
////////                case 'a' ... 'f':
////////                    newHandle *= 16;
////////                    newHandle += 10 + (c - 'a');
////////                    break;
////////                case '0' ... '9':
////////                    newHandle *= 16;
////////                    newHandle += (c - '0');
////////                    break;
////////                case '\n':
////////                {
////////                    ++nbHandle;
////////                    if (nbHandle > maListe.number)
////////                    {
////////                        HWND *tmp1 = (HWND *) realloc(maListe.h, nbHandle);
////////                        RECT *tmp2 = (RECT *) realloc(maListe.r, nbHandle);
////////
////////                        if (tmp1 == NULL) return 1;
////////                        if (tmp2 == NULL) return 1;
////////
////////                        maListe.h = tmp1;
////////                        maListe.r = tmp2;
////////                    }
////////
////////                    maListe.h[nbHandle - 1] = (HWND) newHandle;
////////                    maListe.r[nbHandle - 1] = getRect(maListe.h[nbHandle - 1]);
////////
////////                    newHandle = 0;
////////
////////                    if (valHandleC[++i] != '0' || valHandleC[++i] != 'x') i = 1000;
////////                }
////////                    break;
////////                default:
////////                    i = 1000;
////////                    break;
////////                }
////////            }
////////
////////            if (i < 1000 && valHandleC[i] == '\0')
////////                ::MessageBeep(MB_ICONERROR);
////////
//////////            valTimer = atoi(valTimerC);
//////////            isBug = strcmp(tmp, "") == 0 || valTimer == 0;
////////        }

//        GetWindowText(hwndWindowClickNb, tmp, MAX_LEN);
//        if(strcmp(tmp, valNbAddC) != 0)
//        {
//            strcpy(valNbAddC, tmp);
//            valNbAdd = atoi(valNbAddC);
//            isBug = strcmp(tmp, "") == 0 || valTimer == 0;
//
//            maListe.p[valSelectedW] = (POINT*) realloc(maListe.p[valSelectedW], valNbAdd * sizeof(POINT));
//        }

//        GetWindowText(hwndWindowNb, tmp, MAX_LEN);
//        if(strcmp(tmp, valSelectedWC) != 0)
//        {
//            strcpy(valSelectedWC, tmp);
//            valSelectedW = atoi(valSelectedWC);
//            isBug = strcmp(tmp, "") == 0 || valTimer == 0;
//        }

        memset(tmp, 0, MAX_LEN * sizeof(char));
        GetWindowText(hwndNumberWindow, tmp, MAX_LEN);
        if(strcmp(tmp, valNumberC) != 0)
        {
            printf("%d\n", valNumber);
            canBeStarted = FALSE;
            isStarted = FALSE;
            SetWindowText(hwndRegister, "Register");
            strcpy(valNumberC, tmp);
            //Lfree(maListe);
//            maListe.p = (POINT**) malloc(valNumbr * sizeof(POINT*));
//            maListe.nbclicks = (size_t*) malloc(valNumbr * sizeof(size_t));
//            for(size_t i = 0; i < valNumber; i ++)
//            {
//                maListe.p[i] = NULL;
//                maListe.nbclicks[i] = 0;
//            }

            valNumber = atoi(valNumberC);
            if(strcmp(tmp, "") == 0 || valNumber == 0)
                canBeStarted = FALSE;
        }
    }

    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
            isChangingKey = FALSE;
            ::SetFocus(hwndALL);
        break;

        case WM_COMMAND:
            isChangingKey = false;
            switch (wParam)
            {
                case ID_TIMER:
                case ID_NUMBER:
                    break;
                case ID_TOGGLE:
                    SetWindowText(hwndToggle, !isStarted && canBeStarted ?
                                  "It's ON" : "It's OFF");
                    isStarted = !isStarted && canBeStarted;

                    if (isStarted && isMimic && isPlaceWindow)
                    {
                        for(size_t i = 0; i < maListe.number; i ++)
                            setBorders(maListe.h[i], !isStarted && isPlaceWindow);
                        changeWindowPositions();
                    }

                    SetFocus(hwndALL);

                    break;
                case ID_REGISTER:
                {
                    Lfree(maListe);

                    maListe.number = valNumber;
                    updateList(&maListe, hwnd);

                    canBeStarted = TRUE;
                    ::SetWindowText(hwndRegister, "Register\n(done)");

                    ::SetFocus(hwndALL);
                    ::SetForegroundWindow(hwndALL);

//                    std::string s = "";
//                    for (size_t i = 0; i < maListe.number; i++)
//                    {
//                        std::stringstream stringstreamBuffer;
//                        stringstreamBuffer << maListe.h[i] << std::endl;
//                        s += stringstreamBuffer.str();
//                    }
//
//                    ::SetWindowText(hwndHandleTextField, s.c_str());
                }
                    break;
                case ID_TOGGLE_BORDERS:
                {
                    BOOL borders = (WS_THICKFRAME & GetWindowLong(maListe.h[0], GWL_STYLE)) == 0;
                    for(size_t i = 0; i < maListe.number; i ++)
                        setBorders(maListe.h[i], borders);
                    ::SetFocus(hwndALL);
                }
                    break;

                case ID_CHANGEKEY:
                    isChangingKey = TRUE;
                    ::SetFocus(hwndALL);
                    break;

                case ID_MIMIC:
                    isMimic = !isMimic;
                    if (isMimic)
                    {
                        std::thread t(mimicFastMessageForAllK);
                        t.detach();
                    }
                    else
                    {
                        std::thread t(postFastMessageForAllK);
                        t.detach();
                    }
                    ::SetFocus(hwndALL);
                    break;
                case ID_MIMIC_MOVEMENT:
                    isMimicMovement = !isMimicMovement;
                    SetFocus(hwndALL);
                    break;
                case ID_PLACE_WINDOW:
                    isPlaceWindow = !isPlaceWindow;

                    SetFocus(hwndALL);
                    break;
                case ID_FILE_EXIT:
                    PostMessage(hwnd, WM_CLOSE, 0, 0);
                    break;
            }
            break;
        case WM_KEYDOWN:
            switch(wParam)
            {
                case VK_ESCAPE:
                    if(isChangingKey == false && lParam == 1073807361) PostQuitMessage(0);
                    if(isChangingKey == true) isChangingKey = false;
                    SetFocus(hwndALL);
                    break;
                default:
                    if(isChangingKey)
                    {
                        keyToSend = wParam;
                        LPSTR s = (LPSTR) malloc(10 * sizeof(char));
                        GetKeyNameText(lParam, s, 10);

                        SetWindowText(hwndChangeKey, s);
                        free(s);
                        isChangingKey = false;
                    }
                    break;
            }
            break;
        case WM_KEYUP:
            break;
        case WM_DESTROY:
        case WM_CLOSE:

            ::PostQuitMessage (0);
            break;
        default:
            return ::DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

