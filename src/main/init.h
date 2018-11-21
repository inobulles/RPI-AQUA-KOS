
printf("Initializing the RPI OPENGLES AQUA compatibility wrapper ...\n");

printf("Initializing the BCM host ...\n");
bcm_host_init();

printf("Clearing state ...\n");
memset(state, 0, sizeof(*state));

printf("Setting up OPENGLES ...\n");

opengl_init(state);
opengl_view(state);

screen_width = state->screen_width;
screen_height = state->screen_height;

// objects

loading_init();
pass_init();
