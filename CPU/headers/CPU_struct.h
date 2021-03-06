

#ifdef COMMANDS_CPU
//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  *		COMMANDS
  *
  */
		CMD(push)
		CMD(pop)
		CMD(add)
		CMD(sub)
		CMD(mul)
		CMD(div)
		CMD(out)
		CMD(in)
		CMD(jmp)
		CMD(je)
		CMD(jne)
		CMD(ja)
		CMD(jae)
		CMD(jb)
		CMD(jbe)
		CMD(cmp)
		CMD(call)
		CMD(ret)
		CMD(sin)
		CMD(cos)
		CMD(sqrt)
		CMD(end)
 //}-------------------------------------------------------------------------------------------------------------------------------------- 
#endif

#ifdef REGISTERS_CPU
//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  *		REGISTERS
  *
  */
 
		reg(rax)
		reg(rbx)
		reg(rcx)
		reg(rdx)
//}-------------------------------------------------------------------------------------------------------------------------------------- 
#endif

#ifdef FLAGS_CPU
//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  *		FLAGS
  *
  */
 
		flag(ZF)
		flag(CF)
//}-------------------------------------------------------------------------------------------------------------------------------------- 
#endif