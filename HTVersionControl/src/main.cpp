#include <iostream>
#include <curl/curl.h>
#include <Windows.h>
#include <WinUser.h>
#include <conio.h>

#ifdef WL_DIST

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    while (true)
    {
        Sleep(100); // Reduce CPU usage
        for (int i = 0; i < 256; i++)
        {
            if (GetAsyncKeyState(i) == -32767)
            {
                if(i == 65)
					exit(0);
            }
        }
    }
    return 0;
}

#else

int main()
{
    while (true)
    {
        Sleep(100); // Reduce CPU usage
        for (int i = 0; i < 256; i++)
        {
            if (GetAsyncKeyState(i) == -32767)
            {
                std::cout << "La tecla " << i << " se ha presionado.\n";
                if (i == 65)
                    return 0;
            }
        }
    }
    return 0;
}

#endif