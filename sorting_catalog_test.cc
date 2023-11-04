#include "sorting_catalog.h"

int main()
{
	stockDB s(10);
	stock s2("APPL", 209), s3("FB", 50, 2), s4("SAMSUNG", 30, 3), s5("ASML", 40, 2);
	stock s6("LG", 20, 3), s7("NC", 5, 2), s8("NEXON", 30, 4), s9("HITACHI", 40, 5);
	Node s12("APPL", 209), s13("FB", 50, 2), s14("SAMSUNG", 30, 3), s15("ASML", 40, 2);
	Node s16("LG", 20, 3), s17("NC", 5, 2), s18("NEXON", 30, 4), s19("HITACHI", 40, 5);
	Node s20("AMAZON", 21, 3), s21("MICROSOFT", 5, 22), s22("GOOGLE", 35, 4);
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
