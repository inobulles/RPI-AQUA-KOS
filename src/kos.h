
/// STARTED 3 MARCH 2018

#include <stdio.h>
#include <time.h>

#define MAX_PATH_LENGTH 4096

#define GET_PATH(_path) \
	char path[MAX_PATH_LENGTH] = "root/"; \
	strncat(path, (char*) (_path), MAX_PATH_LENGTH - strlen(path)); \

#include "lib/macros.h"
#include "lib/structs.h"

#include "gl/init.h"
#include "gl/exit.h"
#include "gl/draw.h"
#include "gl/view.h"
#include "gl/surf.h"
#include "gl/texture.h"

#include "h264/decoder.h"

state_t* state;

unsigned int screen_width;
unsigned int screen_height;

typedef struct {
	clock_t time_1;
	clock_t time_2;
	
	float delta;
	state_t state;
	
} kos_t;

static kos_t* current_kos;

#include "decoders/bmp.h"
#include "functions/system.h"
#include "functions/fs.h"
#include "functions/video.h"
#include "functions/font.h"
#include "functions/screenshot.h"

//~ #include "openvg/test.h"

int kos_init(kos_t* self) {
	current_kos = self;
	state = (state_t*) &self->state;
	
	printf("Initializing the RPI OPENGLES AQUA compatibility wrapper ...\n");
	
	printf("Initializing the BCM host ...\n");
	bcm_host_init();
	
	printf("Clearing state ...\n");
	memset(state, 0, sizeof(*state));
	
	printf("Setting up OPENGLES ...\n");
	
	opengl_init(state);
	opengl_view(state);
	
	screen_width  = state->screen_width;
	screen_height = state->screen_height;
	
	printf("Setting up predefined textures ...\n");
	
	if (kos_setup_predefined_textures(self)) {
		printf("WARNING Failed to setup predefined textures\n");
		
	}
	
	return 0;
	
}

void kos_quit(kos_t* self) {
	printf("Exiting OPENGLES ...\n");
	opengl_exit(state);
	
	printf("Disposing of all objects ...\n");
	
	kos_free_predefined_textures(self);
	kos_destroy_fonts();
	
}
