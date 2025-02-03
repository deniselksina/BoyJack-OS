#include "kernel.h"
#include "memory.h"
#include "process.h"
#include "scheduler.h"
#include "syscall.h"
#include "io.h"

// Главное ядро ОС
void kernel_main(void) {
    // Инициализация видеорежима
    init_video();

    // Инициализация системы памяти
    init_memory();

    // Инициализация системных вызовов
    init_syscalls();

    // Инициализация процессора
    init_processor();

    // Инициализация планировщика
    init_scheduler();

    // Запуск базового процесса (например, init)
    start_first_process();

    // Основной цикл ядра
    while (1) {
        // Обработка событий (например, ввод с клавиатуры, прерывания)
        handle_events();

        // Выполнение планировщика для переключения контекста между процессами
        schedule();
    }
}

// Инициализация видеорежима
void init_video(void) {
    // Пример низкоуровневой инициализации видеорежима
    // Настройка текстового видеорежима VGA
    // Здесь могут быть добавлены функции для работы с графическим режимом

    // Например, настройка VGA
    init_vga();
}

// Функция для вывода текста на экран
void print(const char *str) {
    while (*str) {
        // Печать каждого символа на экране (например, с использованием VGA)
        put_char(*str++);
    }
}

// Инициализация системы памяти
void init_memory(void) {
    // Инициализация менеджера памяти
    // Настройка heap и stack
    memory_init();
}

// Инициализация системных вызовов
void init_syscalls(void) {
    // Установка таблицы системных вызовов
    setup_syscalls();
}

// Инициализация процессора
void init_processor(void) {
    // Настройка процессора, например, обработка прерываний
    setup_processor();
}

// Инициализация планировщика
void init_scheduler(void) {
    // Инициализация планировщика процессов
    setup_scheduler();
}

// Запуск базового процесса, например, init
void start_first_process(void) {
    // Запуск процесса инициализации
    create_process("init", init_process);
}

// Основной цикл обработки событий
void handle_events(void) {
    // Обработка событий, таких как:
    // - Ввод с клавиатуры
    // - Прерывания от устройств
    // - Обработка сигналов
    // Этот цикл может быть расширен для поддержки других типов событий

    // Пример: проверка ввода с клавиатуры
    if (keyboard_input_available()) {
        char c = get_key_pressed();
        handle_key_input(c);
    }
}

// Запуск планировщика процессов
void schedule(void) {
    // Использование планировщика для выбора процесса
    // и переключения контекста между ними

    // Пример: выбрать и запустить следующий процесс
    select_next_process();
    switch_context();
}
