;/*********************** (C) COPYRIGHT 2010 Libraworks *************************
;* File Name	: os_cpu_a.asm 
;* Author		: Librae 
;* Version		: V1.0
;* Date			: 06/10/2010
;* Description	: ��COS-II asm port
;*******************************************************************************/

		IMPORT  OSRunning               ; External references
        IMPORT  OSPrioCur
        IMPORT  OSPrioHighRdy
        IMPORT  OSTCBCur
        IMPORT  OSTCBHighRdy
        IMPORT  OSIntNesting
        IMPORT  OSIntExit
        IMPORT  OSTaskSwHook
		IMPORT  OSInterrputSum
         
            
        EXPORT  OSStartHighRdy               
        EXPORT  OSCtxSw
        EXPORT  OSIntCtxSw
		EXPORT  OS_ENTER_CRITICAL
        EXPORT  OS_EXIT_CRITICAL
		EXPORT  ItDisAll        
            
        EXPORT  PendSV_Handler
        	
     
NVIC_INT_CTRL   	EQU     0xE000ED04  ; �жϿ��ƼĴ���
NVIC_SYSPRI2    	EQU     0xE000ED20  ; ϵͳ���ȼ��Ĵ���(2)
NVIC_PENDSV_PRI 	EQU     0xFFFF0000  ; ����жϺ�ϵͳ�����ж�
                                        ; (��Ϊ��ͣ�0xff).
NVIC_PENDSVSET  	EQU     0x10000000  ; ��������жϵ�ֵ.


		PRESERVE8 
		
		AREA    |.text|, CODE, READONLY
        THUMB 
    
           

;/***************************************************************************************
;* ��������: OS_ENTER_CRITICAL
;*
;* ��������: �����ٽ��� 
;*            
;* ��    ��: None
;*
;* �� �� ֵ: None
;*****************************************************************************************/ 

OS_ENTER_CRITICAL
 
		CPSID   I                       ; Disable all the interrupts
                                                                        
		PUSH 	{R1,R2}      

		LDR 	R1, =OSInterrputSum	    ; OSInterrputSum++
        LDRB 	R2, [R1]
        ADD   	R2, R2, #1
        STRB 	R2, [R1]
		POP     {R1,R2}
  		BX LR

;/***************************************************************************************
;* ��������: OS_EXIT_CRITICAL
;*
;* ��������: �˳��ٽ��� 
;*            
;* ��    ��: None
;*
;* �� �� ֵ: None
;*****************************************************************************************/

OS_EXIT_CRITICAL
		PUSH    {R1, R2}
		LDR     R1, =OSInterrputSum     ; OSInterrputSum--
        LDRB    R2, [R1]
        SUB     R2, R2, #1
        STRB    R2, [R1]
		MOV     R1,  #0	      
		CMP     R2,  #0			        ; if OSInterrputSum=0,enable 
                                        ; interrupts���OSInterrputSum=0��
		MSREQ  PRIMASK, R1   
	    POP   	{R1, R2}
		BX LR

;/**************************************************************************************
;* ��������: OSStartHighRdy
;*
;* ��������: ʹ�õ��������е�һ������
;* 
;* ��    ��: None
;*
;* �� �� ֵ: None
;**************************************************************************************/  

OSStartHighRdy
        LDR     R4, =NVIC_SYSPRI2      ; set the PendSV exception priority
        LDR     R5, =NVIC_PENDSV_PRI
        STR     R5, [R4]

        MOV     R4, #0                 ; set the PSP to 0 for initial context switch call
        MSR     PSP, R4

        LDR     R4, =OSRunning         ; OSRunning = TRUE
        MOV     R5, #1
        STRB    R5, [R4]

                                       ;�л���������ȼ�������
        LDR     R4, =NVIC_INT_CTRL     ;rigger the PendSV exception (causes context switch)
        LDR     R5, =NVIC_PENDSVSET
        STR     R5, [R4]

        CPSIE   I                      ;enable interrupts at processor level
OSStartHang
        B       OSStartHang            ;should never get here

;/**************************************************************************************
;* ��������: OSCtxSw
;*
;* ��������: �����������л�         
;*
;* ��    ��: None
;*
;* �� �� ֵ: None
;***************************************************************************************/
  
OSCtxSw
		PUSH    {R4, R5}
        LDR     R4, =NVIC_INT_CTRL  	;����PendSV�쳣 (causes context switch)
        LDR     R5, =NVIC_PENDSVSET
        STR     R5, [R4]
		POP     {R4, R5}
        BX      LR

;/**************************************************************************************
;* ��������: OSIntCtxSw
;*
;* ��������: �жϼ������л�
;*
;* ��    ��: None
;*
;* �� �� ֵ: None
;***************************************************************************************/

OSIntCtxSw
		PUSH    {R4, R5}
        LDR     R4, =NVIC_INT_CTRL      ;����PendSV�쳣 (causes context switch)
        LDR     R5, =NVIC_PENDSVSET
        STR     R5, [R4]
		POP     {R4, R5}
        BX      LR
        NOP

;/**************************************************************************************
;* ��������: OSPendSV
;*
;* ��������: OSPendSV is used to cause a context switch.
;*
;* ��    ��: None
;*
;* �� �� ֵ: None
;***************************************************************************************/

PendSV_Handler
    CPSID   I                                                   ; Prevent interruption during context switch
    MRS     R0, PSP                                             ; PSP is process stack pointer �������PSP��ջ,����Ժ��Ա���Ĵ���,�ο�CM3Ȩ���е�˫��ջ-�ײ�ע
    CBZ     R0, PendSV_Handler_Nosave		                    ; Skip register save the first time

    SUBS    R0, R0, #0x20                                       ; Save remaining regs r4-11 on process stack
    STM     R0, {R4-R11}

    LDR     R1, =OSTCBCur                                       ; OSTCBCur->OSTCBStkPtr = SP;
    LDR     R1, [R1]
    STR     R0, [R1]                                            ; R0 is SP of process being switched out

                                                                ; At this point, entire context of process has been saved
PendSV_Handler_Nosave
    PUSH    {R14}                                               ; Save LR exc_return value
    LDR     R0, =OSTaskSwHook                                   ; OSTaskSwHook();
    BLX     R0
    POP     {R14}

    LDR     R0, =OSPrioCur                                      ; OSPrioCur = OSPrioHighRdy;
    LDR     R1, =OSPrioHighRdy
    LDRB    R2, [R1]
    STRB    R2, [R0]

    LDR     R0, =OSTCBCur                                       ; OSTCBCur  = OSTCBHighRdy;
    LDR     R1, =OSTCBHighRdy
    LDR     R2, [R1]
    STR     R2, [R0]

    LDR     R0, [R2]                                            ; R0 is new process SP; SP = OSTCBHighRdy->OSTCBStkPtr;
    LDM     R0, {R4-R11}                                        ; Restore r4-11 from new process stack
    ADDS    R0, R0, #0x20
    MSR     PSP, R0                                             ; Load PSP with new process SP
    ORR     LR, LR, #0x04                                       ; Ensure exception return uses process stack
    CPSIE   I
    BX      LR                                                  ; Exception return will restore remaining context


;/**************************************************************************************
;* ��������: ItDisAll
;*
;* ��������: �ر��жϿ������������ж�.
;*
;* ��    ��: None
;*
;* �� �� ֵ: None
;***************************************************************************************/

ItDisAll
    	CPSID   I
    	BX      LR


    	ALIGN
					
        END
        
;/*********************** (C) COPYRIGHT 2010 Libraworks ************************/
