#include <windows.h>
#include <string.h>
#include <stdio.h>

// Функция для безопасного извлечения расширения файла
void GetFileExtension(const char* filePath, char* outExt, size_t maxLen) {
    const char* dot = strrchr(filePath, '.');
    if (!dot || dot == filePath) {
        strncpy(outExt, "unknown", maxLen);
    } else {
        strncpy(outExt, dot + 1, maxLen);
    }
}

// УНИВЕРСАЛЬНЫЙ ИМПОРТ ЛЮБОГО РЕСУРСА ДЛЯ РЕДАКТОРА
// sourcePath — полный путь к файлу на ПК пользователя (хоть .pdf, хоть .png, хоть .mp4)
// targetDir  — папка, куда твой редактор складывает ассеты (например, "Editor/Redactor/Assets/")
// assetName  — как этот ресурс будет называться в твоей системе (например, "main_bg", "player_icon", "manual")
BOOL ImportAsset(const char* sourcePath, const char* targetDir, const char* assetName) {
    if (sourcePath == NULL || strlen(sourcePath) == 0) return FALSE;

    // 1. Узнаем расширение исходного файла (.pdf, .bmp, .mp4)
    char ext[16] = {0};
    GetFileExtension(sourcePath, ext, sizeof(ext) - 1);

    // 2. Создаем папку для ассетов, если редактор запускается впервые
    CreateDirectoryA(targetDir, NULL);

    // 3. Собираем элитный финальный путь
    // На выходе будет, например: "Editor/Redactor/Assets/main_bg.pdf" или "Editor/Redactor/Assets/player_icon.png"
    char finalDestPath[MAX_PATH] = {0};
    snprintf(finalDestPath, sizeof(finalDestPath), "%s%s.%s", targetDir, assetName, ext);

    // 4. Копируем байты файла. FALSE означает, что мы молча перезапишем старый файл, если он там был
    if (CopyFileA(sourcePath, finalDestPath, FALSE)) {
        return TRUE; // Файл успешно импортирован в систему твоего редактора!
    }

    return FALSE; // Ошибка (например, если у файла нет прав на чтение)
}
