section .note.GNU-stack noalloc noexec nowrite progbits
; RDI: pointer to consumer_ctrl (contains 'head')
; RSI: pointer to producer_ctrl (contains 'tail')
; RDX: Pointer to shared memory (ring buffer base)

section .text
global poll_and_consume

poll_and_consume:
    ; RDI points to consumer_ctrl struct
    ; RSI points to producer_ctrl struct
    
    mov     rax, [rsi]          ; Load current tail (index updated by NIC DMA)
    
.spin_loop:
    cmp     rax, [rdi]          ; Compare tail with local head
    je      .wait               ; If equal, queue is empty; wait
    
    ; Data is available! 
    ; Fall through to processing or copy routine
    ret

.wait:
    pause                       ; Crucial: de-pipeline spinning, improves efficiency
    mov     rax, [rsi]          ; Reload tail from producer_ctrl
    jmp     .spin_loop