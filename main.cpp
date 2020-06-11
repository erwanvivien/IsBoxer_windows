#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#define MAX_LEN 256
#include <tchar.h>
#include "res.h"

#include <windows.h>
#include <iostream>
#include <thread>
#include <mutex>

#define ull unsigned long long
#define ll long long

struct listChain{
    size_t number, *nbclicks;
    HWND *h;
    RECT *r;
    POINT **p;
};

std::mutex mut;

unsigned long long get_time_ms(void)
{
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}


/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("Is Boxer");
HWND hwndALL, hwndToggle, hwndText1, hwndText2,
     hwndTimer, hwndNumber, hwndRegister,
     hwndTextTime, hwndChangeKey, hwndWindowNb, hwndWindowClickNb,
     hwndAddClicks, hwndMimic, hwndMimicMovement;               /* This is the handle for our window */


BOOL canBeStarted = FALSE, isStarted = FALSE, changeKey = FALSE, isBug = FALSE,
    mimic = FALSE, avoidMovementKey = TRUE;

unsigned int nbKeyToPress = 1;
unsigned int valNumbr = 1;
unsigned int valTimer = 500;
unsigned int valSelectedW = 0;
unsigned int valNbAdd = 2;
WPARAM keyToSend = VK_F6;

struct listChain maListe; /// List of all handles

