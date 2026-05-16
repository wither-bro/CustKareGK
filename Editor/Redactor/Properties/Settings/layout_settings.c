#include <stdio.h>

typedef struct {
    int posX;          // Позиция по горизонтали
    int posY;          // Позиция по вертикали
    int anchorPoint;   // 1 - Лево/Верх, 2 - Центр, 3 - Право/Низ
    int layerOrder;    // Слой (Z-index): кто выше — Пет или окно?
} LayoutData;

// ФУНКЦИЯ: Привязка расположения к объекту
void SetObjectLocation(const char* toolName, LayoutData data) {
    printf("[Layout] Объект: %s перемещен в координаты (%d, %d)\n", toolName, data.posX, data.posY);
    
    // Если это Пет — он бежит в этот угол.
    // Если это Текст — он приклеивается к этой части экрана.
}

// Отрисовка в нижней панели
void RenderLayoutPicker() {
    printf("\n--- РАСПОЛОЖЕНИЕ (LAYOUT) ---\n");
    printf(" [ Сетка ]: [↖] [↑] [↗] \n");
    printf("            [←] [C] [→] \n");
    printf("            [↙] [↓] [↘] \n");
    printf(" [ Поля ввода ]: X: [____]  Y: [____] \n");
}
