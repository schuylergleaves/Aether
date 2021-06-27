#include "terminal.h"

void Terminal::init() 
{
    this->row = 0;
    this->col = 0;
    this->color = VGA::entryColor(VGA::VGA_COLOR_GREEN, VGA::VGA_COLOR_BLACK);

    this->buffer = (uint16_t*) VGA::BUFFER_ADDR;
    for (size_t y = 0; y < VGA::HEIGHT; y++) {
        for (size_t x = 0; x < VGA::WIDTH; x++) {
            const size_t index = y * VGA::WIDTH + x;
            buffer[index] = VGA::entry(' ', this->color);
        }
    }
}

void Terminal::writeString(const char* data) 
{
    for (size_t i = 0; i < strlen(data); i++) {
        writeChar(data[i]);
    }
}

void Terminal::writeChar(const char c) {
    putEntryAt(c, this->color, this->col, this->row);
}

void Terminal::setColor(uint8_t newColor) 
{
    color = newColor;
}

void Terminal::putEntryAt(char c, uint8_t color, size_t x, size_t y) 
{
    switch (c) {
        // For line break we want to push col to the end so
        // it wraps over.
        case '\n':
            col = VGA::WIDTH;
            break;

        default:
            const size_t index = y * VGA::WIDTH + x;
            buffer[index] = VGA::entry(c, color);

            col++;
            break;
    }

    handleWrapping();
}

void Terminal::handleWrapping() {
    if (col == VGA::WIDTH) {
        col = 0;
        row++;

        if (row == VGA::HEIGHT) {
            row = 0;
        }
    }
}




