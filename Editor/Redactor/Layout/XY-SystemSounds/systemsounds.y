// Вертикаль для Звуков (6-й столбик)
int column_index = 6; 
int row_height = 80; 

void set_sounds_column() {
    // (6 - 1) * 80 = 400px от верха меню
    int target_y = (column_index - 1) * row_height;
    
    render_at_y("sounds.svg", target_y);
    render_text_at_y("System Sounds", target_y);
}
