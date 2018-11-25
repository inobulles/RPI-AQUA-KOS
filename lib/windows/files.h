
#ifndef __AQUA__WINDOWS_FILES_H
	#define __AQUA__WINDOWS_FILES_H
	
	#include "../ui/side.h"
	#include "../ui/button.h"
	
	#include "../string/strcmp.h"
	#include "../string/strplace.h"
	#include "../string/strlen.h"
	
	#include "utils.h"
	#include "images.h"
	#include "fonts.h"
	#include "run_zed.h"
	
	#define __lib_function_window_files_side_width    (_UI64_MAX_MARGIN                       / 2)
	#define __lib_function_window_files_content_width (_UI64_MAX_MARGIN * 2 - __lib_function_window_files_side_width)
	#define __lib_function_window_files_mid           (__lib_function_window_files_side_width / 2)
	
	#define __lib_function_D_BUTTON_COUNT 3
	#define __lib_function_M_BUTTON_COUNT 4
	#define __lib_function_CATEGORY_COUNT 11
	
	#define __lib_function_window_files_recent      0
	#define __lib_function_window_files_recent_path 1
	#define __lib_function_window_files_media       2
	#define __lib_function_window_files_music       3
	#define __lib_function_window_files_photos      4
	#define __lib_function_window_files_videos      5
	#define __lib_function_window_files_misc        6
	#define __lib_function_window_files_temp        7
	#define __lib_function_window_files_documents   8
	#define __lib_function_window_files_downloads   9
	#define __lib_function_window_files_root        10
	#define __lib_function_window_files_back        11
	
	#define __lib_function_window_files_max_list_entries 16
	
	#define __lib_function_NUL_EXTENSION 0
	#define __lib_function_UNK_EXTENSION 1
	#define __lib_function_BMP_EXTENSION 2
	#define __lib_function_TXT_EXTENSION 3
	#define __lib_function_FNT_EXTENSION 4
	#define __lib_function_PRO_EXTENSION 5
	#define __lib_function_LIF_EXTENSION 6
	#define __lib_function_OBJ_EXTENSION 7
	#define __lib_function_ZED_EXTENSION 8
	
	#define GET_TEXT_FROM_FS_LIST_ENTRY(entry) (((var*) entry) + 1)
	
	#define FM_NAVIGATE 0
	#define FM_SELECT   1
	
	typedef struct {
		chr* path;
		ui_t* ui;
		ui_side_t side;
		bool yet_moved;
		
		var    path_text_duty;
		text_t path_text[2];
		
		var button_count;
		ui_button_t buttons[lib(D_BUTTON_COUNT)];
		
		var category_count;
		text_t categories[lib(CATEGORY_COUNT)];
		
		text_t copy_entries[lib(window_files_max_list_entries)];
		bool   copy_draw   [lib(window_files_max_list_entries)];
		
		text_t list_entries[lib(window_files_max_list_entries)];
		bool   list_draw   [lib(window_files_max_list_entries)];
		
		char** list;
		var    list_count;
		
		var fm_type;
		var result;
		bool close;
		
	} __lib_window_files_t;
	
	private var window_files_check_extension(final char* __path) {
		var* path = (var*) __path;
		
		var                         extension_buffer_bytes = 64;
		uchr   extension_buffer    [extension_buffer_bytes / sizeof(uchr)];
		memset(extension_buffer, 0, extension_buffer_bytes);
		
		var extension_buffer_index = 0;
		var start_extension_count  = 0;
		
		var i;
		for (i = strlen(path) - 1; i >= 0; i--) {
			var current = strindex(path, i);
			
			if (current == '/') {
				break;
				
			} elif (current == '.') {
				start_extension_count = i;
				break;
				
			}
			
		}
		
		if (!start_extension_count) {
			return lib(NUL_EXTENSION);
			
		}
		
		for (i = ++start_extension_count; i < strlen(path); i++) {
			strplace(extension_buffer, extension_buffer_index++, ((char*) path)[i]);
			
		}
		
		if   (strcmp(extension_buffer, (var*) "bmp", DEFAULT_LENGTH) == 0) return lib(BMP_EXTENSION);
		elif (strcmp(extension_buffer, (var*) "txt", DEFAULT_LENGTH) == 0) return lib(TXT_EXTENSION);
		elif (strcmp(extension_buffer, (var*) "ttf", DEFAULT_LENGTH) == 0) return lib(FNT_EXTENSION);
		elif (strcmp(extension_buffer, (var*) "c",   DEFAULT_LENGTH) == 0) return lib(PRO_EXTENSION);
		elif (strcmp(extension_buffer, (var*) "h",   DEFAULT_LENGTH) == 0) return lib(PRO_EXTENSION);
		elif (strcmp(extension_buffer, (var*) "cu",  DEFAULT_LENGTH) == 0) return lib(PRO_EXTENSION);
		elif (strcmp(extension_buffer, (var*) "sh",  DEFAULT_LENGTH) == 0) return lib(PRO_EXTENSION);
		elif (strcmp(extension_buffer, (var*) "asm", DEFAULT_LENGTH) == 0) return lib(PRO_EXTENSION);
		elif (strcmp(extension_buffer, (var*) "lif", DEFAULT_LENGTH) == 0) return lib(LIF_EXTENSION);
		elif (strcmp(extension_buffer, (var*) "obj", DEFAULT_LENGTH) == 0) return lib(OBJ_EXTENSION);
		elif (strcmp(extension_buffer, (var*) "zed", DEFAULT_LENGTH) == 0) return lib(ZED_EXTENSION);
		else                                                               return lib(UNK_EXTENSION);
		
	}
	
	private void lib(window_files_free_list)(__lib_window_files_t self[notnull]) {
		if (self->list != nullptr) {
			fs_list_free(self->list, self->list_count);
			
		}
		
	}
	
	#include "hex_edit.h"
	#include "obj.h"
	
	private bool lib(window_files_move_to_path)(__lib_window_files_t self[notnull], final char* path, bool update_path) {
		if (update_path && strcmp((var*) path, (var*) self->path, -1) == 0) {
			return true;
			
		}
		
		char** list = fs_list(path);
		
		if (list == nullptr) {
			if (self->fm_type == FM_NAVIGATE) {
				var extension = window_files_check_extension(path);
				
				switch (extension) {
					case lib(BMP_EXTENSION): preview_bmp  (self->ui, path);   break;
					case lib(TXT_EXTENSION): printf("TXT\n");                 break;
					case lib(FNT_EXTENSION): preview_fonts(self->ui, path);   break;
					case lib(LIF_EXTENSION): printf("LIF\n");                 break;
					case lib(ZED_EXTENSION): run_zed(self->ui, path);         break;
					case lib(OBJ_EXTENSION): preview_obj(self->ui, path);     break;
						
					case lib(PRO_EXTENSION): {
						char    command[8192];
						sprintf(command, "geany \"%s\" &", path);
						system (command);
						break;
						
					} default: {
						hex_edit(self->ui, path);
						break;
						
					}
					
				}
				
			} else if (self->fm_type == FM_SELECT) {
				self->close = true;
				
			}
			
			return true;
			
		} else {
			if (self->list != nullptr) {
				iterate(lib(window_files_max_list_entries)) {
					if (self->list_draw[i]) {
						self->copy_draw[i] = true;
						
						text_set_text    (&self->copy_entries[i], (final char*) GET_TEXT_FROM_FS_LIST_ENTRY(self->list[i]));
						text_set_position(&self->copy_entries[i], self->list_entries[i].layer.x, self->list_entries[i].layer.y);
						text_fade_out    (&self->copy_entries[i], self->ui->frost->theme.fade_out);
						text_set_grey    (&self->copy_entries[i], self->list_entries[i].grey);
						
					}
					
				}
				
			}
			
			lib(window_files_free_list)(self);
			self->list = list;
			
			self->list_count = fs_list_count(path);
			iterate(lib(window_files_max_list_entries)) self->list_draw[i] = false;
			var entry_count = self->list_count;
			
			if (entry_count > lib(window_files_max_list_entries)) {
				entry_count = lib(window_files_max_list_entries);
				
			}
			
			iterate(entry_count) {
				self->list_draw[i] = true;
				
				var y = _UI64_MAX_MARGIN - (_UI64_MAX_MARGIN * 3 / 2) / (entry_count + 1) * (i + 1) - 12009599006321322;
				var x = lib(window_files_side_width) + self->ui->frost->theme.general_margin - _UI64_MAX_MARGIN;
				
				text_set_text      (&self->list_entries[i], (final char*) GET_TEXT_FROM_FS_LIST_ENTRY(self->list[i]));
				text_point_to_point(&self->list_entries[i], self->ui->frost->theme.snap_tier + self->ui->frost->theme.snap_tier / entry_count * i, x, -_UI64_MAX_MARGIN, x, y);
				text_set_grey      (&self->list_entries[i], *self->list[i] != FS_LIST_ENTRY_DIRECTORY);
				
			}
			
			if (update_path) {
				self->path      = (chr*) path;
				self->yet_moved = true;
				
				text_fade_out      (&self->path_text[self->path_text_duty], self->ui->frost->theme.fade_out);
				self->path_text_duty =               self->path_text_duty == 1 ? 0 : 1;
				text_set_text      (&self->path_text[self->path_text_duty], path);
				text_point_to_point(&self->path_text[self->path_text_duty], self->ui->frost->theme.text_tier, lib(window_files_mid), 72057594037927932, lib(window_files_mid), 66052794534767271);
				
			}
			
			return false;
			
		}
		
	}
	
	private bool lib(window_files_move_back)(__lib_window_files_t self[notnull]) {
		var last_slash = -1;
		
		iterate (strlen(self->path)) {
			chr current = strindex(self->path, i);
			last_slash  = current == '/' ? i : last_slash;
			
		}
		
		if (last_slash != -1) {
			last_slash += !last_slash;
			strplace(self->path, last_slash, '\0');
			lib(window_files_move_to_path)(self, (final char*) self->path, false);
			
			return false;
			
		} else {
			return true;
			
		}
		
	}
	
	private void lib(window_files_init)(__lib_window_files_t self[notnull], ui_t ui[notnull]) {
		self->ui   = ui;
		self->list = nullptr;
		
		self->button_count   = is_device_supported("keyboard") ? lib(D_BUTTON_COUNT) : lib(M_BUTTON_COUNT);
		self->category_count = lib(CATEGORY_COUNT);
		
		self->path_text_duty = 0;
		self->yet_moved      = false;
		
		final char* buttons[lib(M_BUTTON_COUNT)] = {
			"Back",
			"Cancel",
			"New",
			"Search",
		};
		
		iterate(lib(window_files_max_list_entries)) {
			self->list_draw[i] = false;
			self->copy_draw[i] = false;
			
			new_text(&self->list_entries[i], ui->fonts[3], "-", ui->frost->theme, 15);
			new_text(&self->copy_entries[i], ui->fonts[3], "-", ui->frost->theme, 14);
			
			text_align(&self->list_entries[i], 0, 1);
			text_align(&self->copy_entries[i], 0, 0);
			
		}
		
		iterate(self->button_count) {
			var x = lib(window_files_mid) - lib(window_files_content_width) / 2 + lib(window_files_content_width) / (self->button_count + 1) * (i + 1);
			
			new_ui_button           (&self->buttons[i], ui->fonts[0], buttons[i], ui->frost, 16);
			ui_button_point_to_point(&self->buttons[i], ui->frost->theme.button_tier + ui->frost->theme.button_tier / self->button_count * i, x, -72057594037927932, x, -60047995031606610);
			
		} iterate(self->category_count) {
			char* string = "FIXME";
			bool  clickable = false;
			
			switch (i) {
				case lib(window_files_recent):      string = "Recent";    clickable = false; break;
				case lib(window_files_recent_path): string = "-";         clickable = true;  break;
				case lib(window_files_media):       string = "Media";     clickable = false; break;
				case lib(window_files_music):       string = "Music";     clickable = true;  break;
				case lib(window_files_photos):      string = "Photos";    clickable = true;  break;
				case lib(window_files_videos):      string = "Videos";    clickable = true;  break;
				case lib(window_files_misc):        string = "Misc";      clickable = false; break;
				case lib(window_files_temp):        string = "Temp";      clickable = true;  break;
				case lib(window_files_documents):   string = "Documents"; clickable = true;  break;
				case lib(window_files_downloads):   string = "Downloads"; clickable = true;  break;
				case lib(window_files_root):        string = "Root";      clickable = true;  break;
				
			}
			
			var y = _UI64_MAX_MARGIN - (_UI64_MAX_MARGIN * 2) / (self->category_count + 1) * (i + 1);
			
			new_text           (&self->categories[i], ui->fonts[clickable ? 3 : 0], string, ui->frost->theme, 65);
			text_point_to_point(&self->categories[i], ui->frost->theme.button_tier + ui->frost->theme.button_tier / self->category_count * i, -_UI64_MAX_MARGIN, y, lib(window_files_side_width) / 2 - _UI64_MAX_MARGIN, y);
			
			if (clickable) {
				text_set_grey(&self->categories[i], true);
				
			}
			
		}
		
		iterate(2) new_text(&self->path_text[i], ui->fonts[0], (const char*) self->path, ui->frost->theme, 16 + i);
		text_point_to_point(&self->path_text[self->path_text_duty], self->ui->frost->theme.text_tier, lib(window_files_mid), 72057594037927932, lib(window_files_mid), 66052794534767271);
		
		new_ui_side (&self->side, ui, lib(window_files_side_width));
		ui_side_open(&self->side);
		
		lib(window_files_move_to_path)(self, (final char*) self->path, false);
		
	}
	
	private void lib(window_files_draw)(__lib_window_files_t self[notnull], var fps) {
		frost_draw_window(self->ui->frost);
		text_draw(&self->path_text[0], fps);
		
		if (self->yet_moved) {
			text_draw(&self->path_text[1], fps);
						
		}
		
		ui_side_draw(&self->side, fps);
		
		iterate(self->button_count)   ui_button_draw(&self->buttons   [i], fps);
		iterate(self->category_count) text_draw     (&self->categories[i], fps);
		
		iterate(lib(window_files_max_list_entries)) {
			if (self->list_draw[i]) {
				text_draw(&self->list_entries[i], fps);
				
			}
			
		} iterate(lib(window_files_max_list_entries)) {
			if (self->copy_draw[i]) {
				text_draw(&self->copy_entries[i], fps);
				
			}
			
		}
		
	}
	
	#include "text_input.h"
	
	private bool lib(window_files_click)(__lib_window_files_t self[notnull], var _x, var _y) {
		var x = POINTER_X(_x);
		var y = POINTER_Y(_y);
		
		chr new_path_buffer[4096 / sizeof(chr)];
		chr path_copy      [4096 / sizeof(chr)];
		
		iterate(self->category_count) {
			if   (i == lib(window_files_recent_path) && text_click(&self->categories[i], x, y)) print("TODO\n");
			elif (i == lib(window_files_music)       && text_click(&self->categories[i], x, y)) lib(window_files_move_to_path)(self, "/home/obiwac/Music",     true);
			elif (i == lib(window_files_photos)      && text_click(&self->categories[i], x, y)) lib(window_files_move_to_path)(self, "/home/obiwac/Pictures",  true);
			elif (i == lib(window_files_videos)      && text_click(&self->categories[i], x, y)) lib(window_files_move_to_path)(self, "/home/obiwac/Videos",    true);
			elif (i == lib(window_files_temp)        && text_click(&self->categories[i], x, y)) lib(window_files_move_to_path)(self, "/tmp",                   true);
			elif (i == lib(window_files_documents)   && text_click(&self->categories[i], x, y)) lib(window_files_move_to_path)(self, "/home/obiwac/Documents", true);
			elif (i == lib(window_files_downloads)   && text_click(&self->categories[i], x, y)) lib(window_files_move_to_path)(self, "/home/obiwac/Downloads", true);
			elif (i == lib(window_files_root)        && text_click(&self->categories[i], x, y)) lib(window_files_move_to_path)(self, ".",                      true);
			else continue;
			
		} iterate(lib(window_files_max_list_entries)) {
			if (self->list_draw[i]) {
				if (text_click(&self->list_entries[i], x, y)) {
					memcpy(path_copy, self->path, strlen(self->path) + 1);
					sprintf((char*) new_path_buffer, "%s/%s", self->path, GET_TEXT_FROM_FS_LIST_ENTRY(self->list[i]));
					
					if (lib(window_files_move_to_path)(self, (final char*) new_path_buffer, true)) {
						self->path = path_copy;
						
					}
					
					break;
					
				}
				
			}
			
		}
		
		if (ui_button_click(&self->buttons[1], x, y)) {
			self->path = nullptr;
			return true;
			
		} elif (ui_button_click(&self->buttons[2], x, y)) {
			char result[MAX_INPUT_LENGTH];
			text_input(self->ui, (char**) &result, MAX_INPUT_LENGTH / sizeof(var));
			print("TODO NEW %s\n", result);
			
		} elif (ui_button_click(&self->buttons[0], x, y)) {
			lib(window_files_move_back)(self);
			
		}
		
		if (self->close) {
			self->path = new_path_buffer;
			return true;
			
		} else {
			return false;
			
		}
		
	}
	
	private void lib(window_files_dispose)(__lib_window_files_t self[notnull]) {
		lib(window_files_free_list)(self);
		
		iterate(2) dispose_text(&self->path_text[i]);
		dispose_ui_side(&self->side);
		
		iterate(lib(window_files_max_list_entries)) dispose_text(&self->list_entries[i]);
		
		iterate(self->button_count)   dispose_ui_button(&self->buttons   [i]);
		iterate(self->category_count) dispose_text     (&self->categories[i]);
		
	}
	
	#define OPEN_WINDOW_FILES(_path, _fm_type) \
		__lib_window_files_t window; \
		window.path = _path; \
		window.fm_type = _fm_type; \
		window.close = false; \
		__LIB_EXECUTE_WINDOW( \
		{     lib(window_files_init)   (&window, ui);                                                     }, \
		{     lib(window_files_draw)   (&window, fps);                                                    }, \
		{ if (lib(window_files_click)  (&window, events.pointer_x, events.pointer_y)) __LIB_CLOSE_WINDOW; }, \
		{     lib(window_files_dispose)(&window);                                                         });
	
	void open_file_manager(ui_t* ui, void** output_path, const char* input_path) {
		var __fm_type = output_path == nullptr ? FM_NAVIGATE : FM_SELECT;
		OPEN_WINDOW_FILES((chr*) input_path, __fm_type);
		
		if (output_path != nullptr) {
			memcpy(output_path, window.path, strlen(window.path) * sizeof(var));
			
		}
		
	}
	
#endif
