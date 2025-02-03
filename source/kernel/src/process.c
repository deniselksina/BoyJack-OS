#include "process.h"
#include "kernel.h"
#include "memory.h"
#include "scheduler.h"
#include "io.h"

// Структура для хранения информации о процессе
typedef struct {
    unsigned int pid;               // Идентификатор процесса
    unsigned int state;             // Состояние процесса
    unsigned int priority;          // Приоритет процесса
    unsigned int *stack;            // Указатель на стек процесса
    unsigned int stack_size;        // Размер стека
    unsigned int program_counter;   // Указатель на следующую инструкцию
    unsigned int entry_point;       // Точка входа в процесс (функция)
} process_t;

// Дефиниции состояний процесса
#define STATE_READY    0
#define STATE_RUNNING  1
#define STATE_BLOCKED  2
#define STATE_TERMINATED 3

// Переменные для управления процессами
static unsigned int next_pid = 1;         // Следующий доступный PID
static process_t *current_process = NULL;  // Текущий выполняющийся процесс
static process_t process_table[256];       // Таблица процессов (ограничена 256 процессами)

void init_process_manager(void) {
    // Инициализация таблицы процессов (сразу помечаем все как "неактивные")
    for (int i = 0; i < 256; i++) {
        process_table[i].pid = 0;  // Процесс ещё не существует
        process_table[i].state = STATE_TERMINATED;
    }
}

// Создание нового процесса
int create_process(const char *name, unsigned int entry_point) {
    // Поиск первого свободного процесса
    for (int i = 0; i < 256; i++) {
        if (process_table[i].state == STATE_TERMINATED) {
            // Заполнение структуры процесса
            process_table[i].pid = next_pid++;
            process_table[i].state = STATE_READY;
            process_table[i].priority = 1;  // Можно добавить механизм управления приоритетом
            process_table[i].entry_point = entry_point;
            process_table[i].stack_size = 1024;  // Стек размером 1KB
            process_table[i].stack = (unsigned int *)allocate_page();
            process_table[i].program_counter = process_table[i].entry_point;

            // Инициализация стека (можно более детально настроить стек)
            for (unsigned int j = 0; j < process_table[i].stack_size / sizeof(unsigned int); j++) {
                process_table[i].stack[j] = 0;
            }

            return process_table[i].pid;
        }
    }

    // Если нет свободных слотов для процессов
    return -1;
}

// Завершение процесса
void terminate_process(int pid) {
    for (int i = 0; i < 256; i++) {
        if (process_table[i].pid == pid) {
            process_table[i].state = STATE_TERMINATED;
            free_page(process_table[i].stack);  // Освобождение памяти стека
            return;
        }
    }
}

// Сохранение контекста текущего процесса
void save_context(process_t *process) {
    // Здесь будет сохраняться состояние процессора: регистры, состояние стека и т. д.
    // В реальной системе это может включать использование ассемблерных команд
    // для сохранения состояния процессора в структуре процесса.
    process->program_counter = get_program_counter();  // Получаем текущий счетчик команд
    save_stack_state(process->stack);  // Сохраняем состояние стека
}

// Восстановление контекста процесса
void restore_context(process_t *process) {
    // Здесь будет восстанавливаться состояние процессора
    set_program_counter(process->program_counter);  // Восстановление счетчика команд
    restore_stack_state(process->stack);  // Восстановление состояния стека
}

// Планировщик процессов
void schedule(void) {
    // Простая модель планирования: выбор первого процесса с состоянием READY
    for (int i = 0; i < 256; i++) {
        if (process_table[i].state == STATE_READY) {
            // Сохраняем контекст текущего процесса
            if (current_process != NULL) {
                save_context(current_process);
            }

            // Переключаем на новый процесс
            current_process = &process_table[i];
            process_table[i].state = STATE_RUNNING;

            // Восстанавливаем контекст нового процесса
            restore_context(current_process);
            return;
        }
    }

    // Если нет процессов в состоянии READY, переключаемся в "блокированное" состояние
    print("No ready processes found, entering idle state...\n");
    while (1) {
        // Блокировка процессора или переход в режим ожидания
    }
}

// Пример процесса
void init_process(void) {
    // Этот процесс будет выполнен первым
    print("Process 'init' started.\n");

    // Ваш код для процесса здесь
    // Например, создание других процессов
    create_process("child_process", (unsigned int)child_process);
}

// Пример дочернего процесса
void child_process(void) {
    print("Child process started.\n");
    // Дочерний процесс может выполнять свои задачи
    terminate_process(current_process->pid);  // Завершаем дочерний процесс
}
