#include "syscall.h"
#include "io.h"

// Главная точка входа для приложения 1
int main(void) {
    // Печать приветственного сообщения
    syscall_write("Hello, welcome to my custom OS!\n", 30);

    // Выполнение системного вызова для ожидания
    syscall_sleep(2000); // Спим 2000 миллисекунд

    // Печать сообщения после сна
    syscall_write("Finished sleeping for 2000 ms.\n", 32);

    // Демонстрация системного вызова fork (создание нового процесса)
    syscall_fork();

    // Завершаем текущий процесс
    syscall_exit(0);
    
    // Мы не должны сюда попасть, так как syscall_exit завершает процесс
    return 0;
}

// Функция для печати строки
void print(char *str) {
    syscall_write(str, strlen(str));
}

// Функция для подсчета длины строки
unsigned int strlen(char *str) {
    unsigned int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}
