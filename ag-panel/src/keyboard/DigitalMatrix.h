/** @file DigitalMatrix.h
    @brief AG-Panel Project digital keypad keyboard interface
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

/** @brief Digital Matrix class

    This class implements digital matrix based on several buttons connected between columns and rows wires.
 */
class DigitalMatrix: public AbstractKeyboard {

public:
    explicit DigitalMatrix(
        uint8_t Columns,            /**< Number of columns of the matrix */
        uint8_t Rows,               /**< Number of rows of the matrix */
        const uint8_t *CPinsArray,  /**< Array of digital pins for columns of the matrix */
        const uint8_t *RPinsArray   /**< Array of digital pins for rows of the matrix */
    ): AbstractKeyboard(),
        m_Columns(Columns),
        m_Rows(Rows),
        m_CPinsArray(CPinsArray),
        m_RPinsArray(RPinsArray) { Init(); }
    virtual ~DigitalMatrix() override { Exit(); }

    virtual uint8_t GetKey() override;
    virtual uint8_t GetKeyCount() override;

protected:
    uint8_t m_Columns;            /**< Number of columns of the matrix */
    uint8_t m_Rows;               /**< Number of rows of the matrix */
    const uint8_t *m_CPinsArray;  /**< Array of digital pins for columns of the matrix */
    const uint8_t *m_RPinsArray;  /**< Array of digital pins for rows of the matrix */

private:
    bool Init();
    void Exit();
};
