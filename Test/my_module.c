#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

static int simple_init(void){
    struct task_struct *p;
    p = NULL;
    p = &init_task;
    printk(KERN_INFO "ListTask module loaded\n");
    printk(KERN_INFO "PID\tStatus\tPriority\tName\n");
    for_each_process(p){
        printk(KERN_INFO "%d\t%ld\t%d\t%s\n",p->pid,p->__state,p->normal_prio,p->comm);
    }
    return 0;
}

// 内核模块初始化函数
static int __init task_list_init(void) {
    printk(KERN_INFO "加载 task_list 模块...\n");
    simple_init();
    return 0;
}

// 内核模块退出函数
static void __exit task_list_exit(void) {
    printk(KERN_INFO "卸载 task_list 模块...\n");
}

// 注册内核模块初始化和退出函数
module_init(task_list_init);
module_exit(task_list_exit);

// 设置模块信息
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("一个简单的 Linux 内核模块，用于列出所有任务");

