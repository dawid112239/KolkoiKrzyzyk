#include<Windows.h>
#include<stdio.h>
#include "res.h"
#include <cstdlib>

bool isGameOnn = true;
bool isFirstPlayer = true;
int pola[3][3];
bool krzyzykWygral = false;
int licznik = 0;


bool wygrana()
{
  int zmienna = -10;
  for (int i = 0; i < 3; i++)
  {
    if ((pola[i][0]==pola[i][1]) && (pola[i][0]==pola[i][2]) && (pola[i][0] != -1))
    {
      isGameOnn = false;
      if (pola[i][0] == 1)
      {
        krzyzykWygral = true;
      }
      return true;
    }
  }
  for (int i = 0; i < 3; i++)
  {
    if ((pola[0][i] == pola[1][i]) && (pola[0][i] == pola[2][i]) && (pola[0][i] != -1))
    {
      isGameOnn = false;
      if (pola[0][i] == 1)
      {
        krzyzykWygral = true;
      }
      return true;
    }
  }
  if ((pola[0][0] == pola[1][1]) && (pola[0][0] == pola[2][2]) && (pola[1][1] != -1))
  {
    isGameOnn = false;
    if (pola[0][0] == 1)
    {
      krzyzykWygral = true;
    }
    return true;
  }
  if ((pola[2][0] == pola[1][1]) && (pola[2][0] == pola[0][2]) && (pola[1][1] != -1))
  {
    isGameOnn = false;
    if (pola[1][1] == 1)
    {

      krzyzykWygral = true;
    }
    return true;
  }
  return false;
}






INT_PTR CALLBACK DialogProc(HWND hwndDig, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_COMMAND:
    
    switch (HIWORD(wParam))
    {
    case BN_CLICKED:
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON1:
      case IDC_BUTTON2:
      case IDC_BUTTON3:
      case IDC_BUTTON4:
      case IDC_BUTTON5:
      case IDC_BUTTON6:
      case IDC_BUTTON7:
      case IDC_BUTTON8:
      case IDC_BUTTON9:
      { 
      
        if (isGameOnn == true)
        {

          if (isFirstPlayer == true)
          {
            HWND hwndButton = (HWND)lParam;
            if (GetWindowTextLength(hwndButton) == 0)
            {
              licznik++;
              CHAR szText[500];
              wsprintf(szText, "X");
              SetWindowText(hwndButton, szText);
              isFirstPlayer = false;
              CheckRadioButton(hwndDig, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);

            }
          }
          else
          {
            HWND hwndButton = (HWND)lParam;
            if (GetWindowTextLength(hwndButton) == 0)
            {
              licznik++;
              CHAR szText[500];
              wsprintf(szText, "O");
              SetWindowText(hwndButton, szText);
              isFirstPlayer = true;
              CheckRadioButton(hwndDig, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
            }
          }
          int znacznik = LOWORD(wParam);
          znacznik = znacznik - 1007;
          int x = znacznik % 3;
          int y = znacznik / 3;
          if (isFirstPlayer == false)
            pola[x][y] = 1;
          else
            pola[x][y] = 0;
          


          if (wygrana() == true)
          {
            isGameOnn = false;
            if (krzyzykWygral == true)
            {
              HWND hwndStatic = GetDlgItem(hwndDig, IDC_STATIC1);
              CHAR szText[500];
              wsprintf(szText, "Brawo pierwszy gracz wygra�, aby zagra� ponownie - restart");
              SetWindowText(hwndStatic, szText);
            }
            else
            {
              HWND hwndStatic = GetDlgItem(hwndDig, IDC_STATIC1);
              CHAR szText[500];
              wsprintf(szText, "Brawo drugi gracz wygra�, aby zagra� ponownie - restart");
              SetWindowText(hwndStatic, szText);
            }
          }
        }
        if ((licznik == 9) && (wygrana() == false))
        {
          isGameOnn = false;
          HWND hwndStatic = GetDlgItem(hwndDig, IDC_STATIC1);
          CHAR szText[500];
          wsprintf(szText, "Brak roztrzygni�cia - restart");
          SetWindowText(hwndStatic, szText);
        }
        return TRUE;
      }

      case IDC_BUTTON10:
        krzyzykWygral = false;
        isGameOnn = true;
        licznik = 0;
        CheckRadioButton(hwndDig, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
        HWND hwndStatic = GetDlgItem(hwndDig, IDC_STATIC1);
        CHAR szText[500];
        wsprintf(szText, "");
        SetWindowText(hwndStatic, szText);
        isFirstPlayer = true;
        for (int i = 0; i < 9; i++) 
        {
          HWND hwndButton = GetDlgItem(hwndDig, IDC_BUTTON1 + i);
          CHAR szText[500];
          wsprintf(szText, "");
          SetWindowText(hwndButton, szText);
          if (i < 3)
          {
            for (int j = 0; j < 3; j++)
            {
              pola[i][j]=-1;
            }
          }

        }
        return TRUE;
      }

      return FALSE;

    }


    return FALSE;
  case WM_CLOSE:
    DestroyWindow(hwndDig);
    PostQuitMessage(0);
    return TRUE;
  }
  return FALSE;
}



int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, PSTR szCmdLIne, int iCmdShow)
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      pola[i][j] = -1;
    }
  }
  HWND hwndMainWindow = CreateDialog(hinstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);
  MSG msg = {};
  CheckRadioButton(hwndMainWindow, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
