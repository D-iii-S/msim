static exc_t instr_bgtzl(cpu_t *cpu, instr_t instr)
{
	bool cond;
	
	if (CPU_64BIT_MODE(cpu))
		cond = (((int64_t) cpu->regs[instr.i.rs].val) > 0);
	else
		cond = (((int32_t) cpu->regs[instr.i.rs].lo) > 0);
	
	if (cond) {
		cpu->pc_next.ptr +=
		    (((int64_t) sign_extend_16_64(instr.i.imm)) << TARGET_SHIFT);
		cpu->branch = BRANCH_COND;
		return excJump;
	}
	
	cpu->pc_next.ptr += 4;
	return excNone;
}

static void mnemonics_bgtzl(ptr64_t addr, instr_t instr,
    string_t *mnemonics, string_t *comments)
{
	string_printf(mnemonics, "bgtzl");
	disassemble_rs_offset(addr, instr, mnemonics, comments);
}
