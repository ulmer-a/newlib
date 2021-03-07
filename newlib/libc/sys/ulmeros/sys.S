
.global _ulmeros_syscall0
.global _ulmeros_syscall1
.global _ulmeros_syscall2
.global _ulmeros_syscall3
.global _ulmeros_syscall4
.global _ulmeros_syscall5

_ulmeros_syscall0:
    mov %rdi, %rax
    int $0x80
    ret

_ulmeros_syscall1:
    mov %rdi, %rax
    mov %rsi, %r8
    int $0x80
    ret

_ulmeros_syscall2:
    mov %rdi, %rax
    mov %rsi, %r8
    mov %rdx, %r9
    int $0x80
    ret

_ulmeros_syscall3:
    mov %rdi, %rax
    mov %rsi, %r8
    mov %rdx, %r9
    mov %rcx, %r10
    int $0x80
    ret

_ulmeros_syscall4:
    mov %rdi, %rax
    mov %rsi, %r8
    mov %rdx, %r9
    mov %rcx, %r10
    mov %r8, %r11
    int $0x80
    ret

_ulmeros_syscall5:
    mov %rdi, %rax
    mov %rsi, %r8
    mov %rdx, %r9
    mov %rcx, %r10
    mov %r8, %r11
    mov %r9, %r12
    int $0x80
    ret