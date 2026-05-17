// Вертикаль для фона (1-й столбик)
int column_index = 1;
int row_height = 80;

void set_bg_column() {
    // (1 - 1) * 80 = 0px (самый верх меню)
    int target_y = (column_index - 1) * row_height;
    
    render_at_y("background.svg", target_y);
    render_text_at_y("Backgrounds", target_y);
}
