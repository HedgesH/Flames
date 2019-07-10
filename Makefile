flames: flames.c graphics.c
	clang -std=c11 -pedantic -g flames.c graphics.c  -lSDL2 -o flames \
	 -fsanitize=undefined -fsanitize=address