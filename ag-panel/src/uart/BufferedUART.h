/*!
  \file BufferedUART.h
  \brief AG-Panel Project buffered UART interface
  \copyright (C) 2019-2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractUART.h"

/*!
  \brief Default buffer size in bytes for buffered UART if no other value is given.
 */
const auto DefaultBufferedUARTBufferSize = 512;

/*!
  \brief Hardware UART class

  This is a class which implements buffred UART filter.
  This class requires another UART class for I/O operations.
 */
class BufferedUART: public AbstractUART {

public:
  explicit BufferedUART(
    AbstractUART *UART,     /*!< Real UART for I/O operations */
    uint32_t BufferSize = DefaultBufferedUARTBufferSize /*!< Size of UART Buffer */
  ): AbstractUART(),
    m_BufferSize(BufferSize),
    m_UART(UART),
    m_Buffer(nullptr),
    m_BufferFilled(0)
    { Init(); }
  virtual ~BufferedUART() override { Exit(); }

  virtual uint8_t PutCh(uint8_t txbyte) override;
  virtual uint8_t GetCh() override;
  virtual void Prefill() override;
  virtual uint32_t Available() override;

protected:
  uint32_t m_BufferSize;    /*!< Size of UART buffer */
  AbstractUART *m_UART;     /*!< Pointer to an UART for I/O operations */
  uint8_t *m_Buffer;        /*!< Pointer to UART buffer */
  uint32_t m_BufferFilled;  /*!< Number of bytes stored in UART buffer */

private:
  bool Init();
  void Exit();
  uint8_t PushBuffer();
  uint8_t FillBuffer();
};
