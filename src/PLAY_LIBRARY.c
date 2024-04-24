int x = 40;
int y = 40;
int quit = 0;
int score = 0;
int health = 100;
int is_mine_in_window;
int is_fighter_in_window;
struct bullet {
	int bullet_x;
	int bullet_y;
	int is_in_window;
};

struct bullet bullets[30];

struct mine {
	int mine_x;
	int mine_y;
	int is_in_window;
};
struct mine mines[7];

struct bomber {
	int bomber_x;
	int bomber_y;
	int is_in_window;
	int bomber_health;
};
struct bomber bombers;

struct bomber_bomb {
	int bomb_x;
	int bomb_y;
	int is_in_window;
	int is_shot;
};
struct bomber_bomb bombs[6];		

struct fighter {
	int fighter_x;
	int fighter_y;
	int fighter_health;
	int is_in_window;
};

struct fighter fighters[6];

struct fighter_bullet {
	int f_bullet_x;
	int f_bullet_y;
	int is_in_window;
	int is_shot;
};

struct fighter_bullet fighter_bullets[24];


struct kit_plane {
	int kit_x;
	int kit_y;
	int kit_health;
	int is_in_window;
};

struct kit_plane kit;


void draw_plane() {
	move(y,x);
	printf("     /\\");
	move(y + 1, x);
	printf("    /II\\");
	move(y + 2, x);
	printf("   /\"\"\"\"\\");
	move(y + 3, x);
	printf("  /@@@@@@\\");
	move(y + 4, x);
	printf(" /********\\");
	move(y + 5, x);
	printf("/HHHHHHHHHH\\");
	move(y + 6, x);
	printf("||||||||||||");
    move(y + 7, x);
    printf("<><><><><><>");
}

void move_right() {
	move(y,x);
	printf("        ");
	move(y + 1, x);
	printf("         ");
	move(y + 2, x);
	printf("              ");
	move(y + 3, x);
	printf("           ");
	move(y + 4, x);
	printf("            ");
	move(y + 5, x);
	printf("             ");
	move(y + 6, x);
	printf("            ");
    move(y + 7, x);
    printf("            ");
    if (x < 160)
		x += 3;
}
void move_left() {
	move(y,x);
	printf("        ");
	move(y + 1, x);
	printf("         ");
	move(y + 2, x);
	printf("              ");
	move(y + 3, x);
	printf("           ");
	move(y + 4, x);
	printf("            ");
	move(y + 5, x);
	printf("             ");
	move(y + 6, x);
	printf("            ");
    move(y + 7, x);
    printf("            ");
	if (x > 7) 
		x -= 3;	
}

void update_bullet() {
	for (int i = 0; i < 30; i++) {
		if (bullets[i].is_in_window) {
			move(bullets[i].bullet_y, bullets[i].bullet_x);
			printf("   ");
			bullets[i].bullet_y--;
			if (bullets[i].bullet_y == 0) {
				bullets[i].is_in_window = 0;
			}
			else {
			move(bullets[i].bullet_y, bullets[i].bullet_x);
			printf("|||");
			}
		}			
	}
	
}

int bullet_num;

void shoot() {
    bullets[bullet_num].bullet_x = x + 5;
    bullets[bullet_num].bullet_y = y - 1;
    bullets[bullet_num].is_in_window = 1;
	bullet_num++;	
    if (bullet_num > 29) {
    	bullet_num = 0;
	}
	
}
void spawn_mine() {
	srand(time(0));
	for (int i = 0; i < 7 ; i++) {
		if (!mines[i].is_in_window) {
			mines[i].is_in_window = 1;
//			mines[i].mine_x = rand() % (150 + 1 - 10) + 10 ;
			mines[0].mine_x = rand() % (20 + 1 - 10) + 10 ;
			mines[1].mine_x = rand() % (40 + 1 - 21) + 21 ;
			mines[2].mine_x = rand() % (60 + 1 - 41) + 41 ;
			mines[3].mine_x = rand() % (80 + 1 - 61) + 61 ;
			mines[4].mine_x = rand() % (100 + 1 - 81) + 81 ;
			mines[5].mine_x = rand() % (120 + 1 - 101) + 101 ;
			mines[6].mine_x = rand() % (160 + 1 - 121) + 121 ;									
			mines[i].mine_y = 2;
		}
	}
//	mines[0].mine_x = rand() % (40 + 1 - 10) + 10 ;
//	mines[1].mine_x = rand() % (80 + 1 - 41) + 41 ;
//	mines[2].mine_x = rand() % (120 + 1 - 81) + 81 ;
//	mines[3].mine_x = rand() % (150 + 1 - 121) + 121 ;
}
	
