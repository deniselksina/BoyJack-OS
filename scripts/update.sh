#!/bin/bash

# Проверка на наличие обновлений
echo "Проверка на наличие обновлений..."
sudo apt-get update
sudo apt-get upgrade -y

# Обновление системных конфигурационных файлов
echo "Обновление конфигурационных файлов..."
cp ./configs/system.conf /etc/system.conf
cp ./configs/user.conf /etc/user.conf

# Обновление файлов ядра и приложений
echo "Обновление ядра и приложений..."
cp ./build/kernel/kernel.bin /boot/kernel.bin
cp ./build/apps/app1.bin /usr/local/bin/app1

# Перезагрузка для применения изменений
echo "Обновления завершены. Перезагружаем систему..."
sudo reboot
