// Позиционирование по вертикали (Ось Y) для инструмента Pet
// Сажаем его на 4-й столбик (строку)

int column_index = 4; // Питомец идет 4-м по счету
int row_height = 80;  // Та же высота ячейки, что и у курсора

void set_pet_column() {
    // Рассчитываем Y: (4 - 1) * 80 = 240px от верха меню
    int target_y = (column_index - 1) * row_height;
    
    render_at_y("pet.svg", target_y);
    render_text_at_y("Pet", target_y); // Текст тоже на эту высоту
}
