#!/bin/bash

# Параметры
KERNEL_VERSION=$1
OUTPUT_PATH="/boot/initrd.img-${KERNEL_VERSION}"

if [ -z "$KERNEL_VERSION" ]; then
  echo "Укажите версию ядра, например: ./initrd.sh <kernel-version>"
  exit 1
fi

# Проверяем, существует ли каталог для текущего ядра
if [ ! -d "/lib/modules/${KERNEL_VERSION}" ]; then
  echo "Модули для указанного ядра не найдены: ${KERNEL_VERSION}"
  exit 2
fi

# Создание initrd.img
echo "Создание initrd.img для ядра ${KERNEL_VERSION}..."

# Использование mkinitrd для создания initrd.img с предзагрузкой модулей
mkinitrd --preload netdev --preload ext4 --preload btrfs --preload pci --preload usb -o "${OUTPUT_PATH}" "${KERNEL_VERSION}"

if [ $? -ne 0 ]; then
  echo "Ошибка при создании initrd.img"
  exit 3
fi

echo "initrd.img успешно создан: ${OUTPUT_PATH}"

# Добавление дополнительных модулей вручную
echo "Добавление дополнительных модулей..."
depmod -a "${KERNEL_VERSION}"

# Пример монтирования дополнительной файловой системы или устройств:
echo "Монтирование дополнительных файловых систем..."
mkdir -p /mnt/extra_fs
mount -t ext4 /dev/sdb1 /mnt/extra_fs   # Пример монтирования дополнительного диска
# Если нужно монтировать сетевые файловые системы, можно использовать команду mount.cifs или nfs

# Монтируем дополнительные разделы, если они необходимы
echo "Монтируем другие разделы, если необходимо..."
# mount /dev/sdX1 /mnt/another_disk

# Пример загрузки специфических драйверов
echo "Загрузка драйверов для специфических устройств..."
modprobe nvidia  # Пример загрузки драйвера для GPU (заменить на нужный драйвер)

# Если нужно, можно добавить другие драйвера
# modprobe your_driver

echo "Готово! Вы можете обновить загрузчик GRUB для использования нового initrd.img."

# Обновляем конфигурацию GRUB, чтобы указать на новый initrd.img
sudo grub-mkconfig -o /boot/grub/grub.cfg
sudo update-grub
sudo reboot
