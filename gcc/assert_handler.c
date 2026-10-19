/* Keep SDK assertions visible to a debugger without pulling in stdio/syscalls. */
__attribute__((noreturn)) void __assert_func(
    const char *file, int line, const char *function, const char *expression)
{
    (void)file;
    (void)line;
    (void)function;
    (void)expression;
    __asm volatile("cpsid i");
    for (;;) {
    }
}
