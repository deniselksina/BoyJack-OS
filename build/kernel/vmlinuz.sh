#!/bin/bash

# Настройка конфигурации ядра
make menuconfig  # Открывает меню настройки конфигурации ядра

# Сборка ядра
make            # Компилирует ядро на основе текущей конфигурации

# Сборка модулей ядра
make modules     # Компилирует модули ядра

# Установка ядра и модулей
make install     # Устанавливает ядро в каталог /boot и модули в соответствующие каталоги

# Копирование скомпилированного ядра в каталог загрузки
cp /path/to/vmlinuz /boot/vmlinuz-5.x.x

# Обновление загрузчика (grub)
sudo update-grub  # Обновляет конфигурацию grub для добавления нового ядра

# Перезагрузка системы
sudo reboot       # Перезагружает систему для загрузки с новым ядром
