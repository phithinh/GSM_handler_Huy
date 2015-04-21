#include <Common.h>
#include "SIM900.h"

uint8 SIM900_Rei_Buffer[1024];
uint16 Sim900_Rei_Buffer_Count = 0;

//char Sim900Tmp0[] = "AT\r\r\nOK\r\n";

//char Sim900Tmp1[] = "AT+CMGD=1,4\r\r\nOK\r\n";

//char Sim900Tmp2[] = "AT+CMGF=1\r\r\nOK\r\n";

char Sim900Tmp0[] = "\r\nOK\r\n";

char Sim900Tmp1[] = "\r\nOK\r\n";

char Sim900Tmp2[] = "\r\nOK\r\n";

char Sim900TmpError[] = "ERROR\r\n";
//\r\n+CMTI: "SM",1\r\n
char Sim900SMSIncoming[] = { '\r', '\n', '+', 'C', 'M', 'T', 'I', ':', ' ', '"',
		'S', 'M', '"', ',', '1', '\r', '\n' };
void SIM900_Init(void) {
	SIM900_Init_McuDriver();
	SIM900_PWR_ON();
	SIM900_NRESET();
	DelayMs(2000);
	SIM900_Buffer_Reset();

        printf("ATE0&W");
		DelayMs(20);
	//Check AT cmd
	while (!SIM900_AT_Rei_Check_CMD(Sim900Tmp0, sizeof(Sim900Tmp0), 0)) {
		LED3_TOG;
		SIM900_Buffer_Reset();
		printf("AT\r");
		DelayMs(200);
	}
	SIM900_Buffer_Reset();
//Clear all SMS
	while (!SIM900_AT_Rei_Check_CMD(Sim900Tmp1, sizeof(Sim900Tmp1), 0)) {
		LED3_TOG;
		SIM900_Buffer_Reset();
		printf("AT+CMGD=1,4\r");
		DelayMs(200);
	}
	SIM900_Buffer_Reset();
//Set SMS in text mode
	while (!SIM900_AT_Rei_Check_CMD(Sim900Tmp2, sizeof(Sim900Tmp2), 0)) {
		LED3_TOG;
		SIM900_Buffer_Reset();
		printf("AT+CMGF=1\r");
		DelayMs(200);
	}
	SIM900_Buffer_Reset();

	do {
//		SIM900_Send_SMS("01283573315","BOARD READY!! ");
		DelayMs(200);
		DelayMs(200);
	} while (SIM900_AT_Rei_Check_CMD(Sim900TmpError, sizeof(Sim900TmpError), 42));
	DelayMs(100);
	DelayMs(100);
    LED3_ON;
	SIM900_Buffer_Reset();
}

uint8 SIM900_AT_Rei_Check_CMD(char tmp[], uint8 SizeOftmp, uint8 PosBuffer) {
	uint8 i;
	for (i = 0; i < SizeOftmp; i++) {
		if (SIM900_Rei_Buffer[i + PosBuffer] != tmp[i])
			return 0;

	}

	return 1;
}
void SIM900_Send_SMS(char NumberPhone[], char Mess[]) {
//Send SMS
	printf("AT+CMGS=");
	USART_SendData(SIM900_USART, '"');
	while (USART_GetFlagStatus(SIM900_USART, USART_FLAG_TC) == eFALSE)
		;
	printf("%s", NumberPhone);
	USART_SendData(SIM900_USART, '"');
	while (USART_GetFlagStatus(SIM900_USART, USART_FLAG_TC) == eFALSE)
		;
	printf("\r");
	DelayMs(1000);
	printf("%s", Mess);
	DelayMs(1000);
	USART_SendData(SIM900_USART, 0x1A);
	while (USART_GetFlagStatus(SIM900_USART, USART_FLAG_TC) == eFALSE)
		;
//SIM900_Buffer_Reset();
	DelayMs(500);

}
extern void GSM_IRQ_Handler(unsigned char p_data_ub);
void SIM900_IRQHandler(void) {
 unsigned char t_rx_data_ub;
	if (USART_GetITStatus(SIM900_USART, USART_IT_RXNE) != RESET) {
      t_rx_data_ub = (uint8) (USART_ReceiveData(
				SIM900_USART));
		SIM900_Rei_Buffer[Sim900_Rei_Buffer_Count] = t_rx_data_ub;
		Sim900_Rei_Buffer_Count++;
		SIM900_Rei_Buffer[1023] = 1;
		if (Sim900_Rei_Buffer_Count == 1024)
			Sim900_Rei_Buffer_Count = 0;
		GSM_IRQ_Handler(t_rx_data_ub);
	}
}
void SIM900_Buffer_Reset(void) {
	uint16 Count = 0;
	for (Count = 0; Count < 1024; Count++) {
		SIM900_Rei_Buffer[Count] = '\0';
	}
	Sim900_Rei_Buffer_Count = 0;
}

