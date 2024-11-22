 #include <linux/module.h>
 #include <linux/kernel.h>
 #include <linux/init.h>
 #include <linux/xarray.h>
 #include <linux/slab.h>
 ​
 MODULE_LICENSE("GPL");
 ​
 struct my_data {
     int id;
     char name[20];
 };
 ​
 DEFINE_XARRAY(my_xarray);  // 定义一个全局的XArray
 ​
 static void insert_data(int id, const char* name) {
     struct my_data* data = kmalloc(sizeof(struct my_data), GFP_KERNEL);
     data->id = id;
     strncpy(data->name, name, sizeof(data->name));
     
     xa_store(&my_xarray, id, data, GFP_KERNEL);
 }
 ​
 static void remove_data(int id) {
     struct my_data* data = xa_erase(&my_xarray, id);
     if (data)
         kfree(data);
 }
 ​
 static struct my_data* get_data(int id) {
     return xa_load(&my_xarray, id);
 }
 ​
 static int __init xarray_example_init(void) {
     pr_info("xarray_example: Initializing XArray example module\n");
 ​
     insert_data(1, "John");
     insert_data(2, "Alice");
     insert_data(3, "Bob");
     insert_data(4, "Steve");
 ​
     struct my_data* data = get_data(2);
     if (data)
         pr_info("xarray_example: ID: %d, Name: %s\n", data->id, data->name);
 ​
     unsigned long index;
 ​
     pr_info("xarray_example: before remove data 3");
     xa_for_each(&my_xarray, index, data) {
         pr_info("index = %d, data = %p, data->id = %d, data->name = %s\n", 
                 index, data, data->id, data->name);
    }
 ​
     remove_data(3);
 ​
     pr_info("xarray_example: after remove data 3\n");
     xa_for_each(&my_xarray, index, data) {
         pr_info("index = %d, data = %p, data->id = %d, data->name = %s\n", 
                 index, data, data->id, data->name);
    }
 ​
     return 0;
 }
 ​
 static void __exit xarray_example_exit(void) {
     pr_info("xarray_example: Cleaning up XArray example module\n");
 ​
     struct my_data* data;
     unsigned long index;
 ​
     xa_for_each(&my_xarray, index, data) {
         xa_erase(&my_xarray, index);
         kfree(data);
    }
 }
 ​
 module_init(xarray_example_init);
 module_exit(xarray_example_exit);
 