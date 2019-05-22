#pragma once

/** Classifications 
 * VXXBY
 * V = Volterra
 * XX = 2019 (Last two digits of year of definition) 
 * B = 400 (First digit of build volume) 
 * X = Machine Configuration (Eg. Volterra Speed/Single)
 * 
 * V194S: Volterra Speed/Single
 * V194D: Volterra Dual
 * V194H: Volterra High Temperature
 * 
**/ 

#define VOLTERRA_2019_400_S          0
#define VOLTERRA_2019_400_D          1
#define VOLTERRA_2019_400_HT         2

#include "_Variant.h"

#define BV(var)       (VARIANT == var)
#define NBV(var)      (VARIANT != var)

#define BV_S()              ( BV(VOLTERRA_2019_400_S) )
#define BV_D()              ( BV(VOLTERRA_2019_400_D) )
#define BV_HT()             ( BV(VOLTERRA_2019_400_HT) )
#define BV_DUAL_NOZZLE()    ( BV(VOLTERRA_2019_400_D) || BV(VOLTERRA_2019_400_HT) )
