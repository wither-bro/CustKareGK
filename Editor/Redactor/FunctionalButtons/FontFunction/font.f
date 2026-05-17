// Логика кнопки Fonts
function on_click() {
    // 1. Обращаемся к менеджеру шрифтов
    import_logic("fontmanager.c");
    
    // 2. Открываем список установленных шрифтов
    show_font_picker();
    
    // 3. При выборе — меняем шрифт текста в проекте
    if (on_font_selected()) {
        apply_font_to_ui(selected_font_id);
        // Обновляем ник кнопки (чтобы в FontName.txt подставилось новое имя)
        update_button_nickname(); 
    }
}
