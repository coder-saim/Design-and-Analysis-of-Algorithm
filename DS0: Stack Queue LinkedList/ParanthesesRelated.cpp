#include <iostream>
using namespace std;
class Node
{
public:
	int data;
	Node *next;
	// Node *previous;
	Node()
	{
		data = 0;
		next = NULL;
		// previous = NULL;
	}
	Node(int data)
	{
		this->data = data;
		this->next = NULL;
		// this->previous = NULL;
	}
};
class LinkedList
{
private:
	Node *LinkedListHead;
	int LengthOfLinkedList;
	Node *ReverseRecursion(Node *current)
	{

		if (current == NULL || current->next == NULL)
			return current;
		Node *newhead = ReverseRecursion(current->next);
		current->next->next = current;
		current->next = NULL;
		return newhead;
	}
	Node *ReverseIterative(Node *current)
	{
		Node *prev = NULL, *next = NULL;
		while (current != NULL)
		{
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		return prev;
	}
	void partition(Node *head, Node **front, Node **back)
	{
		Node *fast, *slow;
		if (head == NULL || head->next == NULL)
		{
			*front = head; // &a
			*back = NULL;  //&b
		}
		else
		{
			slow = head;
			fast = head->next;

			while (fast != NULL)
			{
				fast = fast->next;
				if (fast != NULL)
				{
					slow = slow->next;
					fast = fast->next;
				}
			}
			*front = head;		// &a
			*back = slow->next; //&b
			slow->next = NULL;
		}
	}
	Node *mergeLists(Node *a, Node *b)
	{
		Node *mergedList = NULL;
		if (a == NULL)
		{
			return b;
		}
		else if (b == NULL)
		{
			return a;
		}

		if (a->data <= b->data)
		{
			mergedList = a;
			mergedList->next = mergeLists(a->next, b);
		}
		else
		{
			mergedList = b;
			mergedList->next = mergeLists(a, b->next);
		}
		return mergedList;
	}
	void mergeSort(Node **source)
	{
		Node *head = *source;
		Node *a = NULL, *b = NULL;
		if (head == NULL || head->next == NULL)
			return;

		partition(head, &a, &b);
		mergeSort(&a);
		mergeSort(&b);

		*source = mergeLists(a, b);
	}
	bool detectLoop(Node *head)
	{
		Node *slow_p = head, *fast_p = head;
		while (slow_p && fast_p && fast_p->next)
		{
			slow_p = slow_p->next;
			fast_p = fast_p->next->next;
			if (slow_p == fast_p)
				return 1;
		}
		return 0;
	}
	bool isPalindrome(Node *head)
	{
		Node *temp = head;
		string str1, str2;
		while (temp)
		{
			str1 = str1 + to_string(temp->data);
			str2 = to_string(temp->data) + str2;
			temp = temp->next;
		}

		if (str1 == str2)
			return true;

		return false;
	}
	Node *ReturnMiddle(Node *head)
	{
		// Delete middle is also easy
		Node *slow_ptr = head;
		Node *fast_ptr = head;
		// Node * store = NULL; //To delete the middle element

		if (head != NULL)
		{
			while (fast_ptr && fast_ptr->next)
			{
				fast_ptr = fast_ptr->next->next;
				slow_ptr = slow_ptr->next;
				// if(fast_ptr->next) store = slow_ptr; //To delete the middle element
			}
			// cout << "The middle element is [" << slow_ptr->data << "]" << endl; //To Print the middle element
			// store->next= slow_ptr->next;//To delete the middle element
		}
		return slow_ptr;
	}

public:
	LinkedList()
	{
		LinkedListHead = NULL;
		LengthOfLinkedList = 0;
	}
	LinkedList(Node *head)
	{
		this->LinkedListHead = head;
		Node *current = head;
		int count = 0;
		while (current != NULL)
		{
			count++;
			current = current->next;
		}
		this->LengthOfLinkedList = count;
	}
	int Length()
	{
		return this->LengthOfLinkedList;
	}
	void InsertNode(int data, int position)
	{
		Node *newNode = new Node(data);
		if (position < 0)
			printf("Invalid Position!\n");
		else if (LinkedListHead == NULL)
		{
			newNode->next = NULL;
			LinkedListHead = newNode;
		}
		else if (position == 0)
		{
			newNode->next = LinkedListHead;
			LinkedListHead = newNode;
		}
		else
		{
			Node *temp = LinkedListHead;
			for (int i = 0; i < position - 1; i++)
			{
				temp = temp->next;
				if (temp == NULL)
				{
					printf("Invalid Position!\n");
					return;
				}
			}
			newNode->next = temp->next;
			temp->next = newNode;
		}
		LengthOfLinkedList++;
	}
	void PrintList()
	{
		Node *temp = LinkedListHead;
		if (LinkedListHead == NULL)
		{
			cout << "List is empty!" << endl;
			return;
		}
		while (temp != NULL)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << "\n";
	}
	void DeleteNode(int position)
	{
		if (this->LinkedListHead == NULL)
			return;

		Node *temp = this->LinkedListHead;
		if (position == 0)
		{
			this->LinkedListHead = temp->next;
			free(temp);
			return;
		}
		for (int i = 0; temp != NULL && i < position - 1; i++)
			temp = temp->next;
		if (temp == NULL || temp->next == NULL)
			return;
		Node *next = temp->next->next;
		free(temp->next);
		temp->next = next;
	}
	Node *ReturnLinkedListHead()
	{
		return LinkedListHead;
	}
	void Reverse()
	{
		this->LinkedListHead = ReverseIterative(this->LinkedListHead);
		// this->LinkedListHead = ReverseRecursion(this->LinkedListHead);
	}
	void Sort()
	{
		mergeSort(&this->LinkedListHead);
	}
	bool IsLoopExist()
	{
		return detectLoop(this->LinkedListHead);
	}
	bool IsPalindrome()
	{
		return isPalindrome(this->LinkedListHead);
	}
	Node *ReturnMiddleElement()
	{
		return ReturnMiddle(this->LinkedListHead);
	}
};
class Stack
{
private:
	LinkedList stacklist;
	int lengthofstack;

public:
	Stack()
	{
		LinkedList stacklist = LinkedList();
		lengthofstack = 0;
	}
	void Push(int num)
	{
		stacklist.InsertNode(num, 0);
		lengthofstack++;
	}
	int Pop()
	{
		int firstelement = stacklist.ReturnLinkedListHead()->data;
		stacklist.DeleteNode(0);
		lengthofstack--;
		return firstelement;
	}
	int Top()
	{
		if (IsEmpty())
		{
			printf("Stack Is Empty!\n");
			return 0;
		}
		return stacklist.ReturnLinkedListHead()->data;
	}
	bool IsEmpty()
	{
		if (stacklist.ReturnLinkedListHead() == NULL)
			return 1;
		return 0;
	}
	void Print()
	{
		stacklist.PrintList();
	}
	int Length()
	{
		return lengthofstack;
	}
};
bool isparanthesesok(string arr)
{
	Stack Container;
	int i = 0;
	while (arr[i] != '\n' && arr[i] != '\0')
	{

		if (arr[i] == ']' && Container.Top() == '[')
			Container.Pop();
		else if (arr[i] == '}' && Container.Top() == '{')
			Container.Pop();
		else if (arr[i] == ')' && Container.Top() == '(')
			Container.Pop();
		else if (arr[i] == '(' || arr[i] == '[' || arr[i] == '{')
			Container.Push(arr[i]);

		i++;
	}
	if (Container.IsEmpty())
		return true;
	else
		return false;
}
int maxdepth(string arr)
{
	int maxdept = 0, i = 0;
	Stack Container;

	while (arr[i] != '\n' && arr[i] != '\0')
	{

		if (arr[i] == ']' && Container.Top() == '[')
		{
			if (Container.Length() > maxdept)
				maxdept = Container.Length();

			Container.Pop();
		}
		else if (arr[i] == '}' && Container.Top() == '{')
		{
			if (Container.Length() > maxdept)
				maxdept = Container.Length();

			Container.Pop();
		}
		else if (arr[i] == ')' && Container.Top() == '(')
		{
			if (Container.Length() > maxdept)
				maxdept = Container.Length();
			Container.Pop();
		}
		else if (arr[i] == '(' || arr[i] == '[' || arr[i] == '{')
			Container.Push(arr[i]);

		i++;
	}

	return maxdept;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string UserInput;
	cin >> UserInput;
    cout<<isparanthesesok(UserInput)<<endl;
	cout<<maxdepth(UserInput)<<endl;
	return 0;
}
