#include <linux/fs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>  

static int __init init(void);
static void __exit cleanup(void);

static int device_open(struct inode *inode, struct file *file) {
  pr_info("OPENING\n");
  return 0;
}

static int device_release(struct inode *inode, struct file *file) {
  pr_info("RELEASING\n");
  return 0;
}

const struct file_operations fops = {
    .open = device_open,
    .release = device_release,
};

unsigned int Major;
static struct class *dev_class;
static struct device *dev_device;

static int __init init(void) {
  int ret;
  
  pr_info("Initializing\n");

  // Регистрируем символьное устройство
  Major = register_chrdev(0, "pz3", &fops);  // Изменили имя на "pz3"
  if (Major < 0) {
    pr_alert("Registering char device failed with %d\n", Major);
    return Major;
  }

  // Создаем класс устройства
  dev_class = class_create(THIS_MODULE, "pz3_class");
  if (IS_ERR(dev_class)) {
    pr_alert("Failed to create device class\n");
    unregister_chrdev(Major, "pz3");
    return PTR_ERR(dev_class);
  }

  // Создаем устройство в /dev
  dev_device = device_create(dev_class, NULL, MKDEV(Major, 0), NULL, "pz3");
  if (IS_ERR(dev_device)) {
    pr_alert("Failed to create device\n");
    class_destroy(dev_class);
    unregister_chrdev(Major, "pz3");
    return PTR_ERR(dev_device);
  }

  pr_info("Driver initialized successfully. Major number: %d\n", Major);
  pr_info("Device created: /dev/pz3\n");

  return 0;
}

static void __exit cleanup(void) {
  pr_info("CLEANUP\n");
  
  // Удаляем устройство
  if (dev_device)
    device_destroy(dev_class, MKDEV(Major, 0));
  
  // Удаляем класс
  if (dev_class)
    class_destroy(dev_class);
  
  // Отменяем регистрацию устройства
  if (Major > 0)
    unregister_chrdev(Major, "pz3");
}

module_init(init);
module_exit(cleanup);

MODULE_DESCRIPTION("MAI drivers training");
MODULE_LICENSE("GPL");
