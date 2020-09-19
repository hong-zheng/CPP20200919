/*
#include "SORT.h"
void display(int arr[], int len){
	for (int i = 0; i < len; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}
void swap(int arr[], int start, int min){
	int tmp = arr[start];
	arr[start] = arr[min];
	arr[min] = tmp;
}

// 三数取中
// 三数取中--> 找到三个数中的中间数
// 其最重要的目的就是防止序排序数组的有序情况，其时间复杂度为O(n^2)
// 在三个数中去中值极大的避免了这种已有序情况
int getMid(int* arr, int begin, int end){
	int mid = begin + (end - begin) / 2;
	// 先与中间值mid比较
	if (arr[begin] < arr[mid]){
		if (arr[mid] < arr[end]){
			return mid;
		}
		else{ // mid >= end && mid > begin
			if (arr[begin] > arr[end]){
				return begin;
			}
			else{
				return end;
			}
		}
	}
	else{ // begin <= mid
		if (arr[mid] < arr[end]){
			return mid;
		}
		else{ // mid >= end && begin<=mid
			if (arr[begin] > arr[end])
				return end;
			else
				return begin;
		}
	}
}

/*
	时间复杂度：
		满二叉树均衡划分 划分层次 logn
		时间复杂度 O(nlogn)
		最坏：数据有序的情况可能会崩掉，内存栈溢出，由于递归层数过多
			数据有序：划分：每次只能产生一个待划分的区间
					此时快速排序退化为冒泡排序：递归算法的递归深度太大，容易导致栈溢出
						调用栈太多，只有压栈，没有出栈，栈压满
			O(n^2)
			因此快排需要优化
				三数取中法
		平均情况 O(nlogn)
	空间复杂度：
		空间就是变量的个数
			栈的空间  函数调用栈 O(logn) ， 极端情况下就是O(n)
	稳定性：
		不稳定
		2 2 2 1：此时如果以第一个2作为基准值，则会发生变化，由于基准值需要发生变化，所以不稳定
	数据敏感与否：
			数据敏感

	·解决划分不均衡问题 
		  几个数中去取中间值作为基准值
		  begin mid end : 三数取中解决不均衡问题
		  三数取中法：可以把最坏的情况-->均衡划分


	·小区间优化 ，当划分在一定数据量时
		做正常的排序
		减少底层递归的调用次数，提高性能
*/
int getmid(int* arr, int begin, int end){
	int mid = begin + (end - begin) / 2;
	// begin , mid , end 选择中间值的位置
	if (arr[begin] < arr[mid]){
		// begin < mid
		if (arr[mid] < arr[end]){
			return mid;
		}
		else{
			// begin < mid , end <= mid
			if (arr[begin] > arr[end]){
				return begin;
			}
			else{
				return end;
			}
		}
	}
	else{ // begin >= mid
		if (arr[mid] > arr[end]){
			return mid;
		}
		else{
			// begin >= mid , end >= mid
			if (arr[begin] <= arr[end]){
				return begin;
			}
			else{
				return end;
			}
		}
	}
}
int partion(int* arr, int l, int h){
	int mid = getmid(arr, l, h);
	swap(arr, l, mid);
	//int mid = l;
	int cur = arr[l];
	while (l < h){
		while (l < h && arr[h] > cur)
			h--;
		arr[l] = arr[h];
		while (l < h && arr[l] <= cur)
			l++;
		arr[h] = arr[l];
	}
	arr[l] = cur;
	return l;
}
void QSORT(int* arr, int l, int h){
	if (l < h){
		int m = partion(arr, l, h);
		QSORT(arr, l, m - 1);
		QSORT(arr, m + 1, h);
	}
}
void QUICKSORT(int* arr, int len){
	QSORT( arr, 0, len - 1);
}


void test(){
	srand((unsigned long)time(NULL));
	int num = 10;
	int* arr = (int*)malloc(sizeof(int) * num);
	for (int i = 0; i < num; i++){
		arr[i] = rand();
	}
	display(arr, num);
	QUICKSORT(arr, num);
	display(arr, num);
}

typedef int Type;
typedef struct Node{
	Type _data;
	struct Node* _next;
}Node;

// 栈的实现

// 单链表: pushFront popFront
// 顺序表: pushBack popBack  优先选择 栈的实现基本上都是顺序表实现
//#pragma once
// 顺序表实现栈
typedef struct Stack{
	Type* _array;
	size_t _size;
	size_t _capacity;
}Stack;
void stackInit(Stack* st, size_t n){
	st->_capacity = n;
	st->_array = (Type*)malloc(sizeof(Type)*st->_capacity);
	st->_size = 0;
}

void stackPush(Stack* st, Type data){
	// 检查容量
	if (st->_size == st->_capacity){
		st->_capacity *= 2;
		st->_array = (Type*)realloc(st->_array, sizeof(Type)*st->_capacity);
	}
	st->_array[st->_size++] = data;
}
void stackPop(Stack* st){
	// 尾删
	if (NULL == st){
		return;
	}
	if (st->_size){
		st->_size--;
	}
}

Type stackTop(Stack* st){
	return st->_array[st->_size - 1];
}
size_t stackSize(Stack* st){
	return st->_size;
}
int stackEmpty(Stack* st){
	if (st->_size == 0){
		return 1;
	}
	return 0;
}


void stackDestory(Stack* st){
	free(st->_array);
	st->_array = NULL;
	st->_size = st->_capacity = 0;
}
// 快排非递归算法
// 划分区间，先大区间后小区间
// 用栈实现非递归
// 先划分左边子区间，再划分右边子区间
		// 因此入栈时先右后左
