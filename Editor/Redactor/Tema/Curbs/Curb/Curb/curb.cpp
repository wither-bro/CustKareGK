#include <iostream>

/* Файл: Tema/Curbs/Curb/Curb/curb.cpp
   Логика отрисовки разделительных бордюров для интерфейса палитры.
*/

class InterfaceCurb {
public:
    // Параметры бордюра
    const char* curb_color = "#808080"; // Серый цвет бордюра
    const int curb_thickness = 1;       // Толщина в 1 пиксель

    // Функция отрисовки бордюра над NEX-кодом
    void drawCurbAboveNEX(int x, int y, int width) {
        // Рисуем горизонтальную серую линию
        render_line(x, y, x + width, y, curb_color, curb_thickness);
    }

    // Функция отрисовки бордюра над рекомендациями
    void drawCurbAboveRecommendations(int x, int y, int width) {
        // Рисуем горизонтальную серую линию
        render_line(x, y, x + width, y, curb_color, curb_thickness);
    }
    
    // Системный вызов для рендера всех разделителей
    void renderAllCurbs(int menu_x, int menu_width, int rec_y, int nex_y) {
        // 1. Бордюр над рекомендациями (отделяет их от Меша)
        drawCurbAboveRecommendations(menu_x, rec_y - 5, menu_width);
        
        // 2. Бордюр над NEX-кодом (отделяет его от рекомендаций)
        drawCurbAboveNEX(menu_x, nex_y - 5, menu_width);
    }
};
