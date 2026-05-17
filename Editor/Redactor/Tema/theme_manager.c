#include <stdio.h>

// Храним текущий цвет в формате HEX (например, 0xFF5733)
unsigned int custom_ui_color = 0x0000FF; // По умолчанию синий

void SetCustomTheme(unsigned int hex_color) {
    custom_ui_color = hex_color;
    
    // Применяем цвет ко всем элементам интерфейса
    // (Кнопки, рамки Preview, текст в NameButtons)
    ApplyGlobalStyle(custom_ui_color);
    
    // Отправляем сигнал в наш MasterScript, что визуальная часть обновилась
    // Чтобы даже "Лунное солнце" могло подсветиться новым цветом
    printf("[Theme] Цвет изменен на: #%06X\n", custom_ui_color);
}
