.code

RETURN_NOVALUE PROC
	; rcx, rdx: rbp, rsp
	mov rbp, rcx
	mov rsp, rdx
	sub rsp, 8
	ret
RETURN_NOVALUE ENDP

END