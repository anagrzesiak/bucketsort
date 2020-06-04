#include<iostream>
#include<cstdlib>
#include<ctime>
#include"header.h"
using namespace std;

int *random_arr(int arr_amount) {
	int *arr = new int[arr_amount];
	for (int i = 0; i < arr_amount; i++) {
		arr[i] = rand() % arr_amount;
	}
	return arr;
}

int *staticar(int amount) {
	static int *arr = random_arr(amount);
	return arr;
}

bucket::bucket(int bucket_size, int sort_amount) {
	int *arr = new int[sort_amount];
	//arr = random_arr(sort_amount);
	arr = staticar(sort_amount);
	int rows = sort_amount / bucket_size;
	neighbours_list = new node *[rows];
	for (int i = 0; i < rows; i++){
		neighbours_list[i] = nullptr;
	}
	for (int i = 0; i < sort_amount; i++) {
		neighbours_list[arr[i] / bucket_size]->add(arr[i], neighbours_list[arr[i] / bucket_size]);
	}
	sort(rows);
	show(rows);
	ready();
}

void bucket::node::add_priv(int dist, node *& root){
	node *a = new node;
	a->val = dist;
	a->next = root;
	root = a;
}

void bucket::node::show_priv(node *b) {
	while (b) {
		cout << b->val << "->";
		b = b->next;
	}
	cout << endl;
}

void bucket::show(int size) {
	for (int i = 0; i < size; i++)
	{
		cout << "arr[" << i << "]->";
		neighbours_list[i]->show(neighbours_list[i]);
	}
}

void bucket::sort(int size) {
	clock_t start = clock();
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < size; k++) {
				srand(time(NULL));
				neighbours_list[j]->sort_bubble(neighbours_list[j]);
			}
		}
	}
	clock_t end = clock();
	double time_spent = (double)(end - start);
	cout << "time: " << time_spent << endl;
}

void bucket::node::add(int dist, node *&arrlink) {
	add_priv(dist, arrlink);
}

void bucket::node::show(node *root) {
	show_priv(root);
}

void::bucket::node::sort_bubble(node *&root){
	node *help = root;
	int temp;
	while (help && help->next){
		node *help1 = help->next;
		while (help1){
			if (help->val > help1->val)
			{
				swap(help1->val, help->val);
			}
			help1 = help1->next;
		}
		help = help->next;
	}
}

int partition(int tablica[], int p, int r) // dzielimy tablice na dwie czesci, w pierwszej wszystkie liczby sa mniejsze badz rowne x, w drugiej wieksze lub rowne od x
{
	int x = tablica[p]; // obieramy x
	int i = p, j = r, w; // i, j - indeksy w tabeli
	while (true) // petla nieskonczona - wychodzimy z niej tylko przez return j
	{
		while (tablica[j] > x) // dopoki elementy sa wieksze od x
			j--;
		while (tablica[i] < x) // dopoki elementy sa mniejsze od x
			i++;
		if (i < j) // zamieniamy miejscami gdy i < j
		{
			w = tablica[i];
			tablica[i] = tablica[j];
			tablica[j] = w;
			i++;
			j--;
		}
		else // gdy i >= j zwracamy j jako punkt podzialu tablicy
			return j;
	}
}

void quicksort(int tablica[], int p, int r) // sortowanie szybkie
{
	int q;
	if (p < r)
	{
		q = partition(tablica, p, r); // dzielimy tablice na dwie czesci; q oznacza punkt podzialu
		quicksort(tablica, p, q); // wywolujemy rekurencyjnie quicksort dla pierwszej czesci tablicy
		quicksort(tablica, q + 1, r); // wywolujemy rekurencyjnie quicksort dla drugiej czesci tablicy
	}
}

void bucket::ready() {
	int *arr = staticar(100);
	clock_t start = clock();
	srand(time(NULL));
	int n = 100;
	quicksort(arr, 0, n);
	clock_t end = clock();
	double time_spent = (double)(end - start);
	cout << "time: " << time_spent << endl;
	cout << "Sorted array: \n";
	for (int i = 1; i < n; i++) // wypisanie posortowanej tablicy
		cout << "tablica[" << i << "] = " << arr[i] << endl;
};