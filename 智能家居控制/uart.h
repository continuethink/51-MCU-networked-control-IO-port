#ifndef _uart_H_
#define _uart_H_

void Uart_Init();
void Uart_SendByte(unsigned char Byte);
void Uart_SendFile(unsigned char *file);

#endif