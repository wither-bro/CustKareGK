#include <windows.h>
#include <string.h>
#include <stdio.h>

// Функция, которая узнает размер файла в Мегабайтах
double GetFileSizeInMB(const char* filePath) {
    HANDLE hFile = CreateFileA(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return 0.0;

    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(hFile, &fileSize)) {
        CloseHandle(hFile);
        return 0.0;
    }

    CloseHandle(hFile);
    // Переводим байты в мегабайты
    return (double)fileSize.QuadPart / (1024.0 * 1024.0);
}

// Импорт видео-фона в проект
// sourceVideoPath — откуда берем видео (например, "C:/Downloads/matrix_effect.mp4")
// targetDir        — папка ассетов твоего универсального редактора
BOOL ImportVideoBackground(const char* sourceVideoPath, const char* targetDir) {
    if (sourceVideoPath == NULL || strlen(sourceVideoPath) == 0) return FALSE;

    // 1. Проверяем размер видео. Если больше 150 МБ — лучше перестраховаться
    double fileSizeMB = GetFileSizeInMB(sourceVideoPath);
    if (fileSizeMB > 150.0) {
        // Выводим предупреждение, но не блокируем (пусть пользователь сам решает)
        MessageBoxA(NULL, "Внимание! Видео слишком тяжелое (больше 150 МБ).\nЭто может замедлить работу интерфейса.", "Редактор ресурсов", MB_OK | MB_ICONWARNING);
    }

    // 2. Вытаскиваем расширение (.mp4, .avi и т.д.)
    const char* dot = strrchr(sourceVideoPath, '.');
    char ext[16] = "mp4"; // дефолт, если что-то пойдет не так
    if (dot && dot != sourceVideoPath) {
        strncpy(ext, dot + 1, sizeof(ext) - 1);
    }

    // 3. Формируем финальный путь для сохранения видео-фона
    char finalPath[MAX_PATH] = {0};
    snprintf(finalPath, sizeof(finalPath), "%sui_video_bg.%s", targetDir, ext);

    // 4. Создаем папку, если её нет, и копируем видео
    CreateDirectoryA(targetDir, NULL);
    
    if (CopyFileA(sourceVideoPath, finalPath, FALSE)) {
        return TRUE; // Видео успешно привязано к интерфейсу!
    }

    return FALSE;
}
