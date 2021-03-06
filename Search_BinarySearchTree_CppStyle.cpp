//
//	OS Windows
//	2019.03.09
//
//	[탐색 알고리즘]
//		<1. 이진 탐색>
//		<2. 보간 탐색 (Interpolation Search)>
//		<3. 이진 탐색 트리>
//			1) 이진 트리에 데이터 저장 규칙을 더한 것이 이진 탐색 트리.
//			2) 이진 탐색 트리의 조건
//				a) 노드에 저장된 key는 유일하다.
//				b) 루트노드의 key가 왼쪽 서브트리 모든 노드의 key보다 크다. (부모노드의 key가 왼쪽 자식노드의 key보다 크다)
//				c) 루트노드의 key가 오른쪽 서브트리 모든 노드의 key보다 작다. (부모노드의 key가 오른쪽 자식노드의 key보다 작다)
//				d) 왼쪽과 오른쪽 서브트리도 이진 탐색 트리이다.
//			3) 이진 탐색 트리의 삭제
//				a) 삭제에 대한 경우의 수
//					1) 삭제할 노드가 단말노드인 경우
//						step 1) 그냥 제거
//					2) 삭제할 노드가 하나의 서브트리를 가진 경우
//						- 삭제할 노드를 삭제하고, 삭제할 노드의 부모노드와 삭제할 노드의 자식노드를 연결
//						step 1) 삭제할 노드의 부모노드와의 연결을 삭제할 노드의 자식노드로 교체하면 됨
//					3) 삭제할 노드가 두 개의 서브트리를 가진 경우
//						step 1) 삭제할 노드를 대체할 노드를 찾음
//							- 삭제할 노드의 왼쪽 서브트리에서 제일 큰 값 / 오른쪽서브트리에서 제일 작은 값을 넣을 수 있음
//						step 2) 대체할 노드에 '저장된 값'을 삭제할 노드에 대입함
//						step 3) 대체할 노드의 부모노드와 자식노드를 연결
//

/////////////Binary Tree////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;

template <typename T>
class BinaryTree;

typedef void VisitFuncPtr(int data);

template <typename T>
class Node
{
	friend class BinaryTree<T>;
public:
	T data;
	int check;
	BinaryTree<T> *left;
	BinaryTree<T> *right;
public:
	Node(T data, BinaryTree<T>* left = NULL, BinaryTree<T>* right = NULL)
	{
		this->data = data;
		check = 1;
		this->left = left;
		this->right = right;
	}
	~Node()
	{
		delete left;
		delete right;
	}
};

template <typename T>
class BinaryTree
{
	friend class Node<T>;
public:
	Node<T> *BTnode;
public:
	BinaryTree(T data = 0)
	{
		BTnode = new Node<T>(data);
	}
	~BinaryTree()
	{
		delete BTnode;
	}
	void SetData(T data)
	{
		BTnode->data = data;
	}
	T GetData()
	{
		if (BTnode != NULL)
			return BTnode->data;
		else
		{
			cout << "Node is empty" << endl << endl;
			return -1;
		}
	}
	BinaryTree<T>* GetCurSubTree()
	{
		return BTnode;
	}
	BinaryTree<T>* GetLeftSubTree()
	{
		return BTnode->left;
	}
	BinaryTree<T>* GetRightSubTree()
	{
		return BTnode->right;
	}
	void MakeLeftSubTree(BinaryTree<T>* bt)
	{
		if (BTnode != NULL)
		{
			if (BTnode->left != NULL)
			{
				delete BTnode->left;
				BTnode->left = NULL;
			}
			BTnode->left = bt;
		}
		else
		{
			cout << "root node is empty" << endl << endl;
			exit(-1);
		}
	}
	void MakeRightSubTree(BinaryTree<T>* bt)
	{
		if (BTnode != NULL)
		{
			if (BTnode->right != NULL)
			{
				delete BTnode->right;
				BTnode->right = NULL;
			}
			BTnode->right = bt;
		}
		else
		{
			cout << "root node is empty" << endl << endl;
			exit(-1);
		}
	}

	void InorderTraverse(BinaryTree<T> *bt, VisitFuncPtr action)
	{
		BinaryTree<T> *temp = new BinaryTree<T>();
		temp = bt;

		if (temp == NULL)
		{
			return;
		}
		else
		{
			InorderTraverse(temp->BTnode->left, action);
			action(temp->BTnode->data);
			InorderTraverse(temp->BTnode->right, action);
		}
	}
	void DeleteTree(BinaryTree<T> *bt)
	{
		if (bt == NULL)
		{
			return;
		}
		else
		{
			DeleteTree(bt->BTnode->left);
			DeleteTree(bt->BTnode->right);
			cout << "Delete " << bt->BTnode->data << endl;
			delete bt;
			bt = NULL;
		}
	}
/////////////Binary Tree////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////Binary Search Tree/////////////////////////////////////////////////////////////////////////////////////////////
	T BSTGetNodeData();
	void BSTInsert(BinaryTree<T> **pRoot, T data);
	BinaryTree<T>* BSTSearch(BinaryTree<T> *bst, T target);
	void BSTShowAll(BinaryTree<T> *bst);
/////////////Binary Search Tree/////////////////////////////////////////////////////////////////////////////////////////////

/////////////Delete/////////////////////////////////////////////////////////////////////////////////////////////////////////
	BinaryTree<T>* RemoveLeftSubTree();
	BinaryTree<T>* RemoveRightSubTree();
	void ChangeLeftSubTree(BinaryTree<T>* main, BinaryTree<T>* sub);
	void ChangeRightSubTree(BinaryTree<T>* main, BinaryTree<T>* sub);

