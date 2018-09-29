#include "cpu/x86/timer.h"
#include "drivers/screen.h"
#include "libc/string.h"

void process_user_input(char *input)
{
        if(strcmp(input, "TIMER") == 0) {
                kprint("Timer: ");
                char str[11];
		str[0] = '\0';
                itoa(g_TickCounter, str);
                kprint(str);
                kprint(" : ");
		str[0] = '\0';
                htoa(g_TickCounter, str);
                kprint(str);
        }
        kprint("\n");
}

