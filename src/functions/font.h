
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
		if (self < 0 && self >= KOS_MAX_FONTS && !kos_fonts[self].used) { \
			printf("WARNING Font %lld does not exist\n", self); \
			return (return_value); \
		} \
	}
#endif

static void kos_unuse_font(kos_font_t* self) {
	self->used    = 0;
	self->text    = NULL;
	self->has_bmp = 0;
	
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

static void kos_font_create_text(kos_font_t* self, char* text) {
	if          (self->text == NULL || strcmp(text, self->text) != 0) {
		if      (self->text) {
			free(self->text);
			
		}
		
		if (self->has_bmp) {
			self->has_bmp = 1;
			bmp_free(&self->bmp);
				
		}
		
		self->text = (char*) malloc(strlen(text) + 1);
		strcpy(self->text,                 text);
		
		#define TEMP_TEXT_RESULT_IMAGE      ".__temp_text_result.bmp"
		#define TEMP_TEXT_RESULT_IMAGE_ROOT "root/" TEMP_TEXT_RESULT_IMAGE
		
		#define TEMP_TEXT_RESULT_TEXT       ".__temp_text_text.bmp"
		#define TEMP_TEXT_RESULT_TEXT_ROOT  "root/" TEMP_TEXT_RESULT_TEXT
		
		fs_write((unsigned long long) TEMP_TEXT_RESULT_TEXT, (unsigned long long) self->text, strlen(self->text) + 1);
		
		#define                          ORIGINAL_COMMAND_BYTES 256
		char*   command = (char*) malloc(ORIGINAL_COMMAND_BYTES + strlen(self->text));
		sprintf(command, "convert -background transparent -fill white -font \"%s\" -pointsize %d label:@" TEMP_TEXT_RESULT_TEXT_ROOT " " TEMP_TEXT_RESULT_IMAGE_ROOT, self->path, (int) (self->size * video_width()));
		system (command);
		
		bmp_load(&self->bmp,   (unsigned long long) TEMP_TEXT_RESULT_IMAGE);
		system("rm " TEMP_TEXT_RESULT_TEXT_ROOT " " TEMP_TEXT_RESULT_IMAGE_ROOT);
		
	}
	
}

unsigned long long font_remove(font_t self) {
	KOS_CHECK_FONT(-1)
	
	if      (kos_fonts[self].text != NULL) {
		free(kos_fonts[self].text);
		
	} if         (kos_fonts[self].has_bmp) {
		bmp_free(&kos_fonts[self].bmp);
		
	}
	
	kos_unuse_font(&kos_fonts[self]);
	return 0;
	
}

texture_t create_texture_from_font(font_t self, char* text) {
	KOS_CHECK_FONT(0)
	
	kos_font_t* font = &kos_fonts[self];
	kos_font_create_text(font, text);
	
	return texture_create(font->bmp.data, 32, font->bmp.width, font->bmp.height);
	
}

unsigned long long get_font_width(font_t self, char* text) {
	KOS_CHECK_FONT(-1)
	
	kos_font_t* font = &kos_fonts[self];
	kos_font_create_text(font, text);
	
	return font->bmp.width;
	
}

unsigned long long get_font_height(font_t self, char* text) {
	KOS_CHECK_FONT(-1)
	
	kos_font_t* font = &kos_fonts[self];
	kos_font_create_text(font, text);
	
	return font->bmp.height;
	
}
