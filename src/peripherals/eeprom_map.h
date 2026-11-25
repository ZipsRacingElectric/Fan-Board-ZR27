#ifndef EEPROM_MAP_H
#define EEPROM_MAP_H

// EEPROM Mapping -------------------------------------------------------------------------------------------------------------
//
// Author: Jake Nowak
// Date Created: 2026.11.25
//
// Description: Structing mapping the data of an EEPROM data to variables.

// Includes -------------------------------------------------------------------------------------------------------------------

#include "peripherals/adc/analog_linear.h"

// Constants ------------------------------------------------------------------------------------------------------------------

/// @brief The magic string of the EEPROM. Update this value every time the memory map changes to force manual re-programming.
#define EEPROM_MAP_STRING "FAN_BOARD_2026_11_25"

// Datatypes ------------------------------------------------------------------------------------------------------------------

typedef struct 
{   
    uint8_t pad0 [16];
} eepromMap_t;

// Functions ------------------------------------------------------------------------------------------------------------------

/// @brief Handles a write to the 'write-only' section of the device's virtual EEPROM.
/// @note Currently is not implemented.
bool eepromWriteonlyWrite (void* eeprom, uint16_t addr, const void* data, uint16_t dataCount);

/// @brief Handles a read from the 'read-only' section of the device's virtual EEPROM.
/// @note Used for reading temporary data.
bool eepromReadonlyRead (void* eeprom, uint16_t addr, void* data, uint16_t dataCount);

#endif // EEPROM_MAP_H