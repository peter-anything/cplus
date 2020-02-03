#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define M 3 //The minimum degree of this B+ tree
#define KeyNumMax 2*M-1//Maximum Key Number
#define KeyNumMin M-1//Minimum Key Number


//
typedef int KeyType;
typedef struct Node* Position;
typedef struct rNode* Search_Insert_Position_Result;
typedef struct List_Node* Path_List;
//data struct
typedef struct Node {
	bool IsLeaf;
	int KeyNum;
	KeyType Key[KeyNumMax];
	Position PtrChild[KeyNumMax];
	Position Next_Leaf_Node;
}Node;
typedef struct rNode {
	Position Insert_Position;
	int Key_Position;
}rNode;
typedef struct List_Node {
	Path_List Pre_List_Node;
	Path_List Next_List_Node;
	Position Path_List_Tree_Node;
	int The_Ith_Child_of_Parent;
}List_Node;

//global variable
Position ROOT;
Path_List Path_List_Header;
Path_List Path_List_Tail;
//Make Node
Position Make_New_Node()
{
	Position New_Node = (Position)malloc(sizeof(Node));
	New_Node->IsLeaf = false;
	New_Node->KeyNum = 0;
	New_Node->Next_Leaf_Node = NULL;
	return New_Node;
}

//Search the Leaf Node to Insert
Search_Insert_Position_Result BPT_Search(Position Current_Node, KeyType Key, int Index)
{
	int i = 0;
	Path_List Path_List_Node = (Path_List)malloc(sizeof(List_Node));

	Path_List_Node->Path_List_Tree_Node = Current_Node;

	Path_List_Tail->Pre_List_Node->Next_List_Node = Path_List_Node;
	Path_List_Node->Pre_List_Node = Path_List_Tail->Pre_List_Node;
	Path_List_Node->Next_List_Node = Path_List_Tail;
	Path_List_Tail->Pre_List_Node = Path_List_Node;
	Path_List_Node->The_Ith_Child_of_Parent = Index;
	//printf("%d\n",Path_List_Tail->Pre_List_Node->Path_List_Tree_Node->KeyNum);
	//if(Path_List_Tail->Pre_List_Node->Pre_List_Node==Path_List_Header)
	//	puts("here");

	Search_Insert_Position_Result Insert_Node_Position = (Search_Insert_Position_Result)malloc(sizeof(rNode));
	if (Current_Node->IsLeaf == true)
	{
		while (Key > Current_Node->Key[i] && i < Current_Node->KeyNum)
			i++;
		Insert_Node_Position->Insert_Position = Current_Node;
		Insert_Node_Position->Key_Position = i;
		return Insert_Node_Position;
	}
	else
	{
		while (i<Current_Node->KeyNum && Key>Current_Node->Key[i])
		{
			i++;
		}
		if (i == Current_Node->KeyNum)
			i--;
		Search_Insert_Position_Result Insert_Position_1 = BPT_Search(Current_Node->PtrChild[i], Key, i);
		return Insert_Position_1;
	}
}

//function of Node Splict,case 1:leaf node;   case 2:internal node;
Position BplusTree_Node_Split(Position Current_Node)
{
	int i = 0;
	Position New_Node = Make_New_Node();
	New_Node->IsLeaf = Current_Node->IsLeaf;
	if (Current_Node->IsLeaf == true) {
		New_Node->Next_Leaf_Node = Current_Node->Next_Leaf_Node;
		Current_Node->Next_Leaf_Node = New_Node;
		for (i = 0; i < M - 1; i++)
			New_Node->Key[i] = Current_Node->Key[i + M];
		Current_Node->KeyNum = M;
		New_Node->KeyNum = M - 1;
	}
	else {
		for (i = 0; i < M - 1; i++)
		{
			New_Node->Key[i] = Current_Node->Key[i + M];
			New_Node->PtrChild[i] = Current_Node->PtrChild[i + M];
		}
		Current_Node->KeyNum = M;
		New_Node->KeyNum = M - 1;
	}
	return New_Node;
}

