#include <windows.h>
#include <string.h>
#include <stdio.h>

// ID мелких UI-событий для интерфейса
typedef enum {
    UI_EVENT_CLICK = 1,       // Обычный клик по кнопке
    UI_EVENT_HOVER = 2,       // Наведение курсора на элемент
    UI_EVENT_SUCCESS = 3,     // Успешное действие (например, файл сохранился)
    UI_EVENT_WARNING = 4,     // Всплывающее предупреждение
    UI_EVENT_POPUP = 5        // Открытие любого диалогового окна
} UiEventID;

// Настройки конкретного звука в паке
typedef struct {
    UiEventID eventId;
    float volume;             // Громкость (0.0 - 1.0)
    float pitch;              // Тональность/Скорость (например, 1.0 - нормальный, 1.2 - чуть писклявее и быстрее)
} UiSoundConfig;

// ГЛАВНЫЙ ИНСТРУМЕНТ ДЛЯ СБОРКИ ЗВУКОВЫХ ПАКОВ Интерфейса
// sourcePath — откуда берем аудио (MP3, WAV)
// targetDir  — папка ассетов (например, "Editor/Redactor/Assets/SoundPacks/")
// packName   — имя пака, который собирает юзер (например, "Cyberpunk", "Retro_8Bit", "Memes")
BOOL ImportUiSoundToPack(const char* sourcePath, const char* targetDir, const char* packName, UiSoundConfig config) {
    if (sourcePath == NULL || strlen(sourcePath) == 0) return FALSE;

    // 1. Формируем путь к конкретному паку: "Assets/SoundPacks/Cyberpunk/"
    char fullPackDir[MAX_PATH] = {0};
    snprintf(fullPackDir, sizeof(fullPackDir), "%s%s/", targetDir, packName);

    // Создаем эту папку (сначала общую, потом подпапку пака)
    CreateDirectoryA(targetDir, NULL);
    CreateDirectoryA(fullPackDir, NULL);

    // 2. Определяем имя UI-триггера
    char uiEventName[32];
    switch (config.eventId) {
        case UI_EVENT_CLICK:   strcpy(uiEventName, "click"); break;
        case UI_EVENT_HOVER:   strcpy(uiEventName, "hover"); break;
        case UI_EVENT_SUCCESS: strcpy(uiEventName, "success"); break;
        case UI_EVENT_WARNING: strcpy(uiEventName, "warning"); break;
        case UI_EVENT_POPUP:   strcpy(uiEventName, "popup"); break;
        default:               strcpy(uiEventName, "custom"); break;
    }

    // 3. Выцепляем расширение (.wav, .mp3)
    const char* dot = strrchr(sourcePath, '.');
    char ext[16] = "wav";
    if (dot && dot != sourcePath) {
        strncpy(ext, dot + 1, sizeof(ext) - 1);
    }

    // 4. Финальный путь к аудиофайлу внутри пака
    char finalAudioPath[MAX_PATH] = {0};
    snprintf(finalAudioPath, sizeof(finalAudioPath), "%s%s.%s", fullPackDir, uiEventName, ext);

    // 5. Копируем исходный звук в папку пака
    if (!CopyFileA(sourcePath, finalAudioPath, FALSE)) {
        return FALSE;
    }

    // 6. ГЕНЕРИРУЕМ КОНФИГ ДЛЯ КОНКРЕТНОГО ЗВУКА (.cfg)
    char configPath[MAX_PATH] = {0};
    snprintf(configPath, sizeof(configPath), "%s%s.cfg", fullPackDir, uiEventName);

    FILE* file = fopen(configPath, "w");
    if (file == NULL) return FALSE;

    fprintf(file, "[UiSound]\n");
    fprintf(file, "PACK_NAME=%s\n", packName);
    fprintf(file, "EVENT=%s\n", uiEventName);
    fprintf(file, "FILE=%s.%s\n", uiEventName, ext);
    fprintf(file, "VOLUME=%.2f\n", config.volume);
    fprintf(file, "PITCH=%.2f\n", config.pitch); // Передаем тональность!

    fclose(file);
    return TRUE;
}
