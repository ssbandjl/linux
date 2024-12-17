struct kobj_attribute etx_attr = __ATTR(etx_value, 0660, sysfs_show, sysfs_store);

static ssize_t sysfs_show(struct kobject *kobj, 
                struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d", etx_value);
}

static ssize_t sysfs_store(struct kobject *kobj, 
                struct kobj_attribute *attr,const char *buf, size_t count)
{
        sscanf(buf,"%d",&etx_value);
        return count;
}

//This Function will be called from Init function
/*Creating a directory in /sys/kernel/ */
kobj_ref = kobject_create_and_add("etx_sysfs",kernel_kobj);
 
/*Creating sysfs file for etx_value*/
if(sysfs_create_file(kobj_ref,&etx_attr.attr)){
    printk(KERN_INFO"Cannot create sysfs file......\n");
    goto r_sysfs;
}
//This should be called from exit function
kobject_put(kobj_ref); 
sysfs_remove_file(kernel_kobj, &etx_attr.attr);

