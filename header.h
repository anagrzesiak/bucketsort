#pragma once
class bucket {
public:
	struct node {
		int val;
		node *next;
	private:
		void add_priv(int dist, node *&link);
		void show_priv(node *root);
	public:
		void add(int dist, node *&arrlink);
		void show(node *root);
		void sort_bubble(node *&root);
	};
	bucket(int bucket_size, int sort_amount);
private:
	node **neighbours_list;
	void show(int size);
	void sort(int size);
	void ready();
};