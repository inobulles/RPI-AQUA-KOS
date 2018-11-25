
#ifndef __AQUA__UITILS_ANIMATION_H
	#define __AQUA__UITILS_ANIMATION_H
	
	typedef struct {
		unsigned short time;
		
		float original_prolongment;
		float original_base;
		
		float prolongment;
		float base;
		
		float scale;
		float elapsed;
		
	} animation_t;
	
	animation_t animation(float base, float prolongment) {
		animation_t self = {
			.time = 3,
			
			.prolongment = prolongment,
			.base = base,
			
			.original_prolongment = prolongment,
			.original_base = base,
			
			.scale = 0.0f,
			.elapsed = 0.0f
			
		};
		
		return self;
		
	}
	
	void reset_animation(animation_t* self) {
		self->prolongment = self->original_prolongment;
		self->base = self->original_base;
		
		self->scale = 0.0f;
		self->elapsed = 0.0f;
		
	}
	
	float animate(animation_t* self, float delta) {
		self->elapsed++;
		
		self->scale += ((self->scale / 10.0f) + 0.2f) * delta * 60.0f / self->prolongment;
		self->base = 1.0f / (self->scale + 1.0f);
		
		if (self->elapsed > 70 * self->time) {
			self->base = 0.0f;
			
		}
		
		return self->base;
		
	}
	
#endif
