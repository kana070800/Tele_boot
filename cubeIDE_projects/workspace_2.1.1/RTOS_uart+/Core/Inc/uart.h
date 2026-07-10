//#ifndef __UART3H__
//#define __UART3H__
//
//void UART3_Init(void);
//void UART3_Send_Byte(char ch);
//void UART3_Send_String(char* p);
//uint32_t UART3_Printf(const char* msg, ...);
//
//#endif

#ifndef __UART3H__
#define __UART3H__

#include <stdint.h>

void UART3_Init(void);
void UART3_Send_Byte_IT(char ch);
uint8_t UART3_Receive_Byte_IT(char* pData);
void UART3_Send_String(char* p);
uint32_t UART3_Printf(const char* msg, ...);

#endif /* __UART3H__ */
