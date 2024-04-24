#include "MENU_LIBRARY.c"
#include "PLAY_LIBRARY.c"


int main () {
	SetConsoleTitle("Fighter Plane");
	make_options();
	InitConsole(14, 3);
	while (ptr_selected != exit1) {
		system("cls");
		back_to_normal();
		InitConsole(14, 3);	
		menu();
		if (ptr_selected == play) {
			system("cls");
			InitConsole(24, 0);
			play_game();
		}
		if (ptr_selected == record) {
			system("cls");
			InitConsole(0, 14);
			read_data();
			show_logs();
			int b;
			while(b != 13) {
				 b = getch();
			}
			b = 11;
		}	
	}
	system("cls");
	return 0;
}
