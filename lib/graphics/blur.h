
#ifndef __AQUA__LIB_GRAPHICS_H
	#define __AQUA__LIB_GRAPHICS_H
	
	#include "../framebuffer.h"
	#include "../shader.h"
	#include "../fast/fast.h"
	
	texture_t blur(layer_t* layer, theme_t* theme, var x, var y, var width, var height, uvar radius) {
		texture_t result;
		bool next = true;
		
		if (framebuffer_support() && shader_support()) {
			shader_program_t test;
			
			if (!new_shader_program(&test, "#version 120\nvoid main(){gl_Position=ftransform();}", "#version 120\nvoid main(){gl_FragColor=vec4(0.0);}", nullptr)) {
				dispose_shader(&test);
				next = false;
				
				texture_t first           = texture_create(nullptr, 24, video_width(), video_height());
				framebuffer_t framebuffer = framebuffer_create(first);
				
				char fragment_code[1 << 16];
				
				var biggest = video_width() > video_height() ? video_width() : video_height();
				var passes  = biggest / radius / 3;
				
				sprintf(fragment_code, R"shader-code(
					#version 120
					
					uniform sampler2D sampler_texture;
					uniform int       has_texture;
					
					vec3 offset = vec3(0.0,          1.3846153846, 3.2307692308);
					vec3 weight = vec3(0.2270270270, 0.3162162162, 0.0702702703);
					
					void main(void) {
						vec4 colour;
						
						if (has_texture != 0) {
							vec2 uv    = gl_TexCoord[0].xy;
							vec3 texel = texture2D(sampler_texture, uv).rgb * weight[0];
							
							float passes    = %lld;
							float dimension = %lld / passes;
							
							int i;
							int j;
							
							for (i = 1; i < 3; i++) {
								for (j = 0; j < passes; j++) {
									texel += texture2D(sampler_texture, uv + vec2(0.0, offset[i] + j) / dimension).rgb * weight[i] / passes;
									texel += texture2D(sampler_texture, uv - vec2(0.0, offset[i] + j) / dimension).rgb * weight[i] / passes;
									
								}
								
							}
							
							colour = vec4(texel, 1.0);
							
						} else {
							colour = gl_Color;
							
						}
						
						if (colour.w > 0.0f) gl_FragColor = colour;
						else                 discard;
						
					}
				)shader-code", passes, video_width());
				
				shader_program_t    vertical;
				new_shader_program(&vertical, R"shader-code(
					#version 120
					
					void main(void) {
						gl_TexCoord[0] = gl_MultiTexCoord0;
						gl_Position    = ftransform();
						
					}
				)shader-code", fragment_code, nullptr);
				
				sprintf(fragment_code, R"shader-code(
					#version 120
					
					uniform sampler2D sampler_texture;
					uniform int       has_texture;
					
					vec3 offset = vec3(0.0,          1.3846153846, 3.2307692308);
					vec3 weight = vec3(0.2270270270, 0.3162162162, 0.0702702703);
					
					void main(void) {
						vec4 colour;
						
						if (has_texture != 0) {
							vec2 uv    = gl_TexCoord[0].xy;
							vec3 texel = texture2D(sampler_texture, uv).rgb * weight[0];
							
							float passes    = %lld;
							float dimension = %lld / passes;
							
							int i;
							int j;
							
							for (i = 1; i < 3; i++) {
								for (j = 0; j < passes; j++) {
									texel += texture2D(sampler_texture, uv + vec2(offset[i] + j, 0.0) / dimension).rgb * weight[i] / passes;
									texel += texture2D(sampler_texture, uv - vec2(offset[i] + j, 0.0) / dimension).rgb * weight[i] / passes;
									
								}
								
							}
							
							colour = vec4(texel, 1.0);
							
						} else {
							colour = gl_Color;
							
						}
						
						if (colour.w > 0.0f) gl_FragColor = colour;
						else                 discard;
						
					}
				)shader-code", passes, video_height());
				
				shader_program_t    horizontal;
				new_shader_program(&horizontal, R"shader-code(
					#version 120
					
					void main(void) {
						gl_TexCoord[0] = gl_MultiTexCoord0;
						gl_Position    = ftransform();
						
					}
				)shader-code", fragment_code, nullptr);
				
				framebuffer_bind_pos(framebuffer, x, y, width, height);
				set_shader(&vertical);
				
				video_clear();
				layer_draw(layer);
				
				framebuffer_unbind();
				set_shader(&horizontal);
				
				result             = texture_create(nullptr, 24, video_width(), video_height());
				framebuffer_t last = framebuffer_create(result);
				framebuffer_bind(last);
				
				video_clear();
				load_framebuffer(old, first);
				layer_draw(&old);
				
				framebuffer_unbind();
				set_default_shader();
				texture_remove(first);
				
				framebuffer_remove(framebuffer);
				framebuffer_remove(last);
				
				dispose_shader(&horizontal);
				dispose_shader(&vertical);
				
			}
			
		} if (next) {
			if (is_device_supported("blur")) {
				print("TODO Blur device\n");
				
			} else {
				var* data = (var*) malloc(sizeof(var));
				data[0] = theme->layer_colour << 32;
				
				result = texture_create(data, 24, 1, 1);
				mfree(data, sizeof(var));
				
			}
			
		}
		
		return result;
		
	}
	
#endif
