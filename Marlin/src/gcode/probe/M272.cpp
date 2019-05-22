/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "../../inc/MarlinConfig.h"

#if HAS_BED_PROBE && HOTENDS > 1

#include "../gcode.h"
#include "../../module/motion.h"

#include "../../module/tool_change.h"
#include "../../module/planner.h"
#include "../../module/configuration_store.h"

/**
 * M272: Automatic hotend Z-offset calculation
 *
 * Parameters:
 *
 *   S   Save to EEPROM
 */
void GcodeSuite::M272() {
    // const uint8_t old_tool_index = active_extruder;
    const bool save = parser.seen('S');
    float z1, z2, del_z;

    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) {
        SERIAL_ECHOLNPAIR("M272: save=", save);
      }
    #endif

    // Step 1: Home if unhomed
    if (axis_unhomed_error()) home_all_axes();

    // Step 2: Zero T1 hotend Z-offset
    if (save) {
      hotend_offset[Z_AXIS][1] = 0;
    }

    // Step 3: Tool change to T0
    tool_change(0, MMM_TO_MMS(HOMING_FEEDRATE_Z), false);
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) {
        SERIAL_ECHOPGM("M272: S3 Tool change to T0");
        SERIAL_ECHOLNPAIR(", current_position[Z_AXIS]=", current_position[Z_AXIS]);
      }
    #endif

    // Step 4: Go to staging XYZ
    do_blocking_move_to_xy(X_BED_SIZE / 2, Y_BED_SIZE / 2, MMM_TO_MMS(HOMING_FEEDRATE_XY));
    do_blocking_move_to_z(15, MMM_TO_MMS(HOMING_FEEDRATE_Z));
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) {
        SERIAL_ECHOPGM("M272: S4 Go to staging XYZ");
        SERIAL_ECHOPAIR(", current_position={", current_position[X_AXIS]);
        SERIAL_ECHOPAIR(", ", current_position[Y_AXIS]);
        SERIAL_ECHOPAIR(", ", current_position[Z_AXIS]);
        SERIAL_ECHOLNPGM("}");
      }
    #endif


    // Step 5: Probe Z
    G30();
    planner.synchronize();
    z1 = current_position[Z_AXIS];
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) {
        SERIAL_ECHOPGM("M272: S5 Probe Z");
        SERIAL_ECHOLNPAIR(", z1=", z1);
      }
    #endif

    // Step 6: Go to staging Z
    do_blocking_move_to_z(15, MMM_TO_MMS(HOMING_FEEDRATE_Z));
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) {
        SERIAL_ECHOPGM("M272: S6 Go to staging Z");
        SERIAL_ECHOLNPAIR(", current_position[Z_AXIS]=", current_position[Z_AXIS]);
      }
    #endif

    // Step 7: Tool change to T1
    tool_change(1, MMM_TO_MMS(HOMING_FEEDRATE_Z), false);
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) {
        SERIAL_ECHOPGM("M272: S7 Tool change to T1");
        SERIAL_ECHOLNPAIR(", current_position[Z_AXIS]=", current_position[Z_AXIS]);
      }
    #endif

    // Step 8: Probe Z
    G30();
    planner.synchronize();
    z2 = current_position[Z_AXIS];
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) {
        SERIAL_ECHOPGM("M272: S8 Probe Z");
        SERIAL_ECHOLNPAIR(", z2=", z2);
      }
    #endif

    // Step 9: Go to staging Z
    do_blocking_move_to_z(15, MMM_TO_MMS(HOMING_FEEDRATE_Z));
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) {
        SERIAL_ECHOPGM("M272: S9 Go to staging Z");
        SERIAL_ECHOLNPAIR(", current_position[Z_AXIS]=", current_position[Z_AXIS]);
      }
    #endif

    // Step 10: Calculate offset
    del_z = z2 + z1;
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) {
        SERIAL_ECHOPGM("M272: S10 Calculate offset");
        SERIAL_ECHOLNPAIR(", del_z=", del_z);
      }
    #endif

    // Step 11: Set offset
    if (save) {
      hotend_offset[Z_AXIS][1] = (-1.0 * del_z);
      (void) settings.save();
    }
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) {
        SERIAL_ECHOPGM("M272: S11 Set offset");
        SERIAL_ECHOLNPAIR(", hotend_offset[Z_AXIS][1]=", hotend_offset[Z_AXIS][1]);
      }
    #endif

    // Step 12: T0 and Home
    tool_change(0, MMM_TO_MMS(HOMING_FEEDRATE_Z), false);
    home_all_axes();
}

#endif // HAS_BED_PROBE
