#include <stdio.h>
#include <string.h>

// Максимальное количество замен, которые может сделать юзер
#define MAX_REPLACEMENTS 100

typedef struct {
    char original[128];    // Что ищем (напр. "Recycle Bin")
    char replacement[128]; // На что меняем (напр. "Trash Can")
    int isActive;          // Включена ли замена сейчас
} StringPatch;

// Наш массив всех замен
StringPatch userDictionary[MAX_REPLACEMENTS];
int patchCount = 0;

// ФУНКЦИЯ: Добавление новой пары слов через Поле Ввода
void AddNewStringPatch(const char* oldText, const char* newText) {
    if (patchCount < MAX_REPLACEMENTS) {
        strcpy(userDictionary[patchCount].original, oldText);
        strcpy(userDictionary[patchCount].replacement, newText);
        userDictionary[patchCount].isActive = 1;
        
        printf("[Patcher] Добавлена новая цель: %s -> %s\n", oldText, newText);
        patchCount++;
    }
}

// ФУНКЦИЯ: Отрисовка тех самых полей ввода (Input Fields)
void RenderPatcherUI() {
    printf("\n--- РЕДАКТОР СИСТЕМНЫХ НАДПИСЕЙ ---\n");
    printf(" [ Input 1 ]: Введите системное слово... \n");
    printf(" [ Input 2 ]: Введите ваш вариант... \n");
    printf(" [ Button  ]: ЗАМЕНИТЬ НАВСЕГДА \n");
    
    printf("\n Список активных замен:\n");
    for(int i = 0; i < patchCount; i++) {
        printf("  %d. %s ===> %s [X]\n", i+1, 
               userDictionary[i].original, 
               userDictionary[i].replacement);
    }
}
