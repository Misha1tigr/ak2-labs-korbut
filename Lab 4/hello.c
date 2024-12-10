// SPDX-License-Identifier: Dual BSD/GPL
/*
 * Linux Kernel Module: Hello, World! with modifications for lab 4
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>

MODULE_AUTHOR("Korbut Mykhailo IO-23");
MODULE_DESCRIPTION("Modified Hello, World! module for lab 4");
MODULE_LICENSE("Dual BSD/GPL");

/* Module parameter */
static uint repeat = 1; // Default value
module_param(repeat, uint, 0444);
MODULE_PARM_DESC(repeat, "Number of times to print 'Hello, world!'");

/* Structure definition for linked list */
struct hello_entry {
    struct list_head list;
    ktime_t time;
};

/* Static list head */
static LIST_HEAD(hello_list);

/* Initialization function */
static int __init hello_init(void)
{
    int i;
    struct hello_entry *entry;

    /* Parameter validation */
    if (repeat == 0 || (repeat >= 5 && repeat <= 10)) {
        pr_warn("Warning: repeat is 0 or between 5 and 10\n");
    } else if (repeat > 10) {
        pr_err("Error: repeat is greater than 10\n");
        return -EINVAL;
    }

    /* Print messages and store timestamps in the list */
    for (i = 0; i < repeat; i++) {
        entry = kmalloc(sizeof(*entry), GFP_KERNEL);
        if (!entry)
            return -ENOMEM;

        entry->time = ktime_get();
        list_add_tail(&entry->list, &hello_list);

        pr_info("Hello, world! (%d)\n", i + 1);
    }

    return 0;
}

/* Exit function */
static void __exit hello_exit(void)
{
    struct hello_entry *entry, *tmp;

    /* Traverse and clean up the list */
    list_for_each_entry_safe(entry, tmp, &hello_list, list) {
        pr_info("Event time: %llu ns\n", ktime_to_ns(entry->time));
        list_del(&entry->list);
        kfree(entry);
    }
}

module_init(hello_init);
module_exit(hello_exit);
