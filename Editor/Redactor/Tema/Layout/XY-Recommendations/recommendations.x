/* recommendations.x - Горизонтальная сетка кнопок */

int rec_start_x = 15;      // Отступ первого кружка от левого края
int rec_spacing_x = 25;    // Расстояние между центрами кружков
int rec_button_width = 20; // Диаметр самого кружка/квадрата цвета

// Функция расчета X для конкретного цвета по счетчику (0, 1, 2...)
int get_recommendation_x(int index) {
    // Рассчитываем позицию: отступ + (индекс цвета * шаг)
    return rec_start_x + (index * rec_spacing_x);
}
