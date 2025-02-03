#!/bin/bash

# Установка зависимостей
echo "Устанавливаем необходимые зависимости..."
sudo apt-get update
sudo apt-get install -y build-essential gcc make curl

# Настройка системных параметров
echo "Настройка системы..."
cp ./configs/system.conf /etc/system.conf
cp ./configs/user.conf /etc/user.conf

# Установка файлов ядра и приложений
echo "Копирование файлов..."
cp ./build/kernel/kernel.bin /boot/kernel.bin
cp ./build/apps/app1.bin /usr/local/bin/app1

# Настройка прав доступа
echo "Настройка прав доступа..."
chmod +x /usr/local/bin/app1

# Завершение установки
echo "Установка завершена!"
echo "Перезагрузите систему для применения изменений."
sudo reboot
