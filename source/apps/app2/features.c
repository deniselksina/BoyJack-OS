#include "syscall.h"
#include "utils.h"

// Функция для обработки ввода пользователя в текстовом формате
void get_input_string(char *buffer, unsigned int buffer_size) {
    unsigned int i = 0;
    char ch;

    syscall_write("\nEnter a string: ", 17);

    // Чтение символов, пока не достигнут лимит или не введен символ новой строки
    while (i < buffer_size - 1) {
        ch = syscall_read_char();  // Чтение символа с клавиатуры
        if (ch == '\n') {
            break;  // Прерывание при нажатии Enter
        }
        buffer[i++] = ch;
    }
    buffer[i] = '\0';  // Завершаем строку
    syscall_write("\nString received: ", 18);
    syscall_write(buffer, i);  // Выводим полученную строку
    syscall_write("\n", 1);
}

// Функция для сохранения строки в файл
void save_string_to_file(const char *filename, const char *data) {
    int file_descriptor = syscall_open(filename, O_WRONLY | O_CREAT);
    if (file_descriptor < 0) {
        syscall_write("Error opening file for writing\n", 31);
        return;
    }

    syscall_write(file_descriptor, data, strlen(data));  // Записываем данные в файл
    syscall_close(file_descriptor);  // Закрываем файл
    syscall_write("\nData saved to file: ", 20);
    syscall_write(filename, strlen(filename));
    syscall_write("\n", 1);
}

// Функция для загрузки содержимого файла в строку
void load_file_to_string(const char *filename, char *buffer, unsigned int buffer_size) {
    int file_descriptor = syscall_open(filename, O_RDONLY);
    if (file_descriptor < 0) {
        syscall_write("Error opening file for reading\n", 30);
        return;
    }

    unsigned int bytes_read = syscall_read(file_descriptor, buffer, buffer_size - 1);
    buffer[bytes_read] = '\0';  // Завершаем строку

    syscall_close(file_descriptor);  // Закрываем файл

    syscall_write("\nFile contents loaded: ", 23);
    syscall_write(buffer, bytes_read);  // Выводим содержимое файла
    syscall_write("\n", 1);
}

// Функция для выполнения математических операций с двумя числами
void perform_math_operations() {
    int num1 = 10;
    int num2 = 20;
    int result;

    syscall_write("\nPerforming math operations...\n", 30);

    // Сложение
    result = num1 + num2;
    syscall_write("Addition: ", 11);
    print_number(result);  // Используем функцию для вывода числа
    syscall_write("\n", 1);

    // Вычитание
    result = num1 - num2;
    syscall_write("Subtraction: ", 14);
    print_number(result);  // Используем функцию для вывода числа
    syscall_write("\n", 1);

    // Умножение
    result = num1 * num2;
    syscall_write("Multiplication: ", 17);
    print_number(result);  // Используем функцию для вывода числа
    syscall_write("\n", 1);

    // Деление (проверка на деление на ноль)
    if (num2 != 0) {
        result = num1 / num2;
        syscall_write("Division: ", 10);
        print_number(result);  // Используем функцию для вывода числа
        syscall_write("\n", 1);
    } else {
        syscall_write("Error: Division by zero!\n", 25);
    }
}

// Функция для отображения списка файлов в текущей директории
void list_files_in_directory() {
    // Эта функция может быть реализована для перечисления файлов в директории.
    // В примере она выводит сообщение, чтобы показать функциональность.

    syscall_write("\nListing files in current directory...\n", 38);

    // Для реальной реализации необходимо добавить функционал для работы с файловой системой,
    // например, использовать системные вызовы для чтения содержимого директории.

    syscall_write("file1.txt\nfile2.txt\nfile3.txt\n", 31);  // Пример вывода
}

// Функция для поиска подстроки в строке
int find_substring(char *haystack, char *needle) {
    int i, j;

    for (i = 0; haystack[i] != '\0'; i++) {
        for (j = 0; needle[j] != '\0' && haystack[i + j] == needle[j]; j++);
        if (needle[j] == '\0') {
            return i;  // Возвращаем индекс первого вхождения подстроки
        }
    }
    return -1;  // Не нашли подстроку
}
