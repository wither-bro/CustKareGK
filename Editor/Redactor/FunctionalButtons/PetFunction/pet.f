// Логика кнопки Pet
function on_click() {
    // 1. Обращаемся к основному скрипту
    import_logic("pet.c");
    
    // 2. Открываем окно выбора питомца
    open_menu("PetSelection");
    
    // 3. Загружаем превью (из твоих ассетов)
    load_preview_icons("assets/pets/");
    
    // 4. Ждем выбора пользователя
    if (user_select_item()) {
        apply_pet_to_editor(selected_id);
        close_menu();
    }
}

// Состояние кнопки
void update_state() {
    // Если питомец уже выбран, подсвечиваем кнопку
    if (is_pet_active()) {
        set_button_glow(true);
    }
}
