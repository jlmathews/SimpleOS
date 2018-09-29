
#ifndef SIMPLEOS_UTILS
#define SIMPLEOS_UTILS

void dead_loop();

#define UNUSED(x) (void)(x)

#define ASSERT(x) if(!(x)) { dead_loop(); }

#endif

