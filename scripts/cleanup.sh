#!/bin/bash

# Проверка на запуск от root
if [[ $EUID -ne 0 ]]; then
   echo "Этот скрипт должен быть запущен от root (используйте sudo)." 
   exit 1
fi

# Очистка ненужных пакетов и кэша
echo "Очистка системы..."
sudo apt-get autoremove -y
sudo apt-get autoclean -y

# Удаление ненужных зависимостей
echo "Удаление ненужных зависимостей..."
sudo apt-get autoremove --purge -y

echo "Очистка завершена!"