void update_mine() {
	for (int i = 0; i < 7; i++) {
		if (mines[i].is_in_window) {
			move(mines[i].mine_y, mines[i].mine_x + 1);
			printf(" ");
			move(mines[i].mine_y + 1, mines[i].mine_x);
			printf("   ");
			move(mines[i].mine_y + 2, mines[i].mine_x + 1);
			printf(" ");
			mines[i].mine_y += 1;
			is_mine_in_window = 1;
			if (mines[i].mine_y > 45) {
				mines[i].is_in_window = 0;
				is_mine_in_window = 0;
			}
			else {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
			WORD saved_attributes;
			GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
			saved_attributes = consoleInfo.wAttributes;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);	
			move(mines[i].mine_y, mines[i].mine_x + 1);
			printf("-");
			move(mines[i].mine_y + 1, mines[i].mine_x);
			printf("|*|");
			move(mines[i].mine_y + 2, mines[i].mine_x + 1);
			printf("-");	
			SetConsoleTextAttribute(hConsole, saved_attributes);	
			}		
		}
	}
}

void mine_bullet_collision() {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 30; j++) {
			if (bullets[j].is_in_window && mines[i].is_in_window) {
				if (bullets[j].bullet_x >= mines[i].mine_x - 3 && bullets[j].bullet_x <= mines[i].mine_x + 3 && 
				     (bullets[j].bullet_y == mines[i].mine_y || bullets[j].bullet_y == mines[i].mine_y + 1 ||
					  bullets[j].bullet_y == mines[i].mine_y + 2 || bullets[j].bullet_y == mines[i].mine_y + 3)) {
				     	mines[i].is_in_window = 0;
				     	move(mines[i].mine_y, mines[i].mine_x + 1);
				     	printf(" ");
				     	move(mines[i].mine_y + 1, mines[i].mine_x);
				     	printf("   ");
				     	move(mines[i].mine_y + 2, mines[i].mine_x + 1);
				     	printf(" ");
				     	move(bullets[j].bullet_y, bullets[j].bullet_x);
				     	printf("   ");
				     	bullets[j].is_in_window = 0;
				     	score += 100;
					 }
			}
		}
	}
}

void mine_ship_collision() {
	for (int i = 0; i < 7; i++) {
		if (mines[i].is_in_window) {
			if (mines[i].mine_x >= x - 3 && mines[i].mine_x <= x + 12  && (mines[i].mine_y) >= 40) {
				health -= 100;
				mines[i].is_in_window = 0;
				move(mines[i].mine_y, mines[i].mine_x + 1);
				printf(" ");
				move(mines[i].mine_y + 1, mines[i].mine_x);
				printf("   ");
				move(mines[i].mine_y + 2, mines[i].mine_x + 1);
				printf(" ");				
			}
		}
	}
}

void spawn_bomber() {
	bombers.is_in_window = 1;
	bombers.bomber_x = 5;
	bombers.bomber_y = 5;
	bombers.bomber_health = 2;
}

void shoot_bomb() {
	for (int i = 0; i < 6; i++) {
		if (!bombs[i].is_in_window) {
			bombs[i].is_in_window = 1;	
		}
	}
	bombs[0].bomb_x = 9;
	bombs[0].bomb_y = 6;
	bombs[1].bomb_x = 41;
	bombs[1].bomb_y = 14;
	bombs[2].bomb_x = 81;
	bombs[2].bomb_y = 24;
	bombs[3].bomb_x = 101;
	bombs[3].bomb_y = 29;	
	bombs[4].bomb_x = 121;
	bombs[4].bomb_y = 34;
	bombs[5].bomb_x = 141;
	bombs[5].bomb_y = 39;			
}

