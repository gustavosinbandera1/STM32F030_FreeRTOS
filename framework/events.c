/*
 * @filename: events.c
 * @date: 16/5/2018
 */
/******************************************************************************/
/**!                               INCLUDE                                    */
/******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "stm32f0xx.h"
#include "queue.h"
#include "task.h"
#include "events.h"
#include "sysctl.h"
/******************************************************************************/
/**!                            LOCAL TYPEDEF                                 */
/******************************************************************************/

/******************************************************************************/
/**!                            LOCAL SYMBOLS                                 */
/******************************************************************************/

/******************************************************************************/
/**!                         EXPORTED VARIABLES                               */
/******************************************************************************/
extern xQueueHandle xSysEventQueue;
extern xQueueHandle xSerialQueue;

extern button_event_status_t button_event;
/******************************************************************************/
/**!                          LOCAL VARIABLES                                 */
/******************************************************************************/

/******************************************************************************/
/**!                    LOCAL FUNCTIONS PROTOTYPES                            */
/******************************************************************************/

/******************************************************************************/
/**!                        EXPORTED FUNCTIONS                                */
/******************************************************************************/
void vBUTTON_EventHandler(button_event_t event)
{
	/* do nothing, for debouncing */
	if(button_event.status == true)
		return;
	/* Set blocking flag */
	button_event.status = true;
	sys_events_t xSysEvent;
	xSysEvent.event = SYS_EVENT_BUTTON;
	/* Send to system even queue */
	xQueueSend(xSysEventQueue,(void*)&xSysEvent, 0);
	taskYIELD();
}

void vSERIAL_EventHandler(uint8_t error, uint8_t byte)
{
    if (error == SERIAL_ERR_NONE)
    {
        xQueueSend(xSerialQueue,(void*)&byte,0);
        /* Yield for higher priority task */
        taskYIELD();
    }
}
/******************************************************************************/
/**!                           LOCAL FUNCTIONS                                */
/******************************************************************************/

