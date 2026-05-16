#include <stdio.h>
#include <string.h>

typedef struct {
    unsigned int hexColor;    // Цвет в формате 0xFFFFFFFF
    char uploadPath[260];     // Путь для кнопок "Upload Photo/Video"
    char originalString[128]; // Что меняем (например, "Поиск")
    char customString[128];   // На что меняем (например, "Искать")
} VisualFxData;

void ApplyVisualChanges(const char* toolTarget, VisualFxData data) {
    printf("[VisualFX] Применяем к: %s\n", toolTarget);
    
    // Если это ШРИФТЫ - активируем безумную подмену текста
    if (strcmp(toolTarget, "fontmanager.c") == 0) {
        printf("  -> Подмена текста: [%s] заменен на [%s]\n", data.originalString, data.customString);
    }
    
    // Если нажата кнопка UPLOAD
    if (strlen(data.uploadPath) > 0) {
        printf("  -> Загружен медиа-файл: %s\n", data.uploadPath);
    }

    printf("  -> Установлен HEX-цвет: #%06X\n", data.hexColor & 0xFFFFFF);
}