LRESULT CALLBACK WindowProcedure
            (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void postFastMessageForAllK(void);
void mimicFastMessageForAllK(void);
void checkKey(ull keys[191], size_t KEY, size_t real_key = 0);

ull start = 0;

RECT getRect(HWND h)
{
    RECT r, r1;
    GetWindowRect(h, &r);
    GetClientRect(h, &r1);
    r.bottom = r1.bottom;
    r.right = r1.right;
//    maListe.r[i] = r;
    return r;
}


int WINAPI WinMain (HINSTANCE hThisInstance,
                     __attribute__((unused)) HINSTANCE hPrevInstance,
                     __attribute__((unused)) LPSTR lpszArgument,
                     int nCmdShow)
{
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    char valTimerC[10] = "500\0";
    char valSelectedWC[10] = "0\0";
    char valNbAddC[10] = "2\0";
    char valNumbrC[10] = "1\0";


    {
    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwndALL = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           szClassName,//_T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
       );
    ShowWindow (hwndALL, nCmdShow);

    hwndToggle = CreateWindow(
        "BUTTON",  // Predefined class; Unicode assumed
        "It's OFF",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        10,         // x position
        10,         // y position
        100,        // Button width
        100,        // Button height
        hwndALL,       // Parent window
        (HMENU)ID_TOGGLE,       // No menu.
        hThisInstance,
        NULL);      // Pointer not needed.

    hwndRegister = CreateWindow(
        "BUTTON",  // Predefined class; Unicode assumed
        "Register",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_MULTILINE,  // Styles
        10,         // x position
        120,         // y position
        100,        // Button width
        100,        // Button height
        hwndALL,       // Parent window
        (HMENU)ID_REGISTER,       // No menu.
        hThisInstance,
        NULL);      // Pointer not needed.

    hwndTimer = CreateWindow(
        "EDIT",  // Predefined class; Unicode assumed
        valTimerC,      // Button text
        ES_NUMBER | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        225,         // x position
        45,         // y position
        60,        // Button width
        18,        // Button height
        hwndALL,       // Parent window
        (HMENU)ID_TIMER,       // No menu.
        hThisInstance,
        NULL);      // Pointer not needed.

    hwndWindowNb = CreateWindow(
        "EDIT",  // Predefined class; Unicode assumed
        valSelectedWC,      // Button text
        ES_NUMBER | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        325,         // x position
        45,         // y position
        60,        // Button width
        18,        // Button height
        hwndALL,       // Parent window
        (HMENU)ID_SELECTW,       // No menu.
        hThisInstance,
        NULL);      // Pointer not needed.
    hwndWindowClickNb = CreateWindow(
        "EDIT",  // Predefined class; Unicode assumed
        valNbAddC,      // Button text
        ES_NUMBER | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        325,         // x position
        85,         // y position
        60,        // Button width
        18,        // Button height
        hwndALL,       // Parent window
        (HMENU) ID_ADDCLICK,       // No menu.
        hThisInstance,
        NULL);      // Pointer not needed.

    hwndAddClicks = CreateWindow(
        "BUTTON",  // Predefined class; Unicode assumed
        "AddClicks",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_MULTILINE,  // Styles
        325,         // x position
        120,         // y position
        100,        // Button width
        100,        // Button height
        hwndALL,       // Parent window
        (HMENU)ID_ADDCLICK,       // No menu.
        hThisInstance,
        NULL);      // Pointer not needed.


    hwndNumber = CreateWindow(
        "EDIT",  // Predefined class; Unicode assumed
        valNumbrC,      // Button text
        ES_NUMBER | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        225,         // x position
        155,         // y position
        30,        // Button width
        18,        // Button height
        hwndALL,       // Parent window
        (HMENU)ID_NUMBER,       // No menu.
        hThisInstance,
        NULL);      // Pointer not needed.

    hwndText1 = CreateWindow(
        "STATIC",  // Predefined class; Unicode assumed
        "The number of windows you wanna handle :",      // Button text
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        115,         // x position
        145,         // y position
        100,        // Button width
        50,        // Button height
        hwndALL,       // Parent window
        NULL,       // No menu.
        hThisInstance,
        NULL);      // Pointer not needed.
    hwndText2 = CreateWindow(
        "STATIC",  // Predefined class; Unicode assumed
        "The timer between each action\n(\'0\' to disable)",      // Button text
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        115,         // x position
        25,         // y position
        100,        // Button width
        70,        // Button height
        hwndALL,       // Parent window
        NULL,       // No menu.
        hThisInstance,
        NULL);      // Pointer not needed.
    hwndTextTime = CreateWindow(
        "STATIC",  // Predefined class; Unicode assumed
        "0",      // Button text
        WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        35,         // x position
        230,         // y position
        50,        // Button width
        18,        // Button height
        hwndALL,       // Parent window
        NULL,       // No menu.
        hThisInstance,
        NULL);      // Pointer not needed.
    hwndChangeKey = CreateWindow(
        "BUTTON",  // Predefined class; Unicode assumed
        "F6",      // Button text
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        135,         // x position
        230,         // y position
        50,        // Button width
        50,        // Button height
        hwndALL,       // Parent window
        (HMENU)ID_CHANGEKEY,       // No menu.
        hThisInstance,
        NULL);      // Pointer not needed.
    hwndMimic = CreateWindow(
        "BUTTON",  // Predefined class; Unicode assumed
        "Mimic",      // Button text
        BS_CHECKBOX | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        50,         // x position
        230,         // y position
        70,        // Button width
        50,        // Button height
        hwndALL,       // Parent window
        (HMENU)ID_MIMIC,       // No menu.
        hThisInstance,
        NULL);      // Pointer not needed.
    hwndMimicMovement = CreateWindow(
        "BUTTON",  // Predefined class; Unicode assumed
        "Mov. Keys",      // Button text
        BS_CHECKBOX | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        135,         // x position
        230,         // y position
        100,        // Button width
        50,        // Button height
        hwndALL,       // Parent window
        (HMENU)ID_MIMIC_MOVEMENT,       // No menu.
        hThisInstance,
        NULL);      // Pointer not needed.
    }

    std::thread t(postFastMessageForAllK);
    t.detach();
    ShowWindow (hwndALL, nCmdShow);

    start = get_time_ms();
    maListe.p = (POINT**) malloc(sizeof(POINT*));
    maListe.nbclicks = (size_t*) malloc(sizeof(size_t));
    while (GetMessage (&messages, NULL, 0, 0) > 0)
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);

        char tmp[MAX_LEN];
        GetWindowText(hwndTimer, tmp, MAX_LEN);
        if(strcmp(tmp, valTimerC) != 0)
        {
            strcpy(valTimerC, tmp);
            valTimer = atoi(valTimerC);
            isBug = strcmp(tmp, "") == 0 || valTimer == 0;
        }

        GetWindowText(hwndWindowClickNb, tmp, MAX_LEN);
        if(strcmp(tmp, valNbAddC) != 0)
        {
            strcpy(valNbAddC, tmp);
            valNbAdd = atoi(valNbAddC);
            isBug = strcmp(tmp, "") == 0 || valTimer == 0;

            maListe.p[valSelectedW] = (POINT*) realloc(maListe.p[valSelectedW], valNbAdd * sizeof(POINT));
        }

        GetWindowText(hwndWindowNb, tmp, MAX_LEN);
        if(strcmp(tmp, valSelectedWC) != 0)
        {
            strcpy(valSelectedWC, tmp);
            valSelectedW = atoi(valSelectedWC);
            isBug = strcmp(tmp, "") == 0 || valTimer == 0;
        }

        GetWindowText(hwndNumber, tmp, MAX_LEN);
        if(strcmp(tmp, valNumbrC) != 0)
        {
            canBeStarted = FALSE;
            isStarted = FALSE;
            SetWindowText(hwndRegister, "Register");
            strcpy(valNumbrC, tmp);
            maListe.p = (POINT**) malloc(valNumbr * sizeof(POINT*));
            maListe.nbclicks = (size_t*) malloc(valNumbr * sizeof(size_t));
            for(size_t i = 0; i < valNumbr; i ++)
            {
                maListe.p[i] = NULL;
                maListe.nbclicks[i] = 0;
            }

            valNumbr = atoi(valNumbrC);
            if(strcmp(tmp, "") == 0 || valNumbr == 0)
                canBeStarted = FALSE;
        }

        EnableWindow( hwndTimer, !mimic && !isStarted);
        EnableWindow( hwndChangeKey, !mimic && !isStarted);
        EnableWindow( hwndMimic, true);
        ShowWindow( hwndMimicMovement, mimic);
        ShowWindow( hwndChangeKey, !mimic);
        EnableWindow( hwndWindowClickNb, false /**canBeStarted && !isStarted*/ );
        EnableWindow( hwndWindowNb, false /**canBeStarted && !isStarted*/ );
        EnableWindow( hwndAddClicks, false /**canBeStarted && !isStarted*/ );
        EnableWindow( hwndRegister, !isStarted);
        EnableWindow( hwndNumber, !isStarted);
        EnableWindow( hwndToggle, canBeStarted && !isBug);
    }
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
//    std::cout << message << " " << wParam << ' ' << lParam << std::endl;
    switch (message)                  /* handle the messages */
    {
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
            changeKey = FALSE;
            SetFocus(hwndALL);
        break;
        case WM_COMMAND:
            changeKey = FALSE;

            switch(/*LOWORD*/(wParam))
            {
                case ID_TOGGLE:
                    if(!isStarted && canBeStarted)
                    {
                        SetWindowText(hwndToggle, "It's ON");
                    }
                    else
                    {
                        SetWindowText(hwndToggle, "It's OFF");
                    }
                    isStarted = !isStarted && canBeStarted;

                    SetFocus(hwndALL);
                break;
                case ID_REGISTER:
                {
                    ShowWindow (hwndChangeKey, SW_SHOWNORMAL);
                    UpdateWindow(hwnd);

                    maListe.number = valNumbr;
                    maListe.h = (HWND*) malloc(maListe.number * sizeof(HWND)); /// allocating it
                    maListe.r = (RECT*) malloc(maListe.number * sizeof(RECT)); /// allocating it

                    ShowWindow (hwndTextTime, SW_SHOWNORMAL);
                    UpdateWindow(hwnd);

                    ull ms1 = get_time_ms();
                    for(size_t i = 0; i < maListe.number;)
                    {
                        ull ms2 = get_time_ms();

                        size_t dif = 1500-(ms2 - ms1);
                        if(dif % 50 == 0)
                        {
                            char tmp[12];
                            sprintf(tmp, "%llu", dif);
                            SetWindowText(hwndTextTime, tmp);
                        }
                        if( ms2 - ms1 >= 1500 )
                        {
                            maListe.r[i] = getRect(maListe.h[i]);
                            maListe.h[i] = GetForegroundWindow();

                            std::cout << "Got Handle - " << maListe.h[i] << std::endl;
                            i++;
                            ms1 = ms2;
                            MessageBeep(MB_ICONERROR);
                        }
                        //Sleep(5);
                    } /// Get all the handles (one by one)
                      /// Doing it by getting the focused window
                      /// and sets the midpoint of the window
                    canBeStarted = TRUE;
                    SetWindowText(hwndRegister, "Register\n(done)");
//
//                    for(size_t i = 0; i < maListe.number; i++)
//                    {
//
//
//                    }
//
                    ShowWindow (hwndTextTime, FALSE);
                    UpdateWindow(hwnd);
                    SetFocus(hwndALL);
                    SetForegroundWindow(hwndALL);
                }
                break;
                case ID_ADDCLICK:
                    if(valSelectedW >= valNumbr) break;
                    maListe.r[valSelectedW] = getRect(maListe.h[valSelectedW]);
                    maListe.nbclicks[valSelectedW] = valNbAdd;
                    maListe.p[valSelectedW] = (POINT*) malloc(sizeof(POINT) * valNbAdd);

                    SetForegroundWindow(maListe.h[valSelectedW]);
                    for(size_t i = 0; i < valNbAdd; i ++)
                    {
                        Sleep(2000);
                        POINT p;

                        GetCursorPos(&p);
                        ScreenToClient(maListe.h[valSelectedW], &p);
                        if(p.x < 0 || p.y < 0) break;
                        p.y += 30;
                        maListe.p[valSelectedW][i] = p;
                        MessageBeep(MB_ICONASTERISK);
                    }

                    break;
                case ID_TIMER:
                case ID_NUMBER:
                    //SetFocus(hwndALL);
                case ID_CHANGEKEY:
                    changeKey = TRUE;
                    SetFocus(hwndALL);
                break;
                case ID_MIMIC:
                    if (!mimic)
                    {
                        std::thread t(mimicFastMessageForAllK);
                        t.detach();
                    }
                    else
                    {
                        std::thread t(postFastMessageForAllK);
                        t.detach();
                    }

                    mimic = !mimic;

                    SetFocus(hwndALL);
                    break;
                case ID_MIMIC_MOVEMENT:
                    avoidMovementKey = !avoidMovementKey;
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
                    if(changeKey == FALSE && lParam == 1073807361) PostQuitMessage(0);
                    if(changeKey == TRUE) changeKey = FALSE;
                    SetFocus(hwndALL);
                break;
                default:
                    if(changeKey)
                    {
                        keyToSend = wParam;
                        LPSTR s = (LPSTR) malloc(10 * sizeof(char));
                        GetKeyNameText(lParam, s, 10);

                        SetWindowText(hwndChangeKey, s);
                        free(s);
                        changeKey = FALSE;
                    }
                break;
            }
        break;
        case WM_KEYUP:

        break;

        case WM_DESTROY:
        case WM_CLOSE:
            PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}



