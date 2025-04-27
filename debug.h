//
// Created by red on 27.04.2025.
//
#pragma once

#ifndef DEBUG_ON
#define DEBUG_ON 0  // Значение по умолчанию, если не определено
#endif

#if DEBUG_ON
#define X_DEBUG(v) { v }
#define X_DEBUG_DEF(v) v
#else
#define X_DEBUG(v)
#define X_DEBUG_DEF(v)
#endif