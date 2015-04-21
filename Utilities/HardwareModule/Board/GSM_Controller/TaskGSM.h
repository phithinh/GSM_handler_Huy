#ifndef _TASK_GSM_H_
#define _TASK_GSM_H_

/* -----------------------------Include ------------------------------------- */
//#include "Common.h"



/* -----------------------------Define -------------------------------------- */
//#define TASK_GSM_PROCESS_NAME           "GSM Process"
//#define TASK_GSM_PROCESS_STACK          configMINIMAL_STACK_SIZE
//#define TASK_GSM_PROCESS_PRIORITY       ( tskIDLE_PRIORITY + 2 )
//#define TASK_GSM_PROCESS_RATE_MS         500    /* Rate Delay in ms */
           
typedef enum _enumGSMTask
{
    eGSMTask_GetPhoneBook,
    eGSMTask_WritePhoneBook,
    eGSMTask_SendSMS,
    eGSMTask_ReceiveSMS,
    eGSMTask_ClearMessage,
    
    eGSMTask_Idle,
}enumGSMTask;

typedef enum _enumGSMStatus
{
    eGSMTask_DONE = 1,
    eGSMTask_PROCESSING,
}enumGSMStatus;

/* -----------------------------Prototype Function--------------------------- */
void TaskGSM_Init(void);
void TaskGSMProcess(void);

#endif /* _TASK_GSM_H_ */
