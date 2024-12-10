// SPDX-License-Identifier: Dual BSD/GPL
/*
 * Linux Kernel Module: Hello1 with export for lab 5
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include "../inc/hello1.h"

MODULE_AUTHOR("Korbut Mykhailo IO-23");
MODULE_DESCRIPTION("Hello1 module exporting print_hello() for lab 5");
MODULE_LICENSE("Dual BSD/GPL");

/* Глобальна змінна - голова двозв'язного списку */
static LIST_HEAD(hello_list);

/* 
 * Реалізація функції друку, яка:
 * - Виділяє пам'ять для запису про кожен виклик.
 * - Фіксує час початку та завершення друку.
 * - Додає запис у список.
 */
void print_hello(int count)
{
    int i;
    struct hello_entry *entry;

    for (i = 0; i < count; i++) {
        entry = kmalloc(sizeof(*entry), GFP_KERNEL);
        if (!entry) {
            pr_err("Memory allocation failed for entry\n");
            return;
        }

        entry->time_start = ktime_get();
        pr_info("Hello, world! (%d)\n", i + 1);
        entry->time_end = ktime_get();

        list_add_tail(&entry->list, &hello_list);
    }
}

EXPORT_SYMBOL(print_hello);

/* 
 * Функція завершення модуля:
 * - Обчислює тривалість кожного виклику друку.
 * - Звільняє пам'ять для кожного запису.
 */
static void __exit hello1_exit(void)
{
    struct hello_entry *entry, *tmp;

    list_for_each_entry_safe(entry, tmp, &hello_list, list) {
        pr_info("Event duration: %llu ns\n", 
                ktime_to_ns(entry->time_end) - ktime_to_ns(entry->time_start));
        list_del(&entry->list);
        kfree(entry);
    }
}

/* Ініціалізація модуля */
static int __init hello1_init(void)
{
    pr_info("Hello1 module loaded\n");
    return 0;
}

module_init(hello1_init);
module_exit(hello1_exit);
