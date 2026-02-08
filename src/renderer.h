#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <stdint.h>
#include <termios.h>

void renderer_init(struct termios *old_settings);
void renderer_update(uint8_t *const buffer);
int renderer_process_input(uint8_t *keys);
void renderer_close(struct termios *old_settings);

#endif
