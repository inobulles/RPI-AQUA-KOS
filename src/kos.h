
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

static state_t _state;
state_t* state = &_state;

int place = PLACE_LOADING;
static float delta;

static volatile int terminate;

void (*pass_dispose) (void);
void (*pass_draw) (float delta);
void (*pass_init) (void);

unsigned int screen_width;
unsigned int screen_height;

/// KOS

typedef struct {
	
} kos_t;

int foundation_main(void) {
	#include "main/init.h"
	
	clock_t time_1;
	clock_t time_2;
	
	terminate = 0;
	while (!terminate) {
		time_1 = clock();
		delta = -(time_2 - time_1) / 1000000.0f * 1000.0f;
		
		draw(state);
		flip(state);
		
		time_2 = clock();
		
	}
	
	printf("Exiting OPENGLES ...\n");
	opengl_exit(state);
	
	printf("Disposing of all objects ...\n");
	#include "main/dispose.h"
	
	return ERROR_SUCCESS;

}
