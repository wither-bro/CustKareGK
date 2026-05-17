// Логика кнопки Cursor (Теперь со всеми форматами)
function on_click() {
    import_logic("cursor.c");
    
    // Теперь разрешаем всё, что он любит
    open_asset_picker({
        filter: ["*.png", "*.ani", "*.cur", "*.svg"]
    });
    
    if (new_cursor_selected()) {
        // Загружаем выбранный файл (будь то анимация или статика)
        load_cursor_from_file(selected_file);
        set_cursor_active(true);
    }
}
