#!/bin/bash

# Проверка запуска от root
if [[ $EUID -ne 0 ]]; then
   echo "Этот скрипт должен быть запущен от root (используйте sudo)." 
   exit 1
fi

sudo apt-get update || { echo "Ошибка обновления пакетов!"; exit 1; }
sudo apt-get install -y build-essential gcc make curl dpkg mate-desktop-environment gnome-software android-tools-adb android-tools-fastboot libssl-dev libncurses-dev bison flex || { echo "Ошибка установки зависимостей!"; exit 1; }

if [ -z "$CHROME_URL" ]; then
    echo "⚠️ URL для загрузки Google Chrome не задан!"
    exit 1
fi

if [[ -f "google-chrome.deb" ]]; then
    sudo dpkg -i google-chrome.deb || { echo "Ошибка установки Google Chrome!"; exit 1; }
    sudo apt-get install -f -y || { echo "Ошибка исправления зависимостей после установки Google Chrome!"; exit 1; }
    rm -f google-chrome.deb || { echo "Не удалось удалить временный файл Google Chrome!"; exit 1; }
else
    echo "⚠️ Ошибка загрузки Google Chrome!"
fi

for file in "$SYSTEM_CONF" "$USER_CONF"; do
    if [[ -f "$file" ]]; then
        sudo cp "$file" "/etc/$(basename $file)" || { echo "Не удалось скопировать $file!"; exit 1; }
    else
        echo "⚠️ Файл $(basename $file) не найден! Пропускаем."
    fi
done

echo "✅ Все пакеты установлены и настроены успешно!"
