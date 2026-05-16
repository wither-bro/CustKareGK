#include <windows.h>

#define CUSTOM_BUTTON_ID 1001

// Процедура обработки сообщений нашего кастомного Пуска
LRESULT CALLBACK ButtonWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            // Здесь будет отрисовка твоих кастомных обоев/иконок из редактора.
            // Пока просто зальем кнопку красивым цветом для теста.
            HBRUSH brush = CreateSolidBrush(RGB(0, 120, 215)); // Фирменный синий
            FillRect(hdc, &ps.rcPaint, brush);
            DeleteObject(brush);
            
            EndPaint(hwnd, &ps);
            return 0;
        }
        case LBUTTONDOWN: { // Кликнули левой кнопкой мыши
            // Активируем меню Пуск через имитацию клавиши Win (работает на любой Windows)
            INPUT inputs[2] = {0};
            
            // Нажатие Win
            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_LWIN;
            
            // Отпускание Win
            inputs[1].type = INPUT_KEYBOARD;
            inputs[1].ki.wVk = VK_LWIN;
            inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
            
            SendInput(2, inputs, sizeof(INPUT));
            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Функция внедрения нашей кнопки в панель задач
void CreateCustomStartButton(HINSTANCE hInst) {
    // Находим современную панель задач
    HWND hwndTaskbar = FindWindow("Shell_TrayWnd", NULL);
    if (!hwndTaskbar) return;

    // Регистрируем класс нашего окна кнопки
    WNDCLASS wc = {0};
    wc.lpfnWndProc = ButtonWindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "CustKareGK_StartButton";
    RegisterClass(&wc);

    // Создаем окно кнопки как дочернее ПРЯМО внутри панели задач (размер 48x48 пикселей)
    HWND hwndBtn = CreateWindowEx(
        WS_EX_TOPMOST,
        "CustKareGK_StartButton",
        NULL,
        WS_CHILD | WS_VISIBLE,
        0, 0, 48, 48, // Координаты X, Y и размеры кнопки
        hwndTaskbar,
        (HMENU)CUSTOM_BUTTON_ID,
        hInst,
        NULL
    );
    
    ShowWindow(hwndBtn, SW_SHOW);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    CreateCustomStartButton(hInstance);

    // Легковесный цикл обработки сообщений, чтобы кнопка жила в памяти
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
