
namespace kos {
	#include "src/kos.h"
	#include "asm/asm.h"

	void mfree(void* ptr, unsigned long long bytes) { // for some reason, self was not already defined
		free(ptr);
		
	}

	static kos_t kos;

	#define ROM_PATH "ROM.zed"
	static unsigned long long kos_roms_loaded = 0;

	signed long long load_rom(unsigned long long __path) {
		const char* ____path;
		
		if (kos_roms_loaded++) {
			GET_PATH((char*) __path);
			____path = path;
			
		} else {
			____path = (const char*) __path;
			
		}
		
		const char* path = ____path;
		
		void*                 __pointer_current_program_previous = __pointer_current_program;
		__pointer__program_t* __pointer___self_previous          = __pointer___self;
		
		program_t de_program;
		FILE* fp = fopen(path, "rb");
		
		if (!fp) {
			printf("WARNING Could not open ROM file (%s)\n", path);
			kos_quit(&kos);
			exit(1);
			
		}
		
		fseek(fp, 0, SEEK_END);
		unsigned long long bytes = ftell(fp);
		rewind(fp);
		
		char* rom = (char*) malloc(bytes);
		fread(rom, sizeof(char), bytes, fp);
		
		de_program.pointer = rom;
		
		printf("Starting run setup phase ...\n");
		program_run_setup_phase(&de_program);
		
		while (!program_run_loop_phase(&de_program));
		program_free(&de_program);
		
		#if !OLD_ROM_FORMAT
			mfree(rom, bytes);
		#endif
		
		__pointer_current_program = __pointer_current_program_previous;
		__pointer___self          = __pointer___self_previous;
		
		return de_program.error_code;
		
	}

	void kos_main(void) {
		printf("\nControl passed to the CW\n");
		printf("Initializing the KOS ...\n");
		
		if (kos_init(&kos)) {
			printf("WARNING Failed to initialize KOS. Exitting ...\n");
			exit(1);
			
		}
		
		printf("Entering the DE ...\n");
		
		//~ int error_code = load_rom((unsigned long long) ROM_PATH);
		//~ printf("DE return code is %d\n", error_code);
		
		//~ printf("Quitting KOS ...\n");
		//~ kos_quit(&kos);
		
		//~ return error_code;
		
	}
	
}

#include "root.h"
#include "lib/fast/wizard.h"

#define BLANK                0
#define TITLE_NIR_VS_UK_RIOT 1
#define TD_NIR_VS_UK_RIOT    2
#define PLACES               3
#define DERRY_OVERVIEW       4
#define DERRY_PRECISE        5
#define BOTBS                6
#define INFO_NIR_VS_UK_RIOT  7
#define INFO_NIR_VS_UK_RIOT1 8
#define BLACK_BEFORE_U2      9
#define SUNRISE              10
#define ALBUM_COVER          11
#define TITLE_U2             12
#define ALBUM_SPECS          13
#define SONG_TITLE           14
#define LYRICS_FULL          15
#define LYRICS_HIGHLIGHT     16
#define LYRICS_SELECTED      17
#define IMAGE1               18
#define FROST1               19
#define IMAGE2               20
#define FROST2               21
#define IMAGE3               22
#define FROST3               23
#define CREDITS              24
#define SOURCES              25

#define theme_default theme_dark

