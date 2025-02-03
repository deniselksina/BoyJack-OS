#!/bin/bash

# Переключаемся в директорию с исходным кодом
cd ../source/

# Устанавливаем зависимости
echo "Установка зависимостей..."
sudo apt-get install -y build-essential

# Компилируем ядро
echo "Компиляция ядра..."
gcc -o ../build/kernel/kernel.bin kernel.c

# Компилируем приложения
echo "Компиляция приложений..."
gcc -o ../build/apps/app1.bin app1.c

# Записываем лог сборки
echo "Завершение сборки..." > ../build/logs/build.log
