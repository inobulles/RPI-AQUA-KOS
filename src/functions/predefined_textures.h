
static texture_t predefined_background_texture;
static texture_t predefined_frost_background_texture;

static unsigned long long predefined_background_texture_dimensions      [2];
static unsigned long long predefined_frost_background_texture_dimensions[2];

void bmp_load(bitmap_image_t* self, unsigned long long _path);
void bmp_free(bitmap_image_t* self);

static int kos_setup_predefined_textures(kos_t* self) {
	int warning = 0;
	bitmap_image_t temp_bmp;
	
	bmp_load(&temp_bmp, (unsigned long long) "wallpaper/wallpaper.bmp");
	predefined_background_texture = texture_create(temp_bmp.data, temp_bmp.bpp, temp_bmp.width, temp_bmp.height);
	
	predefined_background_texture_dimensions[0] = temp_bmp.width;
	predefined_background_texture_dimensions[1] = temp_bmp.height;
	
	bmp_free(&temp_bmp);
	warning += predefined_background_texture == -1;
	
	bmp_load(&temp_bmp, (unsigned long long) "wallpaper/frost.bmp");
	predefined_frost_background_texture = texture_create(temp_bmp.data, temp_bmp.bpp, temp_bmp.width, temp_bmp.height);
	
	predefined_frost_background_texture_dimensions[0] = temp_bmp.width;
	predefined_frost_background_texture_dimensions[1] = temp_bmp.height;
	
	bmp_free(&temp_bmp);
	warning += predefined_frost_background_texture == -1;
	
	return warning;
	
}

static void kos_free_predefined_textures(kos_t* self) {
	if (predefined_background_texture       != -1) texture_remove(predefined_background_texture);
	if (predefined_frost_background_texture != -1) texture_remove(predefined_frost_background_texture);
	
}

texture_t get_predefined_texture(unsigned long long name) {
	switch (name) {
		case TEXTURE_BACKGROUND:         return predefined_background_texture;
		case TEXTURE_FROSTED_BACKGROUND: return predefined_frost_background_texture;
		
		default: {
			printf("WARNING Texture %lld is unknown. Returning -1 ...\n", name);
			return -1;
			
		}
		
	}
	
}

static unsigned long long* get_predefined_texture_size(unsigned long long name) {
	switch (name) {
		case TEXTURE_BACKGROUND:         return predefined_background_texture_dimensions;
		case TEXTURE_FROSTED_BACKGROUND: return predefined_frost_background_texture_dimensions;
		
		default: {
			printf("WARNING Texture %lld is unknown. Returning 0 ...\n", name);
			return 0;
			
		}
		
	}
	
}

unsigned long long get_predefined_texture_width (unsigned long long name) { return get_predefined_texture_size(name)[0]; }
unsigned long long get_predefined_texture_height(unsigned long long name) { return get_predefined_texture_size(name)[1]; }

#define GET_PREDEFINED_TEXTURE_SIZES 1

void update_predefined_texture(unsigned long long name) {
	switch (name) {
		case TEXTURE_BACKGROUND: {
			break;
			
		} case TEXTURE_FROSTED_BACKGROUND: {
			break;
			
		} default: {
			printf("WARNING Texture %lld is unknown\n", name);
			break;
			
		}
		
	}
	
}
