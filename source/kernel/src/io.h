#ifndef IO_H
#define IO_H

// Функции для работы с вводом/выводом
void init_io(void);                  // Инициализация устройств ввода/вывода
void write_char(char c);             // Вывод одного символа
void write_string(const char *str);  // Вывод строки
char read_char(void);                // Чтение одного символа с клавиатуры

#endif // IO_H
