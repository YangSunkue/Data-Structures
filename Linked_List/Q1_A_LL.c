//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{ // 구조체 정의, LinkedList라는 이름의 자료형을 사용 가능
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	// LinkedList 구조체 값 초기화
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c); // 1,2,3,0 중 하나를 c에 입력받기

		switch (c)  // 입력받은 값에 따라 함수 진행
		{
		case 1:  // 1을 입력했을 경우 정수 삽입하기
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);  // 삽입할 정수 입력받기
			j = insertSortedLL(&ll, i);  // index번호를 j에 리턴받는다
			printf("The resulting linked list is: ");
			printList(&ll);  // 현재 리스트 출력하기
			break;
		case 2:  // 2를 입력했을 경우 최근에 추가된 값과 index를 출력한다
			printf("The value %d was added at index %d\n", i, j);  // i는 값, j 는 index
			break;
		case 3:  // 3을 입력했을 경우 현재 리스트를 출력한다
			printf("The resulting sorted linked list is: ");
			printList(&ll);  // 현재 리스트 출력
			break;
		case 0:  // 0을 입력했을 경우 while문 종료
			removeAllItems(&ll);
			break;
		default:  // 1,2,3,0이 아닌 값을 입력했다면 Choice unknown 출력
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
int insertSortedLL(LinkedList *ll, int item) {
	// 1번 케이스로 정상적으로 입력받았다면, 입력받은 정수의 index 번호를 return 한다.
	// 2번 케이스는 "The value %d was added at index %d\n" 를 출력하며, 각각 추가된 값과 index이다.
	// int insertNode(LinkedList *ll, int index, int value) -1또는 0 리턴
	int result;
	ListNode *findIndex;

	for(int i = 0; i < ll->size + 1; i++) {  // 리스트 모든 값에 대해 반복, i = 인덱스
		if(i == ll->size) {  // 배열 끝까지 다 돌았을 경우 ( item이 가장 큰 값일 경우 )
			result = insertNode(ll, i, item);  // 마지막에 추가한다
			if(result == 0) {  // 성공적으로 삽입되었으면
				return i;
			}
		}
		findIndex = findNode(ll, i);
		if(findIndex->item == item) {  // 중복값일 경우
			return -1;
		}
		else if(findIndex->item > item) {  // 리스트에서 더 큰 값을 찾았을 경우 
			result = insertNode(ll, i, item);  // 해당 큰 값 자리에 item 삽입

			if(result == 0) { // 성공적으로 삽입되었으면
				return i;  // 삽입된 인덱스 반환
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////

// 리스트를 출력하는 함수
void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


// 연결리스트 메모리 할당 해제하고 다 지워버리기
void removeAllItems(LinkedList *ll) // 연결리스트 포인터를 입력받는다
{
	ListNode *cur = ll->head;  // 연결리스트 시작노드를 *cur 변수에 담는다
	ListNode *tmp;  // *tmp 포인터 변수 선언

	while (cur != NULL){  // 노드가 없을 때까지 반복한다
		tmp = cur->next;  // tmp에 다음 노드 주소를 담는다
		free(cur);  // cur 포인터가 가리키던 메모리 할당 해제
		cur = tmp;  // tmp에 담겨있던 다음 노드 주소를 할당한다
	}
	ll->head = NULL;  // 연결리스트 시작지점을 지워버린다.
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
