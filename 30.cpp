#include <stdio.h>
#include <stdint.h>

// CBC-MAC calculation (simplified for one-block message)
uint8_t cbc_mac(uint8_t key, uint8_t message) {
    // Example encryption: XOR with key (simplified)
    return message ^ key;
}

int main() {
    uint8_t key = 0x5A; // Example key
    uint8_t message = 0x33; // Example one-block message

    uint8_t mac = cbc_mac(key, message);
    printf("MAC: %02X\n", mac);

    uint8_t two_block_message[2];
    two_block_message[0] = message;
    two_block_message[1] = message ^ mac;

    uint8_t mac_two_blocks = cbc_mac(key, two_block_message[0]);
    mac_two_blocks = cbc_mac(key, two_block_message[1] ^ mac_two_blocks);
    printf("MAC for two-block message: %02X\n", mac_two_blocks);

    return 0;
}
