#include <stdio.h>

typedef struct {
    float angle;            // Угол от 0 до 360
    int snapToGrid;         // Привязка к углам (0, 90, 180, 270)
    int autoRotationSpeed;  // Скорость авто-вращения (если юзер хочет, чтобы курсор крутился сам)
} RotationData;

// Привязка к инструментам
void ApplyRotation(const char* toolTarget, RotationData data) {
    printf("[Rotation] Цель: %s | Угол: %.1f градусов\n", toolTarget, data.angle);
    
    // Логика привязки:
    // fontmanager.c -> текст перевернут или под углом
    // cursor.c -> курсор смотрит в другую сторону
    // window_geometry.c -> рамки окон или эффекты наклонены
}
