#ifndef PROCESS_H
#define PROCESS_H

// Структуры для представления процессов
typedef struct process {
    int pid;                    // Идентификатор процесса
    int status;                 // Статус процесса (запущен, завершен)
    unsigned long *stack;       // Стек процесса
} process_t;

// Инициализация процессов
void init_processes(void);

// Основные операции с процессами
int create_process(void (*entry_point)());  // Создание процесса
void exit_process(void);                     // Завершение процесса
void schedule(void);                         // Планирование процессов

#endif // PROCESS_H
