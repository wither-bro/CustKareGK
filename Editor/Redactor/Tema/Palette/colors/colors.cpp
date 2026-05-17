#include <iostream>
#include <vector>
#include <string>

// Структура для хранения цвета
struct Color {
    int r, g, b;
    std::string hex;
};

class ColorPicker {
public:
    // 1. ПРЕДЛОЖЕННЫЕ ЦВЕТА (Квадратики)
    void renderPalletSquares() {
        std::vector<std::string> presets = {"#FFA500", "#FF0000", "#FFC0CB", "#0000FF"};
        for (const auto& hex : presets) {
            drawSquare(hex); // Отрисовка кликабельного квадрата
        }
    }

    // 2. ГЛАВНЫЙ КВАДРАТ (Color Field)
    // Тот самый, где "катаешь шарик"
    void renderMainGradientSquare() {
        // Логика отрисовки градиента от белого к выбранному тону
        // И захват позиции "шарика" (cursor_x, cursor_y)
        float ball_x, ball_y; 
        updateBallPosition(&ball_x, &ball_y);
        
        // Превращаем координаты шарика в HEX
        std::string selectedHex = calculateHexFromCoords(ball_x, ball_y);
        applyTint(selectedHex);
    }

    // 3. ПОДДЕРЖКА NEX (HEX) КОДОВ
    void handleHexInput(std::string input) {
        if (input[0] == '#') {
            applyTint(input); // Мгновенная перекраска
        }
    }

private:
    void applyTint(std::string hex) {
        // Отправляем команду в систему на смену цвета всех панелей редактора
        std::cout << "Editor Theme Changed to: " << hex << std::endl;
        // Здесь идет вызов твоего click_logic.f через мост
    }
};
