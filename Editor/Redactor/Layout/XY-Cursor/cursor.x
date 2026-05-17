// Позиционирование по горизонтали (Ось X)
// Прижимаем иконку к левому краю контейнера
float anchor_x = 0.0f; // 0.0 — это крайний левый угол

void align_left() {
    display_element("cursor.svg", anchor_x);
}
