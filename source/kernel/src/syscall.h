#ifndef SYSCALL_H
#define SYSCALL_H

// Прототипы системных вызовов
void syscall_init(void);                  // Инициализация системных вызовов
int syscall_handler(int syscall_num, void *arg);  // Обработчик системных вызовов

// Системные вызовы
#define SYS_EXIT 1
#define SYS_READ 2
#define SYS_WRITE 3
#define SYS_FORK 4

#endif // SYSCALL_H
