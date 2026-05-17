#include <iostream>
#include <string>
#include <map>
#include <algorithm>

class NexConverter {
private:
    // База данных названий цветов
    std::map<std::string, std::string> colorNames = {
        {"orange", "#FF9F00"},
        {"red",    "#FF0000"},
        {"pink",   "#FFC0CB"},
        {"blue",   "#0000FF"},
        {"black",  "#000000"},
        {"white",  "#FFFFFF"}
    };

public:
    // Главная функция обработки ввода
    std::string processInput(std::string input) {
        // Приводим к нижнему регистру, чтобы "RED" и "red" работали одинаково
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        // 1. Проверка: Это название цвета?
        if (colorNames.count(input)) {
            return colorNames[input];
        }

        // 2. Проверка: Это NEX-код (начинается с #)?
        if (input[0] == '#' && (input.length() == 7 || input.length() == 4)) {
            return input; // Возвращаем как валидный код
        }

        // 3. Если введено что-то непонятное
        return "#INVALID"; 
    }
};

// Мост для связи с остальным редактором
extern "C" void apply_nex_input(const char* userInput) {
    NexConverter converter;
    std::string result = converter.processInput(userInput);

    if (result != "#INVALID") {
        // Передаем результат в твой основной движок покраски colors.cpp
        // И обновляем интерфейс
        std::cout << "[NEX SYSTEM]: Применяем цвет " << result << std::endl;
    }
}
