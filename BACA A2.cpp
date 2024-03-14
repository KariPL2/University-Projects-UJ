//Karol Bargiel
#include <iostream>
class Aristocrat;
class Aristocrat {
public:
	int priority;
	std::string name;
	int number_corridor;
	int length;
	int curr_ind;
	Aristocrat() {};
	Aristocrat(int priority, std::string name, int number_corridor, int length, int curr_ind) {
		this->priority = priority;
		this->name = name;
		this->number_corridor = number_corridor;
		this->length = length;
		this->curr_ind = curr_ind;
	}

};
class Corridor {
public:
	int length;
	Aristocrat* A;
	Corridor() {};
	Corridor(int length) {
		this->length = length;
		A = new Aristocrat[length];
	}


};



class queueArray {
public:
	int maxSize;
	Aristocrat* elem;
	int Size;

	queueArray(int size) {
		maxSize = size;
		elem = new Aristocrat[maxSize];
		Size = 0;
	}

	void enQueue(Aristocrat x) {
		if (isFull()) {
			return;
		}
		else {
			elem[Size] = x;
			heapifyUp(Size);
			Size++;
		}
	}

	Aristocrat deQueue() {
		if (isEmpty()) {
			return Aristocrat();
		}

		Aristocrat tmp = elem[0];
		elem[0] = elem[Size - 1];
		Size--;
		heapifyDown(0);

		return tmp;
	}

	Aristocrat getFront() {
		if (isEmpty()) {
			return Aristocrat();
		}
		else {
			return elem[0];
		}
	}

	bool isEmpty() {
		return (Size == 0);
	}

	bool isFull() {
		return (Size == maxSize);
	}

	void heapifyUp(int index) {
		while (index > 0) {
			int parentIndex = (index - 1) / 2;
			if (compare(elem[index], elem[parentIndex])) {
				swap(elem[index], elem[parentIndex]);
				index = parentIndex;
			}
			else {
				break;
			}
		}
	}

	void heapifyDown(int index) {
		int leftChild = 2 * index + 1;
		int rightChild = 2 * index + 2;
		int smallest = index;

		if (leftChild < Size && compare(elem[leftChild], elem[smallest])) {
			smallest = leftChild;
		}
		if (rightChild < Size && compare(elem[rightChild], elem[smallest])) {
			smallest = rightChild;
		}

		if (smallest != index) {
			swap(elem[index], elem[smallest]);
			heapifyDown(smallest);
		}
	}

	bool compare(Aristocrat& a, Aristocrat& b) {
		return (a.priority < b.priority) ||
			(a.priority == b.priority && (a.length - a.curr_ind) > (b.length - b.curr_ind)) ||
			(a.priority == b.priority && (a.length - a.curr_ind) == (b.length - b.curr_ind) && a.number_corridor < b.number_corridor);
	}

	void swap(Aristocrat& a, Aristocrat& b) {
		Aristocrat temp = a;
		a = b;
		b = temp;
	}
};




int main()
{
	int M; 
	std::cin >> M;

	queueArray q = queueArray(M);
	Corridor** all_corridors = new Corridor * [M];
	int priority;
	std::string name;
	for (int i = 0; i < M; i++)
	{
		int n; 
		std::cin >> n;
		Corridor* corridor = new Corridor(n);
		all_corridors[i] = corridor;
		for (int j = 0; j < n; j++)
		{
			std::cin >> priority >> name;
			Aristocrat aristocrat(priority, name, i, n, j);
			corridor->A[j] = aristocrat;
		}

		q.enQueue(corridor->A[0]);
	}

	while (!q.isEmpty())
	{
		Aristocrat currentPerson = q.getFront();
		int currentCorridor = currentPerson.number_corridor;

		std::cout << currentPerson.name << '\n';

		q.deQueue();

		int nextIndex = currentPerson.curr_ind + 1;
		if (nextIndex < all_corridors[currentPerson.number_corridor]->length)
		{
			q.enQueue(all_corridors[currentPerson.number_corridor]->A[nextIndex]);
		}
	}

	return 0;
}