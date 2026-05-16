#include <stdio.h>

typedef struct {
    float volume;       // 0.0 - 1.0 (ползунок)
    int mute;           // Кнопка "выключить звук"
    float fadeTime;     // Плавное появление звука
} AudioSettingsData;

void SetGlobalVolume(const char* toolTarget, AudioSettingsData data) {
    printf("[Audio] Цель: %s | Уровень громкости: %.0f%%\n", toolTarget, data.volume * 100);
    // Отправляем данные в микшер твоего движка
}
