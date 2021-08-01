#include "terminal.h"

static Terminal terminal;

void Terminal::init() {
    terminal.init_();
    terminal.writeString("Terminal Initialized!\n");
}

void Terminal::init_() {
    this->row = 0;
    this->col = 0;
    this->color = VGA::entryColor(VGA::VGA_COLOR_GREEN, VGA::VGA_COLOR_BLACK);

    this->buffer = (uint16_t*) VGA::BUFFER_ADDR;
    for (size_t i = 0; i < VGA::HEIGHT; i++) {
        for (size_t j = 0; j < VGA::WIDTH; j++) {
            const size_t index = i * VGA::WIDTH + j;
            buffer[index] = VGA::entry(' ', color);
        }
    }
}

Terminal& Terminal::get() {
    return terminal;
}

void Terminal::writeString(const char* data) {
    for (size_t i = 0; i < strlen(data); i++) {
        writeChar(data[i]);
    }
}

void Terminal::writeChar(const char c) {
    putEntryAt(c, color, col, row);
}

void Terminal::setColor(uint8_t newColor) {
    color = newColor;
}

void Terminal::putEntryAt(char c, uint8_t color, size_t row, size_t col) {
    switch (c) {
        // For line break we want to push col to the end so
        // it wraps over.
        case '\n':
            this->col = VGA::WIDTH;
            break;

        default:
            const size_t index = col * VGA::WIDTH + row;
            buffer[index] = VGA::entry(c, color);

            this->col++;
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




