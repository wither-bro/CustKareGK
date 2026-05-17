// Горизонталь для Шрифтов
float anchor_x = 0.0f; // Левый край

void align_font_left() {
    // Иконка font.svg (или ttf.svg) в левый ряд
    set_element_x("font.svg", anchor_x);
}
