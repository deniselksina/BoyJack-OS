#!/bin/bash

# Проверка запуска от root
if [[ $EUID -ne 0 ]]; then
   echo "Этот скрипт должен быть запущен от root (используйте sudo)." 
   exit 1
fi

# Установка необходимых зависимостей для сборки ядра
echo "Устанавливаем зависимости для сборки ядра..."
sudo apt-get update
sudo apt-get install -y build-essential libncurses-dev bison flex libssl-dev

# Проверка успешности установки зависимостей
if [[ $? -ne 0 ]]; then
    echo "Ошибка установки зависимостей! Проверьте интернет-соединение и попробуйте снова."
    exit 1
fi

# Загрузка исходников ядра
KERNEL_VERSION="5.x.x"
KERNEL_URL="https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-$KERNEL_VERSION.tar.xz"
echo "Скачиваем исходники ядра $KERNEL_VERSION..."
wget -q $KERNEL_URL -O linux-$KERNEL_VERSION.tar.xz

if [[ $? -ne 0 ]]; then
    echo "⚠️ Ошибка при скачивании исходников ядра. Проверьте соединение и URL."
    exit 1
fi

# Распаковка исходников
echo "Распаковываем исходники ядра..."
tar -xvf linux-$KERNEL_VERSION.tar.xz
cd linux-$KERNEL_VERSION || { echo "Не удалось войти в директорию исходников."; exit 1; }

# Настройка ядра
echo "Настройка параметров ядра..."
make menuconfig  # Здесь можно вручную настроить параметры ядра

# Сборка ядра
echo "Сборка ядра..."
make -j$(nproc)  # Сборка с использованием всех доступных ядер процессора

# Установка модулей и ядра
echo "Установка модулей и ядра..."
sudo make modules_install
sudo make install

# Обновление загрузчика
echo "Обновление загрузчика..."
sudo update-grub

# Очистка исходников ядра
echo "Удаляем исходники ядра для экономии места..."
cd ..
rm -rf linux-$KERNEL_VERSION
rm -f linux-$KERNEL_VERSION.tar.xz

# Перезагрузка системы для применения изменений
# Запрос на перезагрузку
read -p "Хотите перезагрузить систему сейчас? (y/n): " choice
if [[ "$choice" == "y" ]]; then
    echo "Перезагрузка системы..."
    sudo reboot
else
    echo "Перезагрузите систему вручную для применения изменений."
fi