	BinaryTree<T>* BSTRemove(BinaryTree<T> **pRoot, T target);
/////////////Delete/////////////////////////////////////////////////////////////////////////////////////////////////////////
};

/////////////Binary Search Tree/////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
T BinaryTree<T>::BSTGetNodeData()
{
	return BTnode->data;
}
template <typename T>
void BinaryTree<T>::BSTInsert(BinaryTree<T> **pRoot, T data)
{
	BinaryTree<T> *parentNode = new BinaryTree<T>();
	BinaryTree<T> *currentNode = new BinaryTree<T>();
	currentNode = *pRoot;
	BinaryTree<T> *newNode = new BinaryTree<T>();

	while (currentNode != NULL)
	{
		if (currentNode->BTnode->data == data)
			return;

		parentNode = currentNode;

		if (currentNode->BTnode->data > data)
			currentNode = currentNode->GetLeftSubTree();
		else if (currentNode->BTnode->data < data)
			currentNode = currentNode->GetRightSubTree();
	}

	newNode->SetData(data);

	if (parentNode != NULL)
	{
		if (data < parentNode->GetData())
			parentNode->MakeLeftSubTree(newNode);
		else
			parentNode->MakeRightSubTree(newNode);
	}
	else
		*pRoot = newNode;
}
template <typename T>
BinaryTree<T>* BinaryTree<T>::BSTSearch(BinaryTree<T> *bst, T target)
{
	BinaryTree<T> *currentNode = new BinaryTree<T>();
	currentNode = bst;
	T cur_data;

	while (currentNode != NULL)
	{
		cur_data = currentNode->GetData();

		if (cur_data == target)
			return currentNode;
		else if (cur_data > target)
			currentNode = currentNode->GetLeftSubTree();
		else
			currentNode = currentNode->GetRightSubTree();
	}
	return NULL;
}
void ShowIntData(int data)
{
	cout << data << ' ';
}

template <typename T>
void BinaryTree<T>::BSTShowAll(BinaryTree<T> *bst)
{
	InorderTraverse(bst, ShowIntData);
}
/////////////Binary Search Tree/////////////////////////////////////////////////////////////////////////////////////////////

