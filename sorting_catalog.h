#ifndef SORTING_CATALOG_H
#define SORTING_CATALOG_H

#include <iostream>
#include <string>
#include <queue>

class stock {
public:
	stock() { symbol = ""; cost = 0; shares = 0; }
	stock(std::string symbol, int cost, int shares = 1);
	friend std::ostream& operator<<(std::ostream& outs, const stock& st);
	friend bool operator<(const stock& left, const stock& right);
	friend bool operator<=(const stock& left, const stock& right);
	friend stock operator+(const stock& left, const stock& right);
	friend int operator/(const stock& left, const int& right);

private:
	std::string symbol;
	int cost;
	int shares;
};

typedef struct stockNode {
	struct stockNode* next;
	std::string symbol;
	int cost;
	int shares;
	stockNode(std::string symbol, int cost, int shares = 1) : next(NULL)
	{
		this->symbol = symbol; this->cost = cost; this->shares = shares;
	}
	friend bool operator<(const struct stockNode& lobj, const struct stockNode& robj);
	friend std::ostream& operator<<(std::ostream& outs, const struct stockNode& st);
} Node;

struct stockDB {
public:
	stockDB(int stocks);
	~stockDB() { delete[] numStocks; }
	void bubbleSort();
	void selectionSort();
	void insertionSort();
	void linkedInsertionSort();
	void shellSort();
	void startQuickSort();
	void startMergeSort();
	void mergeSort();  //for linked list, function overloading
	void heapSort();
	void radixSort();
	void set(stock a);
	void setpq(stock a);
	void paste(Node* a);
	void getpq() const;
	void getList() const;
	void showDB() const;

private:
	int partition(int first, int last);
	void quickSort(int first, int last);
	void merge(int first, int mid, int last);
	void mergeSort(int first, int last);  //for array
	void divideList(Node* source, Node** first1, Node** first2);
	Node* mergeList(Node* first1, Node* first2);
	void recMergeSort(Node** headRef);
	void heapify(int low, int high);
	void buildHeap();
	stock getMax(stock arr[]);
	void countSort(stock arr[], int exp);
	std::priority_queue<stock> pq;
	Node* first, * last;
	stock* numStocks;
	int index;
	int length;
};

#endif