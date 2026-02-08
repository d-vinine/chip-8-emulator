#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <stdint.h>

void renderer_update(uint8_t *const buffer);
int renderer_process_input(uint8_t *keys);

#endif
