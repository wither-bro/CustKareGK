// Вертикаль для Шрифтов (5-й столбик)
int column_index = 5; 
int row_height = 80; 

void set_font_column() {
    // (5 - 1) * 80 = 320px от верха меню
    int target_y = (column_index - 1) * row_height;
    
    render_at_y("font.svg", target_y);
    render_text_at_y("Font Manager", target_y);
}
