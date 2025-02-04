#ifndef IO_H
#define IO_H

// Функции для работы с вводом/выводом
void init_io(void);                  // Инициализация устройств ввода/вывода
void write_char(char c);             // Вывод одного символа
void write_string(const char *str);  // Вывод строки
char read_char(void);                // Чтение одного символа с клавиатуры

// Функции работы с портами ввода-вывода
void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
void outw(uint16_t port, uint16_t value);
uint16_t inw(uint16_t port);

// Ввод строки (например, с клавиатуры)
void read_string(char *buffer, int max_length);

// Функция задержки
void io_wait(void);

#endif // IO_H
