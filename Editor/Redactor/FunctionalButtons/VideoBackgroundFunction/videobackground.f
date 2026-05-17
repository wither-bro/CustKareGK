// Логика кнопки Videobackground
function on_click() {
    // Подключаем движок видео-фонов
    import_logic("videobackground.c");
    
    // Открываем браузер видео-файлов (mp4/webm)
    open_video_browser("Assets/VideoBG/");
    
    // При выборе видео
    if (video_picked()) {
        // Запускаем превью в фоне редактора
        start_video_bg_stream(selected_video);
        play_mode(LOOP); // Цикличный повтор
    }
}
