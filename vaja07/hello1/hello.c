#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h> 

static int __init init_modul(void) {
  printk(KERN_INFO "Hello, world 4\n");
  return 0;
}

static void __exit cleanup_modul(void) {
  printk(KERN_INFO "Goodbye, world 4\n");
}

module_init(init_modul);
module_exit(cleanup_modul);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anze Pintar");
MODULE_DESCRIPTION("Hello world kernel modul");
MODULE_VERSION("1.0");