/////////////Delete/////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
BinaryTree<T>* BinaryTree<T>::RemoveLeftSubTree()
{
	BinaryTree<T> *delNode = new BinaryTree<T>();
	if (BTnode != NULL)
	{
		delNode = BTnode->left;
		BTnode->left = NULL;
	}
	return delNode;
}
template <typename T>
BinaryTree<T>* BinaryTree<T>::RemoveRightSubTree()
{
	BinaryTree<T> *delNode = new BinaryTree<T>();
	if (BTnode != NULL)
	{
		delNode = BTnode->right;
		BTnode->right = NULL;
	}
	return delNode;
}
template <typename T>
void BinaryTree<T>::ChangeLeftSubTree(BinaryTree<T>* main, BinaryTree<T>* sub)
{
	main->BTnode->left = sub;
}
template <typename T>
void BinaryTree<T>::ChangeRightSubTree(BinaryTree<T>* main, BinaryTree<T>* sub)
{
	main->BTnode->right = sub;
}
template <typename T>
BinaryTree<T>* BinaryTree<T>::BSTRemove(BinaryTree<T> **pRoot, T target)
{
	BinaryTree<T> *VirtualRootNode = new BinaryTree<T>();		//삭제 대상이 루트 노드인 경우를 고려하여 가상루트노드 변수 생성
	BinaryTree<T> *parentNode = new BinaryTree<T>();
	parentNode = VirtualRootNode;
	BinaryTree<T> *currentNode = new BinaryTree<T>();
	currentNode = *pRoot;
	BinaryTree<T> *delNode = new BinaryTree<T>();

	VirtualRootNode->ChangeRightSubTree(VirtualRootNode, *pRoot);

	//Search target
	while (currentNode != NULL && currentNode->GetData() != target)
	{
		parentNode = currentNode;
		
		if (currentNode->GetData() > target)
			currentNode = currentNode->BTnode->left;
		else
			currentNode = currentNode->BTnode->right;
	}
	if (currentNode == NULL)
		return NULL;

	delNode = currentNode;

	//Case 1) 삭제할 노드가 단말노드인 경우
	if (delNode->BTnode->left == NULL && delNode->BTnode->right == NULL)
	{
		if (parentNode->BTnode->left == delNode)
			parentNode->RemoveLeftSubTree();
		else
			parentNode->RemoveRightSubTree();
	}

	//Case 2) 삭제할 노드가 하나의 자식노드를 갖는 경우
	else if (delNode->BTnode->left == NULL || delNode->BTnode->right == NULL)
	{
		BinaryTree<T> *childNode = new BinaryTree<T>();

		if (delNode->BTnode->left != NULL)
			childNode = delNode->BTnode->left;
		else
			childNode = delNode->BTnode->right;

		if (parentNode->BTnode->left == delNode)
			parentNode->ChangeLeftSubTree(parentNode, childNode);
		else
			parentNode->ChangeRightSubTree(parentNode, childNode);
	}

	//Case 3) 삭제할 노드가 두 개의 자식노드를 갖는 경우
	else
	{
		BinaryTree<T> *replaceNode = new BinaryTree<T>();
		replaceNode = delNode->BTnode->right;
		BinaryTree<T> *replaceParentNode = new BinaryTree<T>();
		replaceParentNode = delNode;

		int delData;

		//삭제할 노드의 대체 노드 검색
		while (replaceNode->BTnode->left != NULL)
		{
			replaceParentNode = replaceNode;
			replaceNode = replaceNode->BTnode->left;
		}

		//대체할 노드에 저장된 값을 삭제할 노드에 대입
		delData = delNode->GetData();
		delNode->SetData(replaceNode->GetData());

		//대체할 노드의 부모노드와 자식노드를 연결
		if (replaceParentNode->BTnode->left == replaceNode)
			replaceParentNode->ChangeLeftSubTree(replaceParentNode, replaceNode->BTnode->right);
		else
			replaceParentNode->ChangeRightSubTree(replaceParentNode, replaceNode->BTnode->right);

		delNode = replaceNode;
		delNode->SetData(delData);
	}

	//삭제된 노드가 루트노드인 경우
	if (VirtualRootNode->BTnode->right != *pRoot)
		*pRoot = VirtualRootNode->BTnode->right;

	//delete VirtualRootNode;
	//VirtualRootNode = NULL;
	return delNode;
}
/////////////Delete/////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
	BinaryTree<int> *bstRoot = new BinaryTree<int>();
	BinaryTree<int> *searchNode = new BinaryTree<int>();
	BinaryTree<int> *deleteNode = new BinaryTree<int>();

	bstRoot->BSTInsert(&bstRoot, 7);
	bstRoot->BSTInsert(&bstRoot, 1);
	bstRoot->BSTInsert(&bstRoot, 9);
	bstRoot->BSTInsert(&bstRoot, 4);
	bstRoot->BSTInsert(&bstRoot, 5);
	bstRoot->BSTInsert(&bstRoot, 8);
	bstRoot->BSTInsert(&bstRoot, 2);
	bstRoot->BSTInsert(&bstRoot, 3);
	bstRoot->BSTInsert(&bstRoot, 6);

	cout << "Current Binary Tree : ";
	bstRoot->BSTShowAll(bstRoot);
	cout << endl<<endl;

	cout << "Search 1" << endl;
	searchNode = bstRoot->BSTSearch(bstRoot, 1);
	if (searchNode == NULL)
		cout << "Fail" << endl << endl;
	else
		cout << "Key : " << searchNode->BSTGetNodeData() << endl << endl;

	cout << "Search 2" << endl;
	searchNode = bstRoot->BSTSearch(bstRoot, 2);
	if (searchNode == NULL)
		cout << "Fail" << endl << endl;
	else
		cout << "Key : " << searchNode->BSTGetNodeData() << endl << endl;

	cout << "Search 3" << endl;
	searchNode = bstRoot->BSTSearch(bstRoot, 3);
	if (searchNode == NULL)
		cout << "Fail" << endl << endl;
	else
		cout << "Key : " << searchNode->BSTGetNodeData() << endl << endl;

	cout << "Search 4" << endl;
	searchNode = bstRoot->BSTSearch(bstRoot, 4);
	if (searchNode == NULL)
		cout << "Fail" << endl << endl;
	else
		cout << "Key : " << searchNode->BSTGetNodeData() << endl << endl;

	cout << "Search 10" << endl;
	searchNode = bstRoot->BSTSearch(bstRoot, 10);
	if (searchNode == NULL)
		cout << "Fail" << endl << endl;
	else
		cout << "Key : " << searchNode->BSTGetNodeData() << endl << endl;

	cout << "Delete 3" << endl;
	deleteNode = bstRoot->BSTRemove(&bstRoot, 3);
	cout << "Deleted : " << deleteNode->BSTGetNodeData() << endl;
	cout << "Current Binary Tree : ";
	bstRoot->BSTShowAll(bstRoot);
	cout << endl << endl;

	return 0;
}