
#ifndef __AQUA__LIB__LOADERS_OBJ_H
	#define __AQUA__LIB__LOADERS_OBJ_H
	
	#include "../floats.h"
	#include "../memory/realloc.h"
	
	typedef struct {
		flt x;
		flt y;
		flt z;
		
	} vertex_t;
	
	typedef struct { // quads
		uvar pair1[2];
		uvar pair2[2];
		uvar pair3[2];
		uvar pair4[2];
		
	} vertex_line_face_t;
	
	typedef struct {
		char name[1024];
		var  name_index;
		
		var       vertex_count;
		vertex_t* vertices;
		
		var                 face_count;
		vertex_line_face_t* faces;
		
	} obj_t;
	
	#define OBJ_DEFAULT_INDEX_EXPONENT 1000000000000
	#define OBJ_FACES_QUADS false
	
	bool new_obj(obj_t* self, final char* path) {
		char* data;
		var   bytes;
		
		if (fs_read(path, &data, &bytes)) {
			print("WARNING Failed to load OBJ file (probably wrong path `%s`?)\n", path);
			return true;
			
		} else {
			self->name_index = 0;
			memset(self->name, 0, sizeof(self->name));
			
			self->vertex_count = 1;
			self->face_count   = 1;
			
			self->vertices = (vertex_t*)           malloc(self->vertex_count * sizeof(vertex_t));
			self->faces    = (vertex_line_face_t*) malloc(self->face_count   * sizeof(vertex_line_face_t));
			
			var current_line = 1;
			
			bool previous_newline = true;
			bool parsing_comment  = false;
			bool parsing_name     = false;
			
			var  parsing_vertex   = false;
			var  parsing_face     = false;
			
			bool float_negative = false;
			bool float_decimal  = false;
			flt  float_buffer   = 0;
			
			var index_buffer   = 0;
			var index_exponent = OBJ_DEFAULT_INDEX_EXPONENT;
			
			var exponent       =  1;
			var current_vertex = -1;
			var current_face   = -1;
			
			iterate (bytes) {
				if (previous_newline) {
					previous_newline = false;
					
					switch (data[i]) {
						case 'o': {
							i++;
							parsing_name = true;
							break;
							
						} case '#': {
							parsing_comment = true;
							break;
							
						} case 'v': {
							if (data[i + 1] != 'n') {
								parsing_vertex = true;
								i++;
								
								self->vertices = (vertex_t*) realloc(self->vertices, self->vertex_count * sizeof(vertex_t), (self->vertex_count + 1) * sizeof(vertex_t));
								self->vertex_count++;
								current_vertex++;
								
							} else {
								// normals
								
							}
							
							break;
							
						} case 'f': {
							i++;
							
							self->faces = (vertex_line_face_t*) realloc(self->faces, self->face_count * sizeof(vertex_line_face_t), (self->face_count + 1) * sizeof(vertex_line_face_t));
							self->face_count++;
							
							parsing_face = true;
							current_face++;
							
							break;
							
						} default: {
							// unknown
							break;
							
						}
						
					}
					
				} elif (data[i] == '\n') {
					if (parsing_vertex == 3) {
						if (float_negative) {
							float_negative = false;
							float_buffer   = -float_buffer;
							
						}
						
						self->vertices[current_vertex].z = float_buffer;
						
					} elif (parsing_vertex) {
						print("WARNING Not enough dimensions to vertex command in OBJ file (line %lld)\n", current_line);
						
					}
					
					if (parsing_face == (OBJ_FACES_QUADS then 4 orelse 3)) {
						if (not OBJ_FACES_QUADS) {
							self->faces[current_face].pair4[0] = 0;
							self->faces[current_face].pair3[1] = index_buffer / index_exponent - 1;
							
						} else {
							self->faces[current_face].pair4[1] = index_buffer / index_exponent - 1;
							
						}
						
					} elif (parsing_face) {
						print("WARNING Not enough vertex pairs to face command in OBJ file (line %lld)\n", current_line);
						
					}
					
					if (parsing_comment) {
						parsing_comment = false;
						print("\n");
						
					}
					
					parsing_name     = false;
					previous_newline = true;
					parsing_vertex   = false;
					parsing_face     = false;
					
					exponent      = 1;
					float_buffer  = 0;
					float_decimal = false;
					
					index_buffer   = 0;
					index_exponent = OBJ_DEFAULT_INDEX_EXPONENT;
					
					current_line++;
					
				} else {
					if (parsing_comment) {
						print("%c", data[i]);
						
					} elif (parsing_name) {
						self->name[self->name_index++] = data[i];
						
					} elif (parsing_vertex) {
						if (data[i] == '-') {
							float_negative = not float_negative;
							
						} elif (data[i] == '.') {
							float_decimal = true;
							exponent = FLOAT_ONE / 10;
							
						} elif (data[i] == ' ') {
							if (float_negative) {
								float_negative = false;
								float_buffer   = -float_buffer;
								
							}
							
							if   (parsing_vertex == 1) self->vertices[current_vertex].x = float_buffer;
							elif (parsing_vertex == 2) self->vertices[current_vertex].y = float_buffer;
							else                       print("WARNING Too many dimensions to vertex command in OBJ file (line %lld)\n", current_line);
							
							parsing_vertex++;
							
							exponent      = 1;
							float_buffer  = 0;
							float_decimal = false;
							
						} else {
							var digit = data[i] - '0';
							
							if (float_decimal) {
								float_buffer += digit * exponent;
								exponent     /= 10;
								
							} else {
								float_buffer += digit * exponent * FLOAT_ONE;
								exponent     *= 10;
								
							}
							
						}
						
					} elif (parsing_face) {
						if (data[i] == '/') {
							i++;
							
							if   (parsing_face == 1) self->faces[current_face].pair1[0] = index_buffer / index_exponent - 1;
							elif (parsing_face == 2) self->faces[current_face].pair2[0] = index_buffer / index_exponent - 1;
							elif (parsing_face == 3) self->faces[current_face].pair3[0] = index_buffer / index_exponent - 1;
							
							#if OBJ_FACES_QUADS
								elif (parsing_face == 4) self->faces[current_face].pair4[0] = index_buffer / index_exponent - 1;
							#endif
							
							else                     print("WARNING Too many vertex pairs to face command in OBJ file (line %lld)\n", current_line);
							
							index_buffer   = 0;
							index_exponent = OBJ_DEFAULT_INDEX_EXPONENT;
							
						} elif (data[i] == ' ') {
							if   (parsing_face == 1) self->faces[current_face].pair1[1] = index_buffer / index_exponent - 1;
							elif (parsing_face == 2) self->faces[current_face].pair2[1] = index_buffer / index_exponent - 1;
							
							#if OBJ_FACES_QUADS
								elif (parsing_face == 3) self->faces[current_face].pair3[1] = index_buffer / index_exponent - 1;
							#endif
							
							else                     print("WARNING Too many vertex pairs to face command in OBJ file (line %lld)\n", current_line);
							
							parsing_face++;
							
							index_buffer   = 0;
							index_exponent = OBJ_DEFAULT_INDEX_EXPONENT;
							
						} else {
							index_exponent /= 10;
							index_buffer   += (data[i] - '0') * index_exponent;
							
						}
						
					}
					
				}
				
			}
			
			self->vertex_count--;
			self->face_count  --;
			
			fs_free(data, bytes);
			return false;
			
		}
		
	}
	
	void dispose_obj(obj_t* self) {
		mfree(self->vertices, (self->vertex_count + 1) * sizeof(vertex_t));
		mfree(self->faces,    (self->face_count   + 1) * sizeof(vertex_line_face_t));
		
	}
	
#endif
