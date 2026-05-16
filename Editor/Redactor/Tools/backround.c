#include <windows.h>
#include <string.h>
#include <stdio.h>

// Функция для получения расширения файла (например, "pdf", "png", "mp4")
void GetExtension(const char* filePath, char* outExt, size_t maxLen) {
    const char* dot = strrchr(filePath, '.');
    if (!dot || dot == filePath) {
        strncpy(outExt, "unknown", maxLen);
    } else {
        strncpy(outExt, dot + 1, maxLen);
    }
}

// Универсальная функция импорта ресурса
// sourcePath - путь к файлу, который выбрал пользователь (например, "C:/Docs/manual.pdf")
// targetDir  - папка твоих ассетов (например, "Editor/Redactor/Assets/")
BOOL ImportUniversalResource(const char* sourcePath, const char* targetDir) {
    if (sourcePath == NULL || strlen(sourcePath) == 0) return FALSE;

    // 1. Извлекаем расширение исходного файла
    char ext[16] = {0};
    GetExtension(sourcePath, ext, sizeof(ext) - 1);

    // 2. Формируем элитное финальное имя файла, сохраняя его родной формат
    // На выходе получится что-то вроде: "Editor/Redactor/Assets/imported_background.pdf"
    char finalDestPath[MAX_PATH] = {0};
    snprintf(finalDestPath, sizeof(finalDestPath), "%simported_background.%s", targetDir, ext);

    // 3. Создаем папку назначения, если её вдруг нет
    CreateDirectoryA(targetDir, NULL);

    // 4. Тупо и надежно копируем байты любого файла (PDF, MP4, PNG, EXE, TXT)
    // FALSE означает, что мы перезапишем старый файл без лишних вопросов
    if (CopyFileA(sourcePath, finalDestPath, FALSE)) {
        return TRUE; // Файл успешно угнан в систему!
    }

    return FALSE; // Ошибка копирования (например, нет прав доступа)
}
