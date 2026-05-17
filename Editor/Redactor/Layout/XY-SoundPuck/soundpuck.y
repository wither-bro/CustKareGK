// Вертикаль для SoundPuck (7-й столбик)
int column_index = 7; 
int row_height = 80; 

void set_audio_column() {
    // (7 - 1) * 80 = 480px от верха меню
    int target_y = (column_index - 1) * row_height;
    
    render_at_y("audio.svg", target_y);
    render_text_at_y("Sound Puck", target_y);
}
