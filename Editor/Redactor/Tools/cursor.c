#include <windows.h>
#include <stdio.h>

// Структура параметров кастомизации курсора
typedef struct {
    float scale;       // Масштаб (например, 1.0 — оригинальный, 1.5 — увеличенный)
    float rotation;    // Угол поворота в градусах (от 0 до 360)
    int cursorType;    // ID типа: 1 - Стрелка, 2 - Палец (Ссылка), 3 - Занято
} CursorProperties;

// ГЛАВНЫЙ ИНСТРУМЕНТ: Обработка и импорт курсора
// sourcePath — путь к исходному файлу пользователя (PNG, JPG, BMP, GIF)
// targetDir  — папка ассетов (например, "Editor/Redactor/Assets/Cursors/")
BOOL ImportCustomCursor(const char* sourcePath, const char* targetDir, CursorProperties props) {
    if (sourcePath == NULL || strlen(sourcePath) == 0) return FALSE;

    // Создаем элитную папку для кастомных курсоров
    CreateDirectoryA(targetDir, NULL);

    // Определяем имя файла в зависимости от типа курсора
    char cursorName[32];
    switch (props.cursorType) {
        case 1: strcpy(cursorName, "arrow"); break;
        case 2: strcpy(cursorName, "pointer"); break;
        case 3: strcpy(cursorName, "busy"); break;
        default: strcpy(cursorName, "custom"); break;
    }

    // Достаем родное расширение файла
    const char* dot = strrchr(sourcePath, '.');
    char ext[16] = "png";
    if (dot && dot != sourcePath) {
        strncpy(ext, dot + 1, sizeof(ext) - 1);
    }

    // Путь, куда сначала сохраняем оригинал ассета
    char finalAssetPath[MAX_PATH] = {0};
    snprintf(finalAssetPath, sizeof(finalAssetPath), "%s%s_orig.%s", targetDir, cursorName, ext);
    
    // Копируем исходник
    if (!CopyFileA(sourcePath, finalAssetPath, FALSE)) return FALSE;

    // Создаем текстовый файл конфигурации для этого курсора!
    // Движок предпросмотра (Preview Window) прочитает этот файл,
    // возьмет исходную картинку и налету повернет/увеличит её на экране через GDI+.
    char configPath[MAX_PATH] = {0};
    snprintf(configPath, sizeof(configPath), "%s%s.cfg", targetDir, cursorName);

    FILE* file = fopen(configPath, "w");
    if (file == NULL) return FALSE;

    fprintf(file, "SOURCE_FILE=%s_orig.%s\n", cursorName, ext);
    fprintf(file, "SCALE=%.2f\n", props.scale);
    fprintf(file, "ROTATION=%.2f\n", props.rotation);

    fclose(file);
    return TRUE;
}
