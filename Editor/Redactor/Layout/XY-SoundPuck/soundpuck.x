// Горизонталь для SoundPuck
float anchor_x = 0.0f; // Левый край

void align_audio_left() {
    // Используем твою иконку audio.svg
    set_element_x("audio.svg", anchor_x);
}
