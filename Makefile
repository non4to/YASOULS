yasouls: src/main.c
	gcc src/main.c src/player/player.c src/player/playerStates.c -o yasouls -lraylib -lGL -lm -lpthread -ldl -lrt -lX11