void postFastMessageForAllK(void)
{
    while(1)
    {
        if (mimic)
            return;

        //if(!canBeStarted) continue;
//        MessageBox(NULL, (isStarted ? "true" : "false"), "title", 0);
        Sleep(1);
        if(!isStarted) continue;
        //MessageBeep(MB_ICONERROR);

        for(size_t i = 0; i < maListe.number && maListe.h[i] != NULL; i++)
        {
//                maListe.r[i] = getRect(maListe.h[i]);

//                std::cout << maListe.h[i] << std::endl;
//            std::cout << maListe.h[i] << ": " << keyToSend << ": " << valTimer << std::endl;
            PostMessage(maListe.h[i], WM_KEYDOWN, keyToSend, 0x001C0001);
            PostMessage(maListe.h[i], WM_KEYUP, keyToSend, keyToSend);
//                for(size_t j = 0; maListe.nbclicks != NULL &&
//                                j < maListe.nbclicks[i]; j++)
//                {
//                    int x = maListe.p[i][j].x*2,
//                        y = maListe.p[i][j].y;
//                    int x = 100, y = 100;
//                    std::cout << x << " - " << y << std::endl;
//                    LPARAM lP = x | (y << 16);
//
//                    PostMessage(maListe.h[i], WM_LBUTTONDOWN, MK_LBUTTON, lP);
//                    PostMessage(maListe.h[i], WM_LBUTTONUP  , 0, lP);
//                    Sleep(5000);
//                }
            //MessageBeep(MB_ICONERROR);
        }

        Sleep(valTimer);
    }
}

