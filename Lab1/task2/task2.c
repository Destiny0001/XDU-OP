#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

// 深度优先搜索遍历进程树
static void dfs(struct task_struct *task) {
    struct task_struct *child;
    struct list_head *list;

    // 输出任务名称、状态、进程标识符
    printk(KERN_INFO "任务: %s,\t 状态: %ld,\t PID: %d\n", task->comm, task->__state, task->pid);

    // 遍历子任务列表
    list_for_each(list, &task->children) {
        child = list_entry(list, struct task_struct, sibling);
        dfs(child);
    }
}

// 内核模块初始化函数
static int __init task_list_init(void) {
    printk(KERN_INFO "加载 task2 模块...\n");
    dfs(&init_task);
    return 0;
}

// 内核模块退出函数
static void __exit task_list_exit(void) {
    printk(KERN_INFO "卸载 task2 模块...\n");
}

// 注册内核模块初始化和退出函数
module_init(task_list_init);
module_exit(task_list_exit);

// 设置模块信息
MODULE_LICENSE("GPL");
MODULE_AUTHOR("TTT");
MODULE_DESCRIPTION("Module for task2");

