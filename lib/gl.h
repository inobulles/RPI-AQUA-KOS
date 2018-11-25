	
#ifndef __AQUA__LIB__GL_H
	#define __AQUA__LIB__GL_H
		
	typedef struct {
		uvar command;
		
		flt left;
		flt right;
		flt bottom;
		flt top;
		
		flt near;
		flt far;
		
		flt x;
		flt y;
		flt z;
		flt w;
		
		void* vertices;
		uvar  vertex_count;
		
		flt red;
		flt green;
		flt blue;
		flt alpha;
		
		void* faces;
		uvar  face_count;
		
	} __lib_function_gl_device_parameters_t;
	
	private bool lib(gl_command)(__lib_function_gl_device_parameters_t* parameters) {
		device gl_device = is_device_supported("gl");
		
		if (gl_device) {
			uvar* device_result = get_device(gl_device, (final char*) parameters);
			
			if (device_result == nullptr) {
				return false;
				
			} else {
				uvar   result = *device_result;
				return result;
				
			}
			
		} else {
			print("WARNING OpenGL is not supported on self platform\n");
			return true;
			
		}
		
	}
	
	private bool lib(gl_camera)(uvar command, flt left, flt right, flt bottom, flt top, flt near, flt far) {
		__lib_function_gl_device_parameters_t parameters;
		parameters.command = command;
		
		parameters.left   = left;
		parameters.right  = right;
		parameters.bottom = bottom;
		parameters.top    = top;
		
		parameters.near = near;
		parameters.far  = far;
		
		return lib(gl_command)(&parameters);
		
	}
	
	bool gl_frustum(flt left, flt right, flt bottom, flt top, flt near, flt far) { return lib(gl_camera)('f', left, right, bottom, top, near, far); }
	bool gl_ortho  (flt left, flt right, flt bottom, flt top, flt near, flt far) { return lib(gl_camera)('o', left, right, bottom, top, near, far); }
	
	bool gl_draw_vertices(void* vertices, uvar vertex_count) {
		__lib_function_gl_device_parameters_t parameters;
		parameters.command = 'v';
		
		parameters.vertices     = vertices;
		parameters.vertex_count = vertex_count;
		
		parameters.face_count = 0;
		return lib(gl_command)(&parameters);
		
	}
	
	bool gl_draw_lines(void* faces, uvar face_count, void* vertices, uvar vertex_count) {
		__lib_function_gl_device_parameters_t parameters;
		parameters.command = 'v';
		
		parameters.faces      = faces;
		parameters.face_count = face_count;
		
		parameters.vertices     = vertices;
		parameters.vertex_count = vertex_count;
		
		return lib(gl_command)(&parameters);
		
	}
	
	bool gl_rotate(flt x, flt y, flt z, flt w) {
		__lib_function_gl_device_parameters_t parameters;
		parameters.command = 'r';
		
		parameters.x = x;
		parameters.y = y;
		parameters.z = z;
		parameters.w = w;
		
		return lib(gl_command)(&parameters);
		
	}
	
	bool gl_colour(flt red, flt green, flt blue, flt alpha) {
		__lib_function_gl_device_parameters_t parameters;
		parameters.command = 'c';
		
		parameters.red   = red;
		parameters.green = green;
		parameters.blue  = blue;
		parameters.alpha = alpha;
		
		return lib(gl_command)(&parameters);
		
	}
	
#endif
	
