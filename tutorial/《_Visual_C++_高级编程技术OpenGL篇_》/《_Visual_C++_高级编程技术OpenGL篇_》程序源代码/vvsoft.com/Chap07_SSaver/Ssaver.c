#include <windows.h>
#include <stdlib.h>
#include <scrnsave.h>
#include "resource.h"

HANDLE hInst;       // current instance
UINT wTimer = 0;    // Timer id

extern HWND  ghWnd; 											   
extern HDC   ghDC; 
extern HGLRC ghRC;

/*
 * RegisterDialogClasses -- Entry point for registering window classes 
 *                          required by configuration dialog box.
 */
BOOL WINAPI RegisterDialogClasses(HINSTANCE hInst)
{
    return 1;
}

/*
 * ScreenSaverConfigureDialog -- Process the screen saver configuration
 *                               messages for the config dialog
 */ 
BOOL CALLBACK ScreenSaverConfigureDialog(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch(Msg)
    {
        case WM_COMMAND:
			switch(LOWORD(wParam))
            {
                case IDOK:  // Exit the dialog
                case IDC_EXIT:
					EndDialog(hWnd, 42);
					break;
            }
        break;
        default:
		    return FALSE;
        break;
    }
    return TRUE;
}

/****************************************************************************
    FUNCTION: ScreenSaverProc(HWND, UINT, WPARAM, LPARAM)
    PURPOSE:  Processes screen saver messages
****************************************************************************/
LONG CALLBACK ScreenSaverProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{      
	RECT rect;

	switch (msg) {
	case WM_CREATE:

		ghDC = GetDC(hWnd); 
        if (!bSetupPixelFormat(ghDC)) 
            PostQuitMessage (0); 
 
        ghRC = wglCreateContext(ghDC); 
        wglMakeCurrent(ghDC, ghRC); 
        GetClientRect(hWnd, &rect); 
		initializeGL(rect.right, rect.bottom);
        resize(rect.right, rect.bottom);  
		//Beep(200,200);
		break;
	case WM_TIMER:
        // Show a frame of our animation
		DrawFrame(hWnd);
		return 0;
    case WM_ERASEBKGND:        
		// Seed the random number generator
        srand(GetTickCount());
		// Tell windows to send us timer messages at 50ms intervals
        wTimer = SetTimer(hWnd, 0, 50, NULL);  
		break;       
    case WM_DESTROY:            /* message: window being destroyed */
		if (ghRC) 
            wglDeleteContext(ghRC); 
        if (ghDC) 
            ReleaseDC(hWnd, ghDC); 
		if (wTimer) // Stop our timer if it was created
			KillTimer(hWnd, wTimer); 
		break;              
    }  
    return DefScreenSaverProc(hWnd, msg, wParam, lParam); 
}