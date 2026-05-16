#include <windows.h>
#include <string.h>
#include <stdio.h>

// Глобальные ID для системных событий
typedef enum {
    SYS_EVENT_STARTUP = 1,     // Запуск системы / Активация ноута
    SYS_EVENT_SHUTDOWN = 2,    // Выключение / Завершение работы
    SYS_EVENT_LOW_BATTERY = 3, // Критический уровень батареи
    SYS_EVENT_USB_IN = 4,      // Подключение флешки / девайса
    SYS_EVENT_USB_OUT = 5      // Отключение девайса
} SystemEventID;

// Структура конфигурации системного звука
typedef struct {
    SystemEventID eventId;
    float volume;       // Громкость от 0.0 до 1.0
    int executeAsync;   // Исполнять асинхронно (1 - играть в фоне и не вешать систему, 0 - ждать окончания звука)
} SystemSoundConfig;

// ГЛАВНЫЙ БЭКЕНД-ИНСТРУМЕНТ СИСТЕМНЫХ ЗВУКОВ
// sourcePath — путь к исходному треку пользователя (MP3, WAV, OGG)
// targetDir  — папка глобальных системных ассетов (например, "Editor/Redactor/Assets/SystemAudio/")
BOOL ImportSystemSound(const char* sourcePath, const char* targetDir, SystemSoundConfig config) {
    if (sourcePath == NULL || strlen(sourcePath) == 0) return FALSE;

    // 1. Создаем глобальную системную папку аудио, если её ещё нет
    CreateDirectoryA(targetDir, NULL);

    // 2. Определяем имя системного триггера
    char sysEventName[64];
    switch (config.eventId) {
        case SYS_EVENT_STARTUP:     strcpy(sysEventName, "sys_startup"); break;
        case SYS_EVENT_SHUTDOWN:    strcpy(sysEventName, "sys_shutdown"); break;
        case SYS_EVENT_LOW_BATTERY: strcpy(sysEventName, "sys_low_battery"); break;
        case SYS_EVENT_USB_IN:      strcpy(sysEventName, "sys_device_in"); break;
        case SYS_EVENT_USB_OUT:     strcpy(sysEventName, "sys_device_out"); break;
        default:                    strcpy(sysEventName, "sys_unknown"); break;
    }

    // 3. Вытаскиваем расширение исходного файла
    const char* dot = strrchr(sourcePath, '.');
    char ext[16] = "wav"; // дефолт
    if (dot && dot != sourcePath) {
        strncpy(ext, dot + 1, sizeof(ext) - 1);
    }

    // 4. Формируем финальный путь для аудиофайла
    char finalAudioPath[MAX_PATH] = {0};
    snprintf(finalAudioPath, sizeof(finalAudioPath), "%s%s.%s", targetDir, sysEventName, ext);

    // 5. Копируем файл в систему с перезаписью (FALSE)
    if (!CopyFileA(sourcePath, finalAudioPath, FALSE)) {
        return FALSE; // Если файл заблокирован системой или нет прав
    }

    // 6. ГЕНЕРИРУЕМ ЭЛИТНЫЙ СИСТЕМНЫЙ КОНФИГ (.cfg)
    // Этот файл прочитает системный демон (служба запуска) и применит настройки
    char configPath[MAX_PATH] = {0};
    snprintf(configPath, sizeof(configPath), "%s%s.cfg", targetDir, sysEventName);

    FILE* file = fopen(configPath, "w");
    if (file == NULL) return FALSE;

    fprintf(file, "[SystemSoundEvent]\n");
    fprintf(file, "EVENT_NAME=%s\n", sysEventName);
    fprintf(file, "FILE_PATH=%s.%s\n", sysEventName, ext);
    fprintf(file, "VOLUME=%.2f\n", config.volume);
    fprintf(file, "ASYNC=%d\n", config.executeAsync);

    fclose(file);
    return TRUE;
}
