
/// STARTED 3 MARCH 2018

#include <stdio.h>
#include <time.h>

#include "common/error.h"

#include "gl/init.h"
#include "gl/exit.h"
#include "gl/draw.h"
#include "gl/view.h"
#include "gl/surf.h"
#include "gl/texture.h"
#include "gl/clear.h"

#include "graphics/layer.h"
#include "graphics/texture.h"

#include "const/places.h"
#include "screens/loading.h"

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

void video_flip(void) {
	current_kos->time_1 = clock();
	current_kos->delta = -(current_kos->time_2 - current_kos->time_1) / 1000000.0f * 1000.0f;
	
	draw(current_kos->state);
	flip(current_kos->state);
	
	current_kos->time_2 = clock();
	
}

int kos_init(kos_t* self) {
	current_kos = self;
	#include "main/init.h"
	
	state = (state_t*) &self->state;
	
}

void kos_quit(kos_t* self) {
	printf("Exiting OPENGLES ...\n");
	opengl_exit(state);
	
	printf("Disposing of all objects ...\n");
	#include "main/dispose.h"
	
}
