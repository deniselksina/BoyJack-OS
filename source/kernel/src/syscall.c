#include "syscall.h"
#include "process.h"
#include "io.h"
#include "memory.h"
#include "scheduler.h"

// Функции для обработки системных вызовов
void syscall_handler(int syscall_num, void *arg1, void *arg2, void *arg3) {
    switch (syscall_num) {
        case SYS_WRITE:
            syscall_write((char *)arg1, (unsigned int)arg2);
            break;

        case SYS_EXIT:
            syscall_exit((int)arg1);
            break;

        case SYS_FORK:
            syscall_fork();
            break;

        case SYS_SLEEP:
            syscall_sleep((unsigned int)arg1);
            break;

        default:
            print("Unknown syscall!\n");
            break;
    }
}

// Системный вызов: Write
// Печатает строку на экране
void syscall_write(char *str, unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
        putchar(str[i]);
    }
}

// Системный вызов: Exit
// Завершает выполнение текущего процесса
void syscall_exit(int status) {
    print("Process exited with status: ");
    print_int(status);
    print("\n");
    terminate_process(current_process->pid);  // Завершаем текущий процесс
}

// Системный вызов: Fork
// Создает новый процесс (копию текущего)
void syscall_fork(void) {
    int pid = create_process("child_process", (unsigned int)init_process);
    if (pid < 0) {
        print("Error: Fork failed.\n");
        return;
    }

    print("Process forked with PID: ");
    print_int(pid);
    print("\n");
}

// Системный вызов: Sleep
// Заставляет процесс спать (не выполнять действия) на определенное время
void syscall_sleep(unsigned int milliseconds) {
    unsigned int start_time = get_current_time();
    while ((get_current_time() - start_time) < milliseconds) {
        // Пауза, например, с помощью бездействия процессора
        asm volatile("nop");  // Ассемблерная инструкция "no operation"
    }
}

// Получить текущее время (например, миллисекунды с момента запуска)
unsigned int get_current_time(void) {
    // Эта функция может быть связана с аппаратным таймером или системным счётчиком
    // Для примера используем просто фиксированное значение
    return 0;  // Это нужно заменить на настоящую реализацию
}

// Функция печати числа
void print_int(int num) {
    if (num == 0) {
        putchar('0');
        return;
    }

    char buffer[10];
    int index = 0;

    while (num > 0) {
        buffer[index++] = (num % 10) + '0';
        num /= 10;
    }

    for (int i = index - 1; i >= 0; i--) {
        putchar(buffer[i]);
    }
}

// Пример использования системных вызовов
void example_usage(void) {
    syscall_write("Hello, world!\n", 14);  // Печать строки
    syscall_sleep(1000);  // Сон на 1000 миллисекунд
    syscall_exit(0);  // Завершение процесса с кодом 0
}
