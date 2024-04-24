#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "MOVER.c"
#include "HIDE_CURSOR.c"
#include "LOGS.c"

 struct menu_node {
	char str_name[20];
	struct menu_node *next;
	struct menu_node *prev;	
};

 struct menu_node *play;
 struct menu_node *record;
 struct menu_node *exit1;
 struct menu_node *ptr_selected;
 
void make_options() {
	play = (struct menu_node *)malloc(sizeof(struct menu_node));
	record = (struct menu_node *)malloc(sizeof(struct menu_node));
	exit1 = (struct menu_node *)malloc(sizeof(struct menu_node));
	ptr_selected = play;
	play->next = record;
	play->prev = exit1;
	strcpy(play->str_name, "1 - Play");
	record->prev = play;
	record->next = exit1;
	strcpy(record->str_name, "2 - Records");
	exit1->next = play;
	exit1->prev = record;
	strcpy(exit1->str_name, "3 - Exit");
}

int x_pointer = 72;
int y_pointer = 3;


void move_ptr_down() {
	move(y_pointer, x_pointer);
	printf("      ");
	move(y_pointer, x_pointer + 28);
	printf("      ");
	y_pointer += 2;
	if(y_pointer > 7) 
		y_pointer = 3;
	move(y_pointer, x_pointer);
	printf("----->");
	x_pointer = 100;
	move(y_pointer, x_pointer);
	printf("<-----");
	x_pointer = 72;
}

void move_ptr_up() {
	move(y_pointer, x_pointer);
	printf("      ");
	move(y_pointer, x_pointer + 28);
	printf("      ");
	y_pointer -= 2;
	if(y_pointer < 3) 
		y_pointer = 7;
	move(y_pointer, x_pointer);
	printf("----->");
	x_pointer = 100;
	move(y_pointer, x_pointer);
	printf("<-----");
	x_pointer = 72;
}

void back_to_normal() {
	ptr_selected = play;
	x_pointer = 72;
	y_pointer = 3;		
}

void menu() {
	int c;
	move(1,80);	
	printf("Welcome To The Game");		
	move(3, 85);
	printf("%s", play->str_name);
	move(3, 72);
	printf("----->");
	move(3,100);
	printf("<-----");
	move(5, 85);
	printf("%s", record->str_name);
	move(7, 85);
	printf("%s", exit1->str_name);
	while (c != 13) {
		c = getch();
		hidecursor();
			if (c == (int)'s') {
				ptr_selected = ptr_selected->next;
				move_ptr_down();
			}
			if (c == (int)'w') {			
				ptr_selected = ptr_selected->prev;
				move_ptr_up();
			}	
	}
}
