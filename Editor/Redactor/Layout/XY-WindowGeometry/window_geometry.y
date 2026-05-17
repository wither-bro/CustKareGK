// Вертикаль для Window Geometry (8-й столбик)
int column_index = 8; 
int row_height = 80; 

void set_window_column() {
    // (8 - 1) * 80 = 560px от верха меню
    int target_y = (column_index - 1) * row_height;
    
    render_at_y("window.svg", target_y);
    render_text_at_y("Window Geometry", target_y);
}
