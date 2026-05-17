/* nex.y - Вертикальное позиционирование поля ввода кода */

// Ориентируемся на нижний бордюр (curb_2_y), который у нас был на 275px
extern int curb_2_y;

int nex_field_height = 25; // Высота строки ввода
int nex_field_start_y = 290; // Начинаем через 15px после бордюра

// Конечная точка всего интерфейса палитры
int palette_window_total_height = 330; 

int get_nex_input_y() {
    return nex_field_start_y;
}
