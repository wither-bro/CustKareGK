// Логика кнопки Background
function on_click() {
    // 1. Подключаем основной скрипт фона
    import_logic("backround.c");
    
    // 2. Вызываем галерею фоновых изображений (твои "цветочки" и прочее)
    open_gallery("Background_List");
    
    // 3. Если юзер выбрал картинку, меняем фон в редакторе
    if (on_item_picked()) {
        set_editor_wallpaper(picked_image_path);
        refresh_preview();
    }
}
