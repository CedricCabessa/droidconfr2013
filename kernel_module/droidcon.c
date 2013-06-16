/*
  Linux Device Drivers, Third Edition
  Chap3 Char Drivers
  http://lwn.net/images/pdf/LDD3/ch03.pdf
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Droid Dev <droid@example.org>");
MODULE_VERSION("0.1");

#define BUFFER_SIZE           1024
#define MODULE_NAME           "droidcon"

int droidcon_open(struct inode *inode, struct file *filp);
int droidcon_release(struct inode *inode, struct file *filp);
ssize_t droidcon_read(struct file *filp, char *buf, size_t count,
                      loff_t *f_pos);
ssize_t droidcon_write(struct file *filp, const char *buf, size_t count,
                       loff_t *f_pos);


struct file_operations droidcon_fops = {
    .owner = THIS_MODULE,
    .read = droidcon_read,
    .write = droidcon_write,
    .open = droidcon_open,
    .release = droidcon_release,
};

struct droidcon_cdev {
    int is_open; /* FIXME: should be atomic something */
    ssize_t size;
    char *buffer;
    struct cdev cdev;
};

struct droidcon_cdev g_dev;
dev_t devt;
struct class *cls;

static int droidcon_init(void) {
    int result;
    result = alloc_chrdev_region(&devt, 0, 1,  MODULE_NAME);
    if (result < 0) {
        printk(KERN_WARNING "cannot get major!\n");
        return result;
    }
    g_dev.buffer = kmalloc(BUFFER_SIZE * sizeof(char), GFP_KERNEL);
    memset(g_dev.buffer, 0, BUFFER_SIZE * sizeof(char *));
    g_dev.size = 0;

    cdev_init(&g_dev.cdev, &droidcon_fops);
    g_dev.cdev.owner = THIS_MODULE;
    g_dev.cdev.ops = &droidcon_fops;
    result = cdev_add(&g_dev.cdev, devt, 1);

    cls = class_create(THIS_MODULE, MODULE_NAME);
    device_create(cls, NULL, devt, NULL, MODULE_NAME);

    if (result < 0) {
        printk(KERN_WARNING "cannot register cdev!\n");
        return result;
    }
    printk(KERN_WARNING MODULE_NAME" loaded\n");

    return 0;
}

static void droidcon_exit(void) {
    kfree(g_dev.buffer);
    device_destroy(cls, devt);
    class_destroy(cls);
    unregister_chrdev_region(devt, 1);
    cdev_del(&g_dev.cdev);
    printk(KERN_WARNING MODULE_NAME" exit\n");
}


int droidcon_open(struct inode *inode, struct file *filp)
{
    struct droidcon_cdev *dev;
    dev = container_of(inode->i_cdev, struct droidcon_cdev, cdev);
    filp->private_data = dev;
    if (dev->is_open > 0)
        return -EBUSY;
    dev->is_open ++;
    return 0;
}

int droidcon_release(struct inode *inode, struct file *filp)
{
    struct droidcon_cdev *dev = filp->private_data;
    dev->is_open --;
    return 0;
}

ssize_t droidcon_read(struct file *filp, char *buf, size_t count,
                      loff_t *f_pos)
{
    struct droidcon_cdev *dev = filp->private_data;
    ssize_t read = count;

    printk(KERN_WARNING "read: count %d pos %lld\n", count, *f_pos);
    if (*f_pos + count > dev->size)
        read = dev->size - *f_pos;

    if(read <= 0) {
        return 0;
    }

    if (copy_to_user(buf, (const void*)(dev->buffer+*f_pos), read))
        return -EFAULT;

    *f_pos += read;
    return read;
}

ssize_t droidcon_write(struct file *filp, const char *buf,
                       size_t count, loff_t *f_pos)
{
    struct droidcon_cdev *dev = filp->private_data;
    ssize_t written = count;
    size_t i = 0;

    if (*f_pos + count > BUFFER_SIZE)
        return -ENOSPC;

    if (copy_from_user(dev->buffer+*f_pos, buf, written))
        return -EFAULT;

    dev->size = *f_pos + written;
    memset(dev->buffer + written, 0, BUFFER_SIZE - written);

    for (i=0; i < written; ++i) {
        char *tmp = dev->buffer+*f_pos+i;
        if( 'a' <= *tmp && *tmp <= 'z')
            *tmp -= 32;
        else if( 'A' <= *tmp && *tmp <= 'Z')
            *tmp += 32;
    }
    *f_pos += written;
    return written;
}

module_init(droidcon_init);
module_exit(droidcon_exit);
