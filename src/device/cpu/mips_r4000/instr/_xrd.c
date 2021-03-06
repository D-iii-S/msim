static exc_t instr__xrd(cpu_t *cpu, instr_t instr)
{
	if (!machine_specific_instructions) {
		return instr__reserved(cpu, instr);
	}

	alert("XRD: Register dump");
	reg_dump(cpu);
	return excNone;
}

static void mnemonics__xrd(ptr64_t addr, instr_t instr,
    string_t *mnemonics, string_t *comments)
{
	if (!machine_specific_instructions) {
		return mnemonics__reserved(addr, instr, mnemonics, comments);
	}

	string_printf(mnemonics, "_xrd");
}
