/*!
 * @file
 * @brief
 */

#include "uart1.h"
#include "stm8s_uart1.h"
#include "stm8s_clk.h"

void uart1_init(void) {
  // Un-gate clock for UART1
  CLK->PCKENR1 |= (1 << CLK_PERIPHERAL_UART1);

  // Configure 230.4k
  // 16,000,000 / UART_DIV = 230,400 => UART_DIV ~= 69 = 0x45
  UART1->BRR2 = 0x5;
  UART1->BRR1 = 0x4;

  // Enable TX, RX
  UART1->CR2 |= UART1_CR2_TEN | UART1_CR2_REN;

  // Enable RXNE (receive data register not empty) interrupt
  UART1->CR2 |= UART1_CR2_RIEN;
}

void uart1_write(uint8_t byte) {
  UART1->DR = byte;
  while(!(UART1->SR & UART1_SR_TC)) {
  }
}

uint8_t uart1_read(void) {
  while(!(UART1->SR & UART1_SR_RXNE)) {
  }
  return UART1->DR;
}
