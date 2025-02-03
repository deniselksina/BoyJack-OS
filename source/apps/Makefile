# Определения переменных
CC = gcc              # Компилятор
CFLAGS = -Wall -Wextra -g  # Флаги компилятора (для отладки и предупреждений)
LDFLAGS =              # Линковочные флаги
OBJ_DIR = obj          # Директория для объектных файлов
BIN_DIR = bin          # Директория для исполнимых файлов
SRC_DIR = src          # Директория исходных файлов

# Папки для приложений
APP_DIRS = apps app1 app2

# Файлы исходников для ядра
KERNEL_SRC = kernel/main.c kernel/memory.c kernel/scheduler.c kernel/syscall.c

# Имя исполнимого файла ядра
KERNEL_BIN = $(BIN_DIR)/kernel

# Функция для создания списка объектных файлов для приложения
define get_obj_files
    $(patsubst %.c, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/$(1)/*.c))
endef

# Правило для компиляции ядра
$(KERNEL_BIN): $(KERNEL_SRC)
    @mkdir -p $(OBJ_DIR)
    $(CC) $(CFLAGS) -c $(KERNEL_SRC) -o $(OBJ_DIR)/main.o
    $(CC) $(CFLAGS) -c $(KERNEL_SRC) -o $(OBJ_DIR)/memory.o
    $(CC) $(CFLAGS) -c $(KERNEL_SRC) -o $(OBJ_DIR)/scheduler.o
    $(CC) $(CFLAGS) -c $(KERNEL_SRC) -o $(OBJ_DIR)/syscall.o
    $(CC) $(OBJ_DIR)/main.o $(OBJ_DIR)/memory.o $(OBJ_DIR)/scheduler.o $(OBJ_DIR)/syscall.o -o $(KERNEL_BIN) $(LDFLAGS)
    @echo "Kernel compiled and linked."

# Правила для компиляции каждого приложения
$(foreach app,$(APP_DIRS),$(eval $(app)_OBJ := $(call get_obj_files,$(app))))
$(foreach app,$(APP_DIRS),$(eval $(app)_BIN := $(BIN_DIR)/$(app)))

$(foreach app,$(APP_DIRS),$(eval $(app)_OBJ):
    @mkdir -p $(OBJ_DIR)
    $(CC) $(CFLAGS) -c $(SRC_DIR)/$(app)/*.c -o $(OBJ_DIR)/$(app).o)

$(foreach app,$(APP_DIRS),$(eval $(app)_BIN): $($(app)_OBJ)
    $(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@ $(LDFLAGS))

# Правило для чистки всех объектов и исполнимых файлов
clean:
    rm -rf $(OBJ_DIR) $(BIN_DIR)
    @echo "Cleaned up build files."

# Правило для сборки всего проекта (ядро и приложения)
all: $(KERNEL_BIN) $(foreach app,$(APP_DIRS),$($(app)_BIN))
    @echo "All components compiled."

# Правила для установки приложений
install: all
    @mkdir -p /usr/local/bin
    cp $(BIN_DIR)/* /usr/local/bin/
    @echo "Applications installed."

