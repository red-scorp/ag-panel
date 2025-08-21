/** @file TemplateTextLCD.h
    @brief AG-Panel Project common TextLCD template interface
    @copyright (C) 2025 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractTextLCD.h"

/** @brief Template class for common TextLCD

    This template class implements common TextLCD for a specific LCD object.
    It's designed to be used as a base for specific LCD classes.
 */
template<typename T>
class TemplateTextLCD : public AbstractTextLCD {
public:

    /** @brief Constructor for TemplateTextLCD

        This constructor initializes the TextLCD with a specific LCD object and its dimensions.
     */
    explicit TemplateTextLCD(
        T* lcdObject,           /**< Pointer to the LCD object */
        uint8_t Columns,        /**< Number of columns of the text LCD */
        uint8_t Rows            /**< Number of rows of the text LCD */
    ) : AbstractTextLCD(nullptr, Columns, Rows), m_LCD(lcdObject) {
        Init();
    }

    /** @brief Destructor for TemplateTextLCD

        This destructor calls Exit() to clean up resources.
     */
    virtual ~TemplateTextLCD() override {
        Exit();
    }

    /** @brief Clear the TextLCD display

        This function clears the display of the TextLCD.
     */
    virtual void Clear() override {
        m_LCD->clear();
    }

    /** @brief Set the cursor position on the TextLCD

        This function sets the cursor to a specific column and row on the TextLCD.
     */
    virtual void SetCursor(
        uint8_t column,     /**< Column position of the cursor */
        uint8_t row         /**< Row position of the cursor */
    ) override {
        m_LCD->setCursor(column, row);
    }

    /** @brief Print a string to the TextLCD

        This function prints a string to the TextLCD.
     */
    virtual void Print(
        const char *str     /**< String to be printed on the TextLCD */
    ) override {
        m_LCD->print(str);
    }

    /** @brief Print a character to the TextLCD

        This function prints a single character to the TextLCD.
     */
    virtual void Print(
        char character      /**< Character to be printed on the TextLCD */
    ) override {
        m_LCD->print(character);
    }

    /** @brief Write a byte to the TextLCD

        This function writes a byte to the TextLCD.
        It is used for low-level communication with the LCD.
     */
    virtual void Write(
        uint8_t byte        /**< Byte to be written to the TextLCD */
    ) override {
        m_LCD->write(byte);
    }

    /** @brief Send a command to the TextLCD

        This function sends a command byte to the TextLCD.
        It is used for controlling the LCD's behavior.
     */    
    virtual void Command(
        uint8_t byte        /**< Command byte to be sent to the TextLCD */
    ) override {
        m_LCD->command(byte);
    }

protected:
    T* m_LCD;       /**< Pointer to the LCD object */

private:
    /** @brief Initialize the TextLCD

        This function initializes the TextLCD by setting up the LCD object.
        @returns true if initialization is successful
     */
    bool Init() {
        return true;
    }

    /** @brief Exit the TextLCD

        This function cleans up resources used by the TextLCD.
     */
    void Exit() {
        m_LCD = nullptr;
    }
};
