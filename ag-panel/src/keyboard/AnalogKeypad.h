/** @file AnalogKeypad.h
    @brief AG-Panel Project analog keypad keyboard interface
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

/** @brief Positions of Keys in range array
 */
enum {
    AbstractKeyboardAnalogDataRangeIndexUp = 0,
    AbstractKeyboardAnalogDataRangeIndexDown,
    AbstractKeyboardAnalogDataRangeIndexLeft,
    AbstractKeyboardAnalogDataRangeIndexRight,
    AbstractKeyboardAnalogDataRangeIndexSelect,
    AbstractKeyboardAnalogDataRangeIndexMax     /**< Data range array length */
};

/** @brief Analog Data Range struct

    This structure helps to define a range of analog input values for key pressed.
 */
struct AnalogDataRange {
    uint16_t min;     /**< Minimum of analog input range */
    uint16_t max;     /**< Maximum of analog input range */
};

/** @brief Analog Keypad class

    This class implements analog keypad based on several buttons connected with different resistors.
 */
class AnalogKeypad: public AbstractKeyboard {

public:
    explicit AnalogKeypad(
        uint8_t DataPin,     /**< Keypad input analog pin */
        const AnalogDataRange *DataRangeArray   /**< Data ranges for keys */
    ): AbstractKeyboard(),
        m_DataPin(DataPin),
        m_DataRangeArray(DataRangeArray) { Init(); }
    virtual ~AnalogKeypad() override { Exit(); }

    virtual uint8_t GetKey() override;
    virtual uint8_t GetKeyCount() override;

protected:
    uint8_t m_DataPin;    /**< Keypad input analog pin */
    const AnalogDataRange *m_DataRangeArray;  /**< Data ranges for keys */

private:
    bool Init();
    void Exit();
};
