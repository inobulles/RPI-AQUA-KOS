
typedef struct {
	unsigned char used;
	
	float size;
	char  path[MAX_PATH_LENGTH];
	char* text;
	
	bitmap_image_t bmp;
	unsigned char  has_bmp;
	
	//~ TTF_Font* font;
	//~ SDL_Surface* surface;
	
} kos_font_t;

#ifndef KOS_MAX_FONTS
	#define KOS_MAX_FONTS 4096
#endif

static kos_font_t kos_fonts[KOS_MAX_FONTS];
//~ static SDL_Color kos_font_colour;

#ifndef KOS_CHECK_FONT
	#define KOS_CHECK_FONT(return_value) { \
		if (this < 0 && this >= KOS_MAX_FONTS && !kos_fonts[this].used) { \
			printf("WARNING Font %lld does not exist\n", this); \
			return (return_value); \
		} \
	}
#endif

static void kos_unuse_font(kos_font_t* this) {
	this->used    = 0;
	this->text    = NULL;
	this->has_bmp = 0;
	
	//~ this->font    = NULL;
	//~ this->surface = NULL;
	
}

void kos_init_fonts(void) { /// TO... IMPLEMENT?
	//~ kos_font_colour.r = 0xFF;
	//~ kos_font_colour.g = 0xFF;
	//~ kos_font_colour.b = 0xFF;
	//~ kos_font_colour.a = 0xFF;
	
	unsigned long long i;
	for (i = 0; i < KOS_MAX_FONTS; i++) {
		kos_unuse_font(&kos_fonts[i]);
		
	}
	
	//~ if (TTF_Init() == -1) {
		//~ printf("WARNING TTF could not initialize (%s)\n", TTF_GetError());
		//~ return;
		
	//~ }
	
}

void kos_destroy_fonts(void) {
	//~ TTF_Quit();
	
}

unsigned long long video_width(void);

font_t new_font(const char* _path, unsigned long long size) {
	unsigned long long i;
	for (i = 0; i < KOS_MAX_FONTS; i++) {
		if (!kos_fonts[i].used) {
			kos_fonts[i].used = 1;
			
			GET_PATH((char*) _path);
			memcpy(kos_fonts[i].path, path, MAX_PATH_LENGTH * sizeof(char));
			
			kos_fonts[i].size = (float) size / _UI64_MAX;
			//~ kos_fonts[i].font = TTF_OpenFont(kos_fonts[i].path, kos_fonts[i].size * video_width());
			
			//~ if (!kos_fonts[i].font) {
				//~ printf("WARNING Font could not be loaded (possibly an incorrect path? `%s`)\n", path);
				//~ kos_fonts[i].used = 0;
				
				//~ return -1;
				
			//~ }
			
			return i;
			
		}
		
	}
	
	printf("WARNING You have surpassed the maximum font count (KOS_MAX_FONTS = %d)\n", KOS_MAX_FONTS);
	return -1;
	
}

void update_all_font_sizes(void) {
	unsigned long long i;
	for (i = 0; i < KOS_MAX_FONTS; i++) {
		if (kos_fonts[i].used) {
			//~ TTF_CloseFont(kos_fonts[i].font);
			//~ kos_fonts[i].font = TTF_OpenFont(kos_fonts[i].path, kos_fonts[i].size * video_width());
			
		}
		
	}
	
}

static void kos_font_create_text(kos_font_t* this, char* text) {
	if          (this->text == NULL || strcmp(text, this->text) != 0) {
		if      (this->text) {
			free(this->text);
			
		}
		
		if (this->has_bmp) {
			this->has_bmp = 1;
			bmp_free(&this->bmp);
				
		}
		
		this->text = (char*) malloc(strlen(text));
		strcpy(this->text,                 text);
		
		#define TEMP_TEXT_RESULT_IMAGE      ".__temp_text_result.bmp"
		#define TEMP_TEXT_RESULT_IMAGE_ROOT "root/" TEMP_TEXT_RESULT_IMAGE
		
		#define                          ORIGINAL_COMMAND_BYTES 256
		char*   command = (char*) malloc(ORIGINAL_COMMAND_BYTES + strlen(this->text));
		sprintf(command, "convert xc:none -fill white -font \"%s\" -pointsize %d label:'testing123' " TEMP_TEXT_RESULT_IMAGE_ROOT, "root/fonts/main.ttf", /*(int) this->size*/ 72);
		system (command);
		
		bmp_load(&this->bmp, (unsigned long long) TEMP_TEXT_RESULT_IMAGE);
		//~ system ("rm "                     TEMP_TEXT_RESULT_IMAGE_ROOT);
		
	}
	
}

unsigned long long font_remove(font_t this) {
	KOS_CHECK_FONT(-1)
	
	if      (kos_fonts[this].text != NULL) {
		free(kos_fonts[this].text);
		
	} if         (kos_fonts[this].has_bmp) {
		bmp_free(&kos_fonts[this].bmp);
		
	}
	
	//~ if (kos_fonts[this].surface) {
		//~ SDL_FreeSurface(kos_fonts[this].surface);
		
	//~ }
	
	//~ TTF_CloseFont(  kos_fonts[this].font);
	kos_unuse_font(&kos_fonts[this]);
	
	return 0;
	
}

texture_t create_texture_from_font(font_t this, char* text) {
	KOS_CHECK_FONT(0)
	
	kos_font_t* font = &kos_fonts[this];
	kos_font_create_text(font, text);
	
	return texture_create(font->bmp.data, 32, font->bmp.width, font->bmp.height);
	
}

unsigned long long get_font_width(font_t this, char* text) {
	KOS_CHECK_FONT(-1)
	
	kos_font_t* font = &kos_fonts[this];
	kos_font_create_text(font, text);
	
	return font->bmp.width;
	
}

unsigned long long get_font_height(font_t this, char* text) {
	KOS_CHECK_FONT(-1)
	
	kos_font_t* font = &kos_fonts[this];
	kos_font_create_text(font, text);
	
	return font->bmp.height;
	
}
