#pragma once
void RETURN_IMPL();
#define RETURN() do { RETURN_IMPL(); __assume(0); } while(0)