
#include "../../inc/MarlinConfig.h"

/**
 * M2122: Reset LPC1768 host
 */

#ifdef TARGET_LPC1768
  #include "../gcode.h"

  void GcodeSuite::M2122() {
    SERIAL_ECHOLNPGM("Resetting controller...");
    NVIC_SystemReset();
  }

#endif
