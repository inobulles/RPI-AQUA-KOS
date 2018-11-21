
#ifndef __AQUA__PROTOTYPES_H
	#define __AQUA__PROTOTYPES_H
	
	// communication
	
	void (*pass_dispose) (void);
	void (*pass_draw) (float delta);
	void (*pass_init) (void);
	
	// typedefs
	
	#define SURFACE_VERTEX_COUNT 6
	
	typedef struct {
		float a;
		
		float r;
		float g;
		float b;
		
	} colour_t;
	
	typedef float GLfloat;
	typedef unsigned int GLuint;
	typedef unsigned char GLubyte;
	
	typedef struct {
		GLfloat	x;
		GLfloat y;
		GLfloat z;

	} Vertex3D;

	typedef struct {
		GLfloat x;
		GLfloat y;

	} Coord2D;

	typedef struct {
		GLfloat	red;
		GLfloat	green;
		GLfloat	blue;
		GLfloat alpha;

	} Color3D;
	
	typedef struct {
		float r;
		float g;
		float b;
		
		float width;
		float height;

		float x;
		float y;

		int layer;
		float alpha;

		Vertex3D vertices[SURFACE_VERTEX_COUNT];
		Color3D colours[SURFACE_VERTEX_COUNT];
		Coord2D tex_coords[SURFACE_VERTEX_COUNT];
		GLubyte faces[SURFACE_VERTEX_COUNT];

		unsigned char scroll_texture;
		
		float scroll_texture_x;
		float scroll_texture_y;
		
		float scroll_texture_width;
		float scroll_texture_height;

		unsigned char has_texture;
		GLuint texture;

	} surface_t;
	
	typedef struct {
		unsigned char used;
		unsigned int id;
		
		surface_t surface;
		unsigned char* data;
		
		unsigned int width;
		unsigned int height;
		
		unsigned char bpp;
		
	} layer_t;
	
	// prototypes
	
		// variables
	
	unsigned int screen_width;
	unsigned int screen_height;
	
		// functions
	
	colour_t new_colour(float r, float g, float b, float a);
	
	void clear(colour_t colour);
	void clear_alpha(unsigned char alpha_mask);
	
	unsigned char* solid_texture(unsigned int width, unsigned int height, unsigned int bpp, colour_t colour);
	GLuint create_texture(unsigned int width, unsigned int height, unsigned char* data, unsigned char bpp);
	unsigned char* npot_to_pot(unsigned char* data, unsigned int width, unsigned int height);
	
	layer_t* new_layer(unsigned char* data, float x, float y, int depth, float width, float height, unsigned int resolution_x, unsigned int resolution_y, unsigned char bpp);
	void layer_draw(layer_t* this);
	void layer_set_alpha(layer_t* this, float alpha);
	void layer_set_colour(layer_t* this, colour_t colour);
	void layer_dispose(layer_t* this);
	void layer_set_position(layer_t* this, float x, float y);
	void layer_set_outlook(layer_t* this, float x, float y, float width, float height);
	
	int foundation_main(void);
	int printf(const char* format, ...);
	
	void play_video(const char* filename);
	unsigned char* get_accelerated_image(const char* path);
	
#endif
