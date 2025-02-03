# Определение переменных
CC=gcc
CFLAGS=-Wall -g

# Цель для компиляции ядра
kernel.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o build/kernel/kernel.o

# Цель для компиляции приложения
app1.o: app1.c
	$(CC) $(CFLAGS) -c app1.c -o build/apps/app1.o

# Главная цель
all: kernel.o app1.o
	$(CC) build/kernel/kernel.o build/apps/app1.o -o build/system/kernel_app
