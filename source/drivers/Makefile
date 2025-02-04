# Параметры для компиляции
CC = gcc
CFLAGS = -Wall -Wextra -O2 -fno-pie -ffreestanding -nostdlib
LDFLAGS = -nostdlib -T linker.ld

# Путь к исходным файлам драйверов
DRIVER_SRC = keyboard.c ethernet.c wifi.c
DRIVER_OBJ = $(DRIVER_SRC:.c=.o)

# Путь к объектным файлам и выходному файлу
OBJ_DIR = build/obj
OUT_DIR = build/out
KERNEL_OBJ = kernel.o

# Выходной файл (ядерный образ с драйверами)
KERNEL_BIN = $(OUT_DIR)/kernel.bin

# Правила для сборки

# Сборка всех драйверов
all: $(KERNEL_BIN)

# Сборка ядра и драйверов
$(KERNEL_BIN): $(KERNEL_OBJ) $(DRIVER_OBJ)
	$(CC) $(CFLAGS) -o $(KERNEL_BIN) $(KERNEL_OBJ) $(DRIVER_OBJ) $(LDFLAGS)
	@echo "Kernel with drivers built successfully."

# Сборка объектов из исходных файлов драйверов
keyboard.o: keyboard.c
	$(CC) $(CFLAGS) -c keyboard.c -o $(OBJ_DIR)/keyboard.o

ethernet.o: ethernet.c
	$(CC) $(CFLAGS) -c ethernet.c -o $(OBJ_DIR)/ethernet.o

wifi.o: wifi.c
	$(CC) $(CFLAGS) -c wifi.c -o $(OBJ_DIR)/wifi.o

# Очистка временных файлов
clean:
	rm -rf $(OBJ_DIR)/*.o $(OUT_DIR)/*.bin
	@echo "Cleaned up build files."

# Правило для сборки всех объектов
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Отображение помощи
help:
	@echo "Makefile for building the kernel and drivers."
	@echo "Commands:"
	@echo "  make        - Build the kernel with drivers."
	@echo "  make clean  - Clean build artifacts."
	@echo "  make help   - Show this help message."
