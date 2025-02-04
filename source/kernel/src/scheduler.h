#ifndef SCHEDULER_H
#define SCHEDULER_H

// Инициализация планировщика
void init_scheduler(void);

// Операции планировщика
void schedule(void);    // Выбор следующего процесса для выполнения
void switch_context(void); // Переключение контекста между процессами

#endif // SCHEDULER_H
