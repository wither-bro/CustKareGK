#include <iostream>
#include <vector>
#include <string>

struct RecommendedColor {
    std::string name;
    std::string hex;
};

class ColorRecommendations {
public:
    // Список рекомендованных цветов по твоему списку
    std::vector<RecommendedColor> getList() {
        return {
            {"Белый", "#FFFFFF"},
            {"Черный", "#000000"},
            {"Красный", "#FF0000"},
            {"Синий", "#0000FF"},
            {"Зеленый", "#008000"},
            {"Желтый", "#FFFF00"},
            {"Розовый", "#FFC0CB"},
            {"Оранжевый", "#FFA500"},
            {"Бежевый", "#F5F5DC"},
            {"Бордовый", "#800000"},
            {"Серебристый", "#C0C0C0"},
            {"Золотой", "#FFD700"},
            {"Серый", "#808080"}
        };
    }

    void renderUI() {
        auto list = getList();
        std::cout << "--- Рекомендованные цвета ---" << std::endl;
        
        for (const auto& color : list) {
            // Здесь будет код отрисовки кликабельной кнопки/кружка
            // При нажатии вызывается функция из nex.cpp или colors.cpp
            std::cout << "[" << color.name << " (" << color.hex << ")] ";
        }
        std::cout << "\n----------------------------" << std::endl;
    }

    // Функция, которая срабатывает при выборе рекомендации
    void onSelectRecommendation(std::string selectedHex) {
        // Мгновенная передача в систему NEX-кодов для применения темы
        apply_to_editor(selectedHex);
    }
};
