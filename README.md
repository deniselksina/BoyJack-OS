# BoyJack OS

BoyJack OS — это операционная система, разработанная с открытым исходным кодом, предназначенная для использования на компьютерах и мобильных устройствах. Она обеспечивает стабильную работу, поддержку различных приложений и гибкую настройку.

## Особенности

- Совместимость с Android (необходимо разблокировать загрузчик)
- Поддержка работы с GNOME App Store
- Интеграция с Ubuntu MATE
- Многофункциональная настройка системы и приложений

## Установка

Для установки системы выполните следующие шаги:

1. Скачайте образ ISO с официального сайта.
2. Создайте загрузочный USB-накопитель с использованием инструмента, например, `Rufus`.
3. Загрузитесь с USB-накопителя и следуйте инструкциям установщика.

```bash
# Пример команды для создания загрузочного диска
dd if=boyjack-os.iso of=/dev/sdX bs=4M status=progress
