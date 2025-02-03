# Makefile для сборки ядра

# Компилятор и флаги
CC = gcc
ASM = nasm
LD = ld
CFLAGS = -Wall -ffreestanding -nostdlib -m32
LDFLAGS = -m32 -T linker.ld
ASFLAGS = -f elf32

# Папки для исходных файлов и выводов
SRC_DIR = src
BUILD_DIR = build
KERNEL_DIR = kernel
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Исходники
KERNEL_SRC = $(SRC_DIR)/main.c $(SRC_DIR)/memory.c $(SRC_DIR)/scheduler.c $(SRC_DIR)/syscall.c
ASM_SRC = $(SRC_DIR)/start.asm

# Объектные файлы
KERNEL_OBJ = $(OBJ_DIR)/main.o $(OBJ_DIR)/memory.o $(OBJ_DIR)/scheduler.o $(OBJ_DIR)/syscall.o
ASM_OBJ = $(OBJ_DIR)/start.o

# Имя финального исполнимого файла
KERNEL_BIN = $(BIN_DIR)/kernel.bin

# Главная цель (сборка ядра)
all: $(KERNEL_BIN)

# Сборка ядра
$(KERNEL_BIN): $(KERNEL_OBJ) $(ASM_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

# Сборка объектных файлов C
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Сборка объектных файлов ассемблера
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	@mkdir -p $(OBJ_DIR)
	$(ASM) $(ASFLAGS) -o $@ $<

# Чистка всех сгенерированных файлов
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Функция для создания образа загрузки (опционально)
create_iso: $(KERNEL_BIN)
	@mkdir -p $(BIN_DIR)/iso/boot/grub
	cp $(KERNEL_BIN) $(BIN_DIR)/iso/boot/grub/kernel.bin
	echo 'set timeout=0' > $(BIN_DIR)/iso/boot/grub/grub.cfg
	echo 'set default=0' >> $(BIN_DIR)/iso/boot/grub/grub.cfg
	echo 'menuentry "BoyJack OS v1.1" {' >> $(BIN_DIR)/iso/boot/grub/grub.cfg
	echo '  multiboot /boot/grub/kernel.bin' >> $(BIN_DIR)/iso/boot/grub/grub.cfg
	echo '  boot' >> $(BIN_DIR)/iso/boot/grub/grub.cfg
	echo '}' >> $(BIN_DIR)/iso/boot/grub/grub.cfg
	grub-mkrescue -o $(BIN_DIR)/os.iso $(BIN_DIR)/iso

.PHONY: all clean create_iso
