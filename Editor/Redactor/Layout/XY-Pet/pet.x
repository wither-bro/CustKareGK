// Позиционирование по горизонтали (Ось X) для инструмента Pet
// Прижимаем иконку pet.svg к левой границе

float anchor_x = 0.0f; // Левый край

void align_pet_left() {
    // Ставим иконку питомца в левую часть ячейки
    set_element_position_x("pet.svg", anchor_x);
    
    // Здесь же логика поворота иконки по X, если нужно
    float rotation_x = 0.0f;
    apply_rotation_x("pet.svg", rotation_x);
}
