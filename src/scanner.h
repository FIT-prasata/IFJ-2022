#pragma once

// Filename: scanner.h
// IFJ 2022/2023 project
// TRP variant
//
// Scanner for lexical analysis - header file
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

// EXTERNAL INCLUDES
#include <stdio.h>

// LOCAL INCLUDES
#include "error.h"

// !!! DUMMY STRUCT -> REPLACE WITH PROPER TOKEN STRUCT !!!
typedef struct Token {
    int type;
    int value;
} Token_t;