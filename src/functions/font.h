
/// TODO use imagemagick lib instead of system()

typedef struct {
	unsigned char used;
	
	float size;
	char  path[MAX_PATH_LENGTH];
	char* text;
	
	bitmap_image_t bmp;
	unsigned char  has_bmp;
	
} kos_font_t;

#ifndef KOS_MAX_FONTS
	#define KOS_MAX_FONTS 4096
#endif

static kos_font_t kos_fonts[KOS_MAX_FONTS];

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
	
}

void kos_init_fonts(void) { /// TO... IMPLEMENT?
	unsigned long long i;
	for (i = 0; i < KOS_MAX_FONTS; i++) {
		kos_unuse_font(&kos_fonts[i]);
		
	}
	
}

void kos_destroy_fonts(void) {
	
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
		sprintf(command, "convert -background transparent -fill white -font \"%s\" -pointsize %d label:'%s' " TEMP_TEXT_RESULT_IMAGE_ROOT, this->path, (int) (this->size * video_width()), this->text);
		system (command);
		
		bmp_load(&this->bmp, (unsigned long long) TEMP_TEXT_RESULT_IMAGE);
		//~ system("rm "                              TEMP_TEXT_RESULT_IMAGE_ROOT);
		
	}
	
}

unsigned long long font_remove(font_t this) {
	KOS_CHECK_FONT(-1)
	
	if      (kos_fonts[this].text != NULL) {
		free(kos_fonts[this].text);
		
	} if         (kos_fonts[this].has_bmp) {
		bmp_free(&kos_fonts[this].bmp);
		
	}
	
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