void update_bomb() {
	for (int i = 0; i < 6; i++) {
		if (bombs[i].is_in_window && bombs[i].bomb_x == bombers.bomber_x && bombs[i].bomb_y == bombers.bomber_y && 
		    !bombs[i].is_shot) {
		    bombs[i].is_shot = 1;	
			bombs[i].bomb_x++;
			bombs[i].bomb_y += 2;
			move(bombs[i].bomb_y, bombs[i].bomb_x);
			printf("   ");
			bombs[i].bomb_y++;
			move(bombs[i].bomb_y, bombs[i].bomb_x);
			printf("(*)");
		}
		if (bombs[i].is_shot) {
			move(bombs[i].bomb_y, bombs[i].bomb_x);
			printf("   ");
			bombs[i].bomb_y++;
			if (bombs[i].bomb_y > 45) {
				bombs[i].is_in_window = 0;
				bombs[i].is_shot = 0;
			}
			else {
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
				WORD saved_attributes;
				GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
				saved_attributes = consoleInfo.wAttributes;
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);					
				move(bombs[i].bomb_y, bombs[i].bomb_x);
				printf("(*)");
				SetConsoleTextAttribute(hConsole, saved_attributes);
				
			}
		}
	}
}
int f_change;
void update_bomber() {
	if (bombers.is_in_window) {
		move(bombers.bomber_y, bombers.bomber_x);
		printf("                 ");
		if (!(f_change % 3)) {
			bombers.bomber_y++;
		}
		else {
			bombers.bomber_x += 2;
		}
		f_change++;
		if (bombers.bomber_y > 45 || bombers.bomber_x > 160) 
			bombers.is_in_window = 0;
		else	 {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
			WORD saved_attributes;
			GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
			saved_attributes = consoleInfo.wAttributes;
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);				
			move(bombers.bomber_y, bombers.bomber_x);
			printf("<<[ooooooooooo]>>");
			SetConsoleTextAttribute(hConsole, saved_attributes);
		}

	}
}

void bomb_ship_collision() {
	for (int i = 0; i < 6; i++) {
		if (bombs[i].is_in_window && bombs[i].is_shot && bombs[i].bomb_x >= x - 3 && bombs[i].bomb_x <= x + 12 && 
		    bombs[i].bomb_y >=40) {
		    	health -= 20;
		    	bombs[i].is_in_window = 0;
		    	bombs[i].is_shot = 0;
		    	move(bombs[i].bomb_y, bombs[i].bomb_x);
		    	printf("   ");
			}
	}
}

void bomber_ship_collision() {
	if (bombers.is_in_window) {
		if (bombers.bomber_x >= x - 12 && bombers.bomber_x <= x + 12 && bombers.bomber_y >= 40) {
			health -= 50;
			bombers.is_in_window = 0;
			move(bombers.bomber_y, bombers.bomber_x);
			printf("                 ");
		}
	}
}

void bomber_bullet_collision() {
	for (int i = 0; i < 30 ; i++) {
		if (bullets[i].is_in_window && bombers.is_in_window && bullets[i].bullet_x >= bombers.bomber_x &&
		    bullets[i].bullet_x <= bombers.bomber_x + 16 && bullets[i].bullet_y == bombers.bomber_y) {
		    	bombers.bomber_health -= 1;
		    	if (!bombers.bomber_health) {
		    		bombers.is_in_window = 0;
		    		for(int i = 0; i < 4; i++){
		    			bombs[i].is_in_window = 0;
		    			bombs[i].is_shot = 0;
		    			move(bombs[i].bomb_y, bombs[i].bomb_x);
		    			printf("   ");
		    			score += 200;
					}
		    		bullets[i].is_in_window = 0;
		    		move(bombers.bomber_y, bombers.bomber_x);
		    		printf("                 ");
		    		move(bullets[i].bullet_y, bullets[i].bullet_x);
		    		printf("   ");
				}	
			}
	}
}

void spawn_fighter() {
	srand(time(0));
	for (int i = 0; i < 6; i++) {
		if (!fighters[i].is_in_window) {
			fighters[i].is_in_window = 1;
			is_fighter_in_window = 1;
			fighters[0].fighter_x = rand() % (30 + 1 - 10) + 10;
			fighters[1].fighter_x = rand() % (60 + 1 - 36) + 36;
			fighters[2].fighter_x = rand() % (90 + 1 - 66) + 66;
			fighters[3].fighter_x = rand() % (120 + 1 - 96) + 96;
			fighters[4].fighter_x = rand() % (150 + 1 - 126) + 126;
			fighters[5].fighter_x = rand() % (170 + 1 - 156) + 156;
			fighters[i].fighter_y = 5;
			fighters[i].fighter_health = 1;
			shoot_f_bullet();
		}
	}
}

