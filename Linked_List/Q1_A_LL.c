//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next; // 다음 노드를 가르키는 포인터
} ListNode;					// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head; // 첫 번째 노드를 가르키는 포인터
} LinkedList;		// You should not change the definition of LinkedList

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
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

	// Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
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

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
	/* add your code here */
	ListNode *newNode, *cur, *prev;

	// 1. 새로운 노드 생성 및 초기화

	newNode = malloc(sizeof(ListNode));
	// 새로운 노드를 생성하고 메모리를 할당
	// 메모리 할당 실패 시 -1 반환
	if (newNode == NULL)
		return -1;

	// 새로운 노드에 값을 저장하고, 다음 노드를 가리키는 포인터를 초기화
	newNode->item = item;
	newNode->next = NULL;

	// 2. 리스트의 헤드가 비어 있거나 첫 번째 항목보다 작은 경우 처리

	// 리스트가 비어 있거나, 삽입하려는 항목이 리스트의 첫 번째 항목보다 작거나 같은 경우:
	if (ll->head == NULL || ll->head->item >= item)
	{
		// 새로운 노드의 next 포인터는 이전의 헤드를 가리킴
		newNode->next = ll->head;
		// 새로운 노드를 리스트의 헤드로 설정함
		ll->head = newNode;
	}
	else
	{

		// 3. 리스트 중간이나 끝에 삽입할 위치 찾기
		cur = ll->head; //////
		// 현재 노드(cur)와 이전 노드(prev)를 사용하여 삽입할 위치를 찾기
		// 리스트를 처음부터 순회하면서 현재 노드의 값이 삽입할 항목보다 작으면 계속 이동
		while (cur != NULL && cur->item < item)
		{
			prev = cur;
			// 현재 노드가 삽입할 항목보다 크거나 같아지면 순회를 멈춤
			cur = cur->next;
		}
		// 4. 새로운 노드 삽입
		// 새로운 노드를 중간이나 끝에 삽입
		newNode->next = cur;
		prev->next = newNode;

		// 5. 리스트 크기 업데이트 및 삽입된 위치 반환

		// 리스트의 크기를 증가시킵니다.
		ll->size++;

		// 삽입된 위치의 인덱스를 반환
		cur = ll->head;
		int index = 0;
		while (cur != newNode)
		{
			cur = cur->next;
			index++;
		}
		return index;
	}
}

///////////////////////////////////////////////////////////////////////////////////

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
