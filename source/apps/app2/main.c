#include "syscall.h"
#include "ui.h"
#include "utils.h"

// Функция для выполнения некоторых вычислений и отображения результата
void perform_calculations() {
    int num1 = 5;
    int num2 = 3;
    int result;

    syscall_write("\nPerforming calculations...\n", 27);

    // Вычисляем сумму
    result = num1 + num2;
    syscall_write("Sum: ", 5);
    print_number(result);  // Используем функцию для вывода числа
    syscall_write("\n", 1);

    // Вычисляем факториал числа
    result = factorial(num1);
    syscall_write("Factorial of 5: ", 17);
    print_number(result);  // Используем функцию для вывода числа
    syscall_write("\n", 1);

    // Вычисляем степень
    result = power(num2, 2);  // 3^2
    syscall_write("3^2: ", 5);
    print_number(result);  // Используем функцию для вывода числа
    syscall_write("\n", 1);
}

// Главная функция приложения
int main(void) {
    int choice;

    // Печатаем приветствие
    syscall_write("\nWelcome to Application 2\n", 26);
    
    // Главный цикл приложения
    while (1) {
        display_main_menu();  // Печатаем главное меню
        choice = get_user_input();  // Получаем выбор пользователя

        switch (choice) {
            case 1:
                syscall_write("\nRunning a simple calculation...\n", 32);
                perform_calculations();  // Выполняем вычисления
                break;
            case 2:
                syscall_write("\nReturning to main menu...\n", 26);
                return 0;  // Выход из приложения и возврат в меню
            default:
                syscall_write("\nInvalid choice, please try again.\n", 34);
                break;
        }
    }

    return 0;  // Не должно быть достигнуто
}
