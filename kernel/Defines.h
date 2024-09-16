#pragma once

#define SECTION(name) __attribute__((section(#name)))
#define ALIGN(num) __attribute__((aligned(num)))
