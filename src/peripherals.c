// Header
#include "peripherals.h"

// Includes -------------------------------------------------------------------------------------------------------------------

// Global Peripherals ---------------------------------------------------------------------------------------------------------

// Public 
mc24lc32_t physicalEeprom;
virtualEeprom_t virtualEeprom;

// Private 
eeprom_t readonlyWriteonlyEeprom;

// Configuration --------------------------------------------------------------------------------------------------------------

/// @brief Configuration of the I2C bus.
static const I2CConfig I2C1_CONFIG =
{
    .op_mode = OPMODE_I2C,
    .clock_speed = 100000,
    .duty_cycle = STD_DUTY_CYCLE
};

/// @brief Configuration of the on-board EEPROM.
static const mc24lc32Config_t PHYSICAL_EEPROM_CONFIG =
{
    .addr = 0x50,
    .i2c = &I2CD1,
    .timeout = TIME_MS2I (500),
    .magicString = EEPROM_MAP_STRING,
    .dirtyHook = peripheralsReconfigure

};

/// @brief Configuration of the Fan Board's virtual EEPROM.
static const virtualEepromConfig_t VIRTUAL_EEPROM_CONFIG = 
{
    .count = 2,
    .entries = 
    {
        {
            .eeprom = (eeprom_t*) &physicalEeprom,
            .addr = 0x0000,
            .size = 0x1000
        },
        {
            .eeprom = &readonlyWriteonlyEeprom,
            .addr = 0x1000,
            .size = 0x1000
        }
    }
};

bool peripheralsInit()
{
    // I2C driver 1 initialization.
    if (i2cStart (&I2CD1, &I2C1_CONFIG) != MSG_OK)
        return false;

    // Physical EEPROM driver initialization.
    if (!mc24lc32Init(&physicalEeprom, &PHYSICAL_EEPROM_CONFIG) && physicalEeprom.state == MC24LC32_STATE_FAILED)
        return false;

    // Read-only / Write-only EEPROM initialization.
    eepromInit (&readonlyWriteonlyEeprom, eepromWriteonlyWrite, eepromReadonlyRead);

    // Virtual memory initialization.
    virtualEepromInit (&virtualEeprom, &VIRTUAL_EEPROM_CONFIG);

    // Re-configurable peripherals are not considered fatal.
    peripheralsReconfigure(NULL);
    return true;
}

void peripheralsReconfigure(void* caller)
{
    (void) caller;
}