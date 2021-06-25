#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga.h"

class Terminal {
public:
    void init();
    void writeString(const char* data);
    void setColor(uint8_t newColor);

private:
    size_t row;
    size_t col;
    uint8_t color;
    uint16_t* buffer;

    size_t strlen(const char* str);
    void putEntryAt(char c, uint8_t color, size_t x, size_t y);
};