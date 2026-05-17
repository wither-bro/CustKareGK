/* curb.x - Координаты бордюров по горизонтали */

#include <stdio.h>

// Структура для хранения горизонтальных данных бордюра
struct CurbLayoutX {
    int start_x;    // Начальная точка (лево)
    int end_x;      // Конечная точка (право)
    int offset;     // Отступ от края окна
};

// Инициализация координат
struct CurbLayoutX layout_x = {
    .offset = 10,
    .start_x = 10,
    .end_x = 190  // Предположим, ширина окна 200
};

// Функция для получения актуальной ширины линии
int get_curb_width(int window_width) {
    // Автоматически растягиваем линию под размер окна палитры
    layout_x.end_x = window_width - layout_x.offset;
    return layout_x.end_x - layout_x.start_x;
}
