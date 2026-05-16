#include <stdio.h>

// Подключаем данные из соседней папки Settings
// (В реальности здесь будут указатели на переменные из transform_settings.c, rotation_settings.c и т.д.)

typedef struct {
    float currentScale;
    float currentAngle;
    char currentText[128];
    unsigned int currentColor;
    int hasVideoMask;
} PreviewState;

// ГЛАВНЫЙ ЦИКЛ ПРЕДПРОСМОТРА (Обновляется каждый кадр)
void UpdateLivePreview(PreviewState *state) {
    // 1. Очистка окна предпросмотра
    // 2. Считывание данных из нижних панелей (Properties/Settings/)
    
    printf("\n[ LIVE PREVIEW WINDOW ]\n");
    printf("------------------------------------------\n");
    
    // Визуализация объекта (Курсор, Пет или Окно)
    printf(" ОБЪЕКТ: [ ● ] \n"); 
    printf(" СТАТУС: \n");
    printf("  - Масштаб: %.2f (Шире/Выше: OK)\n", state->currentScale);
    printf("  - Поворот: %.1f°\n", state->currentAngle);
    printf("  - Цвет: #%06X\n", state->currentColor);
    
    // Отрисовка того самого кастомного текста
    if (strlen(state->currentText) > 0) {
        printf("  - ТЕКСТ: \"%s\" ", state->currentText);
        if (state->hasVideoMask) printf("[С ВИДЕО-ЭФФЕКТОМ ВНУТРИ]");
        printf("\n");
    }

    // Отрисовка рамок окон (твоя фича с маскированием)
    printf("  - РАМКИ: [Медиа-файл наложен и обрезан по краям окна]\n");
    
    printf("------------------------------------------\n");
    printf(" [ Статус: Ожидание изменений в параметрах... ]\n");
}

// Функция мгновенного отклика (Callback)
void OnParameterChanged() {
    // Как только юзер дернул ползунок в Settings, вызывается эта функция
    // и Live Preview тут же перерисовывает объект.
    printf("[Preview] Данные получены! Обновляю картинку...\n");
}
