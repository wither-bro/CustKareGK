#include <windows.h>
#include <string.h>
#include <stdio.h>

// Режимы кастомизации углов окон
typedef enum {
    CORNER_STYLE_DEFAULT = 0,   // Стандартные углы Windows
    CORNER_STYLE_ROUND = 1,     // Идеально круглые (то, что будут юзать чаще всего)
    CORNER_STYLE_CUSTOM_ANG = 2 // Кастомный острый срез под заданным углом
} CornerStyleID;

// Структура параметров геометрии окон и рамок
typedef struct {
    CornerStyleID cornerStyle;
    float cornerAngle;         // Угол для кастомного среза (если выбран стиль 2)
    int useBorderMedia;        // Флаг: 1 - видео/фото на рамке, 0 - обычный цвет
    float effectScale;         // Масштабирование визуальных эффектов (чтобы они были четко видны)
} WindowFxProperties;

// ГЛАВНЫЙ ИНСТРУМЕНТ: Применение безумных эффектов к окнам и рамкам
// borderMediaPath — путь к кастомному видео или фото для рамки окна
// targetDir       — папка системных конфигураций ("Editor/Redactor/Assets/WindowFX/")
BOOL ApplyWindowGeometryFx(const char* borderMediaPath, const char* targetDir, WindowFxProperties props) {
    
    // 1. Создаем элитную папку для оконных эффектов
    CreateDirectoryA(targetDir, NULL);

    // 2. Копируем медиафайл рамки (фото или видео), если он включен
    char finalMediaName[64] = "none";
    if (props.useBorderMedia && borderMediaPath && strlen(borderMediaPath) > 0) {
        const char* dot = strrchr(borderMediaPath, '.');
        char mediaPath[MAX_PATH] = {0};
        snprintf(mediaPath, sizeof(mediaPath), "%swindow_border_media%s", targetDir, dot ? dot : ".mp4");
        
        // Копируем исходник (твоя логика маскирования: само окно закроет картинку изнутри, так что краев не будет видно!)
        CopyFileA(borderMediaPath, mediaPath, FALSE);
        snprintf(finalMediaName, sizeof(finalMediaName), "window_border_media%s", dot ? dot : ".mp4");
    }

    // 3. ГЕНЕРИРУЕМ УЛИТИМАТИВНЫЙ КОНФИГ ГЕОМЕТРИИ ОКОН (.cfg)
    // Движок предпросмотра (Preview Window) прочитает этот файл и покажет рамку в действии
    char configPath[MAX_PATH] = {0};
    snprintf(configPath, sizeof(configPath), "%swindow_geometry.cfg", targetDir);

    FILE* file = fopen(configPath, "w");
    if (file == NULL) return FALSE;

    fprintf(file, "[WindowCorners]\n");
    fprintf(file, "CORNER_STYLE=%d\n", props.cornerStyle);
    fprintf(file, "CORNER_ANGLE=%.2f\n", props.cornerAngle);

    fprintf(file, "\n[BorderMediaEffects]\n");
    fprintf(file, "USE_MEDIA_BORDER=%d\n", props.useBorderMedia);
    fprintf(file, "MEDIA_FILE=%s\n", finalMediaName);
    fprintf(file, "EFFECT_SCALE=%.2f\n", props.effectScale); // Твоя фича масштабирования эффектов

    fclose(file);
    return TRUE;
}
