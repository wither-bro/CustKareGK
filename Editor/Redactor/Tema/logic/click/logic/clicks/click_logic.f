// [ LOGIC FOR LOONSUN.SVG ]

function on_init() {
    // Подгружаем координаты из файлов .x и .y, которые мы обсуждали
    this.x = load_val("icon.x");
    this.y = load_val("icon.y");
}

function on_click() {
    // 1. При клике вызываем окно редактора цветов (Color Picker)
    // Мы можем вызвать системное окно или наше кастомное
    open_color_editor(); 
    
    // 2. После выбора цвета передаем его в theme_manager.c
    if (user_has_selected_color()) {
        unsigned int new_color = get_selected_hex();
        
        // Передаем цвет в главный менеджер
        call theme_manager.SetCustomTheme(new_color);
        
        // И запускаем принудительное обновление через сигналы
        call signals.force_update_ui();
    }
}

function on_hover() {
    // Эффект при наведении (например, меняем прозрачность)
    set_opacity(0.8);
}
