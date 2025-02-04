#include "io.h"

// Функция для записи байта в порт
void outb(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

// Функция для чтения байта из порта
uint8_t inb(uint16_t port) {
    uint8_t value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

// Функция для записи слова (2 байта) в порт
void outw(uint16_t port, uint16_t value) {
    __asm__ volatile ("outw %0, %1" : : "a"(value), "Nd"(port));
}

// Функция для чтения слова (2 байта) из порта
uint16_t inw(uint16_t port) {
    uint16_t value;
    __asm__ volatile ("inw %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

// Функция для ввода строки (можно использовать для работы с клавиатурой)
void read_string(char *buffer, int max_length) {
    int i = 0;
    while (i < max_length - 1) {
        char c = inb(0x60); // Чтение из порта клавиатуры (пример)
        if (c == '\n') {
            break;
        }
        buffer[i++] = c;
    }
    buffer[i] = '\0';
}

// Функция для задержки
void io_wait(void) {
    __asm__ volatile ("jmp 1f\n\t"
                      "1: jmp 2f\n\t"
                      "2:");
}