void update_fighter() {
	for (int i = 0; i < 6; i++) {
		if (fighters[i].is_in_window) {
			move(fighters[i].fighter_y, fighters[i].fighter_x + 2);
			printf("   ");
			move(fighters[i].fighter_y + 1, fighters[i].fighter_x);
			printf("       ");
			move(fighters[i].fighter_y + 2, fighters[i].fighter_x + 2);
			printf("   ");				
			fighters[i].fighter_y++;
			if (fighters[i].fighter_y > 45) {
				fighters[i].is_in_window = 0;
				is_fighter_in_window = 0;
			}
			else {
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
				WORD saved_attributes;
				GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
				saved_attributes = consoleInfo.wAttributes;
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);				
				move(fighters[i].fighter_y, fighters[i].fighter_x + 2);
				printf("]0[");
				move(fighters[i].fighter_y + 1, fighters[i].fighter_x);
				printf("<<]0[>>");
				move(fighters[i].fighter_y + 2, fighters[i].fighter_x + 2);
				printf("]0[");			
				SetConsoleTextAttribute(hConsole, saved_attributes);	
			}
		}
		
	}
}

void shoot_f_bullet() {
	srand(time(0));
	for (int j = 0; j < 6; j++) {
		for (int i = 0 ; i < 24; i++) {
			if (!fighter_bullets[i].is_in_window && fighters[j].is_in_window) {
				fighter_bullets[i].is_in_window = 1;
				if (i < 4) {
					fighter_bullets[i].f_bullet_x =  fighters[0].fighter_x;
				}
				if (i < 8 && i >= 4) {
					fighter_bullets[i].f_bullet_x =  fighters[1].fighter_x;
				}
				if (i < 12 && i >= 8) {
					fighter_bullets[i].f_bullet_x =  fighters[2].fighter_x;
				}
				if (i < 16 && i >= 12) {
					fighter_bullets[i].f_bullet_x =  fighters[3].fighter_x;
				}				
				if (i < 20 && i >= 16) {
					fighter_bullets[i].f_bullet_x =  fighters[4].fighter_x;
				}
				if (i < 24 && i >= 20) {
					fighter_bullets[i].f_bullet_x =  fighters[5].fighter_x;
				}												
				fighter_bullets[i].f_bullet_y = rand() % (35 + 1 - 6) + 6;
			}
		}		
	}
}

void update_f_bullet() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 24; j++) {
			if (fighter_bullets[j].is_in_window && fighters[i].is_in_window && fighter_bullets[j].f_bullet_x == fighters[i].fighter_x &&
			    fighter_bullets[j].f_bullet_y == fighters[i].fighter_y && !fighter_bullets[j].is_shot) {
			    fighter_bullets[j].is_shot = 1;	
				move(fighter_bullets[j].f_bullet_y, fighter_bullets[j].f_bullet_x + 2);
				printf("  ");
				fighter_bullets[j].f_bullet_y += 1;
					move(fighter_bullets[j].f_bullet_y, fighter_bullets[j].f_bullet_x + 2);
					printf("**");
			}
			if (fighter_bullets[j].is_shot) {
				move(fighter_bullets[j].f_bullet_y, fighter_bullets[j].f_bullet_x + 2);
				printf("  ");	
				fighter_bullets[j].f_bullet_y += 1;
				if (fighter_bullets[j].f_bullet_y > 45) {
					fighter_bullets[j].is_in_window = 0;
					fighter_bullets[j].is_shot = 0;
				}
				else {
					HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
					CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
					WORD saved_attributes;
					GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
					saved_attributes = consoleInfo.wAttributes;	
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED);				
					move(fighter_bullets[j].f_bullet_y, fighter_bullets[j].f_bullet_x + 2);
					printf("**");
					SetConsoleTextAttribute(hConsole, saved_attributes);
				}
			}
		}
		
	}


}

void ship_f_bullet_collision() {
	for (int i = 0; i < 24; i++) {
		if (fighter_bullets[i].is_shot) {
			if (fighter_bullets[i].f_bullet_x >= x - 1 && fighter_bullets[i].f_bullet_x <= x + 12 &&
			    fighter_bullets[i].f_bullet_y >= 40) {
			    	fighter_bullets[i].is_shot = 0;
					fighter_bullets[i].is_in_window = 0;
					health -= 10;
					move(fighter_bullets[i].f_bullet_y, fighter_bullets[i].f_bullet_x + 2);
					printf("  ");	
				}
		}
	}
}

