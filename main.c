#include <psp2/display.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include <vita2d.h>

#define SCREEN_W 960
#define SCREEN_H 544

#define BLACK   RGBA8(  0,   0,   0, 255)
#define WHITE   RGBA8(255, 255, 255, 255)
#define RED     RGBA8(255,   0,   0, 255)
#define ORANGE  RGBA8(255, 165,   0, 255)
#define YELLOW  RGBA8(255, 255,   0, 255)
#define GREEN   RGBA8(  0, 255,   0, 255)
#define CYAN    RGBA8(  0, 255, 255, 255)
#define BLUE    RGBA8(  0,   0, 255, 255)
#define PURPLE  RGBA8(128,   0, 128, 255)

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int randomInRange (int lower, int upper) {
	return (rand() % (upper - lower + 1)) + lower; 
}

int main() {
	
	vita2d_init();
	
	vita2d_texture *logo = vita2d_load_PNG_file("app0:/icons/dvd.png");
	
	vita2d_pgf *pgf;
	
	vita2d_set_clear_color(BLACK);

	pgf = vita2d_load_default_pgf();
	
	int index = 0;
	
	int colors[] = {RGBA8(255, 64, 0, 255), RGBA8(255, 128, 0, 255), RGBA8(255, 191, 0, 255), RGBA8(255, 255, 0, 255), RGBA8(191, 255, 0, 255), RGBA8(128, 255, 0, 255), 
	RGBA8(64, 255, 0, 255), RGBA8(0, 255, 0, 255), RGBA8(0, 255, 64, 255), RGBA8(0, 255, 128, 255), RGBA8(0, 255, 191, 255), RGBA8(0, 255, 255, 255), 
	RGBA8(0, 191, 255, 255), RGBA8(0, 128, 255, 255), RGBA8(0, 64, 255, 255), RGBA8(0, 0, 255, 255), RGBA8(64, 0, 255, 255), RGBA8(128, 0, 255, 255), 
	RGBA8(191, 0, 255, 255), RGBA8(255, 0, 255, 255), RGBA8(255, 0, 191, 255), RGBA8(255, 0, 128, 255), RGBA8(255, 0, 64, 255), RGBA8(255, 0, 0, 255)};
	
	srand(time(NULL));
	
	int posX = randomInRange(1, 960 - 128);
	int posY = randomInRange(1, 544 - 96);
	
	float velocityX = 1.0f;
	float velocityY = 1.0f;
	
	int boings = 0;
	char boingsc[2]; 
	
	while(1){
		
		vita2d_start_drawing();
		vita2d_clear_screen();
		
		sprintf(boingsc, "%i", boings); 
		
		vita2d_draw_texture_tint(logo, posX, posY, colors[boings % 23]);
		vita2d_pgf_draw_text(pgf, 30, 30, WHITE, 1.0f, concat("DVD boings: ", boingsc));
		
		vita2d_end_drawing();
		vita2d_swap_buffers();
		index++;
		
		if (posX >= SCREEN_W - 128) {
			velocityX = -velocityX;
			posX = SCREEN_W - 128;
		} else if (posX <= 0) {
			velocityX = -velocityX;
			posX = 0;
		}
		
		if (posY >= SCREEN_H - 96) {
			velocityY = -velocityY;
			posY = SCREEN_H - 96;
		} else if (posY <= 0) {
			velocityY = -velocityY;
			posY = 0;
		}
		
		posX += velocityX;
		posY += velocityY;
		
		if (posX == 0 || posX == SCREEN_W - 128 || posY == 0 || posY == SCREEN_H - 96)
			boings++;
	}
	
	vita2d_free_texture(logo);
	vita2d_fini();
	vita2d_free_pgf(pgf);
	sceKernelExitProcess(0);
	return 0;
}