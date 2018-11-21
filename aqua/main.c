/// STARTED 5 MARCH 2018

#include "wrapper.h"
#include "screens/desktop.h"

int rand(void);

static unsigned int stage = 0;
static desktop_t main_desktop;

void init_function(void) {
	
}

void draw_function(float delta) {
	switch (stage) {
		case 0: { // opening
			new_desktop(&main_desktop);
			
			stage++;
			break;
			
		} case 1: { // main
			desktop_draw(&main_desktop);
			
			break;
			
		} default: {
			break;
			
		}
		
	}
	
}

void dispose_function(void) {
	desktop_dispose(&main_desktop);
	
}

int main(void) {
	pass_init = init_function;
	pass_draw = draw_function;
	pass_dispose = dispose_function;
	
	return foundation_main();
	
}
