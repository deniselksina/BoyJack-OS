#!/bin/bash

# Проверка на запуск от root
if [[ $EUID -ne 0 ]]; then
   echo "Этот скрипт должен быть запущен от root (используйте sudo)." 
   exit 1
fi

# Кастомная настройка
echo "Начинаем кастомную настройку системы..."

# Настройка конфигурации
echo "Настройка сетевых параметров..."
sudo cp ./configs/network.conf /etc/network/interfaces

# Добавление дополнительных пакетов
echo "Установка дополнительных пакетов..."
sudo apt-get install -y htop vim

# Настройка рабочего окружения
echo "Настройка рабочего окружения..."
sudo cp ./configs/custom.desktop /usr/share/applications/

echo "Кастомная настройка завершена!"
