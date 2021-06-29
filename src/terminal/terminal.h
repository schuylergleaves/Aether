#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga.h"
#include "../libc/string/string.h"

class Terminal {
public:
    static void init();
    static Terminal& get();

    void writeString(const char* data);
    void writeChar(const char c);
    void setColor(uint8_t newColor);

    Terminal();

protected:


private:
    size_t row;
    size_t col;
    uint8_t color;
    uint16_t* buffer;

    void putEntryAt(char c, uint8_t color, size_t x, size_t y);
    void handleWrapping();
};