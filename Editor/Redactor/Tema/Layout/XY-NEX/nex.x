/* nex.x - Горизонтальное позиционирование поля ввода кода */

int nex_field_width = 170;  // Поле чуть уже меша для красоты
int nex_field_start_x = 15; // Отступ слева

// Координата текста внутри поля (отступ для курсора ввода)
int nex_text_padding_x = 5;

int get_nex_input_x() {
    return nex_field_start_x;
}
