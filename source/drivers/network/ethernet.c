#include "ethernet.h"
#include "io.h"
#include "utils.h"

// Определение базового порта для Ethernet
#define ETHERNET_REG_STATUS 0x3000  // Пример адреса регистра состояния
#define ETHERNET_REG_CONTROL 0x3004 // Пример адреса регистра управления
#define ETHERNET_REG_TX 0x3010      // Пример адреса для отправки пакетов
#define ETHERNET_REG_RX 0x3020      // Пример адреса для приема пакетов

// Структура для Ethernet-кадра
typedef struct {
    uint8_t dest_mac[6];  // MAC-адрес получателя
    uint8_t src_mac[6];   // MAC-адрес отправителя
    uint16_t ethertype;   // Тип протокола (например, IPv4, ARP и т.д.)
    uint8_t data[1500];   // Данные
    uint32_t crc;         // Контрольная сумма (CRC)
} ethernet_frame_t;

// Функция инициализации Ethernet-адаптера
void init_ethernet(void) {
    // Установка режима Ethernet
    outb(ETHERNET_REG_CONTROL, 0x01);  // Включаем Ethernet интерфейс
    print_string("Ethernet initialized.\n");

    // Настройка MAC-адреса устройства (например, можно задать заранее или получить динамически)
    uint8_t mac_address[6] = {0x00, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E};
    set_mac_address(mac_address);
}

// Функция для настройки MAC-адреса
void set_mac_address(uint8_t mac[6]) {
    // Установка MAC-адреса в регистры устройства
    for (int i = 0; i < 6; i++) {
        outb(ETHERNET_REG_STATUS + i, mac[i]);
    }
    print_string("MAC address set.\n");
}

// Функция отправки пакета Ethernet
void send_ethernet_packet(ethernet_frame_t *frame) {
    // Запись данных в регистры для отправки
    for (int i = 0; i < sizeof(ethernet_frame_t); i++) {
        outb(ETHERNET_REG_TX + i, ((uint8_t *)frame)[i]);
    }

    // Установка флага на отправку
    outb(ETHERNET_REG_CONTROL, 0x02);  // Команда на отправку пакета
    print_string("Ethernet packet sent.\n");
}

// Функция получения пакета Ethernet
void receive_ethernet_packet(ethernet_frame_t *frame) {
    // Чтение данных из регистров Ethernet
    for (int i = 0; i < sizeof(ethernet_frame_t); i++) {
        ((uint8_t *)frame)[i] = inb(ETHERNET_REG_RX + i);
    }
    print_string("Ethernet packet received.\n");
}

// Вспомогательная функция для печати данных (например, для отладки)
void print_ethernet_frame(ethernet_frame_t *frame) {
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
