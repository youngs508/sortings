#include <iostream>
#include <string>
#include <queue>
using namespace std;

class stock {
public:
	stock() { symbol = ""; cost = 0; shares = 0;}
	stock(string symbol, int cost, int shares = 1);
	friend ostream& operator<<(ostream& outs, const stock& st);
	friend bool operator<(const stock& left, const stock& right);
	friend bool operator<=(const stock& left, const stock& right);
	friend stock operator+(const stock& left, const stock& right);
	friend int operator/(const stock& left, const int& right);

private:
	string symbol;
	int cost;
	int shares;
};

stock::stock(string symbol, int cost, int shares)
{
	this->symbol = symbol;
	this->cost = cost;
	this->shares = shares;
}

ostream& operator<<(ostream& outs, const stock& st)
{
	outs << st.shares << " x " << st.symbol << " @" << st.cost << endl;
	return outs;
}

bool operator<(const stock& left, const stock& right)
{
	return (left.cost * left.shares < right.cost * right.shares);
}

bool operator<=(const stock& left, const stock& right)
{
	return (left.cost * left.shares <= right.cost * right.shares);
}

stock operator+(const stock& left, const stock& right)
{
	stock temp;
	temp.cost = left.cost * left.shares + right.cost * right.shares;
	temp.shares = left.shares + right.shares;
	temp.symbol = left.symbol + right.symbol;
	return temp;
}

int operator/(const stock& left, const int& right)
{
	return left.cost * left.shares / right;
}

struct stockNode {
	stockNode* next;
	string symbol;
	int cost;
	int shares;
	stockNode(string symbol, int cost, int shares=1) : next(NULL) 
	{
		this->symbol = symbol; this->cost = cost; this->shares = shares;
	}
	friend bool operator<(const stockNode& lobj, const stockNode& robj);
	friend ostream& operator<<(ostream& outs, const stockNode& st);
};

bool operator<(const stockNode& lobj, const stockNode& robj)
{
	return (lobj.cost * lobj.shares < robj.cost * robj.shares);
}

ostream& operator<<(ostream& outs, const stockNode& st)
{
	outs << st.shares << " x " << st.symbol << " @" << st.cost << endl;
	return outs;
}

struct stockDB {
public:
	stockDB(int stocks);
	~stockDB() { delete[] numStocks; }
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
	void paste(stockNode* a);
	stock get(int i) const;
	void getpq() const;
	void getList() const;
	void showDB() const;
	
private:
	int partition(int first, int last);
	void quickSort(int first, int last);
	void merge(int first, int mid, int last);
	void mergeSort(int first, int last);  //for array
	void divideList(stockNode* source, stockNode** first1, stockNode** first2);
	stockNode* mergeList(stockNode* first1, stockNode* first2);
	void recMergeSort(stockNode** headRef);
	void heapify(int low, int high);
	void buildHeap();
	stock getMax(stock arr[]);
	void countSort(stock arr[], int exp);
	priority_queue<stock> pq;
	stockNode *first, *last;
	stock *numStocks;
	int index;
	int length;
};

void stockDB::paste(stockNode* a)
{
	if (first == NULL)
	{
		first = a;
	}
	else
	{
		a->next = first;
		first = a;
	}
}

void stockDB::linkedInsertionSort()
{
	cout << "insertion sort by linked list" << endl;
	stockNode* lastInOrder;
	stockNode* firstOutOfOrder;
	stockNode* current;
	stockNode* trailCurrent;

	lastInOrder = first;

	if (first == NULL)
		cerr << "Cannot sort an empty list." << endl;
	else if (first->next == NULL)
		cout << "The list is of length 1. "
		     << "It is already in order." << endl;
	else
		while (lastInOrder->next != NULL)
		{
			firstOutOfOrder = lastInOrder->next;
			if (*firstOutOfOrder < *first)
			{
				lastInOrder->next = firstOutOfOrder->next;
				firstOutOfOrder->next = first;
				first = firstOutOfOrder;
			}
			else
			{
				trailCurrent = first;
				current = first->next;

				while (*current < *firstOutOfOrder)
				{
					trailCurrent = current;
					current = current->next;
				}
				if (current != firstOutOfOrder)
				{
					lastInOrder->next = firstOutOfOrder->next;
					firstOutOfOrder->next = current;
					trailCurrent->next = firstOutOfOrder;
				}
				else
					lastInOrder = lastInOrder->next;
			}
		}
}

void stockDB::set(stock a)
{
	numStocks[++index] = a;
	length++;
}

void stockDB::setpq(stock a)
{
	pq.push(a);
}

stock stockDB::get(int i) const
{
	return numStocks[i];
}

void stockDB::getpq() const
{
	priority_queue<stock> g = pq;
	cout << "Priority Queue: " << endl;
	while (!g.empty())
	{
		cout << g.top();
		g.pop();
	}
}

void stockDB::getList() const
{
	stockNode* temp = first;
	while (temp != NULL)
	{
		cout << temp->symbol << " " << temp->cost << " " << temp->shares << endl;
		temp = temp->next;
	}
}

