#ifndef HELLO1_H
#define HELLO1_H

#include <linux/list.h>
#include <linux/ktime.h>

/* Експортована функція */
void print_hello(int count);

/* Структура для списку */
struct hello_entry {
    struct list_head list;
    ktime_t time_start;
    ktime_t time_end;
};

#endif // HELLO1_H