void ship_fighter_collision() {
	for (int i = 0; i < 6; i++) {
		if (fighters[i].is_in_window) {
			if (fighters[i].fighter_x >= x - 6 && fighters[i].fighter_x <= x + 12 && fighters[i].fighter_y >= 40) {
				fighters[i].is_in_window = 0;
				health -= 40;
				move(fighters[i].fighter_y, fighters[i].fighter_x + 2);
				printf("   ");
				move(fighters[i].fighter_y + 1, fighters[i].fighter_x);
				printf("       ");
				move(fighters[i].fighter_y + 2, fighters[i].fighter_x + 2);
				printf("   ");	
			}
		}
	}
}

void fighter_bullet_collision() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 30; j++) {
			if (bullets[j].is_in_window && fighters[i].is_in_window) {
				if (bullets[j].bullet_x >= fighters[i].fighter_x - 3 && bullets[j].bullet_x <= fighters[i].fighter_x + 6 &&
				    (bullets[j].bullet_y == fighters[i].fighter_y || bullets[j].bullet_y == fighters[i].fighter_y + 1 ||
					  bullets[j].bullet_y == fighters[i].fighter_y + 2 || bullets[j].bullet_y == fighters[i].fighter_y + 3)) {
				    	score += 1000;
				    	bullets[j].is_in_window = 0;
				    	fighters[i].is_in_window = 0;
				    	move(bullets[j].bullet_y, bullets[j].bullet_x);
				    	printf("   ");
				    	for (int x = 0; x < 12; x++) {
				    		fighter_bullets[x].is_in_window = 0;
				    		fighter_bullets[x].is_shot = 0;
				    		move(fighter_bullets[x].f_bullet_y, fighter_bullets[x].f_bullet_x + 2);
				    		printf("  ");
						}
						move(fighters[i].fighter_y, fighters[i].fighter_x + 2);
						printf("   ");
						move(fighters[i].fighter_y + 1, fighters[i].fighter_x);
						printf("       ");
						move(fighters[i].fighter_y + 2, fighters[i].fighter_x + 2);
						printf("   ");	
					}
			}
		}
	}
}

void spawn_kit() {
	srand(time(0));
	kit.is_in_window = 1;
	kit.kit_health = 3;
	kit.kit_x = rand() % (150 + 1 - 50) + 50;
	kit.kit_y = 0;
}

void update_kit() {
	if (kit.is_in_window) {
		move(kit.kit_y, kit.kit_x);
		printf("     ");
		move(kit.kit_y + 1, kit.kit_x);
		printf("     ");
		move(kit.kit_y + 2, kit.kit_x);
		printf("     ");
		kit.kit_y++;
		if (kit.kit_y > 45) {
			kit.is_in_window = 0;
		}
		else {
			move(kit.kit_y, kit.kit_x);
			printf("#####");
			move(kit.kit_y + 1, kit.kit_x);
			printf("# %d #", kit.kit_health);
			move(kit.kit_y + 2, kit.kit_x);
			printf("#####");			
		}		
	}
}

void kit_ship_collision() {
	if(kit.kit_x >= x - 5 && kit.kit_x <= x + 12 && kit.kit_y >= 40 && kit.is_in_window) {
		move(kit.kit_y, kit.kit_x);
		printf("     ");
		move(kit.kit_y + 1, kit.kit_x);
		printf("     ");
		move(kit.kit_y + 2, kit.kit_x);
		printf("     ");
		health -= 30;
		kit.is_in_window = 0;
	}
}

void kit_bullet_collision() {
	for (int i = 0; i < 30; i++) {
		if (bullets[i].bullet_x >= kit.kit_x - 3 && bullets[i].bullet_x <= kit.kit_x + 5 && (bullets[i].bullet_y == kit.kit_y ||
		    bullets[i].bullet_y == kit.kit_y + 1 || bullets[i].bullet_y == kit.kit_y + 2 || bullets[i].bullet_y == kit.kit_y + 3 ) &&
			kit.is_in_window && bullets[i].is_in_window) {
				kit.kit_health -= 1;
				if (!kit.kit_health) {
					kit.is_in_window = 0;
					move(kit.kit_y, kit.kit_x);
					printf("     ");
					move(kit.kit_y + 1, kit.kit_x);
					printf("     ");
					move(kit.kit_y + 2, kit.kit_x);
					printf("     ");
					move(bullets[i].bullet_y, bullets[i].bullet_x);
					printf("   ");
					score += 100;		
				}
				else {
					move(bullets[i].bullet_y, bullets[i].bullet_x);
					printf("   ");
				}
			}
	}
}

