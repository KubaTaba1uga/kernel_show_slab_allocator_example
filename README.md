# show_slug_allocator

A simple Linux kernel module that demonstrates memory allocation and deallocation using the buddy system allocator (BSA). The module showcases different memory allocation techniques in kernel space using functions like `alloc_page`, `get_zeroed_page`, and `alloc_pages`.

## Features

- **Buddy System Allocation:** Demonstrates allocation of single and multiple pages.
- **Memory Management Examples:** Shows how to initialize and free allocated memory.

## Building

1. Install the required build tools and kernel headers:
   ```bash
   sudo apt-get install build-essential linux-headers-$(uname -r)
   ```
2. Build the module:
   ```bash
   make
   ```

## Usage

1. **Load the Module:**
   ```bash
   sudo insmod show_slug_allocator.ko
   ```
2. **Check Kernel Log for Output:**
   ```bash
   dmesg | tail
   ```
3. **Unload the Module:**
   ```bash
   sudo rmmod show_slug_allocator
   ```

## Cleaning Up

To remove build artifacts:
```bash
make clean
```

## License

Dual MIT/GPL
