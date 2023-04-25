#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

static int simple_init(void){
    struct task_struct *task;
    task = &init_task;
   // 输出任务名称、状态、进程标识符 
    for_each_process(task){
        printk(KERN_INFO "任务: %s,\t 状态: %ld,\t PID: %d\n", task->comm, task->__state, task->pid);
    }
    return 0;
}

// 内核模块初始化函数
static int __init task_list_init(void) {
    printk(KERN_INFO "加载 task1 模块...\n");
    simple_init();
    return 0;
}

// 内核模块退出函数
static void __exit task_list_exit(void) {
    printk(KERN_INFO "卸载 task1 模块...\n");
}

// 注册内核模块初始化和退出函数
module_init(task_list_init);
module_exit(task_list_exit);

// 设置模块信息
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("一个简单的 Linux 内核模块，用于列出所有任务");

