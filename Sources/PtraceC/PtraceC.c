//
//  PtraceC.c
//  
//
//  Created by Josseph Colonia on 6/22/20.
//

/**
 C code version:
 
 #include <stdio.h>
 #import <dlfcn.h>
 #import <sys/types.h>
 #include "PtraceC.h"

 typedef int (*ptrace_ptr_t)(int _request, pid_t _pid, caddr_t _addr, int _data);
 #define PT_DENY_ATTACH 31

 void disable_gdb() {
     ptrace_ptr_t ptrace_ptr = dlsym(RTLD_SELF, "ptrace");
     ptrace_ptr(31, 0, 0, 0); // PTRACE_DENY_ATTACH = 31
 }
 
 */

void disable_gdb() {
    #if defined (__arm64__)
    __asm(
        "mov x0, #26\n" // ptrace
        "mov x1, #31\n" // PT_DENY_ATTACH
        "mov x2, #0\n"
        "mov x3, #0\n"
        "mov x16, #0\n"
        "svc #128\n"
    );
    #elif defined(__x86_64__)
    __asm(
        "movq $0, %rcx\n"
        "movq $0, %rdx\n"
        "movq $0, %rsi\n"
        "movq $0x1f, %rdi\n"
        "movq $0x200001A, %rax\n"
        "syscall\n"
    );
    #endif
}