void mimicFastMessageForAllK(void)
{
    ull keys[191] = { 0 };
    while(1)
    {
        if (!mimic)
            return;
        if(!canBeStarted || !isStarted) continue;
        if (GetForegroundWindow() != maListe.h[0]) continue;
//        std::cout << "in" << std::endl;

        for (unsigned char KEY = 'A'; KEY <= 'Z'; KEY++)
        {
            if (avoidMovementKey && (KEY == 'Z' || KEY == 'Q' || KEY == 'S' || KEY == 'D')) continue;
            checkKey(keys, (size_t) KEY);
        }
        for (unsigned char KEY = VK_NUMPAD0; KEY <= VK_NUMPAD9; KEY++)
        {
            checkKey(keys, (size_t) KEY);
        }
        for (unsigned char KEY = '0'; KEY <= '9'; KEY++)
        {
            checkKey(keys, (size_t) KEY);
        }
//        checkKey(keys, (size_t) '0', 'à');
//        checkKey(keys, (size_t) '1', '&');
//        checkKey(keys, (size_t) '2', 'é');
//        checkKey(keys, (size_t) '3', '"');
//        checkKey(keys, (size_t) '4', '\'');
//        checkKey(keys, (size_t) '5', '(');
//        checkKey(keys, (size_t) '6', '-');
//        checkKey(keys, (size_t) '7', 'è');
//        checkKey(keys, (size_t) '8', '_');
//        checkKey(keys, (size_t) '9', 'ç');


//        std::cout << "test2" << std::endl;
        Sleep(15);
    }
}

