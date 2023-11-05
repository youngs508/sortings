#include "sorting_catalog.h"
using namespace std;

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

bool operator<(const Node& lobj, const Node& robj)
{
	return (lobj.cost * lobj.shares < robj.cost * robj.shares);
}

ostream& operator<<(ostream& outs, const Node& st)
{
	outs << st.shares << " x " << st.symbol << " @" << st.cost << endl;
	return outs;
}

void stockDB::paste(Node* a)
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
	Node* lastInOrder;
	Node* firstOutOfOrder;
	Node* current;
	Node* trailCurrent;

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

void stockDB::getpq() const
{
	priority_queue<stock> g = pq;
	cout << "Priority Queue " << endl;
	while (!g.empty())
	{
		cout << g.top() << endl;
		g.pop();
	}
}

void stockDB::getList() const
{
	Node* temp = first;
	while (temp != NULL)
	{
		cout << *temp << endl;
		temp = temp->next;
	}
}

void stockDB::showDB() const
{
	for (int i = 0; i < length; i++)
		cout << numStocks[i] << endl;
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

void stockDB::bubbleSort()
{
	cout << "bubble sort" << endl;
	int i, j;
	for (i = 0; i < length - 1; i++)
	{
		for (j = 0; j < length - i - 1; j++)
		{
			if (numStocks[j+1] < numStocks[j])
				swap(numStocks[j+1], numStocks[j]);
		}
	}
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
				} while (location >= gap && temp < numStocks[location - gap]);
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

	stock* leftArray = new stock[leftSize];
	stock* rightArray = new stock[rightSize];

	for (int i = 0; i < leftSize; i++)
		leftArray[i] = numStocks[first + i];
	for (int j = 0; j < rightSize; j++)
		rightArray[j] = numStocks[mid + 1 + j];

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

void stockDB::divideList(Node* source, Node** first1, Node** first2)
{
	Node* slow;
	Node* fast;
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

Node* stockDB::mergeList(Node* first1, Node* first2)
{
	Node* lastSmall;
	Node* newHead = NULL;
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

void stockDB::recMergeSort(Node** headRef)
{
	Node* head = *headRef;
	Node* firstHead, * secondHead;
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
		heapify(0, lastOutOfOrder - 1);
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
	stock* output = new stock[length];
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

