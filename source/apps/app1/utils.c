#include "syscall.h"
#include "io.h"

// Функция для преобразования числа в строку (например, для вывода чисел)
void itoa(int num, char *str) {
    int i = 0;
    int is_negative = 0;

    // Обработка отрицательных чисел
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    // Преобразование числа в строку
    do {
        str[i++] = (num % 10) + '0';
        num = num / 10;
    } while (num > 0);

    // Добавление знака минус, если число отрицательное
    if (is_negative) {
        str[i++] = '-';
    }

    // Завершаем строку
    str[i] = '\0';

    // Инвертируем строку
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Функция для вычисления факториала числа
int factorial(int num) {
    if (num <= 1) {
        return 1;
    }
    return num * factorial(num - 1);
}

// Функция для вычисления степени числа (num^exp)
int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

// Функция для вывода числа на экран
void print_number(int num) {
    char buffer[20];
    itoa(num, buffer);  // Преобразуем число в строку
    syscall_write(buffer, strlen(buffer));  // Выводим строку
}

// Функция для подсчета длины строки
unsigned int strlen(char *str) {
    unsigned int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Функция для конкатенации двух строк
void strcat(char *dest, const char *src) {
    while (*dest) {
        dest++;  // Идем в конец первой строки
    }
    while (*src) {
        *dest = *src;  // Копируем символы из второй строки
        dest++;
        src++;
    }
    *dest = '\0';  // Завершаем строку
}

// Функция для вывода строки на экран
void print(char *str) {
    syscall_write(str, strlen(str));
}

// Функция для подсчета количества символов в строке
int count_chars(char *str, char c) {
    int count = 0;
    while (*str) {
        if (*str == c) {
            count++;
        }
        str++;
    }
    return count;
}