stockDB::stockDB(int stocks)
{
	numStocks = new stock[stocks];
	index = -1;
	first = NULL;
	last = NULL;
	length = 0;
	pq = {};
}

void swap(stock& a, stock& b)
{
	stock temp;
	temp = a;
	a = b;
	b = temp;
}

void stockDB::selectionSort()
{
	cout << "selection sort" << endl;
	int minIndex;
	for (int loc = 0; loc < length - 1; loc++)
	{
		minIndex = loc;
		for (int i = loc + 1; i < length; i++)
		{
			if (numStocks[i] < numStocks[minIndex])
				minIndex = i;
		}
		swap(numStocks[loc], numStocks[minIndex]);
	}
}

void stockDB::insertionSort()
{
	cout << "insertion sort" << endl;
	int location;
	for (int i = 1; i < length; i++)
	{
		if (numStocks[i] < numStocks[i - 1])
		{
			stock temp = numStocks[i];
			location = i;
			do {
				numStocks[location] = numStocks[location - 1];
				location--;
			} while (location > 0 && temp < numStocks[location - 1]);
			numStocks[location] = temp;
		}
	}
}

void stockDB::shellSort()
{
	cout << "shell sort" << endl;
	for (int gap = length / 2; gap > 0; gap /= 2)
	{
		int location;
		for (int i = gap; i < length; i++)
		{
			if (numStocks[i] < numStocks[i - gap])
			{
				stock temp = numStocks[i];
				location = i;
				do {
					numStocks[location] = numStocks[location - gap];
					location = location - gap;
				} while (location >= gap && temp < numStocks[location-gap]);
				numStocks[location] = temp;
			}
		}
	}
}

int stockDB::partition(int first, int last)
{
	stock pivot;
	swap(numStocks[first], numStocks[(first + last) / 2]);
	pivot = numStocks[first];
	int smallIndex = first;
	int currentIndex = first + 1;
	
	while (currentIndex <= last)
	{
		if (numStocks[currentIndex] < pivot)
		{
			smallIndex++;
			swap(numStocks[smallIndex], numStocks[currentIndex]);
		}
		currentIndex++;
	}
	swap(numStocks[smallIndex], numStocks[first]);
	return smallIndex;
}

void stockDB::quickSort(int first, int last)
{
	if (first < last)
	{
		int pivotLocation = partition(first, last);
		quickSort(first, pivotLocation - 1);
		quickSort(pivotLocation + 1, last);
	}
}

void stockDB::startQuickSort()
{
	cout << "quick sort" << endl;
	quickSort(0, length - 1);
}

void stockDB::merge(int first, int mid, int last)
{
	int leftSize = mid - first + 1;
	int rightSize = last - mid;

	stock *leftArray = new stock[leftSize];
	stock *rightArray = new stock[rightSize];

	for (int i = 0; i < leftSize; i++)
		leftArray[i] = numStocks[first+i];
	for (int j = 0; j < rightSize; j++)
		rightArray[j] = numStocks[mid+1+j];

	int indexLeft = 0, indexRight = 0;
	int indexMergedArray = first;

	while (indexLeft < leftSize && indexRight < rightSize)
	{
		if (leftArray[indexLeft] <= rightArray[indexRight])
		{
			numStocks[indexMergedArray] = leftArray[indexLeft];
			indexLeft++;
		}
		else
		{
			numStocks[indexMergedArray] = rightArray[indexRight];
			indexRight++;
		}
		indexMergedArray++;
	}

	
	while (indexRight < rightSize)
	{
		numStocks[indexMergedArray] = rightArray[indexRight];
		indexRight++;
		indexMergedArray++;
	}
	
	while (indexLeft < leftSize)
	{
		numStocks[indexMergedArray] = leftArray[indexLeft];
		indexLeft++;
		indexMergedArray++;
	}
	
	delete[] leftArray;
	delete[] rightArray;
}

void stockDB::mergeSort(int first, int last)
{
	if (first >= last)
		return;
	
	int mid = (first + last) / 2;
	mergeSort(first, mid);
	mergeSort(mid + 1, last);
	merge(first, mid, last);
}

void stockDB::startMergeSort()
{
	cout << "merge sort by array" << endl;
	mergeSort(0, length - 1);
}

void stockDB::divideList(stockNode* source, stockNode** first1, stockNode** first2)
{
	stockNode* slow;
	stockNode* fast;
	slow = source;
	fast = source->next;

	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	*first1 = source;
	*first2 = slow->next;
	slow->next = NULL;
}

