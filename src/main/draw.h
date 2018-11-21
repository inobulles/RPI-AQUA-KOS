
if (place != PLACE_LOADING) {
	draw(state);
	
}

switch (place) {
	case PLACE_LOADING: {
		loading_draw(delta, state);
		break;
		
	} case PLACE_MAIN: {
		pass_draw(delta);
		break;
		
	} case PLACE_DEBUG:
	default: {
		// do whatever the fuck ya want here
		break;
		
	}
	
}

flip(state);
