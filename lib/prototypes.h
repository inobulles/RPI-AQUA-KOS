
#include "structs.h"
#include "macros.h"

/// NOTE that "support" functions are to check if a KOS supports a certain feature

// misc stuff

void __stack_chk_fail(void);

// basic stuff

void __exit(unsigned long long status);
#define exit __exit

void print(const char* format, ...);
void __sprintf(char* buffer, const char* format, ...);
void debug(void);

// memory stuff

void* memcpy(void* __dest, const void*        __src, unsigned long long __n);
void* memset(void* __dest, unsigned long long __c,   unsigned long long __n);

void* malloc(unsigned long long bytes);
void mfree(void* pointer, unsigned long long bytes);

// platform stuff

unsigned long long get_platform(void);
unsigned long long platform_system(const char* command); // self command is dangerous and the compiler should warn about it
unsigned long long is_device_supported(const char* device); // check if GPS is supported, for example, and return device id if that is the case

unsigned long long* get_device(unsigned long long device, const char* extra);
void send_device(unsigned long long device, const char* extra, unsigned long long* data);

// video stuff

void set_video_visibility(unsigned long long state);
unsigned long long video_fps(void);

void video_clear(void);
void video_clear_colour(unsigned long long red, unsigned long long green, unsigned long long blue, unsigned long long alpha);

void video_draw(void);
void video_flip(void);

void video_zoom(unsigned long long zoom);
void video_translate(unsigned long long x, unsigned long long y);
void video_rotate(unsigned long long roll);

unsigned long long video_width(void);
unsigned long long video_height(void);

// rect stuff (note that self is for debugging mainly)

rectangle_t new_rectangle(unsigned long long x, unsigned long long y, unsigned long long width, unsigned long long height);
void draw_rectangle(rectangle_t* self);

// surface stuff

void surface_new(surface_t* self, signed long long x, signed long long y, unsigned long long width, unsigned long long height);
void surface_free(surface_t* self);

void surface_set_texture(surface_t* self, texture_t texture);
void surface_draw(surface_t* self);
void surface_set_layer(surface_t* self, signed long long layer);

void surface_set_x(surface_t* self, signed long long x);
void surface_set_y(surface_t* self, signed long long y);

void surface_set_width (surface_t* self, unsigned long long width);
void surface_set_height(surface_t* self, unsigned long long height);

void surface_scroll(surface_t* self, signed long long x, signed long long y, unsigned long long width, unsigned long long height);

void surface_set_alpha  (surface_t* self, unsigned long long alpha);
void surface_set_colour (surface_t* self, unsigned long long red, unsigned long long green, unsigned long long blue);
void surface_set_visible(surface_t* self, unsigned long long visible);

void surface_gradient_left  (surface_t* self, unsigned long long red, unsigned long long green, unsigned long long blue, unsigned long long alpha);
void surface_gradient_right (surface_t* self, unsigned long long red, unsigned long long green, unsigned long long blue, unsigned long long alpha);
void surface_gradient_top   (surface_t* self, unsigned long long red, unsigned long long green, unsigned long long blue, unsigned long long alpha);
void surface_gradient_bottom(surface_t* self, unsigned long long red, unsigned long long green, unsigned long long blue, unsigned long long alpha);

// texture stuff

texture_t get_predefined_texture(unsigned long long name);
void   update_predefined_texture(unsigned long long name);

unsigned long long get_predefined_texture_width (unsigned long long name);
unsigned long long get_predefined_texture_height(unsigned long long name);

texture_t texture_create(unsigned long long* bitmap, unsigned long long bpp, unsigned long long width, unsigned long long height);
void texture_remove(texture_t self);

texture_t create_texture_from_screenshot(void);

// font stuff

unsigned long long get_font_width (font_t self, const char* text);
unsigned long long get_font_height(font_t self, const char* text);

texture_t create_texture_from_font(font_t self, const char* text);

font_t new_font(const char* path, unsigned long long size);
void font_remove(font_t self);

// events stuff

void get_events(event_list_t* self);
void free_events(event_list_t* self);

// networking / request / socket stuff

//~ unsigned long long request_support(void);

//~ request_response_t* request_get (const char* address, ...);
//~ request_response_t* request_post(const char* address, const char* data);

unsigned long long socket_support(void);
//~ ip_address_t get_external_ip_address(void);

void socket_server(socket_t* self, ip_address_t host_ip, unsigned long long port);
void socket_client(socket_t* self, ip_address_t host_ip, unsigned long long port);

void socket_close (socket_t* self);

void  socket_send   (socket_t* self, const char* data, unsigned long long bytes);
char* socket_receive(socket_t* self,                   unsigned long long bytes);

// file system

unsigned long long fs_support(void);

unsigned long long fs_list_count(const char* path);
char**             fs_list      (const char* path);
void               fs_list_free (char** list, unsigned long long count);

unsigned long long fs_make_directory(const char* path, ...); // self returns 0 on success and else is a failure. Also, path includes the name
unsigned long long fs_make_file     (const char* path, ...);

unsigned long long fs_write(const char* path, const char*  data, unsigned long long  length); // self REPLACES the data
unsigned long long fs_read (const char* path,       char** data, unsigned long long* length); // self writes data & length at address data & length

unsigned long long fs_remove(const char* path, ...);
void fs_free(char* data, unsigned long long length);

// bitmap image loading

unsigned long long bmp_support(void);

void bmp_load(bitmap_image_t* self, const char* path);
void bmp_free(bitmap_image_t* self);

// math

unsigned long long map(unsigned long long x, unsigned long long y);

// debugging & rom management

void break_point(const char* message);
unsigned long long index_rom(unsigned long long index);
signed long long    load_rom(const char* path);