stockNode* stockDB::mergeList(stockNode* first1, stockNode* first2)
{
	stockNode* lastSmall;
	stockNode* newHead = NULL;
	if (first1 == NULL)
		return first2;
	else if (first2 == NULL)
		return first1;
	
	if (*first1 < *first2)
	{
		newHead = first1;
		first1 = first1->next;
		lastSmall = newHead;
	}
	else
	{
		newHead = first2;
		first2 = first2->next;
		lastSmall = newHead;
	}
	while (first1 != NULL && first2 != NULL)
	{
		if (*first1 < *first2)
		{
			lastSmall->next = first1;
			lastSmall = lastSmall->next;
			first1 = first1->next;
		}
		else
		{
			lastSmall->next = first2;
			lastSmall = lastSmall->next;
			first2 = first2->next;
		}
	}

	if (first1 == NULL)
		lastSmall->next = first2;
	else
		lastSmall->next = first1;
		
	return newHead;
}

void stockDB::recMergeSort(stockNode** headRef)
{
	stockNode* head = *headRef;
	stockNode* firstHead, *secondHead;
	if ((head == NULL) || (head->next == NULL)) {
		return;
	}
	divideList(head, &firstHead, &secondHead);
	recMergeSort(&firstHead);
	recMergeSort(&secondHead);
	*headRef = mergeList(firstHead, secondHead);
}

void stockDB::mergeSort()
{
	cout << "merge sort by linked list" << endl;
	recMergeSort(&first);
	if (first == NULL)
		last = NULL;
	else
	{
		last = first;
		while (last->next != NULL)
		{
			last = last->next;
		}
	}
}

void stockDB::heapify(int low, int high)
{
	int largeIndex;
	stock temp = numStocks[low];
	largeIndex = 2 * low + 1;
	while (largeIndex <= high)
	{
		if (largeIndex < high)
			if (numStocks[largeIndex] < numStocks[largeIndex + 1])
				largeIndex = largeIndex + 1;
		if (numStocks[largeIndex] < temp)
			break;
		else
		{
			numStocks[low] = numStocks[largeIndex];
			low = largeIndex;
			largeIndex = 2 * low + 1;
		}
	}
	numStocks[low] = temp;
}

void stockDB::buildHeap()
{
	for (int index = length / 2 - 1; index >= 0; index--)
		heapify(index, length - 1);
}

void stockDB::heapSort()
{
	cout << "heapsort" << endl;
	stock temp;
	buildHeap();
	for (int lastOutOfOrder = length - 1; lastOutOfOrder >= 0; lastOutOfOrder--)
	{
		temp = numStocks[lastOutOfOrder];
		numStocks[lastOutOfOrder] = numStocks[0];
		numStocks[0] = temp;
		heapify(0, lastOutOfOrder-1);
	}
}

stock stockDB::getMax(stock arr[])
{
	stock mx = arr[0];
	for (int i = 1; i < length; i++)
		if (mx < arr[i])
			mx = arr[i];
	return mx;
}

void stockDB::countSort(stock arr[], int exp)
{
	stock *output = new stock[length];
	int i, count[10] = { 0 };

	for (i = 0; i < length; i++)
		count[(arr[i] / exp) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = length - 1; i >= 0; i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	for (i = 0; i < length; i++)
		arr[i] = output[i];
	delete[] output;
}

void stockDB::radixSort()
{
	cout << "radix soft" << endl;
	stock m = getMax(numStocks);
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(numStocks, exp);
}

void stockDB::showDB() const
{
	for (int i = 0; i < length; i++)
		cout << get(i) << endl;
}

int main()
{
	stockDB s(10);
	stock s2("APPL",209), s3("FB",50,2), s4("SAMSUNG", 30,3), s5("ASML", 40,2);
	stock s6("LG", 20, 3), s7("NC", 5, 2), s8("NEXON", 30, 4), s9("HITACHI", 40, 5);
	stockNode s12("APPL", 209), s13("FB", 50, 2), s14("SAMSUNG", 30, 3), s15("ASML", 40, 2);
	stockNode s16("LG", 20, 3), s17("NC", 5, 2), s18("NEXON", 30, 4), s19("HITACHI", 40, 5);
	stockNode s20("AMAZON", 21, 3), s21("MICROSOFT", 5, 22), s22("GOOGLE", 35, 4);
	s.set(s2);
	s.set(s3);
	s.set(s4);
	s.set(s5);
	s.set(s6);
	s.set(s7);
	s.set(s8);
	s.set(s9);
	//stockDB a = s;
	//cout << s2 + s3;
	//a.selectionSort();
	//s.insertionSort();
	//s.startQuickSort();
	s.startMergeSort();
	//s.radixSort();
	//s.shellSort();
	//s.mergeSort(0, 7);
	//s.heapSort();
	s.showDB();
	s.setpq(s2);
	s.setpq(s3);
	s.setpq(s4);
	s.setpq(s5);
	s.setpq(s6);
	s.setpq(s7);
	s.setpq(s8);
	s.setpq(s9);
	s.getpq();
	
	s.paste(&s12);
	s.paste(&s13);
	s.paste(&s14);
	s.paste(&s15);
	s.paste(&s16);
	s.paste(&s17);
	s.paste(&s18);
	s.paste(&s19);
	s.paste(&s20);
	s.paste(&s21);
	s.paste(&s22);
	//s.mergeSort();
	s.linkedInsertionSort();
	s.getList();
	
	return 0;
}