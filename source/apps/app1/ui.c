#include "syscall.h"
#include "io.h"

// Функция для отображения главного меню
void display_main_menu() {
    syscall_write("\nWelcome to the BoyJack OS! Please choose an option:\n", 54);
    syscall_write("1. Run Application 1\n", 22);
    syscall_write("2. Run Application 2\n", 22);
    syscall_write("3. Exit\n", 8);
}

// Функция для получения ввода пользователя
int get_user_input() {
    char buffer[10];  // Буфер для ввода
    int i = 0;
    char c;

    syscall_write("Enter your choice: ", 18);

    // Чтение ввода пользователя символ за символом
    while (1) {
        c = syscall_getchar();  // Чтение символа с клавиатуры
        if (c == '\n' || c == '\r') {
            buffer[i] = '\0';  // Завершаем строку
            break;
        }
        buffer[i++] = c;  // Сохраняем символ в буфере
        syscall_putchar(c);  // Отображаем символ на экране
    }

    // Преобразуем строку в целое число (ввод предполагается как один символ)
    return buffer[0] - '0';  // Преобразуем символ в число
}

// Главная точка входа в интерфейс
int main(void) {
    int choice;

    // Главный цикл интерфейса
    while (1) {
        display_main_menu();  // Отображаем меню
        choice = get_user_input();  // Получаем ввод пользователя

        switch (choice) {
            case 1:
                syscall_write("\nRunning Application 1...\n", 26);
                // Запуск первого приложения (пример)
                syscall_exec("app1");
                break;
            case 2:
                syscall_write("\nRunning Application 2...\n", 26);
                // Запуск второго приложения (пример)
                syscall_exec("app2");
                break;
            case 3:
                syscall_write("\nExiting...\n", 12);
                syscall_exit(0);  // Выход из интерфейса
                break;
            default:
                syscall_write("\nInvalid choice, please try again.\n", 34);
                break;
        }
    }

    return 0;  // Не должно достигаться, так как программа выходит из цикла
}
