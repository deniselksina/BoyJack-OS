#ifndef ETHERNET_H
#define ETHERNET_H

#include <stdint.h>

// Размеры пакетов Ethernet
#define ETHERNET_MAX_PACKET_SIZE 1518
#define ETHERNET_MIN_PACKET_SIZE 64
#define MAC_ADDRESS_LENGTH 6

// Структура Ethernet-кадра
typedef struct {
    uint8_t destination_mac[MAC_ADDRESS_LENGTH]; // MAC-адрес получателя
    uint8_t source_mac[MAC_ADDRESS_LENGTH];      // MAC-адрес отправителя
    uint16_t ethertype;                          // Тип протокола (IP, ARP и т. д.)
    uint8_t payload[ETHERNET_MAX_PACKET_SIZE - 14]; // Данные
} ethernet_frame_t;

// Инициализация Ethernet-контроллера
void ethernet_init(void);

// Отправка Ethernet-пакета
void ethernet_send(uint8_t *data, uint16_t length);

// Получение Ethernet-пакета
int ethernet_receive(uint8_t *buffer, uint16_t buffer_size);

#endif // ETHERNET_H
