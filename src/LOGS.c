
struct node {
	int score;
	char name[15];
	char date[25];
	struct node *next;
	struct node *prev;
};

struct node *head;
struct node *tail;

void save_data(int score, char name[], char date[]) {
	FILE *file = fopen("logs.txt", "a");
	fprintf(file, "%s\t%-15s%d\n", date, name, score);
	fclose(file);
}
void create_head(char date[], char name[], int score) {
	head = (struct node *) malloc(sizeof(struct node));
	head->score = score;
	strcpy(head->name, name);
	strcpy(head->date, date);
	head->next = NULL;
	head->prev = NULL;
	tail = head;
}

void add_node(char date[], char name[], int score) {
	struct node *new_node = (struct node *) malloc(sizeof(struct node));
	new_node->score = score;
	strcpy(new_node->name, name);
	strcpy(new_node->date, date);	
	new_node->next = NULL;
	new_node->prev = tail;
	tail->next = new_node;
	tail = new_node;
}

void read_data() {
	FILE *file = fopen("logs.txt", "r");
	char str_name[20];
	char str_date[25];
	int score;
	fgets(str_date, 25, file);
	fgets(str_name, 15, file);
	fscanf(file, "%d\n", &score);
	create_head(str_date, str_name, score);
	while(!feof(file)) {
		fgets(str_date, 25, file);
		fgets(str_name, 15, file);
		fscanf(file, "%d\n", &score);
		add_node(str_date, str_name, score);
	}
	fclose(file);
}

void swap_logs(struct node *a, struct node *b) {
	char temp_name[15];
	strcpy(temp_name, a->name);
	strcpy(a->name, b->name);
	strcpy(b->name, temp_name);
	char temp_date[25];
	strcpy(temp_date, a->date);
	strcpy(a->date, b->date);
	strcpy(b->date, temp_date);
	int temp_score;
	temp_score = a->score;
	a->score = b->score;
	b->score = temp_score;
}


void sort_logs() {
	struct node *curr = head;
	struct node *tmp;
	for (; curr->next != NULL; curr = curr->next) {
		for (tmp = curr->next; tmp != NULL; tmp = tmp->next) {
			if (curr->score < tmp->score) {
				swap_logs(curr, tmp);
			}
		}
	}
}

void show_logs() {
	sort_logs();
	struct node *current = head;
	move(50, 150);
	printf("For Menu Press Enter");
	move(0,0);
	while (current != NULL) {
		printf("%s\t%-15s%d\n", current->date, current->name, current->score);
		current = current->next;
	}
}