
//~ #include "src/kos.h"
//~ #include "asm/asm.h"

//~ void mfree(void* ptr, unsigned long long bytes) { // for some reason, this was not already defined
	//~ free(ptr);
	
//~ }

//~ static kos_t kos;

//~ #define ROM_PATH "ROM.zed"
//~ static unsigned long long kos_roms_loaded = 0;

//~ signed long long load_rom(unsigned long long __path) {
	//~ const char* ____path;
	
	//~ if (kos_roms_loaded++) {
		//~ GET_PATH((char*) __path);
		//~ ____path = path;
		
	//~ } else {
		//~ ____path = (const char*) __path;
		
	//~ }
	
	//~ const char* path = ____path;
	
	//~ void*                 __pointer_current_program_previous = __pointer_current_program;
	//~ __pointer__program_t* __pointer___this_previous          = __pointer___this;
	
	//~ program_t de_program;
	//~ FILE* fp = fopen(path, "rb");
	
	//~ if (!fp) {
		//~ printf("WARNING Could not open ROM file (%s)\n", path);
		//~ kos_quit(&kos);
		//~ exit(1);
		
	//~ }
	
	//~ fseek(fp, 0, SEEK_END);
	//~ unsigned long long bytes = ftell(fp);
	//~ rewind(fp);
	
	//~ char* rom = (char*) malloc(bytes);
	//~ fread(rom, sizeof(char), bytes, fp);
	
	//~ de_program.pointer = rom;
	
	//~ printf("Starting run setup phase ...\n");
	//~ program_run_setup_phase(&de_program);
	
	//~ while (!program_run_loop_phase(&de_program));
	//~ program_free(&de_program);
	
	//~ #if !OLD_ROM_FORMAT
		//~ mfree(rom, bytes);
	//~ #endif
	
	//~ __pointer_current_program = __pointer_current_program_previous;
	//~ __pointer___this          = __pointer___this_previous;
	
	//~ return de_program.error_code;
	
//~ }

int main(void) {
	printf("\nControl passed to the CW\n");
	printf("Initializing the KOS ...\n");
	
	//~ if (kos_init(&kos)) {
		//~ printf("WARNING Failed to initialize KOS. Exitting ...\n");
		//~ exit(1);
		
	//~ }
	
	//~ printf("Entering the DE ...\n");
	
	//~ int error_code = load_rom((unsigned long long) ROM_PATH);
	//~ printf("DE return code is %d\n", error_code);
	
	//~ printf("Quitting KOS ...\n");
	//~ kos_quit(&kos);
	
	return 0;//error_code;
	
}
