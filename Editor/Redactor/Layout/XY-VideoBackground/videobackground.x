// Горизонталь для Видео-Фона
float anchor_x = 0.0f; // Прижимаем влево

void align_video_bg_left() {
    // Иконка videobg.svg встает в левый ряд
    set_element_x("videobg.svg", anchor_x);
}
