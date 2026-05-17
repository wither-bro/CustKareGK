// Позиционирование по вертикали (Ось Y)
// Сдвигаем инструмент на уровень третьего столбика (ячейки)
int column_index = 3;
int row_height = 80; // Высота одной ячейки в пикселях

void set_column_position() {
    // Рассчитываем Y так, чтобы курсор встал ровно в 3-й слот
    int target_y = (column_index - 1) * row_height;
    render_at_y(target_y);
}
