#!/bin/bash

# Проверка на запуск от root
if [[ $EUID -ne 0 ]]; then
   echo "Этот скрипт должен быть запущен от root (используйте sudo)." 
   exit 1
fi

# Оптимизация системы
echo "Оптимизация системы..."

# Увеличиваем число открытых файлов
echo "fs.file-max = 100000" | sudo tee -a /etc/sysctl.conf
sudo sysctl -p

# Очистка кеша
sudo sync
echo 3 | sudo tee /proc/sys/vm/drop_caches

# Оптимизация процессора
echo "Настройка оптимальных параметров процессора..."
sudo apt-get install -y cpufrequtils
sudo cpufreq-set -g performance

echo "Система оптимизирована!"
