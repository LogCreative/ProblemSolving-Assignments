// ����һ�������Ϣ��ʹ�÷������Ƚ��̣�������Ϣ������
// ���ȼ�����ʼʱ�䡢����ʱ��Ƭ
// ����ʱ������Ϊ���������͡��������������Ҫ���ȵĽ�������಻����100����

// ���������ɵĽ���ʱ�����У���ʽ���£�P1 P2 P3 ��

#include "std_lib_facilities.h"
#include <queue>


struct program {
	int pid;
	int pri;
	int start;
	queue<long int> timespans;

	program():pid(0) {}
	program(int i, int r, long int s) :
		pid(i), pri(r), start(s) {}
	~program() = default;

    // ��������
		//���ȼ�����Խ�����ȼ�Խ�ߣ����ȼ���1 - 10֮�䣩��
		//������ж�����̾���������ȼ�������ѡ����ʱ������Ľ��̡�
		
    bool operator<(const program &right) const{
        if (start < right.start) return true;
        if (start == right.start) {
            if (pri > right.pri)
                return true;
            return false;
        }
        return false;
    }
};

#ifndef pq
#define pq

// 0 ��Ԫ�ز��棬��С����
class priorityQueue {
private:
    int currentSize;                            // ���г���
    program* array;
    int maxSize;                                // ����

    void doubleSpace() {
        program* tmp = array;
        maxSize *= 2;
        array = new program[maxSize];
        for (int i = 0; i <= currentSize; ++i)
            array[i] = tmp[i];
        delete[] tmp;
    }

    void buildHeap() {
        for (int i = currentSize / 2; i > 0; --i)
            percolateDown(i);
    }

    void percolateDown(int hole) {
        int child;
        program tmp = array[hole];

        for (; hole * 2 <= currentSize; hole = child) {
            child = hole * 2;
            if (child != currentSize && array[child + 1] < array[child])    // ��С��һ��
                ++child;
            if (array[child] < tmp)
                array[hole] = array[child];                             // ����
            else break;
        }
        array[hole] = tmp;
    }

public:

    priorityQueue(int capacity = 100) {
        array = new program[capacity];
        maxSize = capacity;
        currentSize = 0;
    }

    priorityQueue(const program item[], int size) :
        maxSize(size + 10), currentSize(size) {
        array = new program[maxSize];
        for (int i = 0; i < size; ++i)
            array[i + 1] = item[i];
        buildHeap();
    }

    ~priorityQueue() { delete[] array; }

    bool isEmpty() const { return currentSize == 0; }

    void enQueue(const program& x) {
        if (currentSize == maxSize - 1) doubleSpace();

        //���Ϲ���
        int hole = ++currentSize;
        for (; hole > 1 && x < array[hole / 2]; hole /= 2)
            array[hole] = array[hole / 2];
        array[hole] = x;
    }

    program deQueue() {
        program minItem;
        minItem = array[1];
        array[1] = array[currentSize--];
        percolateDown(1);
        return minItem;
    }

    void plus() {
        for (int i = 1; i <= currentSize; ++i)
            array[i].pri++;
        buildHeap();
    }

    program getHead() const { return array[1]; }
};


#endif // !pq


class X {
public:
    X() {}
    ~X() = default;
    void inputProgram(string s);
    void outputQueue();
private:
    //priority_queue<program,vector<program>,pcmp> pp;
    priorityQueue pp;
    program executing;
    long int clock = 0;
    //int execute();
    int oexecute();
};