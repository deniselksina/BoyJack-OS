#!/bin/bash

# Проверка запуска от root
if [[ $EUID -ne 0 ]]; then
   echo "Этот скрипт должен быть запущен от root (используйте sudo)." 
   exit 1
fi

echo "Устанавливаем необходимые зависимости..."
sudo apt-get update
sudo apt-get install -y build-essential gcc make curl dpkg mate-desktop-environment gnome-software android-tools-adb android-tools-fastboot

# Проверяем успешность установки
if [[ $? -ne 0 ]]; then
    echo "Ошибка установки зависимостей! Проверьте интернет-соединение и попробуйте снова."
    exit 1
fi

# Установка рабочего стола
echo "Устанавливаем Ubuntu MATE..."
sudo apt-get install -y ubuntu-mate-desktop || { echo "Ошибка установки Ubuntu MATE!"; exit 1; }

# Установка Google Chrome
echo "Устанавливаем Google Chrome..."
wget -q -O google-chrome.deb https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
if [[ -f "google-chrome.deb" ]]; then
    sudo dpkg -i google-chrome.deb
    sudo apt-get install -f -y
    rm -f google-chrome.deb
else
    echo "⚠️ Ошибка загрузки Google Chrome! Проверьте интернет-соединение."
fi

# Настройка системных параметров
echo "Настройка системы..."
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

# Копирование файлов ядра и приложений
echo "Копирование файлов..."
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

# Настройка совместимости с Android
echo "Настройка совместимости с Android..."
if command -v fastboot &> /dev/null; then
    echo "Fastboot найден!"

    # Проверяем, подключено ли устройство
    fastboot devices | grep -q "fastboot"
    if [[ $? -eq 0 ]]; then
        echo "Устройство найдено в fastboot mode!"
        echo "⚠️ Разблокировка загрузчика приведёт к удалению всех данных с устройства!"
        read -p "Вы уверены, что хотите продолжить? (y/n): " unlock_choice

        if [[ "$unlock_choice" == "y" ]]; then
            sudo fastboot oem unlock
            if [[ $? -eq 0 ]]; then
                echo "✅ Загрузчик успешно разблокирован!"
            else
                echo "❌ Ошибка разблокировки! Убедитесь, что устройство поддерживает fastboot oem unlock."
            fi
        else
            echo "Разблокировка отменена."
        fi
    else
        echo "⚠️ Устройство не обнаружено в fastboot mode. Подключите его и переведите в fastboot mode!"
    fi
else
    echo "⚠️ Fastboot не найден! Убедитесь, что android-tools-fastboot установлен."
fi

# Завершение установки
echo "✅ Установка завершена!"

# Запрос на перезагрузку
read -p "Хотите перезагрузить систему сейчас? (y/n): " choice
if [[ "$choice" == "y" ]]; then
    echo "Перезагрузка системы..."
    sudo reboot
else
    echo "Перезагрузите систему вручную для применения изменений."
fi
