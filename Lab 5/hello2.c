// SPDX-License-Identifier: Dual BSD/GPL
/*
 * Linux Kernel Module: Hello2 for lab 5
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include "../inc/hello1.h"

MODULE_AUTHOR("Korbut Mykhailo IO-23");
MODULE_DESCRIPTION("Hello2 module using print_hello() from hello1 for lab 5");
MODULE_LICENSE("Dual BSD/GPL");

/* Параметр для визначення кількості викликів */
static uint repeat = 1;
module_param(repeat, uint, 0444);
MODULE_PARM_DESC(repeat, "Number of times to call print_hello()");

/* 
 * Ініціалізація модуля:
 * - Перевіряє коректність параметра repeat.
 * - Викликає функцію print_hello() з модуля hello1.
 */
static int __init hello2_init(void)
{
    if (repeat == 0 || (repeat >= 5 && repeat <= 10)) {
        pr_warn("Warning: repeat is 0 or between 5 and 10\n");
    } else if (repeat > 10) {
        pr_err("Error: repeat is greater than 10\n");
        return -EINVAL;
    }

    print_hello(repeat);
    return 0;
}

/* Завершення модуля */
static void __exit hello2_exit(void)
{
    pr_info("Hello2 module unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
