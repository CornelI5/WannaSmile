#ifndef LEXER_H
#define LEXER_H

#include "token.h"

// Scans raw source string stream and populates the token array buffer
void scan_wannasmile(const char *source, Token *stream);

#endif