//Insert Non_Full leaf node
int BplusTree_Node_Insert_Non_Full(Position Current_Node, KeyType Key)
{
	int i = 0;
	int Index_Old = Current_Node->Key[Current_Node->KeyNum - 1];

	while (i<Current_Node->KeyNum && Key>Current_Node->Key[i])
	{
		i++;
	}
	if (i == Current_Node->KeyNum) {
		Current_Node->Key[Current_Node->KeyNum] = Key;
	}
	else {
		int j;
		for (j = Current_Node->KeyNum; j > i; j--)
			Current_Node->Key[j] = Current_Node->Key[j - 1];
		Current_Node->Key[i] = Key;
	}
	Current_Node->KeyNum++;
	return Index_Old;

}
//Insert internal node
void BplusTree_Internal_Node_Insert(Position Current_Node, KeyType Key, Path_List N)
{
	int i = 0;
	int j = 0;
	int k = 0;
	//////////////////////////////////////
	if (Current_Node->KeyNum == KeyNumMax) {
		Position New_Node = BplusTree_Node_Split(Current_Node);
		while (i<M && Key>Current_Node->Key[i])
			i++;
		if (i == M) {
			while (k<New_Node->KeyNum && Key>New_Node->Key[k])
				k++;
			for (j = M - 1; j > k; j--) {
				New_Node->Key[j] = New_Node->Key[j - 1];
				New_Node->PtrChild[j] = New_Node->PtrChild[j - 1];
			}///////////////////////////////////////////////////////////////////////////////////
			New_Node->Key[k] = Key;
			New_Node->PtrChild[k] = N->Next_List_Node->Path_List_Tree_Node;
			New_Node->KeyNum++;
			N->Pre_List_Node->Path_List_Tree_Node->PtrChild[N->The_Ith_Child_of_Parent] = New_Node;
			if (k == M - 1) {
				Path_List New_N = Path_List_Header->Next_List_Node;
				while (New_N->Path_List_Tree_Node != Current_Node) {/////////////////////////////////////////////
					for (k = 0; k < New_N->Path_List_Tree_Node->KeyNum; k++)
					{
						if (New_N->Path_List_Tree_Node->Key[k] == New_Node->Key[M - 2])
							New_N->Path_List_Tree_Node->Key[k] = Key;
					}
					New_N = New_N->Next_List_Node;
				}
			}
			//printf("%d%d\n",N->Pre_List_Node->Path_List_Tree_Node->Key[0],N->Pre_List_Node->Path_List_Tree_Node->Key[1]);
			//BplusTree_Internal_Node_Insert(N->Pre_List_Node->Path_List_Tree_Node,Current_Node->Key[M-1],N->Pre_List_Node);

		}
		else {
			for (j = M; j > i; j--) {
				Current_Node->Key[j] = Current_Node->Key[j - 1];
				Current_Node->PtrChild[j] = Current_Node->PtrChild[j - 1];
			}
			Current_Node->Key[i] = Key;
			Current_Node->PtrChild[i] = N->Next_List_Node->Path_List_Tree_Node;
			Current_Node->KeyNum++;
			N->Pre_List_Node->Path_List_Tree_Node->PtrChild[N->The_Ith_Child_of_Parent] = New_Node;
			//if(N->Pre_List_Node->Path_List_Tree_Node==ROOT){
				//New_Node//////////////////////////////////////////////////////////
			//}
			//BplusTree_Internal_Node_Insert(N->Pre_List_Node->Path_List_Tree_Node,Current_Node->Key[M],N->Pre_List_Node);
		}
	}
	else {
		//printf("%d\n",Key);
		while (i<Current_Node->KeyNum && Key>Current_Node->Key[i])
			i++;
		//printf("%d\n",i);
		//printf("%d\n",Current_Node->PtrChild[0]->KeyNum);
		for (j = Current_Node->KeyNum; j > i; j--) {
			Current_Node->Key[j] = Current_Node->Key[j - 1];
			Current_Node->PtrChild[j] = Current_Node->PtrChild[j - 1];
		}
		//printf("%d\n",Current_Node->Key[1]);
		Current_Node->Key[i] = Key;
		Current_Node->PtrChild[i] = N->Next_List_Node->Path_List_Tree_Node;
		Current_Node->KeyNum++;
	}
}


