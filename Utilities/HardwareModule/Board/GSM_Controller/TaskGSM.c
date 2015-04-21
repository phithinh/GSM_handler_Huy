#define _TASK_GSM_C_

#include <PlatFormType.h>
#include "TaskGSM.h"
#include "GSM_Serial.h"
#include "../SIM900/SIM900.h"

structListSMS strtListSMS;
structSMSMessageInfo strtSMSData;

enumGSMTask gGSMTask_Index;
structPhoneNumberInfo gPhoneBook[PHONE_BOOK_SIZE] = {
		{ 		.bPhoneBookIdx = 0,
				.sPhoneNumber = "+8490953570",
				.sPhoneName = "Hai Tran", },
		{		.bPhoneBookIdx = 1,
				.sPhoneNumber = "+84938819622",
				.sPhoneName = "Hung Rua", },
		{ 		.bPhoneBookIdx = 2,
				.sPhoneNumber = "+84986035797",
				.sPhoneName = "Hai Su", },
		{ 		.bPhoneBookIdx = 3,
				.sPhoneNumber = "+84982988687",
				.sPhoneName = "Sep Man", },
		{		.bPhoneBookIdx = 0xFF,
				.sPhoneNumber = "",
				.sPhoneName = "", }
};

void TaskGSM_Init(void){
	/*Initialize GSM Module */
	GSM_Init();

	GSM_Reset();
	GSM_NewSMSAlertFunc(eENABLE);
	//GSM_SendSMSByPhoneNumber("+84906558678","gsm");
//	SIM900_Send_SMS("+84906558678","gsm");
	gGSMTask_Index = eGSMTask_SendSMS;
}
/*-----------------------------------------------------------------------------
 *Engineer:
 *Historical:
 *Function name:
 *Description:
 *Input:
 *Output:
 -----------------------------------------------------------------------------*/
void TaskGSMProcess(void) {
//	portTickType xLastWakeTime;
//	enumbool curButton1 = eFALSE, lastButton1 = eFALSE, curButton2 = eFALSE,
//			lastButton2 = eFALSE, curButton3 = eFALSE, lastButton3 = eFALSE;
	enumbool first = eTRUE;
	static enumGSMTask eOldTask;
	uint8 i = 1, bIndex = 0;

//	/*Initialize GSM Module */
//	GSM_Init();
//
//	GSM_Reset();
//	GSM_NewSMSAlertFunc(eENABLE);

//	xLastWakeTime = xTaskGetTickCount();
//	for (;;) {
		/* Execute the task only if a certain time has elapsed */
//		vTaskDelayUntil(&xLastWakeTime, TASK_GSM_PROCESS_RATE_MS);

		//        GSM_CheckSIMOrReady();

		switch (gGSMTask_Index) {
		case eGSMTask_ClearMessage:
			if (i < 40)
				GSM_DeleteSMSByIndex(i++);
			else
				gGSMTask_Index = eGSMTask_Idle;
			break;

		case eGSMTask_GetPhoneBook:
			break;

		case eGSMTask_WritePhoneBook:
			break;

		case eGSMTask_SendSMS:
			GSM_SendSMSByPhoneNumber("+84906558678","gsm");
			gGSMTask_Index = eGSMTask_Idle;
			break;

		case eGSMTask_ReceiveSMS:
			//nhan tin nhan luu vao strutSMSData
			GSM_GetNewSMS(&strtSMSData);

			//xoa tin nhan tren sim
			GSM_DeleteSMSByIndex(strtSMSData.bSMSIdx);

			//kiem tra so co nam trong list gPhoneBook ko?
//			for (bIndex = 0; bIndex < 4; bIndex++) {
//				if (memcmp(&strtSMSData.sPhoneNumber, &gPhoneBook[bIndex],
//						sizeof(gPhoneBook[bIndex])) == 1) {
//					//kiem tra dang format dung dang format chua? chua thi gui phan hoi error format, ko co khoi gui
//					//dung set on hoac off thiet bi
//					bIndex = 4;
//					break;
//				};
//			}
			//Rf_WriteRelayState();
			gGSMTask_Index = eGSMTask_Idle;
			break;

		case eGSMTask_Idle:
			break;
		}
//		curButton1 = UserButtonGetState(USER_BUTTON1);
//		curButton2 = UserButtonGetState(USER_BUTTON2);
//		curButton3 = UserButtonGetState(USER_BUTTON3);
//		if ((curButton1 != lastButton1) && (curButton1 == 0)) {
//			GSM_MakeACallByPhone("+84982988687");
//		}
//		if ((curButton2 != lastButton2) && (curButton2 == 0)) {
//			GSM_MakeACallByPhone("+84907953570");
//		}
//		if ((curButton3 != lastButton3) && (curButton3 == 0)) {/*Hang on a call*/
//			GSM_MakeACallByPhone("+84938819622");
//		}
//		lastButton1 = curButton1;
//		lastButton2 = curButton2;
//		lastButton3 = curButton3;

//		eOldTask = gGSMTask_Index;
//	}
}
