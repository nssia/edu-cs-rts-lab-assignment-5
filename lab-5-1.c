#include <sys/mman.h>
#include <native/task.h>
#include <rtdk.h>

void task_body(void *cookie) {

  RT_TASK *current_task;
  RT_TASK_INFO current_task_info;

  rt_printf("Hello, world\n");

  current_task = rt_task_self();
  rt_task_inquire(current_task, &current_task_info);

  rt_printf("Task name: %s\n", current_task_info.name);

}

int main(int argc, char **argv) {

  RT_TASK task;
  int err;

  rt_print_auto_init(1);

  mlockall(MCL_CURRENT|MCL_FUTURE);

  rt_printf("Starting task\n");

  err = rt_task_create(&task, "Lab5Task-1", 0, 50, 0);

  if (!err) {
    rt_task_start(&task, &task_body, NULL);
  }

  rt_task_join(&task);

}
