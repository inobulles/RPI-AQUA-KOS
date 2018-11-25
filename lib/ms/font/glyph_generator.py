
# -*- coding: utf-8 -*-

import time
import pygame
import sys

pygame.init()
pygame.font.init()

font_name = "windows_command_prompt.ttf"
size = 16
width = 8

font_ttf = pygame.font.Font(font_name, size)
base = 32

font_surface = None

def terminate():
	pygame.quit()
	sys.exit()

_chr = base
result = "void ms_get_glyph(ms_glyph_t* self, var code) {"

while 1:
	font_surface = font_ttf.render(chr(_chr), False, (0, 0, 0))
	window = pygame.display.set_mode((width, font_surface.get_size()[1]))
	
	window.fill((255, 255, 255))
	window.blit(font_surface, (0, 0))
	pygame.display.flip()
	
	values = []
	
	for y in xrange(size):
		for x in xrange(width):
			try: values.append(255 - font_surface.get_at((x, y))[1])
			except IndexError: values.append(0)
	
	a = 0
	b = 0
	
	i = 0
	
	for v in values:
		if v > 127:
			if i < 63: a |= 1 << i
			else: b |= 1 << i % 64
		
		i += 1
	
	result = "%s\n\tif (code == %d) { self->halves[0] = %d; self->halves[1] = %d; return; }" % (result, _chr, a, b)
	
	_chr += 1
	time.sleep(0.05)
	
	if _chr >= 127:
		break
	
	for event in pygame.event.get():
		if event.type == pygame.KEYDOWN:
			if event.key == ord('q'):
				terminate()

result = result + "\n\t\n}"
print result
terminate()
