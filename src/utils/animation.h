
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
		animation_t this = {
			.time = 3,
			
			.prolongment = prolongment,
			.base = base,
			
			.original_prolongment = prolongment,
			.original_base = base,
			
			.scale = 0.0f,
			.elapsed = 0.0f
			
		};
		
		return this;
		
	}
	
	void reset_animation(animation_t* this) {
		this->prolongment = this->original_prolongment;
		this->base = this->original_base;
		
		this->scale = 0.0f;
		this->elapsed = 0.0f;
		
	}
	
	float animate(animation_t* this, float delta) {
		this->elapsed++;
		
		this->scale += ((this->scale / 10.0f) + 0.2f) * delta * 60.0f / this->prolongment;
		this->base = 1.0f / (this->scale + 1.0f);
		
		if (this->elapsed > 70 * this->time) {
			this->base = 0.0f;
			
		}
		
		return this->base;
		
	}
	
#endif
