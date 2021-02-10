#include "windowing.h"
#include "GLOBALS.h"

size_t rand_range(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

void setBorders(HWND hwnd, bool b)
{
    LONG lStyle = GetWindowLong(hwnd, GWL_STYLE);
    LONG lExStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
    if (!b)
    {
        lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
        lExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
    }
    else
    {
        lStyle |= (WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
        lExStyle |= (WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
    }

    SetWindowLong(hwnd, GWL_STYLE, lStyle);
    SetWindowLong(hwnd, GWL_EXSTYLE, lExStyle);
    SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
}

RECT getRect(HWND h)
{
    RECT r, r1;
    GetWindowRect(h, &r);
    GetClientRect(h, &r1);
    r.bottom = r1.bottom;
    r.right = r1.right;
    return r;
}

void postFastMessageForAllK()
{
    while (1)
    {
        if (isMimic)
            return;

        //if(!canBeStarted) continue;
        //        MessageBox(NULL, (isStarted ? "true" : "false"), "title", 0);
        Sleep(1);
        if (!isStarted)
            continue;
        //MessageBeep(MB_ICONERROR);

        for (size_t i = 0; i < maListe.number && maListe.h[i] != NULL; i++)
        {
            //                maListe.r[i] = getRect(maListe.h[i]);

            //            std::cout << maListe.h[i] << std::endl;
            //            std::cout << maListe.h[i] << ": " << *keyToSend << ": " << valTimer << std::endl;
            PostMessage(maListe.h[i], WM_KEYDOWN, keyToSend, keyToSend);
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
            //                    PostMessage(maListe.h[i], WM_LBUTTONDOWN, VK_LBUTTON, lP);
            //                    PostMessage(maListe.h[i], WM_LBUTTONUP  , VK_LBUTTON, lP);
            //                    Sleep(5000);
            //                }
            //MessageBeep(MB_ICONERROR);
            Sleep(rand_range(20, 50));
        }
        int alea = rand_range(0, valTimer / 5);
        //alea -= valTimer/10;
        Sleep(valTimer + alea);
    }
}

void changeWindowPositions()
{
    size_t NB_WINDOW = maListe.number;
    size_t posNB = 0;
    for (size_t i = 0; i < 4; i++)
    {
        if (i == focusedOne)
        {
            ::MoveWindow(maListe.h[i],
                         0, 0,
                         sWidth, sHeight - (sHeight / NB_WINDOW),
                         true);
            continue;
        }

        ::MoveWindow(maListe.h[i],
                     (posNB) * (sWidth / (NB_WINDOW - 1)), sHeight - (sHeight / NB_WINDOW),
                     (sWidth / (NB_WINDOW - 1)), (sHeight / NB_WINDOW),
                     true);
        posNB++;
    }
}

bool ForceToForeground(HWND hWnd)
{
    HWND hForeground = GetForegroundWindow();

    int curThread    = GetCurrentThreadId();
    int remoteThread = GetWindowThreadProcessId(hForeground,0);

    AttachThreadInput( curThread, remoteThread, TRUE);
    SetForegroundWindow(hWnd);
    AttachThreadInput( curThread, remoteThread, FALSE);

    return GetForegroundWindow() == hWnd;
}

void mimicFastMessageForAllK(void)
{
    size_t ind = 0;
    size_t time_save = 0;

//    unsigned long long keys[191] = {0};
    while (1)
    {
        if (!isMimic)
            return;
        Sleep(1);
        if (!isStarted)
            continue;

        HWND foreground = GetForegroundWindow();
//        if (foreground != maListe.h[focusedOne])
//        {
//            //            std::cout << isPlaceWindow << std::endl;
//            if (!isPlaceWindow)
//                continue;
//            size_t i = 0;
//            for (i = 0; i < maListe.number; i++)
//            {
//                if (maListe.h[i] == foreground)
//                    break;
//            }
//
//            if (i == maListe.number)
//                continue;
//            focusedOne = i;
//            std::cout << focusedOne << std::endl;
//            changeWindowPositions();
//        }
        size_t i = 0;
        for (i = 0; i < maListe.number; i++)
        {
            if (maListe.h[i] == foreground)
                break;
        }
        if (i == maListe.number)
            continue;

        //        std::cout << "in" << std::endl;

//        checkKey(keys, VK_LSHIFT);
//        checkKey(keys, VK_LCONTROL);
        if (time_save + 100 >= get_time_ms())
            continue;
        if ((GetAsyncKeyState(VK_LMENU) & 0x8000) == 0)
            continue;

        ind = (i + 1) % maListe.number;
        printf("i: %lld\n", ind);
        printf("%p\n%p", maListe.h[0], maListe.h[1]);
        ForceToForeground(maListe.h[ind]);
        // SetFocus(maListe.h[ind]);
        printf("\t%p\n", GetForegroundWindow());

        time_save = get_time_ms();

        continue;

//        for (unsigned char KEY = 'A'; KEY <= 'Z'; KEY++)
//        {
//            if (!isMimicMovement && (KEY == 'Z' ||
//                                     KEY == 'Q' ||
//                                     KEY == 'S' ||
//                                     KEY == 'D' ||
//                                     KEY == VK_SPACE))
//                continue;
//            checkKey(keys, KEY);
//        }
//
//        for (unsigned char KEY = VK_NUMPAD0; KEY <= VK_NUMPAD9; KEY++)
//            checkKey(keys, KEY);
//        for (unsigned char KEY = '0'; KEY <= '9'; KEY++)
//            checkKey(keys, KEY);
//        for (unsigned char KEY = VK_F1; KEY <= VK_F12; KEY++)
//            checkKey(keys, KEY);
//        for (unsigned char KEY = VK_LEFT; KEY <= VK_DOWN; KEY++)
//            checkKey(keys, KEY);
//
//        checkKey(keys, VK_OEM_102);   /// '<'
//        checkKey(keys, VK_OEM_8);     /// '<'
//        checkKey(keys, VK_OEM_COMMA); /// ','
//        checkKey(keys, VK_OEM_1); /// ';' or ':' (?)
//        checkKey(keys, VK_OEM_102);
        // checkKey(keys, VK_ESCAPE);

//        checkKey(keys, VK_LMENU, VK_SPACE);

        Sleep(15);
    }
}

size_t OLD = 0;
size_t old_time;

void checkKey(unsigned long long keys[191], size_t KEY, size_t real_key)
{
//    if (GetAsyncKeyState(KEY) & 0x8000)
//    {
//        unsigned long long THRESHOLD = 100;
//        if (old_time + THRESHOLD >= get_time_ms())
//            return;
//
//        printf("OLD: %lld - NEW: %lld\n", OLD, KEY);
//        if (KEY != OLD)
//            ind = 0;
//
//        printf("%lld\n", ind);
////        PostMessage(maListe.h[ind], WM_KEYUP, KEY, KEY);
//
//        OLD=KEY;
//
//        if (keys[KEY] == 0)
//            keys[KEY] = get_time_ms();
//        old_time = get_time_ms();
//    }
//    else if (keys[KEY] != 0)
//    {
//        SetForegroundWindow(maListe.h[ind]);
//        SetFocus(maListe.h[ind]);
//        ind = (ind + 1) % maListe.number;
//        keys[KEY] = 0;
//    }

    return;

    if (real_key == 0)
        real_key = KEY & 0xFF;
    //    if (real_key == VK_SPACE)
    //    std::cout << "checkALT:" << checkALT << std::endl <<
    //        "realKEY:" << real_key << std::endl;

    /// Time in MS before full press
    unsigned long long THRESHOLD = 100;
    if (KEY == VK_LSHIFT || KEY == VK_LCONTROL)
        THRESHOLD = 0;

    if (GetAsyncKeyState(KEY) & 0x8000)
    {
        if (get_time_ms() - keys[KEY] < THRESHOLD && keys[KEY] != 0)
            return;

        if (keys[KEY] != 0)
            return;

        for (size_t i = 0; i < maListe.number && maListe.h[i] != NULL; i++)
        {
            if (i == focusedOne)
                continue;
            PostMessage(maListe.h[i], WM_KEYDOWN, real_key, real_key);
        }

        //            std::cout << (int) KEY << ": " << KEY << std::endl;
        keys[KEY] = get_time_ms();
    }
    else
    {
        if (keys[KEY] == 0)
            return;

        keys[KEY] = 0;
        for (size_t i = 0; i < maListe.number && maListe.h[i] != NULL; i++)
        {
            if (i == focusedOne)
                continue;
            //            PostMessage(maListe.h[i], WM_KEYDOWN, KEY, KEY);
            PostMessage(maListe.h[i], WM_KEYUP, real_key, real_key);
        }
    }
}
