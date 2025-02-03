#include "scheduler.h"
#include "process.h"
#include "io.h"

// Простейшая очередь процессов
#define MAX_PROCESSES 256
static process_t *ready_queue[MAX_PROCESSES];  // Очередь готовых процессов
static unsigned int ready_queue_size = 0;      // Размер очереди готовых процессов
static unsigned int current_process_index = 0; // Индекс текущего процесса в очереди

// Функция для добавления процесса в очередь готовых
void enqueue_ready(process_t *process) {
    if (ready_queue_size < MAX_PROCESSES) {
        ready_queue[ready_queue_size++] = process;
    } else {
        print("Ready queue is full!\n");
    }
}

// Функция для удаления процесса из очереди готовых
process_t *dequeue_ready(void) {
    if (ready_queue_size == 0) {
        return NULL;  // Очередь пуста
    }

    process_t *process = ready_queue[current_process_index];
    ready_queue[current_process_index] = NULL;
    current_process_index++;

    if (current_process_index >= ready_queue_size) {
        current_process_index = 0;  // Сбросить индекс, если очередь перемещена
    }

    ready_queue_size--;
    return process;
}

// Инициализация планировщика
void init_scheduler(void) {
    ready_queue_size = 0;
    current_process_index = 0;
}

// Планировщик процессов (очередь с простым алгоритмом Round-Robin)
void schedule(void) {
    process_t *next_process = dequeue_ready();
    if (next_process == NULL) {
        // Если нет готовых процессов, переходим в режим ожидания
        print("No ready processes, entering idle state...\n");
        while (1) {
            // Можно, например, поставить процесс в режим ожидания или переходить в спящий режим
        }
    }

    // Сохранение контекста текущего процесса
    if (current_process != NULL) {
        save_context(current_process);
    }

    // Переключение на следующий процесс
    current_process = next_process;
    current_process->state = STATE_RUNNING;

    // Восстановление контекста нового процесса
    restore_context(current_process);

    // После завершения выполнения процесса его можно добавить обратно в очередь
    // или пометить как завершенный, в зависимости от состояния.
    if (current_process->state == STATE_READY) {
        enqueue_ready(current_process);
    } else if (current_process->state == STATE_TERMINATED) {
        terminate_process(current_process->pid);  // Завершаем процесс, если он завершен
    }
}

// Добавление процесса в очередь готовых
void add_process_to_ready_queue(process_t *process) {
    if (process->state == STATE_READY) {
        enqueue_ready(process);
    }
}

// Простая реализация функции, которая может быть вызвана для имитации планирования
void trigger_scheduler(void) {
    schedule();
}