void SIM900_NRESET(void) {
	SIM900_NRESET_ON;
	DelayMs(1);
	SIM900_NRESET_OFF;
}

void SIM900_PWR_ON(void) {
	SIM900_CTRL_OFF;
	DelayMs(1000);
	SIM900_CTRL_ON;
	DelayMs(300);
	SIM900_PWRKEY_ON;
	DelayMs(1500);
	SIM900_PWRKEY_OFF;
	DelayMs(1000);
}
void SIM900_Init_McuDriver(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
//SIM900_CTRL_init
	SIM900_CTRL_RCC_ENABLE;
	GPIO_InitStructure.GPIO_Pin = SIM900_CTRL_PIN;
	GPIO_InitStructure.GPIO_Mode = SIM900_CTRL_MODE;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SIM900_CTRL_PORT, &GPIO_InitStructure);
	SIM900_CTRL_OFF;

//SIM900_PWRKEY_init
	SIM900_PWRKEY_RCC_ENABLE;
	GPIO_InitStructure.GPIO_Pin = SIM900_PWRKEY_PIN;
	GPIO_InitStructure.GPIO_Mode = SIM900_PWRKEY_MODE;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SIM900_PWRKEY_PORT, &GPIO_InitStructure);
	SIM900_PWRKEY_OFF;

//SIM900_NRESET_init
	SIM900_NRESET_RCC_ENABLE;
	GPIO_InitStructure.GPIO_Pin = SIM900_NRESET_PIN;
	GPIO_InitStructure.GPIO_Mode = SIM900_NRESET_MODE;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SIM900_NRESET_PORT, &GPIO_InitStructure);
	SIM900_NRESET_OFF;

//SIM900_DTR_init
	SIM900_DTR_RCC_ENABLE;
	GPIO_InitStructure.GPIO_Pin = SIM900_DTR_PIN;
	GPIO_InitStructure.GPIO_Mode = SIM900_DTR_MODE;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SIM900_DTR_PORT, &GPIO_InitStructure);
	SIM900_DTR_OFF;

//SIM900_RING_IND init
	SIM900_RING_IND_RCC_ENABLE;
	GPIO_InitStructure.GPIO_Pin = SIM900_RING_IND_PIN;
	GPIO_InitStructure.GPIO_Mode = SIM900_RING_IND_MODE;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SIM900_RING_IND_PORT, &GPIO_InitStructure);

//SIM900_TX_init
	SIM900_TX_RCC_ENABLE;
	GPIO_InitStructure.GPIO_Pin = SIM900_TX_PIN;
	GPIO_InitStructure.GPIO_Mode = SIM900_TX_MODE;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SIM900_TX_PORT, &GPIO_InitStructure);

//SIM900_RX_init
	SIM900_RX_RCC_ENABLE;
	GPIO_InitStructure.GPIO_Pin = SIM900_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = SIM900_RX_MODE;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SIM900_RX_PORT, &GPIO_InitStructure);

	SIM900_USART_RCC_ENABLE;
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = SIM900_BAUD;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(SIM900_USART, &USART_InitStructure);
	USART_Cmd(SIM900_USART, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;
	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = SIM900_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	/* Enable USARTy Receive and Transmit interrupts */
	USART_ITConfig(SIM900_USART, USART_IT_RXNE, ENABLE);
	USART_ITConfig(SIM900_USART, USART_IT_TXE, DISABLE);
}

