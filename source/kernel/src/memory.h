#ifndef MEMORY_H
#define MEMORY_H

// Инициализация системы управления памятью
void init_memory(void);

// Функции для работы с памятью
void *kmalloc(size_t size);               // Выделение памяти
void kfree(void *ptr);                    // Освобождение памяти
void *kcalloc(size_t num, size_t size);   // Выделение нулевой памяти

#endif // MEMORY_H