void spawn_enemy() {
	srand(time(NULL));
	int a = rand() % (4 + 1 - 1) + 1;
	switch(a) {
		case 1 :
			if (!is_mine_in_window)
				spawn_mine();
			break;
		case 2 :
			if (!bombers.is_in_window) {
				spawn_bomber();
				shoot_bomb();
			}
			break;
		case 3 :
			if (!is_fighter_in_window) {
				spawn_fighter();
				shoot_f_bullet();
			}
			if (!is_mine_in_window)
				spawn_mine();
			break;
		case 4 :
			if (!kit.is_in_window)
				spawn_kit();
			if (!is_mine_in_window) {
				spawn_mine();
			}	 
			break;			
	}
}


void get_input() {
	if (kbhit()) {
		int c = _getch();
		switch(c) {
			case 100 :
				move_right();
				break;
			case 97 :
				move_left();
				break;	
			case 32 :
				shoot();
				break;	
		}
	}
}

void print_score() {
	move(50, 5);
	printf("Score: %d", score);
}

void print_health() {
	move(51, 5);
	printf("Health: %d", health );
	if (health < 100) {
		move(51, 15);
		printf(" ");
	}

}


int played_first;
char str_name[20];
void game_over() {
	if (health <= 0) {
		system("cls");
		quit = 1;
		move(3, 85);
		printf("Game Over!");
		Sleep(5000);
		move(5, 60);
		printf("Would You Like To Play Again? (Press y To Play Again or Press Another Key Ro Reach Menu)");
		int p_again = getch();
		if (p_again == (int)'y') {
			played_first = 1;
			system("cls");
			move(3, 70);
			printf("Enter Your Nick Name (Only 15 Chars) :");
			gets(str_name);
			time_t h;
			time(&h);
			char date[25];
			strncpy(date, ctime(&h), 24);
			date[24] = '\0';
			save_data(score, str_name, date);
			quit = 0;
			health = 100;
			x = 40;
			y = 40;
			score = 0;
			is_mine_in_window = 0;
			is_fighter_in_window = 0;
			one_more_game();
			system("cls");			
		}
	}
}

void one_more_game() {
	for (int i = 0; i < 6; i++) {
		bombs[i].is_in_window = 0;
		bombs[i].is_shot = 0;
	}
	for (int i = 0; i < 30; i++) {
		bullets[i].is_in_window = 0;
	}
	for (int i = 0; i < 6; i++) {
		fighters[i].is_in_window = 0;
	}
	bombers.is_in_window = 0;
	kit.is_in_window = 0;
	for (int i = 0; i < 7; i++) {
		mines[i].is_in_window = 0;
	}
	for (int i = 0; i < 24; i++) {
		fighter_bullets[i].is_in_window = 0;
		fighter_bullets[i].is_shot = 0;
	}
}

void play_game() {
	hidecursor();
	move (3, 75);
	printf("Press Any Key To Start");
	getch();
	system("cls");
	while(!quit) {	
		hidecursor();
		update_bullet();
		draw_plane();
		spawn_enemy();
		spawn_enemy();
		get_input();
		update_mine();
		update_kit();
		mine_bullet_collision();
		mine_ship_collision();
		bomb_ship_collision();
		bomber_ship_collision();
		bomber_bullet_collision();
		ship_f_bullet_collision();
		ship_fighter_collision();
		fighter_bullet_collision();
		kit_ship_collision();
		kit_bullet_collision();
		update_bomber();
		update_bomb();
		update_f_bullet();
		update_fighter();
		score += 1;
		print_score();
		print_health();
		game_over();
		Sleep(25);
	}
		system("cls");
		move(3, 70);
		printf("Enter Your Nick Name (Only 15 Chars) :");
		gets(str_name);
		time_t h;
		time(&h);
		char date[25];
		strncpy(date, ctime(&h), 24);
		date[24] = '\0';
		save_data(score, str_name, date);
		quit = 0;
		health = 100;
		x = 40;
		y = 40;
		score = 0;
		is_mine_in_window = 0;
		is_fighter_in_window = 0;
		one_more_game();	

}