/******************************************************************************
 * This project provides two demo applications.  A simple blinky style project,
 * and a more comprehensive test and demo application.  The
 * mainCREATE_SIMPLE_BLINKY_DEMO_ONLY setting (defined in this file) is used to
 * select between the two.  The simply blinky demo is implemented and described
 * in main_blinky.c.  The more comprehensive test and demo application is
 * implemented and described in main_full.c.
 *
 * This file implements the code that is not demo specific, including the
 * hardware setup and FreeRTOS hook functions.
 *
 */

/* Standard includes. */
#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "sam3n4c.h"
#include "serial.h"

//#include "component_pio.h"

/*
 * main_blinky() is used when mainCREATE_SIMPLE_BLINKY_DEMO_ONLY is set to 1.
 * main_full() is used when mainCREATE_SIMPLE_BLINKY_DEMO_ONLY is set to 0.
 */
//extern void main_blinky( void );
//extern void main_full( void );

/* Prototypes for the standard FreeRTOS callback/hook functions implemented within this file. */
void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName );
void vApplicationTickHook( void );

Pio* pioa = (Pio*)0x400E0E00;

char led[2] = {0,0};
char txbuf[32];
char tx_exists = 0;

#define BIT(x,b) ((x&b)==b)

/*---------------------------------*/
/*            Задача #1            */
/*---------------------------------*/
void vTaskRx( void *pvParameters )
{
   Usart* usart1 = (Usart*)0x40028000;
   char ch;
   char bf[32]; bf[0] = 0;
   /* задача построена на базе бесконечного цикла */
   xComPortHandle serialport = (xComPortHandle)pvParameters;
   for(;;)
   {
      if (xSerialGetChar(serialport, &ch, 0xFFFF) != pdTRUE)
         continue;
//      while (!BIT(usart1->US_CSR, US_CSR_RXRDY));
//      ch = usart1->US_RHR;
      switch (ch)
      {
         case '1':
            led[0] = ~led[0];
            if (led[0])
               strcpy(txbuf, "\nLED1 On\r\n");
            else
               strcpy(txbuf, "\nLED1 Off\r\n");
            tx_exists = 1;
            break;
         case '2':
            led[1] = ~led[1];
            if (led[1])
               strcpy(txbuf, "\nLED2 On\r\n");
            else
               strcpy(txbuf, "\nLED2 Off\r\n");
            tx_exists = 1;
            break;
      }
      /* Задержка на некоторый период Т1 */
      vTaskDelay(10); // T1 = 10 системным тикам
   }
   /* Уничтожить задачу если произошел выход из бесконечного цикла */
   vTaskDelete(NULL);
}

/*---------------------------------*/
/*            Задача #2            */
/*---------------------------------*/
void vTaskTx( void *pvParameters )
{
   Usart* usart1 = (Usart*)0x40028000;
   xComPortHandle serialport = (xComPortHandle)pvParameters;
   for(;;)
   {
      if (tx_exists == 1)
      {
         for (int i=0; txbuf[i]!=0; i++)
         {
            while (!BIT(usart1->US_CSR, US_CSR_TXRDY));
            usart1->US_THR = ( uint32_t ) txbuf[i];
//            xSerialPutChar(serialport, txbuf[i], (portTickType)0);
         }
         if (led[0])
            pioa->PIO_SODR = PIO_SODR_P1;
         else
            pioa->PIO_CODR = PIO_CODR_P1;

         if (led[1])
            pioa->PIO_SODR = PIO_SODR_P2;
         else
            pioa->PIO_CODR = PIO_CODR_P2;
         tx_exists = 0;
      }
      /* Задержка на некоторый период Т2 */
      vTaskDelay(10); // Т2 = 10 системным тикам
   }
   vTaskDelete(NULL);
}

/*-----------------------------------------------------------*/

/* See the documentation page for this demo on the FreeRTOS.org web site for
full information - including hardware setup requirements. */

int main( void )
{
	/* Prepare the hardware to run this demo. */
   extern void SystemCoreClockUpdate( void );

	/* ASF function to setup clocking. */
//	sysclk_init();

   pioa->PIO_OER |= PIO_OER_P0 | PIO_OER_P1 | PIO_OER_P2;         // output for task1 and task2
   pioa->PIO_CODR |= PIO_SODR_P0 | PIO_SODR_P1 | PIO_SODR_P2;     // PA0,1,2 = 0


	/* Ensure all priority bits are assigned as preemption priority bits. */
	NVIC_SetPriorityGrouping( 0 );

	/* Atmel library function to setup for the evaluation kit being used. */
//	board_init();


   xComPortHandle serialport = xSerialPortInitMinimal(9600, 10);

   strcpy(txbuf, "Type 1 or 2 to change LEDx state!\r");
   tx_exists = 1;

   /* Установка задачи #1. При помощи функции xTaskCreate
   создаются задачи для их последующего, самостоятельного выполнения.
   В этом примере не используется проверка на корректное создание задачи */

   xTaskCreate( vTaskRx,          /* Указатель на исполняемую функцию */
      (signed char *) "TaskRx",   /* Имя задачи, необходимое для отладки FreeRTOS */
      configMINIMAL_STACK_SIZE,  /* Размер стека задачи */
      serialport,                      /* Передаваемый параметр */
      1,                         /* Приоритет задачи */
      NULL );                    /* Дескриптор задачи */

   /* Установка задачи #2 */

   xTaskCreate( vTaskTx,          /* Указатель на исполняемую функцию */
      (signed char * ) "TaskTx",  /* Имя задачи, необходимое для отладки FreeRTOS */
      configMINIMAL_STACK_SIZE,  /* Размер стека задачи */
      serialport,                      /* Передаваемый параметр */
      1,                         /* Приоритет задачи */
      NULL );                    /* Дескриптор задачи */

   /* Запустить планировщик. С этого места начнут работать все созданные ранее задачи.
   Планировщик всегда запускает только задачу с самым высоким приоритетом.
   Если имеются несколько задач с максимальным приоритетом, то они будут запущены поочереди.
   При нормальной работе FreeRTOS, планировщик должен работать вечно.*/

   vTaskStartScheduler();
	return 0;
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If the application makes use of the
	vTaskDelete() API function (as this demo application does) then it is also
	important that vApplicationIdleHook() is permitted to return to its calling
	function, because it is the responsibility of the idle task to clean up
	memory allocated by the kernel to any task that has since been deleted. */
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This function will be called by each tick interrupt if
	configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
	added here, but the tick hook is called from an interrupt context, so
	code must not attempt to block, and only the interrupt safe FreeRTOS API
	functions can be used (those that end in FromISR()). */
}
/*-----------------------------------------------------------*/

