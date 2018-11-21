
unsigned long long video_fps(void) {
	return (unsigned long long) (1.0f / current_kos->delta);
	
}

unsigned long long video_width (void) { return (unsigned long long) screen_width;  }
unsigned long long video_height(void) { return (unsigned long long) screen_height; }

void video_flip(void) {
	current_kos->time_1 = clock();
	current_kos->delta = -(current_kos->time_2 - current_kos->time_1) / 1000000.0f * 1000.0f;
	
	flip(&current_kos->state);
	current_kos->time_2 = clock();
	
}

void video_clear_colour(unsigned long long r, unsigned long long g, unsigned long long b, unsigned long long a) {
	glClearColor((float) r / _UI64_MAX, (float) g / _UI64_MAX, (float) b / _UI64_MAX, (float) a / _UI64_MAX);
	
}

void video_clear(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
}

void get_events(event_list_t* self) {
	self->quit = 0;
	
}