// 区间入栈，每次获取栈顶区间，进行划分
// 划分之后的小区间继续入栈
// 直到栈为空结束
void quickAortNoR(int* arr, int n){
	Stack st;
	stackInit(&st,10);
	// 起始区间入栈
	if (n > 1){
	// 先入右再入左
		stackPush(&st, n - 1);
		stackPush(&st, 0);
	}
	// 遍历栈，划分栈中的每一个区间
	while (stackEmpty(&st) != 1){
		// 获取栈顶区间
		int begin = stackTop(&st);
		stackPop(&st);
		int end = stackTop(&st);
		stackPop(&st);

		// 划分
		int keyPos = partion(arr, begin, end);
		// 子区间入栈，为了保持入栈顺序一致，先入右区间，再入左区间
		//右边的子区间 keyPos+1 ， end
		if (keyPos + 1 < end){  // 至少有两个值
			stackPush(&st, end);
			stackPush(&st, keyPos + 1);
		}
		// 左，begin , keyPos-1
		if (begin < keyPos - 1){
			stackPush(&st, keyPos - 1);
			stackPush(&st, begin);
		}
	}
}

void testNoR(){
	srand((unsigned long)time(NULL));
	int num = 10;
	int* arr = (int*)malloc(sizeof(int) * num);
	for (int i = 0; i < num; i++){
		arr[i] = rand();
	}
	display(arr, num);
	quickAortNoR(arr, num);
	display(arr, num);
}


typedef int	QDataType;
typedef struct QNode{
	struct QNode* _next;
	QDataType _data;
}QNode;
typedef struct Queue{
	QNode* _front;
	QNode* _rear;
	int _size;
}Queue;
QNode* createNode(QDataType data){

	// 创建一个结点，将该结点赋予data值，同时下一个元素指向NULL
	QNode* node = (QNode*)malloc(sizeof(QNode));
	node->_data = data;
	node->_next = NULL;
	return node;
}
void queueInit(Queue* q){
	// 初始化空队列
	// 空队列中并无元素，因此前后都指向空
	q->_front = q->_rear = NULL;
	q->_size = 0;
}
// 队尾入队，考虑空队列
void queuePush(Queue* q, QDataType data){
	// 尾插操作
	QNode* node = createNode(data);
	if (q->_front == NULL){
		// 考虑当前队列为空队列的情况，使首位都等于node
		q->_front = q->_rear = node;
	}
	else{
		q->_rear->_next = node;
		q->_rear = node;
	}
	q->_size++;
}
// 队头出队，出队需要释放，需要考虑只有一个结点的情况
void queuePop(Queue* q){
	/*	if (q->_front == NULL){
	return NULL;
	}else*/
	if (q->_front){
		// 记录下头的下一个结点
		QNode* next = q->_front->_next;
		// 释放头结点
		free(q->_front);
		//q->_front = NULL;
		q->_front = next;

		// 队列中只有一个元素，删除之后更新尾指针
		if (q->_front == NULL)
			q->_rear = NULL;
		q->_size--;
	}
}
// 获取队头元素
QDataType queueFront(Queue* q){
	return q->_front->_data;
}
// 获取队尾元素
QDataType queueBack(Queue* q){
	return  q->_rear->_data;
}
int queueSize(Queue* q){
	//int cnt = 0;
	//QNode* cur = q->_front;
	//while (cur){
	//	cnt++;
	//	cur = cur->_next;
	//}
	//return cnt;
	// 增加一个变量之后
	return q->_size;
}
int queueEmpty(Queue* q){
	if (q->_front == NULL)
		return 1;
	return 0;
}
void queueDestory(Queue* q){
	//QNode* prev = q->_front;
	QNode* cur = q->_front;
	while (cur){
		QNode* next = cur->_next;
		free(cur);
		cur = next;
	}
	q->_front = q->_rear = NULL;
	q->_size = 0;
}
// 用队列实现快速排序
void QuickSortQueue(int* arr, int len){
	Queue q;
	queueInit(&q);
	if (len > 1){
		queuePush(&q, 0);
		queuePush(&q, len - 1);
	}
	while (queueEmpty(&q) != 1){
		int begin = queueFront(&q);
		queuePop(&q);
		int end = queueFront(&q);
		queuePop(&q);
		int keyPos = partion(arr, begin, end);
		if (begin < keyPos - 1){
			queuePush(&q, begin);
			queuePush(&q, keyPos - 1);
		}
		if (keyPos + 1 < end){
			queuePush(&q, keyPos+1);
			queuePush(&q, end);
		}
	}
}
void testNoRQueue(){
	srand((unsigned long)time(NULL));
	int num = 10;
	int* arr = (int*)malloc(sizeof(int) * num);
	for (int i = 0; i < num; i++){
		arr[i] = rand();
	}
	display(arr, num);
	QuickSortQueue(arr, num);
	display(arr, num);
}

// 队列实现非递归
void QuickSortQueue2(int* arr, int n){
	Queue q;
	queueInit(&q);
	if (n > 1){
	// 先左后右
		queuePush(&q, 0);
		queuePush(&q, n - 1);
	}
	// 判断队列是否为空
	while (queueEmpty(&q) != 1){
		// 获取队头区间
		int begin = queueFront(&q);
		queuePop(&q);
		int end = queueFront(&q);
		queuePop(&q);
		// 划分
		int keyPos = partion(arr, begin, end);
		// 划分完之后子区间入队
		if (begin < keyPos - 1){
			queuePush(&q,begin);
			queuePush(&q, keyPos - 1);
		}
		if (keyPos + 1 < end){
			queuePush(&q, keyPos + 1);
			queuePush(&q, end);
		}
	}

}
int main(void){
	testNoRQueue();
	system("pause");
	return 0;
}
*/