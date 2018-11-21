
#ifndef __AQUA__DECODERS_BMP_H
	#define __AQUA__DECODERS_BMP_H
	
	#include <math.h>
	#include "../gl/root.h"
	
	#pragma pack(push, 1)
	
	typedef struct bhs {
		uint16_t magic;
		uint32_t file_size;
		
		uint16_t reserved_1;
		uint16_t reserved_2;
		
		uint32_t offset;
		
	} bitmap_header_t;
	
	typedef struct bihs {
		uint32_t size;
		
		int32_t width;
		int32_t height;
		
		uint16_t planes;
		uint16_t bpp;
		
		uint32_t compression_type;
		uint32_t image_bytes;
		
		int64_t pixels_per_meter_x;
		int64_t pixels_per_meter_y;
		
		uint32_t colour_count;
		uint32_t important_colours;
		
	} bitmap_info_header_t;
	
	#pragma pack(pop)
	
	bitmap_image_t load_bmp(const char* path) {
		bitmap_image_t image;
		FILE* file = fopen(path, "rb");
		
		if (!file) {
			printf("ERROR Image file could not be opened\n");
			return *(bitmap_image_t*) 0;
			
		}
		
		bitmap_header_t header;
		bitmap_info_header_t info_header;
		
		fread((char*) &header, sizeof(bitmap_header_t), 1, file);
		
		if (header.magic != 0x4D42) {
			printf("ERROR File is not a bitmap image\n");
			fclose(file);
			
			return *(bitmap_image_t*) 0;
			
		}
		
		fread((char*) &info_header, sizeof(bitmap_info_header_t), 1, file);
		
		image.image_size = info_header.image_bytes;
		image.width = info_header.width;
		image.height = info_header.height;
		
		image.data = (unsigned char*) malloc(image.image_size);
		unsigned char temp;
		
		fseek(file, header.offset, SEEK_SET);
		fread(image.data, info_header.image_bytes, 1, file);
		
		int i;
		for (i = 0; i < image.image_size; i += 3) {
			temp = image.data[i];
			image.data[i] = image.data[i + 2];
			image.data[i + 2] = temp;
			
		}
		
		fclose(file);
		return image;

	}
	
	void dispose_bmp(bitmap_image_t image) {
		free(image.data/*, image.image_size*/);
		
	}
	
#endif