//Insert leaf node
Position Bplus_Tree_Insert(Position P, KeyType Key)
{
	Path_List_Header->Pre_List_Node = Path_List_Tail;
	Path_List_Header->Next_List_Node = Path_List_Tail;
	Path_List_Tail->Pre_List_Node = Path_List_Header;
	Path_List_Tail->Next_List_Node = Path_List_Header;

	int i = 0;
	if (P == NULL)
	{
		P = Make_New_Node();
		P->Key[0] = Key;
		P->KeyNum = 1;
		P->IsLeaf = true;
		return P;
	}
	int Index_Old;
	Path_List N;
	Search_Insert_Position_Result Insert_Node_Position = BPT_Search(P, Key, 0);
	Position Current_Node = Insert_Node_Position->Insert_Position;
	//printf("%d\n",Current_Node->Key[0]);
	if (Current_Node->KeyNum == KeyNumMax)
	{
		Position New_Node = BplusTree_Node_Split(Current_Node);
		if (Path_List_Tail->Pre_List_Node->Pre_List_Node != Path_List_Header)
			Path_List_Tail->Pre_List_Node->Pre_List_Node->Path_List_Tree_Node->PtrChild[Path_List_Tail->Pre_List_Node->The_Ith_Child_of_Parent] = New_Node;

		if (Insert_Node_Position->Key_Position > M) {
			Index_Old = BplusTree_Node_Insert_Non_Full(New_Node, Key);
			if (Current_Node == ROOT) {
				Position New_Root = Make_New_Node();
				New_Root->Key[0] = Index_Old > Key ? Index_Old : Key;
				New_Root->PtrChild[0] = New_Node;
				New_Root->KeyNum++;
				P = New_Root;
			}
			else if (Index_Old < Key) {
				N = Path_List_Header->Next_List_Node;
				while (N->Path_List_Tree_Node->IsLeaf != true) {
					for (i = 0; i < N->Path_List_Tree_Node->KeyNum; i++)
					{
						if (N->Path_List_Tree_Node->Key[i] == Index_Old)
							N->Path_List_Tree_Node->Key[i] = Key;
					}
					N = N->Next_List_Node;
				}
			}
			N = Path_List_Tail->Pre_List_Node->Pre_List_Node;
			if (N == Path_List_Header)
				BplusTree_Internal_Node_Insert(P, Current_Node->Key[M - 1], N);
			else {
				while (N->Path_List_Tree_Node->KeyNum == KeyNumMax && N->Path_List_Tree_Node != P)
				{

					//BplusTree_Internal_Node_Insert(N->Path_List_Tree_Node,Current_Node->Key[M-1],N);///////////
					BplusTree_Internal_Node_Insert(N->Path_List_Tree_Node, N->Next_List_Node->Path_List_Tree_Node->Key[M - 1], N);
					N = N->Pre_List_Node;
				}
				if (N->Path_List_Tree_Node == P && N->Path_List_Tree_Node->KeyNum == KeyNumMax) {
					Position New_Root_1 = Make_New_Node();
					New_Node = BplusTree_Node_Split(N->Path_List_Tree_Node);
					New_Root_1->PtrChild[0] = N->Path_List_Tree_Node;
					New_Root_1->PtrChild[1] = New_Node;
					New_Root_1->Key[0] = N->Path_List_Tree_Node->Key[M - 1];
					New_Root_1->Key[1] = New_Node->Key[M - 2];
					//printf("%d%d\n",New_Root_1->Key[0],New_Root_1->Key[1]);
					P = New_Root_1;
					New_Node->KeyNum = M - 1;
					N->Path_List_Tree_Node->KeyNum = M;
					P->KeyNum = 2;
					Path_List_Header->Next_List_Node->Path_List_Tree_Node = New_Node;
					//return P;
				}
				//printf("%d\n",Current_Node->Key[M-1]);
				BplusTree_Internal_Node_Insert(N->Path_List_Tree_Node, N->Next_List_Node->Path_List_Tree_Node->Key[M - 1], N);
			}
			return P;
		}
		else {
			Index_Old = BplusTree_Node_Insert_Non_Full(Current_Node, Key);
			if (Current_Node == ROOT) {
				Position New_Root = Make_New_Node();
				New_Root->Key[0] = New_Node->Key[M - 2];
				New_Root->PtrChild[0] = New_Node;
				New_Root->KeyNum++;
				P = New_Root;
			}
			/*else if(Index_Old<Key){
				N=Path_List_Header->Next_List_Node;
				while(N->Path_List_Tree_Node->IsLeaf!=true){//????????????????????????
					for(i=0;i<N->Path_List_Tree_Node->KeyNum;i++)
					{
						if(N->Path_List_Tree_Node->Key[i]==Index_Old)
							N->Path_List_Tree_Node->Key[i]=Key;
					}
					N=N->Next_List_Node;
				}
			}*/
			N = Path_List_Tail->Pre_List_Node->Pre_List_Node;
			if (N == Path_List_Header)
				BplusTree_Internal_Node_Insert(P, Current_Node->Key[M - 1], N);
			else {
				while (N->Path_List_Tree_Node->KeyNum == KeyNumMax && N->Path_List_Tree_Node != P)
				{

					//BplusTree_Internal_Node_Insert(N->Path_List_Tree_Node,Current_Node->Key[M-1],N);///////////
					BplusTree_Internal_Node_Insert(N->Path_List_Tree_Node, N->Next_List_Node->Path_List_Tree_Node->Key[M], N);
					N = N->Pre_List_Node;
				}
				if (N->Path_List_Tree_Node == P && N->Path_List_Tree_Node->KeyNum == KeyNumMax) {
					Position New_Root_1 = Make_New_Node();
					New_Node = BplusTree_Node_Split(N->Path_List_Tree_Node);
					New_Root_1->PtrChild[0] = N->Path_List_Tree_Node;
					New_Root_1->PtrChild[1] = New_Node;
					New_Root_1->Key[0] = N->Path_List_Tree_Node->Key[M - 1];
					New_Root_1->Key[1] = New_Node->Key[M - 2];
					//printf("%d%d\n",New_Root_1->Key[0],New_Root_1->Key[1]);
					P = New_Root_1;
					New_Node->KeyNum = M - 1;
					N->Path_List_Tree_Node->KeyNum = M;
					P->KeyNum = 2;
					Path_List_Header->Next_List_Node->Path_List_Tree_Node = New_Node;
					//return P;
				}
				//	printf("%d\n",N->Next_List_Node->Path_List_Tree_Node->KeyNum);
				BplusTree_Internal_Node_Insert(N->Path_List_Tree_Node, N->Next_List_Node->Path_List_Tree_Node->Key[N->Next_List_Node->Path_List_Tree_Node->KeyNum - 1], N);
			}
			return P;
		}

	}
	else {
		Index_Old = BplusTree_Node_Insert_Non_Full(Current_Node, Key);
		if (Index_Old < Key) {
			N = Path_List_Header->Next_List_Node;
			while (N->Path_List_Tree_Node->IsLeaf != true) {
				for (i = 0; i < N->Path_List_Tree_Node->KeyNum; i++)
				{
					if (N->Path_List_Tree_Node->Key[i] == Index_Old)
						N->Path_List_Tree_Node->Key[i] = Key;
				}
				N = N->Next_List_Node;
			}
			return P;
		}
	}
	return P;
}
//bfs tree walk
void Bplus_Tree_Walk(Position ROOT)
{
	int i;
	int QueueNumber = 0;
	Position Queue[100];
	Position CurrentNode;
	Queue[QueueNumber] = ROOT;
	QueueNumber++;
	Queue[QueueNumber] = NULL;
	QueueNumber++;
	while (QueueNumber > 0)
	{
		CurrentNode = Queue[0];
		QueueNumber--;
		i = 0;
		while (i < QueueNumber) {
			Queue[i] = Queue[i + 1];
			i++;
		}
		i = 0;
		if (CurrentNode == NULL)
		{
			printf("\n");
		}
		else
		{
			i = 0;
			while (i < CurrentNode->KeyNum)
			{
				printf("|");
				printf("%d", CurrentNode->Key[i]);
				i++;
			}

			if (CurrentNode != NULL && CurrentNode->IsLeaf == false) {
				i = 0;
				while (i < CurrentNode->KeyNum)
				{
					Queue[QueueNumber] = CurrentNode->PtrChild[i];
					QueueNumber++;
					i++;
				}
				Queue[QueueNumber] = NULL;
				QueueNumber++;
			}
			printf("|   ");
		}

	}
}
#include"datastruct/bptree.h"

