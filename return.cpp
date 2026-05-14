
#include <Windows.h>
#include <winnt.h>
#include <intrin.h>

/*return_asm.asm
RETURN_NOVALUE PROC
	; rcx, rdx: rbp, rsp
	mov rbp, rcx
	mov rsp, rdx;
	sub rsp, 8
	ret
RETURN_NOVALUE ENDP*/

extern "C" {
	void RETURN_NOVALUE(DWORD64 rbp, DWORD64 rsp);
}


void RETURN_IMPL() {
	CONTEXT ctx = { 0 };
	ctx.ContextFlags = CONTEXT_FULL;
	RtlCaptureContext(&ctx);

	// 此处ctx.Rip 是RtlCaptureContext返回地址，在RETURN()栈帧中

	DWORD64 imageBase = 0;
	UNWIND_HISTORY_TABLE  uht = { 0 };// RtlLookupFunctionEntry所需缓存
	RUNTIME_FUNCTION* rf = RtlLookupFunctionEntry(ctx.Rip, &imageBase, &uht);
	DWORD64 establisherFrame = 0;
	PVOID handlerData = NULL;
	RtlVirtualUnwind(UNW_FLAG_NHANDLER,//回溯上一层
		imageBase,
		ctx.Rip,
		rf,
		&ctx,
		&handlerData,
		&establisherFrame,
		NULL);
	// 此处ctx.Rip 是RETURN()返回地址，在RETURN()的调用者栈帧中


	rf = RtlLookupFunctionEntry(ctx.Rip, &imageBase, &uht);
	establisherFrame = 0;
	handlerData = NULL;
	RtlVirtualUnwind(UNW_FLAG_NHANDLER,//回溯上一层
		imageBase,
		ctx.Rip,
		rf,
		&ctx,
		&handlerData,
		&establisherFrame,
		NULL);
	// 此处ctx.Rip 是RETURN()的调用者的返回地址

	DWORD64 destRsp = ctx.Rsp;
	DWORD64 destRbp = ctx.Rbp;
	RETURN_NOVALUE(destRbp, destRsp);
}