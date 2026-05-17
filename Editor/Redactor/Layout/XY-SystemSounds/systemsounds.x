// Горизонталь для Системных Звуков
float anchor_x = 0.0f; // Четко влево

void align_sounds_left() {
    // Иконка sounds.svg (или speaker.svg) в левый ряд
    set_element_x("sounds.svg", anchor_x);
}