int main()
{
	test();
	/*freopen("Bplus_Tree.out", "w", stdout);
	ROOT = NULL;
	Path_List_Header = (Path_List)malloc(sizeof(List_Node));
	Path_List_Tail = (Path_List)malloc(sizeof(List_Node));
	Path_List_Header->Path_List_Tree_Node = NULL;
	Path_List_Tail->Path_List_Tree_Node = NULL;


	if (Path_List_Header->Next_List_Node == Path_List_Tail)
		puts("Head to tail");
	if (Path_List_Tail->Pre_List_Node == Path_List_Header)
		puts("Tail to head");

	ROOT = Bplus_Tree_Insert(ROOT, 1);
	ROOT = Bplus_Tree_Insert(ROOT, 2);
	ROOT = Bplus_Tree_Insert(ROOT, 3);
	ROOT = Bplus_Tree_Insert(ROOT, 4);
	ROOT = Bplus_Tree_Insert(ROOT, 5);
	ROOT = Bplus_Tree_Insert(ROOT, 6);
	ROOT = Bplus_Tree_Insert(ROOT, 7);
	ROOT = Bplus_Tree_Insert(ROOT, 8);
	ROOT = Bplus_Tree_Insert(ROOT, 9);
	ROOT = Bplus_Tree_Insert(ROOT, 10);
	ROOT = Bplus_Tree_Insert(ROOT, 11);
	ROOT = Bplus_Tree_Insert(ROOT, 18);
	ROOT = Bplus_Tree_Insert(ROOT, 19);
	ROOT = Bplus_Tree_Insert(ROOT, 12);
	ROOT = Bplus_Tree_Insert(ROOT, 13);
	ROOT = Bplus_Tree_Insert(ROOT, 14);
	ROOT = Bplus_Tree_Insert(ROOT, 15);
	ROOT = Bplus_Tree_Insert(ROOT, 16);
	ROOT = Bplus_Tree_Insert(ROOT, 17);
	ROOT = Bplus_Tree_Insert(ROOT, 30);
	ROOT = Bplus_Tree_Insert(ROOT, 25);
	ROOT = Bplus_Tree_Insert(ROOT, 28);
	Bplus_Tree_Walk(ROOT);*/
	return 0;
}