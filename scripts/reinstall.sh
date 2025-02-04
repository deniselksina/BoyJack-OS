#!/bin/bash

# Проверка запуска от root
if [[ $EUID -ne 0 ]]; then
    echo "Этот скрипт должен быть запущен от root (используйте sudo)."
    exit 1
fi

echo "Начинаем переустановку системы..."

# Обновление системы и пакетов
echo "Обновление пакетов..."
sudo apt-get update
sudo apt-get upgrade -y

# Удаление старых или ненужных пакетов
echo "Удаляем ненужные пакеты..."
sudo apt-get autoremove -y
sudo apt-get autoclean -y

# Переустановка зависимостей и базовых пакетов
echo "Переустанавливаем зависимости..."
sudo apt-get install --reinstall -y build-essential gcc make curl dpkg mate-desktop-environment gnome-software android-tools-adb android-tools-fastboot

# Переустановка рабочего стола
echo "Переустанавливаем рабочий стол..."
sudo apt-get install --reinstall -y ubuntu-mate-desktop

# Переустановка Google Chrome
echo "Переустанавливаем Google Chrome..."
wget -q -O google-chrome.deb https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
if [[ -f "google-chrome.deb" ]]; then
    sudo dpkg -i google-chrome.deb
    sudo apt-get install -f -y
    rm -f google-chrome.deb
else
    echo "⚠️ Ошибка загрузки Google Chrome! Проверьте интернет-соединение."
fi

# Восстановление конфигурационных файлов
echo "Восстанавливаем конфигурационные файлы..."
if [[ -f "./configs/system.conf" ]]; then
    sudo cp ./configs/system.conf /etc/system.conf
else
    echo "⚠️ Файл system.conf не найден! Пропускаем."
fi

if [[ -f "./configs/user.conf" ]]; then
    sudo cp ./configs/user.conf /etc/user.conf
else
    echo "⚠️ Файл user.conf не найден! Пропускаем."
fi

# Восстановление файлов ядра и приложений
echo "Восстанавливаем ядро и приложения..."
for file in "./build/kernel/kernel.bin" "./build/apps/app1.bin" "./build/apps/app2.bin"; do
    if [[ -f "$file" ]]; then
        sudo cp "$file" /usr/local/bin/
        sudo chmod +x "/usr/local/bin/$(basename $file)"
    else
        echo "⚠️ Файл $file не найден! Пропускаем."
    fi
done

# Установка обоев Ubuntu
echo "Устанавливаем обои Ubuntu..."
if [[ -f "./wallpapers/ubuntu-wallpaper.jpg" ]]; then
    sudo cp ./wallpapers/ubuntu-wallpaper.jpg /usr/share/backgrounds/
else
    echo "⚠️ Файл обоев не найден! Пропускаем."
fi

# Перезагрузка для применения изменений
echo "Переустановка завершена. Перезагружаем систему..."
read -p "Хотите перезагрузить систему сейчас? (y/n): " choice
if [[ "$choice" == "y" ]]; then
    sudo reboot
else
    echo "Перезагрузите систему вручную для применения изменений."
fi
