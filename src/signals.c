#include <string.h>
#include "../includes/signals.h"
#define MAX_SIGNALS 128

typedef struct {
    char name[64];
    int value;
} Signal;

static Signal signals[MAX_SIGNALS];
static int signal_count = 0;

int find_signal(const char *name) {
    for (int i = 0; i < signal_count; ++i) {
        if (strcmp(signals[i].name, name) == 0) return i;
    }
    return -1;
}

void set_signal(const char *name, int value) {
    int idx = find_signal(name);
    if (idx == -1 && signal_count < MAX_SIGNALS) {
        idx = signal_count++;
        strncpy(signals[idx].name, name, 63);
        signals[idx].name[63] = '\0';
    }
    if (idx != -1) signals[idx].value = value;
}

int get_signal(const char *name) {
    int idx = find_signal(name);
    if (idx != -1) return signals[idx].value;
    return 0;
}
