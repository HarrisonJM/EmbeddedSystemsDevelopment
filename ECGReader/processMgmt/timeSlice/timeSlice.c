#include <msp430.h> 

#define LONG unsigned long
#define WORD unsigned short
#define BYTE unsigned char


////////////////////////////
// Start of User Programs //
////////////////////////////




///////////////////////////
// End  of Use Programs  //
///////////////////////////



#define MAX_PROCESSES   2
#define STACK_SIZE      100



struct ProcessControlBlock
{
    LONG sp;
    BYTE stack[STACK_SIZE];
};


struct ProcessControlBlock process[MAX_PROCESSES];

unsigned int current_process = 0;

LONG status;
LONG stack_pointer;
LONG program_counter;
LONG saved_sp;

WORD pc1;
WORD pc2;

void initialise_process(unsigned int process_index, void (*funct)())
{
    if (process_index < MAX_PROCESSES)
    {
        asm(
                " movx.a SR,&status\n"
            );

        stack_pointer = (LONG)&process[process_index] + STACK_SIZE - 2;
        program_counter = (LONG)funct;

        // Construct combined PC+SR used by interrupt

        pc1 = (WORD)program_counter;
        pc2 = (WORD)(((program_counter>>4)&0x0F000) | status&0x00FFF);

        asm(
                " movx.a sp,&saved_sp\n"
                " movx.a &stack_pointer,sp\n"
                " push.w &pc1\n"
                " push.w &pc2\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " movx.a sp,&stack_pointer\n"
                " movx.a &saved_sp,sp\n"
            );

        process[process_index].sp = stack_pointer;
    }
}


void run_process(unsigned int process_index)
{
    if (process_index < MAX_PROCESSES)
    {
        stack_pointer = process[process_index].sp;

        asm(
                " movx.a &stack_pointer,SP \n"
                " pop.a R3 \n"
                " pop.a R4 \n"
                " pop.a R5 \n"
                " pop.a R6 \n"
                " pop.a R7 \n"
                " pop.a R8 \n"
                " pop.a R9 \n"
                " pop.a R10 \n"
                " pop.a R11 \n"
                " pop.a R12 \n"
                " pop.a R13 \n"
                " pop.a R14 \n"
                " pop.a R15 \n"
                " RETI \n"
        );
    }
}


//#pragma vector=TIMER0_A0_VECTOR
//__interrupt void Timer0_A0 (void)    // Timer0 A0 1ms interrupt service routine
//{
//    // Save first process details...
//
//    asm(
////            " push.a R15\n"
////            " push.a R14\n"
////            " push.a R13\n"
////            " push.a R12\n"
////            " push.a R11\n"
//            " push.a R10\n"
//            " push.a R9\n"
//            " push.a R8\n"
//            " push.a R7\n"
//            " push.a R6\n"
//            " push.a R5\n"
//            " push.a R4\n"
//            " push.a R3\n"
//            " movx.a sp,&stack_pointer\n"
//        );
//
//    process[current_process].sp = stack_pointer;
//
//    current_process = (current_process+1) % MAX_PROCESSES;
//
//    stack_pointer = process[current_process].sp;
//
//    asm(
//            " movx.a &stack_pointer,SP \n"
//            " pop.a R3 \n"
//            " pop.a R4 \n"
//            " pop.a R5 \n"
//            " pop.a R6 \n"
//            " pop.a R7 \n"
//            " pop.a R8 \n"
//            " pop.a R9 \n"
//            " pop.a R10 \n"
////            " pop.a R11 \n"
////            " pop.a R12 \n"
////            " pop.a R13 \n"
////            " pop.a R14 \n"
////            " pop.a R15 \n"
//    );
//}



