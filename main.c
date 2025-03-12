/*
 * show_slug_allocator driver
 ****************************************************************
 * Brief Description:
 * A simple module which shows how allocate and deallocate memory using
 *  buddy system allocator.
 */
#include "asm-generic/errno-base.h"
#include "asm/page-def.h"
#include <linux/gfp.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/printk.h>

MODULE_AUTHOR("KubaTaba1uga");
MODULE_DESCRIPTION("a simple LKM showing BSA usage");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.1");

static int __init show_slug_allocator_init(void) {
  pr_info("Inserted\n");

  //// Show alloc_page usage
  // This is at least 4KB page.
  struct page *memory = alloc_page(GFP_KERNEL);
  if (!memory) {
    pr_err("Unable to allocate memory with `alloc_page`\n");
    return -ENOMEM;
  }

  u16 *buf;

  buf = page_address(memory);

  int max_buf_size = PAGE_SIZE / sizeof(u16);
  for (int i = 0; i < max_buf_size; i++) {
    buf[i] = i;
  }

  pr_info("Page size=%lu, buffer size=%d\n", PAGE_SIZE, max_buf_size);
  for (int i = max_buf_size - 1; i >= max_buf_size - 5; i--) {
    pr_info("%d\n", buf[i]);
  }

  free_page((unsigned long)buf);

  //// Show get_zeroed_page usage
  buf = (u16 *)get_zeroed_page(GFP_KERNEL);
  if (!buf) {
    pr_err("Unable to allocate memory with `get_zeroed_page`\n");
    return -ENOMEM;
  }

  for (int i = 0; i < 5; i++) {
    pr_info("%d\n", buf[i]);
  }

  free_page((unsigned long)buf);

  //// Show alloc_pages usage
  memory = alloc_pages(GFP_KERNEL, 4); // 2^4 = 16
  if (!memory) {
    pr_err("Unable to allocate memory with `alloc_page`\n");
    return -ENOMEM;
  }

  buf = page_address(memory);

  max_buf_size = 16 * PAGE_SIZE / sizeof(u16);
  for (int i = 0; i < max_buf_size; i++) {
    buf[i] = i;
  }

  pr_info("Page size=%lu, buffer size=%d\n", PAGE_SIZE * 16, max_buf_size);
  for (int i = max_buf_size - 1; i >= max_buf_size - 5; i--) {
    pr_info("%d\n", buf[i]);
  }

  free_page((unsigned long)buf);

  return 0;
}

static void __exit show_slug_allocator_exit(void) { pr_info("Removed\n"); }

module_init(show_slug_allocator_init);
module_exit(show_slug_allocator_exit);
