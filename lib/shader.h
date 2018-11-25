
#ifndef __AQUA__LIB_SHADER_H
	#define __AQUA__LIB_SHADER_H
	
	#ifndef GEOMETRY_SHADER
		#define GEOMETRY_SHADER 0
	#endif
	
	typedef struct {
		uvar command;
		uvar program;
		
		uvar possible_geom_code;
		uvar possible_vert_code;
		uvar possible_frag_code;
		
	} __lib_function_shader_device_parameters_t;
	
	typedef struct {
		uvar program;
		
		const char* vert;
		const char* frag;
		
		#if GEOMETRY_SHADER
			const char* geom;
		#endif
		
	} shader_program_t;
	
	#define shader_support() (is_device_supported("shader"))
	
	private uvar lib(shader_command)(shader_program_t* self, uvar command, bool give_code) {
		device shader_device = shader_support();
		__lib_function_shader_device_parameters_t parameters;
		
		if (shader_device) {
			parameters.command = command;
			parameters.program = (uvar) &self->program;
			
			if (give_code) {
				parameters.possible_vert_code = (uvar) self->vert;
				parameters.possible_frag_code = (uvar) self->frag;
				
				#if GEOMETRY_SHADER
					parameters.possible_geom_code = (uvar) self->geom;
				#endif
				
			}
			
			uvar* device_result = get_device(shader_device, (const char*) &parameters);
			
			if (device_result == nullptr) {
				return 0;
				
			} else {
				uvar   result = *device_result;
				return result;
				
			}
			
		} else {
			print("WARNING Shaders are not supported on self platform\n");
			return 0;
			
		}
		
	}
	
	bool new_shader_program(shader_program_t* self, const char* vert_code, const char* frag_code, const char* geom_code) {
		self->vert = vert_code;
		self->frag = frag_code;
		
		#if GEOMETRY_SHADER
			self->geom = geom_code;
		#endif
		
		if (lib(shader_command)(self, 'c', true)) {
			print("WARNING Failed to create shader program\n");
			return true;
			
		} else {
			return false;
			
		}
		
	}
	
	void set_shader(shader_program_t* self) {
		lib(shader_command)(self, 'u', false);
		
	}
	
	void set_default_shader(void) {
		shader_program_t self;
		self.program = 0;
		lib(shader_command)(&self, 'u', false);
		
	}
	
	void dispose_shader(shader_program_t* self) {
		lib(shader_command)(self, 'd', false);
		
	}
	
#endif
