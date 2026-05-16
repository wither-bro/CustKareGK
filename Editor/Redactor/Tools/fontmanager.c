#include <windows.h>
#include <string.h>
#include <stdio.h>

// ID ролей шрифта/текста
typedef enum {
    TEXT_ROLE_MAIN = 1,       // Основной текст интерфейса
    TEXT_ROLE_HEADERS = 2,    // Заголовочные элементы
    TEXT_ROLE_CUSTOM_LABELS = 3 // Кастомные надписи и виджеты
} TextRoleID;

// Структура ультимативной кастомизации шрифта и текста
typedef struct {
    TextRoleID role;
    int fontSize;             // Базовый размер
    float scale;              // Масштабирование "на всякий случай" (например, 1.2 — увеличение на 20%)
    float rotation;           // Угол поворота текста в градусах (0 - 360)
    DWORD textColor;          // Цвет текста в формате HEX (ARGB, например 0xFFFFFFFF)
    int useMediaMask;         // Флаг: 1 - использовать фото/видео внутри текста, 0 - обычный цвет
} AdvancedFontProperties;

// ГЛАВНЫЙ СКИПТ: Импорт шрифта, эффектов и таблицы переименования строк
// sourceFontPath — путь к файлу шрифта (.ttf / .otf)
// mediaMaskPath  — путь к фото или видео, которое будет отображаться ВНУТРИ текста (если useMediaMask = 1)
// targetDir      — папка ассетов шрифтов ("Editor/Redactor/Assets/Fonts/")
// originalString — текст, который хотим заменить (например, "Microsoft Store")
// customString   — текст, на который заменяем (например, "Магазин")
BOOL ImportAdvancedFont(const char* sourceFontPath, 
                        const char* mediaMaskPath, 
                        const char* targetDir, 
                        AdvancedFontProperties props,
                        const char* originalString,
                        const char* customString) {
    
    // 1. Создаем папку для продвинутых ассетов шрифта
    CreateDirectoryA(targetDir, NULL);

    char roleName[32];
    switch (props.role) {
        case TEXT_ROLE_MAIN:          strcpy(roleName, "main"); break;
        case TEXT_ROLE_HEADERS:       strcpy(roleName, "headers"); break;
        case TEXT_ROLE_CUSTOM_LABELS: strcpy(roleName, "custom"); break;
        default:                      strcpy(roleName, "generic"); break;
    }

    // 2. Копируем сам файл шрифта (если он передан)
    if (sourceFontPath && strlen(sourceFontPath) > 0) {
        const char* fontDot = strrchr(sourceFontPath, '.');
        char fontPath[MAX_PATH] = {0};
        snprintf(fontPath, sizeof(fontPath), "%s%s_font%s", targetDir, roleName, fontDot ? fontDot : ".ttf");
        CopyFileA(sourceFontPath, fontPath, FALSE);
    }

    // 3. Если включен режим медиа-маски — копируем фото или видео, которое будет ВНУТРИ текста
    char finalMaskName[64] = "none";
    if (props.useMediaMask && mediaMaskPath && strlen(mediaMaskPath) > 0) {
        const char* maskDot = strrchr(mediaMaskPath, '.');
        char maskPath[MAX_PATH] = {0};
        snprintf(maskPath, sizeof(maskPath), "%s%s_text_mask%s", targetDir, roleName, maskDot ? maskDot : ".mp4");
        CopyFileA(mediaMaskPath, maskPath, FALSE);
        snprintf(finalMaskName, sizeof(finalMaskName), "%s_text_mask%s", roleName, maskDot ? maskDot : ".mp4");
    }

    // 4. ГЕНЕРИРУЕМ СВЕРХКРУТОЙ КОНФИГ ТРАНСФОРМАЦИИ И ЛОКАЛИЗАЦИИ
    char configPath[MAX_PATH] = {0};
    snprintf(configPath, sizeof(configPath), "%s%s_text_fx.cfg", targetDir, roleName);

    FILE* file = fopen(configPath, "w");
    if (file == NULL) return FALSE;

    fprintf(file, "[FontTransformation]\n");
    fprintf(file, "FONT_SIZE=%d\n", props.fontSize);
    fprintf(file, "SCALE=%.2f\n", props.scale);
    fprintf(file, "ROTATION=%.2f\n", props.rotation);
    fprintf(file, "COLOR_HEX=0x%08X\n", props.textColor);
    
    fprintf(file, "\n[TextVisualEffects]\n");
    fprintf(file, "USE_MEDIA_MASK=%d\n", props.useMediaMask);
    fprintf(file, "MASK_FILE=%s\n", finalMaskName);

    // Самая сочная фича — подмена строк (как в Telegram (.lang) файлах)
    fprintf(file, "\n[StringTranslation]\n");
    if (originalString && customString && strlen(originalString) > 0) {
        fprintf(file, "ORIGINAL=\"%s\"\n", originalString);
        fprintf(file, "REPLACED_WITH=\"%s\"\n", customString);
    } else {
        fprintf(file, "ORIGINAL=\"\"\n", originalString);
        fprintf(file, "REPLACED_WITH=\"\"\n", customString);
    }

    fclose(file);
    return TRUE;
}
