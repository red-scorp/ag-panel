/** @file AnalogMatrix.h
    @brief AG-Panel Project analog keypad keyboard interface
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

/** @brief Analog Matrix class

    This class implements analog matrix based on several buttons connected with different resistors.
 */
class AnalogMatrix: public AbstractKeyboard {

public:
    explicit AnalogMatrix(
        uint8_t Columns,            /**< Number of columns of the matrix */
        uint8_t Rows,               /**< Number of rows of the matrix */
        const uint16_t *DataArray,  /**< Array of analog values for all different keys of the matrix */
        uint8_t DataPin             /**< Matrix input analog pin */
    ): AbstractKeyboard(),
        m_Columns(Columns),
        m_Rows(Rows),
        m_DataArray(DataArray),
        m_DataPin(DataPin) { Init(); }
    virtual ~AnalogMatrix() override { Exit(); }

    virtual uint8_t GetKey() override;
    virtual uint8_t GetKeyCount() override;

protected:
    uint8_t m_Columns;            /**< Number of columns of the matrix */
    uint8_t m_Rows;               /**< Number of rows of the matrix */
    const uint16_t *m_DataArray;  /**< Array of analog values for all different keys of the matrix */
    uint8_t m_DataPin;            /**< Matrix input analog pin */

private:
    bool Init();
    void Exit();
};
