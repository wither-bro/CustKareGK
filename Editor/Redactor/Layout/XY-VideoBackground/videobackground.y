// Вертикаль для Видео-Фона (2-й столбик)
int column_index = 2; 
int row_height = 80; // Твой стандарт высоты

void set_video_bg_column() {
    // (2 - 1) * 80 = 80px от верха
    int target_y = (column_index - 1) * row_height;
    
    render_at_y("videobg.svg", target_y);
    render_text_at_y("Video Background", target_y);
}
