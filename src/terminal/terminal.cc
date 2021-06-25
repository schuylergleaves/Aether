#include "terminal.h"

void Terminal::init() 
{
    this->row = 0;
    this->col = 0;
    this->color = VGA::vgaEntry(VGA::VGA_COLOR_LIGHT_GREY, VGA::VGA_COLOR_BLACK);

    this->buffer = (uint16_t*) 0xB8000;
    for (size_t y = 0; y < VGA::HEIGHT; y++) {
        for (size_t x = 0; x < VGA::WIDTH; x++) {
            const size_t index = y * VGA::WIDTH + x;
            buffer[index] = VGA::vgaEntry(' ', color);
        }
    }
}

void Terminal::writeString(const char* data) 
{
    for (size_t i = 0; i < strlen(data); i++) {
        putEntryAt(data[i], color, col, row);
    }
}

void Terminal::setColor(uint8_t newColor) 
{
    color = newColor;
}

void Terminal::putEntryAt(char c, uint8_t color, size_t x, size_t y) 
{
    if (c == '\n') {
        return;
    }
    
    const size_t index = y * VGA::WIDTH + x;
    buffer[index] = VGA::vgaEntry(c, color);

    if (++col == VGA::WIDTH || c == '\n') {
        col = 0;
        if (++row == VGA::HEIGHT)
            row = 0;
    }
}

size_t Terminal::strlen(const char* str) 
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}


