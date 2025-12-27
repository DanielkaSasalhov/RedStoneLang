#ifndef SIGNALS_H
#define SIGNALS_H

int find_signal(const char *name);
void set_signal(const char *name, int value);
int get_signal(const char *name);

#endif // SIGNALS_H
