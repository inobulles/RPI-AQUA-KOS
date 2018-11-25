
#ifndef __AQUA__WINDOWS_RUN_ZED_H
	#define __AQUA__WINDOWS_RUN_ZED_H
	
	#include "utils.h"
	#include "template.h"
	#include "text_input.h"
	#include "../string/strcmp.h"
	
	#define ZED_SAFE_WORD   "go ahead"
	#define USELESS_WARNING 0
	
	private void __run_zed_warning(ui_t ui[notnull]) {
		open_template_window(ui, WINDOW_TEMPLATE_SUBTITLE2, (void*[]) {
			"Warning",
			"This file could potentially harm your computer",
			
			#if USELESS_WARNING
				"But now it's too late",
			#else
				"Click then enter \"" ZED_SAFE_WORD "\" to continue",
			#endif
		}, 0, nullptr);
		
	}
	
	void run_zed(ui_t ui[notnull], const char* path) {
		__run_zed_warning(ui);
		
		#if !USELESS_WARNING
			char result[MAX_INPUT_LENGTH];
			text_input(ui, (char**) &result, MAX_INPUT_LENGTH / sizeof(var));
		#endif
		
		#if !USELESS_WARNING
			chr current  = 1;
			bool stop = false;
			
			var i = 0;
			do {
				current = result[i];
				
				if (current != ZED_SAFE_WORD[i]) {
					stop = true;
					break;
					
				} elif (not current) {
					break;
					
				}
				
			} while (i++ < MAX_INPUT_LENGTH);
			
			if (not stop) {
		#endif
				load_rom(path);
		#if !USELESS_WARNING
			}
		#endif
		
	}
	
#endif
