#include <stdio.h>

// Структура для хранения данных масштаба
typedef struct {
    float uniformScale; // Общий масштаб (тот самый главный ползунок)
    float widthScale;   // Масштаб по ширине (из "Дополнительно")
    float heightScale;  // Масштаб по высоте (из "Дополнительно")
    int isAdvanced;     // Флаг: открыто ли меню "Дополнительно"
} TransformData;

// ГЛОБАЛЬНАЯ ФУНКЦИЯ ПРИВЯЗКИ
// Она берет данные из ползунков и "скармливает" их нужному инструменту
void ApplyTransformToTool(const char* toolName, TransformData data) {
    printf("\n[Transform] Применяем настройки к инструменту: %s\n", toolName);
    
    // Вычисляем финальные коэффициенты
    float finalWidth = data.uniformScale * data.widthScale;
    float finalHeight = data.uniformScale * data.heightScale;

    printf("  -> Финальный масштаб: Ширина[%.2f], Высота[%.2f]\n", finalWidth, finalHeight);

    // Здесь идет связка с твоими инструментами из Tools/
    if (strcmp(toolName, "cursor.c") == 0) {
        // Передаем данные в логику курсора
    } else if (strcmp(toolName, "fontmanager.c") == 0) {
        // Передаем данные в логику шрифтов (наши безумные видео-буквы)
    } else if (strcmp(toolName, "window_geometry.c") == 0) {
        // Растягиваем рамки окон и эффекты
    }
}

// Эмуляция отрисовки нижней панели
void RenderTransformPanel(TransformData *data) {
    printf("\n--- ПАНЕЛЬ ПАРАМЕТРОВ: МАСШТАБ ---\n");
    printf("[ Ползунок: ОБЩИЙ РАЗМЕР ] <---[---O---]---> (%.1f)\n", data->uniformScale);
    
    if (data->isAdvanced) {
        printf("\n  [ ДОПОЛНИТЕЛЬНО ]:\n");
        printf("  - Масштаб ШИРИНЫ: [--O-------] (%.1f)\n", data->widthScale);
        printf("  - Масштаб ВЫСОТЫ: [-------O--] (%.1f)\n", data->heightScale);
    } else {
        printf("\n  [ Кнопка: Показать дополнительно ]\n");
    }
}
