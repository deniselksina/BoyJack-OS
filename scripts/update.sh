#!/bin/bash

# Проверка запуска от root
if [[ $EUID -ne 0 ]]; then
   echo "Этот скрипт должен быть запущен от root (используйте sudo)." 
   exit 1
fi

# Обновление системы
echo "Проверка на наличие обновлений..."
sudo apt-get update && sudo apt-get upgrade -y

# Очистка ненужных пакетов
echo "Очистка системы..."
sudo apt-get autoremove -y && sudo apt-get autoclean -y

# Обновление конфигурационных файлов
echo "Обновление конфигурационных файлов..."
if [[ -f "./configs/system.conf" ]]; then
    cp ./configs/system.conf /etc/system.conf
else
    echo "⚠️ Файл system.conf не найден! Пропускаем."
fi

if [[ -f "./configs/user.conf" ]]; then
    cp ./configs/user.conf /etc/user.conf
else
    echo "⚠️ Файл user.conf не найден! Пропускаем."
fi

# Обновление файлов ядра и приложений
echo "Обновление ядра и приложений..."
if [[ -f "./build/kernel/kernel.bin" ]]; then
    cp ./build/kernel/kernel.bin /boot/kernel.bin
else
    echo "⚠️ Файл kernel.bin не найден! Пропускаем."
fi

if [[ -f "./build/apps/app1.bin" ]]; then
    cp ./build/apps/app1.bin /usr/local/bin/app1
    chmod +x /usr/local/bin/app1
else
    echo "⚠️ Файл app1.bin не найден! Пропускаем."
fi

# Перезагрузка для применения изменений
read -p "Хотите перезагрузить систему сейчас? (y/n): " choice
if [[ "$choice" == "y" ]]; then
    echo "Перезагрузка системы..."
    sudo reboot
else
    echo "Перезагрузите систему вручную для применения изменений."
fi
