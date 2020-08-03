#include <linux/init.h>             
#include <linux/module.h>          
#include <linux/kernel.h> 
#include <linux/cdev.h>
#include <linux/debugfs.h>
#include <linux/completion.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/freezer.h>
#include <linux/fs.h>
#include <linux/splice.h>
#include <linux/pagemap.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/poll.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/virtio.h>
#include <linux/virtio_console.h>
#include <linux/wait.h>
#include <linux/workqueue.h>
#include <linux/module.h>
#include <linux/dma-mapping.h>
#include <linux/miscdevice.h>


static struct miscdevice demo_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "demo driver",
};

static int __init misc_demo_init(void)
{
	int err;

	pr_info("demo driver init\n");
	err = misc_register(&demo_dev);
	if (err) {
		pr_err("dump register driver as misc device error!\n");
	}

	char *buf;
	dma_addr_t dma;
	unsigned int buf_size = 0x4000;
	demo_dev.this_device->coherent_dma_mask = 0xffffffff;
	printk("%s,line:%d\n",__func__,__LINE__);
	buf = dma_alloc_coherent(demo_dev.this_device, buf_size, &dma,
			GFP_KERNEL);
	printk("%s,line:%d\n",__func__,__LINE__);
	return err;
}

static void __exit misc_demo_exit(void)
{
	pr_info("demo driver exit\n");

	misc_deregister(&demo_dev);

}

module_init(misc_demo_init);
module_exit(misc_demo_exit);
