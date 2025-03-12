/*
 * show_slab_allocator driver
 ****************************************************************
 * Brief Description:
 * A simple module which shows how allocate and deallocate memory using
 *  slab allocator.
 */
#include "linux/slab.h"
#include <linux/gfp.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

MODULE_AUTHOR("KubaTaba1uga");
MODULE_DESCRIPTION("a simple LKM showing BSA usage");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.1");

static int __init show_slab_allocator_init(void) {
  pr_info("Inserted\n");

  int max_buf_size = 2048;
  u16 *buf = kmalloc(sizeof(u16) * max_buf_size, GFP_KERNEL);
  if (!buf) {
    pr_err("Unable to allocate memory with `kmalloc`\n");
    return -ENOMEM;
  }

  for (int i = 0; i < max_buf_size; i++) {
    buf[i] = i;
  }

  pr_info("Allocated bytes: %zu\n", ksize(buf));
  for (int i = max_buf_size - 1; i >= max_buf_size - 5; i--) {
    pr_info("%d\n", buf[i]);
  }

  kfree(buf);

  buf = kzalloc(sizeof(u16) * max_buf_size, GFP_KERNEL);
  if (!buf) {
    pr_err("Unable to allocate memory with `kzalloc`\n");
    return -ENOMEM;
  }

  pr_info("Allocated bytes: %zu\n", ksize(buf));
  for (int i = 0; i < 5; i++) {
    pr_info("%d\n", buf[i]);
  }

  kfree(buf);

  return 0;
}

static void __exit show_slab_allocator_exit(void) { pr_info("Removed\n"); }

module_init(show_slab_allocator_init);
module_exit(show_slab_allocator_exit);
