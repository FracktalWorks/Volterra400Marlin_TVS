// #ifndef FWCONFIG_H
// #define FWCONFIG_H

#pragma once

//===========================================================================
//========================= Fracktal Works Julia 2018 =======================
//===========================================================================

#include "./_FracktalWorks.h"

#ifndef VARIANT
  #error "Variant not defined"
#endif

/**  Bed dimensions  **/
#define X_BED_SIZE  500
#define Y_BED_SIZE  500
#define Z_MAX_POS   390

#define X_MIN_POS 0
#define Y_MIN_POS 0
#define Z_MIN_POS 0

/**  Stepper  **/
#if BV_DUAL_NOZZLE()
  #define INVERT_X_DIR true
  #define INVERT_Y_DIR true
  #define INVERT_Z_DIR true

  #define INVERT_E0_DIR true
  #define INVERT_E1_DIR false
#else
  #define INVERT_X_DIR false
  #define INVERT_Y_DIR false
  #define INVERT_Z_DIR false

  #define INVERT_E0_DIR true
#endif

// /**  Enstops  **/
#define USE_XMIN_PLUG
#define USE_YMAX_PLUG
#define USE_ZMAX_PLUG

// /**  Homing  **/
#define X_HOME_DIR -1
#define Y_HOME_DIR 1
#define Z_HOME_DIR 1

#if BV_DUAL_NOZZLE()
  #define MANUAL_X_HOME_POS -40 // (-1 * HOTEND_OFFSET_X[1])
  #define MANUAL_Y_HOME_POS Y_BED_SIZE
  #define MANUAL_Z_HOME_POS Z_MAX_POS
#endif

#define HOMING_FEEDRATE_XY (50 * 60)
#define HOMING_FEEDRATE_Z (20 * 60)

/**  Motion  **/
#define DEFAULT_AXIS_STEPS_PER_UNIT   { 160, 160, 1007.874, 280}
#define DEFAULT_MAX_FEEDRATE          {  200, 200, 20, 45 }
#define DEFAULT_MAX_ACCELERATION      { 800, 800, 50, 10000 }

#define DEFAULT_ACCELERATION 800          // X, Y, Z and E acceleration for printing moves
#define DEFAULT_RETRACT_ACCELERATION 2000 // E acceleration for retracts
#define DEFAULT_TRAVEL_ACCELERATION 1000  // X, Y, Z acceleration for travel (non printing) moves

#define S_CURVE_ACCELERATION
#define JUNCTION_DEVIATION
#if ENABLED(JUNCTION_DEVIATION)
  #define JUNCTION_DEVIATION_MM 0.05
#endif

#if DISABLED(JUNCTION_DEVIATION)
  #define DEFAULT_XJERK 10.0
  #define DEFAULT_YJERK 10.0
  #define DEFAULT_ZJERK 0.4
#endif
#define DEFAULT_EJERK 10.0

/** Extruder Count **/
#if BV_DUAL_NOZZLE()
  #define EXTRUDERS 2
#else
  #define EXTRUDERS 1
#endif

/*** Dual Nozzle ***/
#if BV_DUAL_NOZZLE()
  #define SWITCHING_NOZZLE
  #define SWITCHING_NOZZLE_SERVO_NR 0
  #define SWITCHING_NOZZLE_SERVO_ANGLES { 0, 180 }   // Angles for E0, E1

  #define NUM_SERVOS 1
  #define DEACTIVATE_SERVOS_AFTER_MOVE

  #define HOTEND_OFFSET_X {0.0, 36.0}
  #define HOTEND_OFFSET_Y {0.0,  0.0}
  #define HOTEND_OFFSET_Z {0.0, -4.0}
#endif

/**  Thermistor  **/
#define TEMP_SENSOR_0       20
#if BV_DUAL_NOZZLE()
  #define TEMP_SENSOR_1     20
#else
  #define TEMP_SENSOR_1     0
#endif
#define TEMP_SENSOR_BED     3
#define TEMP_SENSOR_CHAMBER 3
#define TEMP_SENSOR_FILBOX  3

/**  Thermal  **/
#define TEMP_RESIDENCY_TIME 1
#define TEMP_HYSTERESIS 4
#define TEMP_BED_RESIDENCY_TIME 2

/**  PID temperature settings  **/
#define DEFAULT_Kp 42.96
#define DEFAULT_Ki 5.14
#define DEFAULT_Kd 89.73

/**  Bed leveling  **/
// #define Z_MIN_PROBE_ENDSTOP
#define FIX_MOUNTED_PROBE
#define Z_PROBE_OFFSET_FROM_EXTRUDER 0.2 // Z offset: -below +above  [the nozzle]

#define DELAY_BEFORE_PROBING 1000 // (ms) To prevent vibrations from triggering sensor

#define MIN_PROBE_EDGE 25
#define Z_PROBE_SPEED_FAST (HOMING_FEEDRATE_Z/10)
#define Z_PROBE_SPEED_SLOW (Z_PROBE_SPEED_FAST / 15)
#define MULTIPLE_PROBING 2

#define Z_CLEARANCE_DEPLOY_PROBE    5 // Z Clearance for Deploy/Stow
#define Z_CLEARANCE_BETWEEN_PROBES  3 // Z Clearance between probe points
#define Z_CLEARANCE_MULTI_PROBE     1 // Z Clearance between multiple probes

#define Z_MIN_PROBE_REPEATABILITY_TEST

#define AUTO_BED_LEVELING_BILINEAR
#define DEBUG_LEVELING_FEATURE

// /**  Additional features  **/
#define NOZZLE_PARK_FEATURE

//===========================================================================
//===================== End of Fracktal Works Julia 2018 ====================
//===========================================================================

// #endif
