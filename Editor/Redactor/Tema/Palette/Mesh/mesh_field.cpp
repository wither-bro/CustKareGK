#include <iostream>

class ColorMesh {
public:
    // Параметры сетки
    const int mesh_size = 200; // Квадрат 200x200 пикселей
    float cursor_x, cursor_y;  // Позиция шарика

    void renderMesh() {
        // Отрисовка двухмерного градиента:
        // Х-ось: от белого к выбранному тону (Hue)
        // Y-ось: от цветного к черному
        draw_gradient_rect(0, 0, mesh_size, mesh_size);
        
        // Отрисовка "шарика" выбора
        draw_selector_circle(cursor_x, cursor_y);
    }

    // Вычисление цвета в зависимости от того, где стоит шарик
    std::string getColorAtCursor() {
        // Математика преобразования координат в NEX-код
        // Насыщенность = x / mesh_size
        // Яркость = 1.0 - (y / mesh_size)
        return calculate_hsv_to_nex(current_hue, cursor_x/mesh_size, 1.0f - cursor_y/mesh_size);
    }

    void onMouseDrag(float x, float y) {
        // Ограничиваем движение шарика внутри квадрата
        cursor_x = clamp(x, 0, mesh_size);
        cursor_y = clamp(y, 0, mesh_size);
        
        // Мгновенно передаем цвет в систему NEX-Codes
        std::string new_color = getColorAtCursor();
        apply_theme_realtime(new_color);
    }
};
