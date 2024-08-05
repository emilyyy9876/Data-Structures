//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 6 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode; // You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList; // You should not change the definition of LinkedList

//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
int moveMaxToFront(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i, j;
	c = 1;

	LinkedList ll;
	// Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move the largest stored value to the front of the list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveMaxToFront(&(ll.head)); // You need to code this function
			printf("The resulting linked list after moving largest stored value to the front of the list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////

int moveMaxToFront(ListNode **ptrHead)
{
	/*
	1. 함수 시작: moveMaxToFront 함수 시작.
	2. 리스트가 비어있는지 확인: ptrHead가 NULL이거나 리스트가 비어있는지 확인합니다.
	3. 최대값 노드와 이전 노드를 찾기 위한 초기화: maxNode와 prevMaxNode를 초기화합니다.
	4. 현재 노드와 이전 노드를 설정: current와 prev를 초기화합니다.
	5. 리스트를 순회하며 최대값 노드 찾기:
		1. 각 노드의 값을 최대값과 비교: 현재 노드의 값이 최대값보다 큰지 확인합니다.
		2. 최대값 노드 업데이트:
			1. 최대값 노드를 업데이트합니다.
			2. 최대값 이전 노드를 업데이트합니다.
		3. 다음 노드로 이동:
			1. prev를 현재 노드로 업데이트합니다.
			2. current를 다음 노드로 업데이트합니다.
	6. 최대값 노드가 이미 헤드인지 확인:
		1. 최대값 노드가 이미 헤드인 경우 아무 작업도 하지 않습니다.
		2. 최대값 노드가 헤드가 아닌 경우:
			1. 이전 노드의 next를 최대값 노드의 next로 설정합니다.
			2. 최대값 노드의 next를 현재 헤드로 설정합니다.
			3. 헤드를 최대값 노드로 업데이트합니다.
	7. 함수 종료: 최대값을 반환합니다.
	*/

	// 1. 함수 시작
	if (ptrHead == NULL || *ptrHead == NULL)
		return -1; // 2. 리스트가 비어있는지 확인

	ListNode *maxNode = *ptrHead; // 3. 최대값 노드와 이전 노드를 찾기 위한 초기화
	ListNode *prevMaxNode = NULL;

	ListNode *current = *ptrHead; // 4. 현재 노드와 이전 노드를 설정
	ListNode *prev = NULL;

	// 5. 리스트를 순회하며 최대값 노드 찾기
	while (current != NULL)
	{
		if (current->item > maxNode->item)
		{					   // 5.1. 각 노드의 값을 최대값과 비교
			maxNode = current; // 5.2. 최대값 노드 업데이트
			prevMaxNode = prev;
		}
		prev = current; // 5.3. 다음 노드로 이동
		current = current->next;
	}

	if (maxNode == *ptrHead)
		return maxNode->item; // 6. 최대값 노드가 이미 헤드인지 확인

	// 6.2. 최대값 노드가 헤드가 아닌 경우
	if (prevMaxNode != NULL)
	{
		prevMaxNode->next = maxNode->next; // 6.2.1. 이전 노드의 next를 최대값 노드의 next로 설정
	}
	maxNode->next = *ptrHead; // 6.2.2. 최대값 노드의 next를 현재 헤드로 설정
	*ptrHead = maxNode;		  // 6.2.3. 헤드를 최대값 노드로 업데이트

	return maxNode->item; // 7. 함수 종료: 최대값을 반환합니다.
}
//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll)
{

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

ListNode *findNode(LinkedList *ll, int index)
{

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0)
	{
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value)
{

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0)
	{
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}

int removeNode(LinkedList *ll, int index)
{

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0)
	{
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{

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

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}
