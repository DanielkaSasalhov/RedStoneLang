#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/signals.h"
#include "../includes/state.h"

#define DEBUG 0

void initialize_keywords(char *line) {
    if (line == NULL) return;
    char keyword[64] = {0};
    char arg1[64] = {0};
    char arg2[64] = {0};
    char arg3[64] = {0};
    int num_args = sscanf(line, "%63s %63s %63s %63s", keyword, arg1, arg2, arg3);

    if (strcmp(keyword, "input") == 0 && num_args >= 3) {
        int value = (strcmp(arg2, "1") == 0) ? 1 : 0;
        set_signal(arg1, value);
#if DEBUG
        printf("[DEBUG][INPUT] %s = %d\n", arg1, value);
#endif
    } else if (strcmp(keyword, "output") == 0 && num_args >= 2) {
        int value = get_signal(arg1);
        printf("[OUTPUT] %s = %d\n", arg1, value);
#if DEBUG
        printf("[DEBUG][OUTPUT] %s = %d\n", arg1, value);
#endif
    } else if (strcmp(keyword, "power") == 0 && num_args >= 2) {
        power_on = 1;
        set_signal(arg1, 1);
#if DEBUG
        printf("[DEBUG][POWER] %s включено.\n", arg1);
#endif
    } else if (strcmp(keyword, "wire") == 0 && num_args >= 3) {
        int value = get_signal(arg1);
        set_signal(arg2, value);
#if DEBUG
        printf("[DEBUG][WIRE] %s -> %s (%d)\n", arg1, arg2, value);
#endif
        wire_connected++;
    } else if (strcmp(keyword, "torch") == 0 && num_args >= 2) {
        torch_active = 1;
        set_signal(arg1, 1);
#if DEBUG
        printf("[DEBUG][TORCH] %s активирован.\n", arg1);
#endif
    } else if (strcmp(keyword, "repeater") == 0 && num_args >= 2) {
        int value = get_signal(arg1);
        set_signal(arg1, value);
#if DEBUG
        printf("[DEBUG][REPEATER] %s значение: %d\n", arg1, value);
#endif
        repeater_count++;
    } else if (strcmp(keyword, "comparator") == 0 && num_args >= 4) {
        int va = get_signal(arg1);
        int vb = get_signal(arg2);
        int res = (va == vb) ? 1 : 0;
        set_signal(arg3, res);
#if DEBUG
        printf("[DEBUG][COMPARATOR] %s(%d) == %s(%d) => %s = %d\n", arg1, va, arg2, vb, arg3, res);
#endif
    } else if (strcmp(keyword, "button") == 0 && num_args >= 2) {
        button_pressed = 1;
        set_signal(arg1, 1);
#if DEBUG
        printf("[DEBUG][BUTTON] %s нажата.\n", arg1);
#endif
    } else {
        printf("[ERROR] SYNTAX ERROR: %s\n", line);
    }
}

void process_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия файла");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        // Пропуск строк-комментариев и пустых строк
        char *trimmed = line;
        while (*trimmed == ' ' || *trimmed == '\t') ++trimmed;
        if (trimmed[0] == '#' || trimmed[0] == '\0') continue;
        initialize_keywords(trimmed);
    }
    fclose(file);
}