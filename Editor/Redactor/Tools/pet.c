#include <windows.h>
#include <string.h>
#include <stdio.h>

// Структура для настроек ИИ питомца
typedef struct {
    int walkTime;    // Сколько секунд пет ходит/бегает
    int idleTime;    // Сколько секунд пет стоит/отдыхает
    int canSpeak;    // Умеет ли говорить/издавать звуки (1 - да, 0 - нет)
} PetIntellect;

// Функция для сохранения "мозгов" питомца в файл конфигурации
BOOL SavePetIntellect(const char* targetDir, PetIntellect intel) {
    char configPath[MAX_PATH] = {0};
    snprintf(configPath, sizeof(configPath), "%spet_brain.cfg", targetDir);

    FILE* file = fopen(configPath, "w");
    if (file == NULL) return FALSE;

    // Записываем настройки ИИ в простом и понятном для любого движка формате
    fprintf(file, "WALK_TIME=%d\n", intel.walkTime);
    fprintf(file, "IDLE_TIME=%d\n", intel.idleTime);
    fprintf(file, "CAN_SPEAK=%d\n", intel.canSpeak);

    fclose(file);
    return TRUE;
}

// ГЛАВНЫЙ ИНСТРУМЕНТ: Импорт питомца и его кастомизация
// sourceVisual — путь к фото/видео питомца
// sourceAudio  — путь к файлу звука (любой формат)
// targetDir    — папка ассетов пета (например, "Editor/Redactor/Assets/Pet/")
BOOL ImportPet(const char* sourceVisual, const char* sourceAudio, const char* targetDir, PetIntellect intel) {
    
    // Создаем элитную отдельную папку чисто под питомца
    CreateDirectoryA(targetDir, NULL);

    // 1. Импортируем визуал (кадр или видео анимации)
    if (sourceVisual && strlen(sourceVisual) > 0) {
        const char* ext = strrchr(sourceVisual, '.');
        char visualDest[MAX_PATH] = {0};
        snprintf(visualDest, sizeof(visualDest), "%spet_visual%s", targetDir, ext ? ext : ".mp4");
        CopyFileA(sourceVisual, visualDest, FALSE);
    }

    // 2. Импортируем звук (мяуканье, голос, эффекты)
    if (sourceAudio && strlen(sourceAudio) > 0) {
        const char* ext = strrchr(sourceAudio, '.');
        char audioDest[MAX_PATH] = {0};
        snprintf(audioDest, sizeof(audioDest), "%spet_voice%s", targetDir, ext ? ext : ".mp3");
        CopyFileA(sourceAudio, audioDest, FALSE);
    }

    // 3. Зашиваем интеллект в конфиг
    return SavePetIntellect(targetDir, intel);
}