var main(void) {
	event_list_t events;
	
	wizard_t wizard;
	new_wizard(&wizard, (SOURCES + 1));
	
	font_t biggest  = new_font(PATH"fonts/main.ttf", _UI64_MAX / 3);
	font_t subtitle = new_font(PATH"fonts/main.ttf", _UI64_MAX / 12);
	font_t smaller  = new_font(PATH"fonts/main.ttf", _UI64_MAX / 20);
	font_t url      = new_font(PATH"fonts/main.ttf", _UI64_MAX / 30);
	
	new_wizard_page(&wizard.pages[BLANK], 0, 0);
	
	new_wizard_page     (&wizard.pages[TITLE_NIR_VS_UK_RIOT], 1, 1);
		new_layer       (&wizard.pages[TITLE_NIR_VS_UK_RIOT].layers[0]);
		layer_set_bitmap(&wizard.pages[TITLE_NIR_VS_UK_RIOT].layers[0], PATH"REMME/dab-frost.bmp");
		wizard.pages[TITLE_NIR_VS_UK_RIOT].layers[0].fullscreen = true;
		layer_init      (&wizard.pages[TITLE_NIR_VS_UK_RIOT].layers[0]);
		
		new_text           (&wizard.pages[TITLE_NIR_VS_UK_RIOT].texts[0], subtitle, "Riots between NIR and UK", theme_default(), 5);
		text_point_to_point(&wizard.pages[TITLE_NIR_VS_UK_RIOT].texts[0], FLOAT_ONE * 3, POSITION_BOTTOM, POSITION_CENTER);
	
	new_wizard_page     (&wizard.pages[TD_NIR_VS_UK_RIOT], 0, 1);
		new_layer       (&wizard.pages[TD_NIR_VS_UK_RIOT].layers[0]);
		layer_set_bitmap(&wizard.pages[TD_NIR_VS_UK_RIOT].layers[0], PATH"REMME/dab-raw.bmp");
		wizard.pages[TD_NIR_VS_UK_RIOT].layers[0].fullscreen = true;
		layer_init      (&wizard.pages[TD_NIR_VS_UK_RIOT].layers[0]);
	
	new_wizard_page     (&wizard.pages[PLACES], 3, 1);
		new_layer       (&wizard.pages[PLACES].layers[0]);
		layer_set_bitmap(&wizard.pages[PLACES].layers[0], PATH"REMME/dab-frost.bmp");
		wizard.pages[PLACES].layers[0].fullscreen = true;
		layer_init      (&wizard.pages[PLACES].layers[0]);
		
		new_text           (&wizard.pages[PLACES].texts[0], smaller, "Riots (called \"Troubles\") mainly occurred in:", theme_default(), 5);
		text_point_to_point(&wizard.pages[PLACES].texts[0], FLOAT_ONE * 3, POSITION_BOTTOM, POSITION_TWO_THIRDS);
		
		new_text           (&wizard.pages[PLACES].texts[1], smaller, "Newry, Armagh, Dungannon", theme_default(), 5);
		text_point_to_point(&wizard.pages[PLACES].texts[1], FLOAT_ONE * 2, POSITION_BOTTOM, POSITION_CENTER);
		
		new_text           (&wizard.pages[PLACES].texts[2], smaller, "Coalisland, Dungiven and Belfast", theme_default(), 5);
		text_point_to_point(&wizard.pages[PLACES].texts[2], FLOAT_ONE, POSITION_BOTTOM, POSITION_ONE_THIRD);
	
	new_wizard_page     (&wizard.pages[DERRY_OVERVIEW], 1, 1);
		new_layer       (&wizard.pages[DERRY_OVERVIEW].layers[0]);
		layer_set_bitmap(&wizard.pages[DERRY_OVERVIEW].layers[0], PATH"REMME/overview.bmp");
		wizard.pages[DERRY_OVERVIEW].layers[0].fullscreen = true;
		layer_init      (&wizard.pages[DERRY_OVERVIEW].layers[0]);
		
		new_text           (&wizard.pages[DERRY_OVERVIEW].texts[0], subtitle, "· Derry", theme_default(), 5);
		text_align         (&wizard.pages[DERRY_OVERVIEW].texts[0], false, true);
		text_point_to_point(&wizard.pages[DERRY_OVERVIEW].texts[0], FLOAT_ONE * 3, POSITION_BOTTOM, POSITION_CENTER);
	
	new_wizard_page     (&wizard.pages[DERRY_PRECISE], 1, 1);
		new_layer       (&wizard.pages[DERRY_PRECISE].layers[0]);
		layer_set_bitmap(&wizard.pages[DERRY_PRECISE].layers[0], PATH"REMME/derry-3d.bmp");
		wizard.pages[DERRY_PRECISE].layers[0].fullscreen = true;
		layer_init      (&wizard.pages[DERRY_PRECISE].layers[0]);
		
		new_text         (&wizard.pages[DERRY_PRECISE].texts[0], subtitle, "· Derry", theme_default(), 5);
		text_align       (&wizard.pages[DERRY_PRECISE].texts[0], false, true);
		text_set_position(&wizard.pages[DERRY_PRECISE].texts[0], POSITION_CENTER);
	
	new_wizard_page        (&wizard.pages[BOTBS], 2, 1);
		new_layer          (&wizard.pages[BOTBS].layers[0]);
		layer_set_bitmap   (&wizard.pages[BOTBS].layers[0], PATH"REMME/derry-3d-frost.bmp");
		wizard.pages[BOTBS].layers[0].fullscreen = true;
		layer_init         (&wizard.pages[BOTBS].layers[0]);
		
		new_text           (&wizard.pages[BOTBS].texts[0], subtitle, "Battle of the Bogside", theme_default(), 5);
		text_point_to_point(&wizard.pages[BOTBS].texts[0], FLOAT_ONE * 3, POSITION_BOTTOM, POSITION_CENTER);
		
		new_text           (&wizard.pages[BOTBS].texts[1], smaller, "(Bloody sunday)", theme_default(), 5);
		text_point_to_point(&wizard.pages[BOTBS].texts[1], FLOAT_ONE * 5, POSITION_BOTTOM, POSITION_ONE_THIRD);
	
	new_wizard_page     (&wizard.pages[INFO_NIR_VS_UK_RIOT], 3, 1);
		new_layer       (&wizard.pages[INFO_NIR_VS_UK_RIOT].layers[0]);
		layer_set_bitmap(&wizard.pages[INFO_NIR_VS_UK_RIOT].layers[0], PATH"REMME/derry-3d-frost.bmp");
		wizard.pages[INFO_NIR_VS_UK_RIOT].layers[0].fullscreen = true;
		layer_init      (&wizard.pages[INFO_NIR_VS_UK_RIOT].layers[0]);
		
		new_text           (&wizard.pages[INFO_NIR_VS_UK_RIOT].texts[0], smaller, "From 12th to 14th August 1969", theme_default(), 5);
		text_point_to_point(&wizard.pages[INFO_NIR_VS_UK_RIOT].texts[0], FLOAT_ONE * 3, POSITION_BOTTOM, POSITION_TWO_THIRDS);
		
		new_text           (&wizard.pages[INFO_NIR_VS_UK_RIOT].texts[1], subtitle, "8 killed", theme_default(), 5);
		text_point_to_point(&wizard.pages[INFO_NIR_VS_UK_RIOT].texts[1], FLOAT_ONE * 2, POSITION_BOTTOM, POSITION_CENTER);
		
		new_text           (&wizard.pages[INFO_NIR_VS_UK_RIOT].texts[2], subtitle, "750 injured", theme_default(), 5);
		text_point_to_point(&wizard.pages[INFO_NIR_VS_UK_RIOT].texts[2], FLOAT_ONE, POSITION_BOTTOM, POSITION_ONE_THIRD);
	
	new_wizard_page     (&wizard.pages[INFO_NIR_VS_UK_RIOT1], 2, 1);
		new_layer       (&wizard.pages[INFO_NIR_VS_UK_RIOT1].layers[0]);
		layer_set_bitmap(&wizard.pages[INFO_NIR_VS_UK_RIOT1].layers[0], PATH"REMME/derry-3d-frost.bmp");
		wizard.pages[INFO_NIR_VS_UK_RIOT1].layers[0].fullscreen = true;
		layer_init      (&wizard.pages[INFO_NIR_VS_UK_RIOT1].layers[0]);
		
		new_text           (&wizard.pages[INFO_NIR_VS_UK_RIOT1].texts[0], subtitle, "1820 families evacuated", theme_default(), 5);
		text_point_to_point(&wizard.pages[INFO_NIR_VS_UK_RIOT1].texts[0], FLOAT_ONE * 3, POSITION_BOTTOM, POSITION_TWO_THIRDS);
		
		new_text           (&wizard.pages[INFO_NIR_VS_UK_RIOT1].texts[1], subtitle, "150 destroyed homes", theme_default(), 5);
		text_point_to_point(&wizard.pages[INFO_NIR_VS_UK_RIOT1].texts[1], FLOAT_ONE, POSITION_BOTTOM, POSITION_ONE_THIRD);
	
	new_wizard_page        (&wizard.pages[SUNRISE], 0, 1);
		new_layer          (&wizard.pages[SUNRISE].layers[0]);
		layer_set_bitmap   (&wizard.pages[SUNRISE].layers[0], PATH"REMME/album-back.bmp");
		wizard.pages[SUNRISE].layers[0].fullscreen = true;
		layer_init         (&wizard.pages[SUNRISE].layers[0]);
		layer_set_animation(&wizard.pages[SUNRISE].layers[0], ANIMATION_TYPE_ENABLED | ANIMATION_TYPE_ALPHA, FLOAT_ONE * 10);
	
	new_wizard_page        (&wizard.pages[ALBUM_COVER], 0, 2);
		new_layer          (&wizard.pages[ALBUM_COVER].layers[0]);
		layer_set_bitmap   (&wizard.pages[ALBUM_COVER].layers[0], PATH"REMME/album-back.bmp");
		wizard.pages[ALBUM_COVER].layers[0].fullscreen = true;
		layer_init         (&wizard.pages[ALBUM_COVER].layers[0]);
		
		new_layer          (&wizard.pages[ALBUM_COVER].layers[1]);
		layer_set_bitmap   (&wizard.pages[ALBUM_COVER].layers[1], PATH"REMME/album-man.bmp");
		wizard.pages[ALBUM_COVER].layers[1].fullscreen = true;
		layer_init         (&wizard.pages[ALBUM_COVER].layers[1]);
		layer_set_layer    (&wizard.pages[ALBUM_COVER].layers[1], 5);
		layer_set_animation(&wizard.pages[ALBUM_COVER].layers[1], ANIMATION_TYPE_ENABLED | ANIMATION_TYPE_ALPHA | ANIMATION_TYPE_POINT_TO_POINT, FLOAT_ONE * 5);
		
		wizard.pages[ALBUM_COVER].layers[1].source_position[0] = 0;
		wizard.pages[ALBUM_COVER].layers[1].source_position[1] = -(_UI64_MAX_MARGIN << 1);
		
		wizard.pages[ALBUM_COVER].layers[1].destination_position[0] = 0;
		wizard.pages[ALBUM_COVER].layers[1].destination_position[1] = 0;
	
	new_wizard_page        (&wizard.pages[TITLE_U2], 2, 2);
		new_layer          (&wizard.pages[TITLE_U2].layers[0]);
		layer_set_bitmap   (&wizard.pages[TITLE_U2].layers[0], PATH"REMME/album-back.bmp");
		wizard.pages[TITLE_U2].layers[0].fullscreen = true;
		layer_init         (&wizard.pages[TITLE_U2].layers[0]);
	
		new_layer          (&wizard.pages[TITLE_U2].layers[1]);
		layer_set_bitmap   (&wizard.pages[TITLE_U2].layers[1], PATH"REMME/album-frost.bmp");
		wizard.pages[TITLE_U2].layers[1].fullscreen = true;
		layer_init         (&wizard.pages[TITLE_U2].layers[1]);
		layer_set_layer    (&wizard.pages[TITLE_U2].layers[1], 5);
		layer_set_animation(&wizard.pages[TITLE_U2].layers[1], ANIMATION_TYPE_ENABLED | ANIMATION_TYPE_ALPHA, FLOAT_ONE * 3);
		
		new_text           (&wizard.pages[TITLE_U2].texts[0], biggest, "U2", theme_default(), 10);
		text_point_to_point(&wizard.pages[TITLE_U2].texts[0], FLOAT_ONE * 5, POSITION_BOTTOM, POSITION_CENTER);
		
		new_text           (&wizard.pages[TITLE_U2].texts[1], subtitle, "Under a blood red sky", theme_default(), 10);
		text_point_to_point(&wizard.pages[TITLE_U2].texts[1], FLOAT_ONE * 7, POSITION_BOTTOM, POSITION_ONE_THIRD);
	
	new_wizard_page        (&wizard.pages[ALBUM_SPECS], 3, 1);
		new_layer          (&wizard.pages[ALBUM_SPECS].layers[0]);
		layer_set_bitmap   (&wizard.pages[ALBUM_SPECS].layers[0], PATH"REMME/album-frost.bmp");
		wizard.pages[ALBUM_SPECS].layers[0].fullscreen = true;
		layer_init         (&wizard.pages[ALBUM_SPECS].layers[0]);
		
		new_text           (&wizard.pages[ALBUM_SPECS].texts[0], subtitle, "Artist: U2", theme_default(), 5);
		text_point_to_point(&wizard.pages[ALBUM_SPECS].texts[0], FLOAT_ONE * 3, POSITION_BOTTOM, POSITION_TWO_THIRDS);
		
		new_text           (&wizard.pages[ALBUM_SPECS].texts[1], subtitle, "Released in: 1983", theme_default(), 5);
		text_point_to_point(&wizard.pages[ALBUM_SPECS].texts[1], FLOAT_ONE * 2, POSITION_BOTTOM, POSITION_CENTER);
		
		new_text           (&wizard.pages[ALBUM_SPECS].texts[2], subtitle, "Genres: New Wave, Rock", theme_default(), 5);
		text_point_to_point(&wizard.pages[ALBUM_SPECS].texts[2], FLOAT_ONE, POSITION_BOTTOM, POSITION_ONE_THIRD);
	
	new_wizard_page        (&wizard.pages[SONG_TITLE], 1, 1);
		new_layer          (&wizard.pages[SONG_TITLE].layers[0]);
		layer_set_bitmap   (&wizard.pages[SONG_TITLE].layers[0], PATH"REMME/album-frost.bmp");
		wizard.pages[SONG_TITLE].layers[0].fullscreen = true;
		layer_init         (&wizard.pages[SONG_TITLE].layers[0]);
		
		new_text           (&wizard.pages[SONG_TITLE].texts[0], subtitle, "Sunday bloody sunday", theme_default(), 5);
		text_point_to_point(&wizard.pages[SONG_TITLE].texts[0], FLOAT_ONE * 3, POSITION_BOTTOM, POSITION_CENTER);
	
	new_wizard_page        (&wizard.pages[LYRICS_FULL], 0, 2);
		new_layer          (&wizard.pages[LYRICS_FULL].layers[0]);
		layer_set_bitmap   (&wizard.pages[LYRICS_FULL].layers[0], PATH"REMME/album-frost.bmp");
		wizard.pages[LYRICS_FULL].layers[0].fullscreen = true;
		layer_init         (&wizard.pages[LYRICS_FULL].layers[0]);
		
		new_layer          (&wizard.pages[LYRICS_FULL].layers[1]);
		layer_set_bitmap   (&wizard.pages[LYRICS_FULL].layers[1], PATH"REMME/lyrics.bmp");
		wizard.pages[LYRICS_FULL].layers[1].fullscreen = true;
		layer_init         (&wizard.pages[LYRICS_FULL].layers[1]);
		layer_set_layer    (&wizard.pages[LYRICS_FULL].layers[1], 5);
		layer_set_animation(&wizard.pages[LYRICS_FULL].layers[1], ANIMATION_TYPE_ENABLED | ANIMATION_TYPE_ALPHA | ANIMATION_TYPE_POINT_TO_POINT, FLOAT_ONE * 5);
		
		wizard.pages[LYRICS_FULL].layers[1].source_position[0] = 0;
		wizard.pages[LYRICS_FULL].layers[1].source_position[1] = -(_UI64_MAX_MARGIN << 1);
		
		wizard.pages[LYRICS_FULL].layers[1].destination_position[0] = 0;
		wizard.pages[LYRICS_FULL].layers[1].destination_position[1] = 0;
	
	new_wizard_page        (&wizard.pages[LYRICS_HIGHLIGHT], 0, 2);
		new_layer          (&wizard.pages[LYRICS_HIGHLIGHT].layers[0]);
		layer_set_bitmap   (&wizard.pages[LYRICS_HIGHLIGHT].layers[0], PATH"REMME/album-frost.bmp");
		wizard.pages[LYRICS_HIGHLIGHT].layers[0].fullscreen = true;
		layer_init         (&wizard.pages[LYRICS_HIGHLIGHT].layers[0]);
		
		new_layer          (&wizard.pages[LYRICS_HIGHLIGHT].layers[1]);
		layer_set_bitmap   (&wizard.pages[LYRICS_HIGHLIGHT].layers[1], PATH"REMME/highlighted.bmp");
		wizard.pages[LYRICS_HIGHLIGHT].layers[1].fullscreen = true;
		layer_init         (&wizard.pages[LYRICS_HIGHLIGHT].layers[1]);
		layer_set_layer    (&wizard.pages[LYRICS_HIGHLIGHT].layers[1], 5);
	
	new_wizard_page        (&wizard.pages[LYRICS_SELECTED], 3, 1);
		new_layer          (&wizard.pages[LYRICS_SELECTED].layers[0]);
		layer_set_bitmap   (&wizard.pages[LYRICS_SELECTED].layers[0], PATH"REMME/album-frost.bmp");
		wizard.pages[LYRICS_SELECTED].layers[0].fullscreen = true;
		layer_init         (&wizard.pages[LYRICS_SELECTED].layers[0]);
		
		new_text           (&wizard.pages[LYRICS_SELECTED].texts[0], smaller, "I can't belive the news today", theme_default(), 5);
		text_point_to_point(&wizard.pages[LYRICS_SELECTED].texts[0], FLOAT_ONE * 3, POSITION_BOTTOM, POSITION_TWO_THIRDS);
		
		new_text           (&wizard.pages[LYRICS_SELECTED].texts[1], smaller, "How long must we sing self song?", theme_default(), 5);
		text_point_to_point(&wizard.pages[LYRICS_SELECTED].texts[1], FLOAT_ONE * 2, POSITION_BOTTOM, POSITION_CENTER);
		
		new_text           (&wizard.pages[LYRICS_SELECTED].texts[2], smaller, "There's many lost, but tell me who has won", theme_default(), 5);
		text_point_to_point(&wizard.pages[LYRICS_SELECTED].texts[2], FLOAT_ONE, POSITION_BOTTOM, POSITION_ONE_THIRD);
	
	new_wizard_page     (&wizard.pages[IMAGE1], 0, 1);
		new_layer       (&wizard.pages[IMAGE1].layers[0]);
		layer_set_bitmap(&wizard.pages[IMAGE1].layers[0], PATH"REMME/newspaper.bmp");
		wizard.pages[IMAGE1].layers[0].fullscreen = true;
		layer_init      (&wizard.pages[IMAGE1].layers[0]);
	
	new_wizard_page        (&wizard.pages[FROST1], 1, 1);
		new_layer          (&wizard.pages[FROST1].layers[0]);
		layer_set_bitmap   (&wizard.pages[FROST1].layers[0], PATH"REMME/newspaper-frost.bmp");
		wizard.pages[FROST1].layers[0].fullscreen = true;
		layer_init         (&wizard.pages[FROST1].layers[0]);
		
		new_text           (&wizard.pages[FROST1].texts[0], smaller, "I can't belive the news today", theme_default(), 5);
		text_point_to_point(&wizard.pages[FROST1].texts[0], FLOAT_ONE * 3, POSITION_BOTTOM, POSITION_CENTER);
	
	new_wizard_page     (&wizard.pages[IMAGE2], 0, 1);
		new_layer       (&wizard.pages[IMAGE2].layers[0]);
		layer_set_bitmap(&wizard.pages[IMAGE2].layers[0], PATH"REMME/song.bmp");
		wizard.pages[IMAGE2].layers[0].fullscreen = true;
		layer_init      (&wizard.pages[IMAGE2].layers[0]);
	
	new_wizard_page        (&wizard.pages[FROST2], 1, 1);
		new_layer          (&wizard.pages[FROST2].layers[0]);
		layer_set_bitmap   (&wizard.pages[FROST2].layers[0], PATH"REMME/song-frost.bmp");
		wizard.pages[FROST2].layers[0].fullscreen = true;
		layer_init         (&wizard.pages[FROST2].layers[0]);
		
		new_text           (&wizard.pages[FROST2].texts[0], smaller, "How long must we sing self song?", theme_default(), 5);
		text_point_to_point(&wizard.pages[FROST2].texts[0], FLOAT_ONE * 3, POSITION_BOTTOM, POSITION_CENTER);
	
	new_wizard_page     (&wizard.pages[IMAGE3], 0, 1);
		new_layer       (&wizard.pages[IMAGE3].layers[0]);
		layer_set_bitmap(&wizard.pages[IMAGE3].layers[0], PATH"REMME/dead.bmp");
		wizard.pages[IMAGE3].layers[0].fullscreen = true;
		layer_init      (&wizard.pages[IMAGE3].layers[0]);
	
	new_wizard_page        (&wizard.pages[FROST3], 1, 1);
		new_layer          (&wizard.pages[FROST3].layers[0]);
		layer_set_bitmap   (&wizard.pages[FROST3].layers[0], PATH"REMME/dead-frost.bmp");
		wizard.pages[FROST3].layers[0].fullscreen = true;
		layer_init         (&wizard.pages[FROST3].layers[0]);
		
		new_text           (&wizard.pages[FROST3].texts[0], smaller, "There's many lost, but tell me who has won", theme_default(), 5);
		text_point_to_point(&wizard.pages[FROST3].texts[0], FLOAT_ONE * 3, POSITION_BOTTOM, POSITION_CENTER);
	
	new_wizard_page        (&wizard.pages[CREDITS], 3, 0);
		new_text           (&wizard.pages[CREDITS].texts[0], smaller, "Noé Dory", theme_default(), 5);
		text_point_to_point(&wizard.pages[CREDITS].texts[0], FLOAT_ONE * 3, POSITION_BOTTOM, POSITION_TWO_THIRDS);
		
		new_text           (&wizard.pages[CREDITS].texts[1], smaller, "Aymeric Wibo", theme_default(), 5);
		new_text           (&wizard.pages[CREDITS].texts[1], subtitle, "Aymeric Wibo", theme_default(), 5);
		//text_rainbow       (&wizard.pages[CREDITS].texts[1]);
		text_point_to_point(&wizard.pages[CREDITS].texts[1], FLOAT_ONE * 2, POSITION_BOTTOM, POSITION_CENTER);
		
		new_text           (&wizard.pages[CREDITS].texts[2], smaller, "Guillaume Wantier", theme_default(), 5);
		text_point_to_point(&wizard.pages[CREDITS].texts[2], FLOAT_ONE, POSITION_BOTTOM, POSITION_ONE_THIRD);
	
	new_wizard_page        (&wizard.pages[SOURCES], 3, 0);
		new_text           (&wizard.pages[SOURCES].texts[0], url, "wikipedia.org/wiki/1969_Nothern_Ireland_riots", theme_default(), 5);
		text_point_to_point(&wizard.pages[SOURCES].texts[0], FLOAT_ONE * 3, POSITION_BOTTOM, POSITION_TWO_THIRDS);
		
		new_text           (&wizard.pages[SOURCES].texts[1], url, "u2.com/lyrics/106", theme_default(), 5);
		text_point_to_point(&wizard.pages[SOURCES].texts[1], FLOAT_ONE * 2, POSITION_BOTTOM, POSITION_CENTER);
		
		new_text           (&wizard.pages[SOURCES].texts[2], url, "wikipedia.org/wiki/Battle_of_the_Bogside", theme_default(), 5);
		text_point_to_point(&wizard.pages[SOURCES].texts[2], FLOAT_ONE, POSITION_BOTTOM, POSITION_ONE_THIRD);
	
	bool click = false;
	bool song  = false;
	
	var fps;
	always {
		fps = video_fps();
		
		video_clear();
		wizard_draw(&wizard, fps);
		video_flip();
		
		get_events(&events);
		
		if (events.quit) {
			break;
			
		} else if (events.pointer_click_type) {
			if (click == false) {
				click =  true;
				wizard_click(&wizard);
				
			}
			
		} else {
			click = false;
			
		}
		
		if (wizard.current_page >= SUNRISE && !song) {
			song = true;
			print("PLAYING SONG ...\n");
			system("mplayer ~/Desktop/sbs.mp3 &");
			
		}
		
	}
	
	font_remove(biggest);
	font_remove(subtitle);
	
	dispose_wizard(&wizard);
	return 0;
	
}
