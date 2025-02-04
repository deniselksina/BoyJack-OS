#include "wifi.h"
#include "io.h"
#include "utils.h"

// Пример базовых регистров для Wi-Fi адаптера
#define WIFI_REG_STATUS 0x4000  // Статус устройства
#define WIFI_REG_CONTROL 0x4004 // Управляющий регистр
#define WIFI_REG_TX 0x4010     // Регистр для отправки данных
#define WIFI_REG_RX 0x4020     // Регистр для получения данных
#define WIFI_REG_SSID 0x4030   // Регистр для настройки SSID
#define WIFI_REG_PASSWORD 0x4040 // Регистр для настройки пароля

// Структура для Wi-Fi кадра
typedef struct {
    uint8_t dest_mac[6];   // MAC-адрес получателя
    uint8_t src_mac[6];    // MAC-адрес отправителя
    uint16_t ethertype;    // Тип протокола (например, IP)
    uint8_t data[1500];    // Данные
    uint32_t crc;          // Контрольная сумма
} wifi_frame_t;

// Функция для инициализации Wi-Fi адаптера
void init_wifi(void) {
    // Инициализация Wi-Fi адаптера
    outb(WIFI_REG_CONTROL, 0x01);  // Включение Wi-Fi адаптера
    print_string("Wi-Fi initialized.\n");

    // Настройка SSID и пароля
    uint8_t ssid[32] = "MyWiFiNetwork"; // Пример SSID
    uint8_t password[32] = "password123"; // Пример пароля
    set_wifi_ssid(ssid);
    set_wifi_password(password);

    // Подключение к сети
    connect_wifi();
}

// Функция для установки SSID
void set_wifi_ssid(uint8_t ssid[32]) {
    for (int i = 0; i < 32; i++) {
        outb(WIFI_REG_SSID + i, ssid[i]);
    }
    print_string("SSID set.\n");
}

// Функция для установки пароля Wi-Fi
void set_wifi_password(uint8_t password[32]) {
    for (int i = 0; i < 32; i++) {
        outb(WIFI_REG_PASSWORD + i, password[i]);
    }
    print_string("Password set.\n");
}

// Функция для подключения к Wi-Fi сети
void connect_wifi(void) {
    // Отправка команды на подключение к сети
    outb(WIFI_REG_CONTROL, 0x02); // Команда на подключение
    print_string("Connecting to Wi-Fi network...\n");

    // Ждем успешного подключения
    while (inb(WIFI_REG_STATUS) != 0x01) {
        // Ждем, пока статус не будет равен 0x01 (подключение успешно)
    }

    print_string("Connected to Wi-Fi network.\n");
}

// Функция для отправки пакета Wi-Fi
void send_wifi_packet(wifi_frame_t *frame) {
    for (int i = 0; i < sizeof(wifi_frame_t); i++) {
        outb(WIFI_REG_TX + i, ((uint8_t *)frame)[i]);
    }

    // Инициализация отправки пакета
    outb(WIFI_REG_CONTROL, 0x04); // Команда на отправку
    print_string("Wi-Fi packet sent.\n");
}

// Функция для получения пакета Wi-Fi
void receive_wifi_packet(wifi_frame_t *frame) {
    for (int i = 0; i < sizeof(wifi_frame_t); i++) {
        ((uint8_t *)frame)[i] = inb(WIFI_REG_RX + i);
    }

    print_string("Wi-Fi packet received.\n");
}

// Вспомогательная функция для вывода Wi-Fi кадра
void print_wifi_frame(wifi_frame_t *frame) {
    print_string("Destination MAC: ");
    for (int i = 0; i < 6; i++) {
        print_hex(frame->dest_mac[i]);
    }

    print_string("\nSource MAC: ");
    for (int i = 0; i < 6; i++) {
        print_hex(frame->src_mac[i]);
    }

    print_string("\nEthertype: ");
    print_hex(frame->ethertype);

    print_string("\nData: ");
    for (int i = 0; i < 1500; i++) {
        print_hex(frame->data[i]);
    }

    print_string("\nCRC: ");
    print_hex(frame->crc);
}
