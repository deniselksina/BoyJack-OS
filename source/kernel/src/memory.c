#include "memory.h"
#include "kernel.h"
#include "io.h"

// Размер страницы памяти (например, 4KB)
#define PAGE_SIZE 4096

// Структура для хранения информации о странице
typedef struct {
    unsigned int start_address;
    unsigned int end_address;
    int is_free;
} page_t;

// Указатель на таблицу страниц
static page_t *page_table;
static unsigned int total_pages;
static unsigned int allocated_pages;

// Инициализация системы памяти
void memory_init(void) {
    // Примерная инициализация адресного пространства
    unsigned int total_memory = 0x10000000;  // 256MB, например
    total_pages = total_memory / PAGE_SIZE;   // Количество страниц в памяти
    allocated_pages = 0;

    // Выделяем память для таблицы страниц
    page_table = (page_t *)0x10000000;  // Начало таблицы страниц в памяти

    // Инициализируем таблицу страниц
    for (unsigned int i = 0; i < total_pages; i++) {
        page_table[i].start_address = i * PAGE_SIZE;
        page_table[i].end_address = (i + 1) * PAGE_SIZE - 1;
        page_table[i].is_free = 1;  // Все страницы изначально свободны
    }

    // Инициализация стека и кучи (простейший пример)
    init_stack();
    init_heap();
}

// Выделение страницы памяти
void *allocate_page(void) {
    for (unsigned int i = 0; i < total_pages; i++) {
        if (page_table[i].is_free) {
            page_table[i].is_free = 0;  // Отметить страницу как занятую
            allocated_pages++;
            return (void *)page_table[i].start_address;
        }
    }

    // Если свободных страниц нет, возвращаем NULL
    return NULL;
}

// Освобождение страницы памяти
void free_page(void *ptr) {
    unsigned int addr = (unsigned int)ptr;
    for (unsigned int i = 0; i < total_pages; i++) {
        if (page_table[i].start_address == addr) {
            page_table[i].is_free = 1;  // Отметить страницу как свободную
            allocated_pages--;
            return;
        }
    }
}

// Инициализация стека
void init_stack(void) {
    unsigned int stack_size = 0x1000;  // Размер стека
    unsigned int stack_start = 0x20000000;  // Стартовая позиция стека (например, 512MB)
    unsigned int stack_end = stack_start - stack_size;

    // Инициализация стека: вы делаете это в зависимости от особенностей вашей ОС
    // Это просто пример: на практике настройка стека происходит на уровне процессора
    print("Stack initialized\n");
}

// Инициализация кучи
void init_heap(void) {
    unsigned int heap_start = 0x30000000;  // Стартовая позиция кучи
    unsigned int heap_end = heap_start + 0x10000;  // Размер кучи

    // Инициализация кучи: создаём область для динамического выделения памяти
    // В реальных системах используется более сложная схема
    print("Heap initialized\n");
}

// Получение общего объёма выделенной памяти
unsigned int get_total_memory(void) {
    return total_pages * PAGE_SIZE;
}

// Получение объёма свободной памяти
unsigned int get_free_memory(void) {
    return (total_pages - allocated_pages) * PAGE_SIZE;
}
