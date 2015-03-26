
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>

int period;

ssize_t timer_sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", period);
}

ssize_t timer_sysfs_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	sscanf(buf, "%d", &period);
	return count;
}

static struct kobj_attribute timer_attribute = __ATTR(timer_period, 0666, timer_sysfs_show, timer_sysfs_store);

static struct attribute *attrs[] = {
	&timer_attribute.attr,
	NULL
};

static struct attribute_group timer_attr_group = {
	.attrs = attrs,
};

static struct kobject *timer_kobj;


static int __init timer_sysfs_init(void)
{
	int retval;
	timer_kobj = kobject_create_and_add("timer_dir", NULL);

	retval = sysfs_create_group(timer_kobj, &timer_attr_group);
	if (retval)
		kobject_put(timer_kobj);

	return retval;
}

static void __exit timer_sysfs_exit(void)
{
	kobject_put(timer_kobj);
}

module_init(timer_sysfs_init);
module_exit(timer_sysfs_exit);
MODULE_LICENSE("GPL");