void checkKey(ull keys[191], size_t KEY, size_t real_key)
{
    if (real_key == 0)
        real_key = KEY;
    ull THRESHOLD = 0;

    if (GetAsyncKeyState(KEY) & 0x8000)
    {
        if (get_time_ms() - keys[KEY] < THRESHOLD && keys[KEY] != 0)  return;

        for(size_t i = 1; i < maListe.number && maListe.h[i] != NULL; i++)
            PostMessage(maListe.h[i], WM_KEYDOWN, real_key, real_key);

//        std::cout << (int) KEY << ": " << KEY << std::endl;

        if (keys[KEY] == 0)
        {
//            std::cout << (int) KEY << ": " << KEY << std::endl;
            keys[KEY] = get_time_ms();
            for(size_t i = 1; i < maListe.number && maListe.h[i] != NULL; i++)
                PostMessage(maListe.h[i], WM_KEYUP, real_key, real_key);
        }
    }
    else
    {
        if (keys[KEY] == 0) return;

        keys[KEY] = 0;
        for(size_t i = 0; i < maListe.number && maListe.h[i] != NULL; i++)
        {
//                    PostMessage(maListe.h[i], WM_KEYDOWN, KEY, KEY);
            PostMessage(maListe.h[i], WM_KEYUP, KEY, KEY);
        }
    }
}


