#ifndef KEYBOARD_H
#define KEYBOARD_H

// Определение портов для клавиатуры
#define KEYBOARD_PORT 0x60          // Порт для чтения скан-кодов клавиш
#define KEYBOARD_STATUS_PORT 0x64   // Порт для управления клавиатурой

// Прототипы функций для инициализации и обработки клавиатуры
void init_keyboard(void);           // Инициализация клавиатуры
void keyboard_interrupt_handler(void); // Обработчик прерывания клавиатуры

// Вспомогательные функции для работы с клавишами
void write_char(char c);            // Функция для вывода символа на экран

#endif // KEYBOARD_H
