
#include "utils.h"

inline void dead_loop()
{
	volatile int dead_loop_assert = 1;
	while(dead_loop_assert) {}
}

