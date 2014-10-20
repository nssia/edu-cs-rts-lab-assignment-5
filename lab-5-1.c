#include <sys/mman.h>
#include <native/task.h>
#include <rtdk.h>

void task_body(void *cookie) {

  RT_TASK *current_task;
  RT_TASK_INFO current_task_info;

  rt_printf("Hello, world\n");

  //Получение дескриптора адреса текущего процесса
  current_task = rt_task_self();
  //Запрос к процессу
  rt_task_inquire(current_task, &current_task_info);

  rt_printf("Task name: %s\n", current_task_info.name);

}

int main(int argc, char **argv) {

  RT_TASK task;
  int err;
  //Инициализировать подсистему печати xenomai
  rt_print_auto_init(1);
  //Запрет страничного обмена для всех страниц в области памяти вызывающего процесса
  mlockall(MCL_CURRENT|MCL_FUTURE);

  rt_printf("Starting task\n");

  //Создание процесса
  err = rt_task_create(&task, "Lab5Task-1", 0, 50, 0);

  //Запуск процесса
  if (!err) {
    rt_task_start(&task, &task_body, NULL);
  }

  //Ожидание завершения задач
  rt_task_join(&task);

}
