#include <stdint.h>
#include "syscon.h"
#include "../uart/uart.h"

void poweroff(void) {
  print("Poweroff requested");
  *(uint32_t *)SYSCON_ADDR = 0x5555;
}

void reboot(void) {
  print("Reboot requested");
  *(uint32_t *)SYSCON_ADDR = 0x7777;
}