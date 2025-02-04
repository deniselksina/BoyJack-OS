#ifndef WIFI_H
#define WIFI_H

#include <stdint.h>

// Максимальная длина SSID и пароля
#define WIFI_SSID_MAX_LENGTH 32
#define WIFI_PASSWORD_MAX_LENGTH 64

// Статусы подключения
typedef enum {
    WIFI_DISCONNECTED,
    WIFI_CONNECTING,
    WIFI_CONNECTED,
    WIFI_ERROR
} wifi_status_t;

// Инициализация Wi-Fi модуля
void wifi_init(void);

// Подключение к сети Wi-Fi
wifi_status_t wifi_connect(const char *ssid, const char *password);

// Отключение от сети Wi-Fi
void wifi_disconnect(void);

// Отправка Wi-Fi-пакета
void wifi_send(uint8_t *data, uint16_t length);

// Получение Wi-Fi-пакета
int wifi_receive(uint8_t *buffer, uint16_t buffer_size);

#endif // WIFI_H
