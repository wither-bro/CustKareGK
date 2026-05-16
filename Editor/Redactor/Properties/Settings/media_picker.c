#include <stdio.h>

typedef struct {
    char sourcePath[260];   // Путь к файлу
    int mediaType;          // 1 - Фото, 2 - Видео, 3 - GIF
    int fitMode;            // 1 - Растянуть, 2 - Заполнить (Masking), 3 - Центр
} MediaPickerData;

// Универсальный выбор для инструментов
void LinkMediaToTool(const char* toolTarget, MediaPickerData data) {
    printf("[MediaPicker] Отправка файла %s в инструмент %s\n", data.sourcePath, toolTarget);
    
    // Если это window_geometry.c -> активируем твою фичу "видео внутри рамок"
    // Если это fontmanager.c -> запускаем видео сквозь буквы
}
