#include "Llist.h"
#include <iostream>
#include <thread>

#include "GLOBALS.h"

unsigned long long get_time_ms(void)
{
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}


void Lfree (struct Llist l){
    for (size_t i = 0; i < l.number; i ++)
        setBorders(l.h[i], true);

    if (l.h != NULL)
        free(l.h);
    if (l.r != NULL)
        free(l.r);
}


void updateList(struct Llist *l, HWND main)
{
    l->h = (HWND*) malloc(l->number * sizeof(HWND)); /// allocating it
    l->r = (RECT*) malloc(l->number * sizeof(RECT)); /// allocating it

    ::ShowWindow (hwndTextTime, true);
    ::UpdateWindow(hwndALL);

//    MSG messages;

    unsigned long long  ms1 = get_time_ms();
    for(size_t i = 0; i < l->number; )
    {
        unsigned long long  ms2 = get_time_ms();

        size_t dif = 1500-(ms2 - ms1);
        if(dif % 50 == 0)
        {
            char tmp[12];
            sprintf(tmp, "%llu", dif);
            ::SetWindowText(hwndTextTime, tmp);
        }

        if( ms2 - ms1 >= 1500 )
        {
            l->h[i] = ::GetForegroundWindow();
            l->r[i] = getRect(l->h[i]);

            std::cout << "Got Handle - " << l->h[i] << std::endl;
            i++;
            ms1 = ms2;
            ::MessageBeep(MB_ICONERROR);
        }

//        if (::GetMessage (&messages, NULL, 0, 0))
//        {
//            ::TranslateMessage(&messages);
//            ::DispatchMessage(&messages);
//        }
        //Sleep(5);
    } /// Get all the handles (one by one)
      /// Doing it by getting the focused window
      /// and sets the midpoint of the window

    ::ShowWindow (hwndTextTime, false);
    ::UpdateWindow(main);
}
