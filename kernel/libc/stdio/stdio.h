#pragma once

#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include "../string/string.h"
#include "../../terminal/terminal.h"

#define EOF (-1)

int printf(const char* format, ...);