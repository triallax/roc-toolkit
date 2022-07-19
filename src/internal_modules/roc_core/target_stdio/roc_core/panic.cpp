/*
 * Copyright (c) 2015 Roc Streaming authors
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <stdarg.h>
#include <stdio.h>

#include "roc_core/die.h"
#include "roc_core/panic.h"

namespace roc {
namespace core {

void panic(const char* module, const char* file, int line, const char* format, ...) {
    fprintf(stderr, "\n%s:%d: error: roc_panic()\n", file, line);
    fflush(stderr);

    char message[256] = {};
    size_t message_sz = sizeof(message) - 1;

    int off = snprintf(message, message_sz, "%s: ", module);
    if (off > 0) {
        message_sz -= (size_t)off;
    }

    va_list args;
    va_start(args, format);
    vsnprintf(message + off, message_sz, format, args);
    va_end(args);

    die_gracefully(message, true);
}

} // namespace core
} // namespace roc
