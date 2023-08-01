/** @file SimpleButton.h
    @brief AG-Panel Project simple button keyboard interface
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

/** @brief Simple Button class

    This class implements simple button(s) connected to single pin each.
 */
class SimpleButton: public AbstractKeyboard {

public:
    explicit SimpleButton(
        uint8_t Number,             /**< Number of buttons (pins) */
        const uint8_t *PinsArray    /**< Array of digital pins for buttons */
    ): AbstractKeyboard(),
        m_Number(Number),
        m_PinsArray(PinsArray) { Init(); }
    virtual ~SimpleButton() override { Exit(); }

    virtual uint8_t GetKey() override;
    virtual uint8_t GetKeyCount() override;

protected:
    uint8_t m_Number;             /**< Number of buttons (pins) */
    const uint8_t *m_PinsArray;   /**< Array of digital pins for buttons */

private:
    bool Init();
    void Exit();
};
