granasatClient: main.c
	gcc main.c -o granasatClient `pkg-config --cflags --libs gtk+-2.0`