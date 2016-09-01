#include <iostream>
#include <fstream> // file op
#include <iomanip> //setw()......
using namespace std;

#define SONG_LENGTH 21
#define ARTIST_LENGTH 21
#define CD_LENGTH 21

class Song{
public:
	char* song;
	char* artist;
	char* cd;
	int rating;
	Song* next;
};

Song* new_song(char* song, char* artist, char* cd, int rating);
Song* insert_by_song(Song* head, Song* node);
void print_list(Song* head);
int update_song(Song* head, char* name, int rating);
Song* delete_even(Song* head);
Song* delete_odd(Song* head);
void free_node(Song* node);
Song* free_list(Song *listHead);


int main(int argc, char** argv){
	cout<<"The size of the struct type Song is "
		<<sizeof(Song)
		<<" bytes."
		<<endl;
	if(argc<2)
	{
		cout<<"Error: Insufficient CommandLine arguments.\n";
		cout<<"Usage: linkedlist <filename><CR>\n";
		return 0;
	}
	Song *head = NULL;
	//print_list(head);
	Song *node = NULL;
	int rating;   /* cout<< hex <<uppercase;*/
	ifstream source(*(argv+1));

	while(!source.eof())
	{

		char *song = new char[SONG_LENGTH];           //这是用new给结构体中的指针分配空间,以便于存放从文件里来的数据
		char *artist = new char[ARTIST_LENGTH];		//这里,你老师写错了,NND,害我一夜没睡这里原来是小括号,现已经改正
		char *cd = new char[CD_LENGTH];		//每个数给加了1,它设的宏空间太小,
		source >> song;        //从文件输入
		source >> artist;
		source >> cd;
		source >> rating;
		node = new_song(song,artist,cd,rating);          //创建新的结构
		head = insert_by_song(head,node);                  //把新建的结构插入原有结构
		cout << endl;
	}
	source.close();
	system("pause");
	system("cls");
	print_list(head);
	system("pause");
	//update_song(head,"荷塘月色",3);    //这四句,可以随便解开一句测试
	//head=delete_even(head);
	//head=delete_odd(head);
	//head=free_list(head);
	system("pause");
	return 0;
}

Song* new_song(char* song, char* artist, char* cd, int rating){
	Song *head=new Song;
	head->song = new char[SONG_LENGTH];
	head->artist = new char[ARTIST_LENGTH];
	head->cd = new char[CD_LENGTH];

	strcpy(head->song,song);
	strcpy(head->artist,artist);
	strcpy(head->cd,cd);
	head->rating=rating;
	head->next=NULL;
	cout << song
		<<": song at "
		<<hex
		<<(unsigned long) song
		<<", artist at "
		<<(unsigned long) artist
		<<", cd at "
		<<(unsigned long) cd
		<<endl;   //要求要输出存放的地址
	cout<<"Node"
		<<"\t"
		<<song
		<<"\t"
		<<artist
		<<"\t"
		<< cd
		<<endl;
	return head;
}


Song* insert_by_song(Song* head, Song* node)//START POINTER AND NEW POINTER{
{
	Song *newNode;
	Song *newHead;
	Song *tmp;
	newNode=node;
	newHead=head;
	//Check IF the List is NULL. If it is,then append the node.
	if(NULL==head)
	{
		head=newNode;
		newNode->next=NULL;
	}
	else
		//Go over the List. See if any "song" in their nodes "great than" that in the newNode.
		//If it is, Insert newNode before it,If the song of the last node is "smaller than" newNode, append newNode at the end.
	{
		//string comparation prototype: extern int strcmp(const char *s1,const char * s2);
		//In the Header: string.h
		//function: compare strings s1 and s2.
		//Format: strcmp(s1, s2)
		// Return -1: if s1<s2
		// Return 0 : if s1==s2
		// Return 1 : if s1>s2
		while((strcmp(newNode->song, newHead->song)>0)&&(newHead->next!=NULL))
		{
			tmp=newHead;
			newHead=newHead->next;
		}
		//a node containing song G.T. that in newNode FOUND
		if(strcmp(newNode->song, newHead->song) <= 0)
		{
			// See if it is the HEAD. If it is, let newNode be head
			if(newHead==head)
			{
				head = newNode;
			}
			else
			{
				tmp->next = newNode;
			}
			newNode->next=newHead;
		}
		else
		{
			newHead->next = newNode;
			newNode->next=NULL;
		}
	}
	cout << "The node with the song NAME \""<<node->song<<"\" inserted successfully!\n";
	return head;
}
/*
* Runs through the linked list specified by the pointer head and prints it
* to the screen
*/
void print_list(Song* head){
	Song *p=head;
	if(p!=NULL)
	{
		cout.clear();
		cout  <<setfill(' ')<<left<<setw(20)
			<<"歌名SongName"
			<<setfill(' ')<<left<<setw(20)
			<<"歌手Artist"
			<<setfill(' ')<<left<<setw(20)
			<<"CD专辑"
			<<"热度 "
			<<"head   "
			<<"next   "
			<<endl;

		int a=0;
		while(p!=NULL)
		{

			cout <<setfill(' ')<<left<<setw(20)
				<<p->song
				<<setfill(' ')<<left<<setw(20)
				<<p->artist
				<<setfill(' ')<<left<<setw(20)
				<<p->cd
				<<setfill(' ')<<left<<setw(5)
				<<p->rating
				<<hex
				<<(unsigned long) p
				<<" "
				<<(unsigned long) p->next
				<<endl;
			p=p->next;
			a++;
		}
		cout <<"Total Node(s) in the linked List:"
			<<dec
			<<a
			<<endl;
	}
	else
	{
		cout <<"Null list"<<endl;
	}
}

int update_song(Song* head, char* name, int rating){
	Song *p=head;
	while(p!=NULL)
	{
		if (strcmp(name,p->song)==0)
		{
			p->rating=rating;
                  cout<<"the node with song"<<p->song<<"is updated successfully <with rating"<<rating<<">"<<endl;    //目录有的歌曲
			return 1;
		}
		p=p->next;
	}
	cout<<"the song named"<<p->song<<"NOT found in the playlist ,try again";//没有这首歌
	return 0;

}
/*
* Runs through the linked list specifed by the pointer head and deletes every node
* whose rating is even. This function should call free_node().
* Return: The head of the linked list
*/
Song* delete_odd(Song* head){
	system("cls");
	Song *p=head;
	Song *before = NULL;
	while(p!=NULL){

		if (p->rating%2==0){
			if(before==NULL){

				head=p->next;
				delete [] (p->artist);
				delete [] (p->cd);
				delete [] (p->song);
				delete p;
				p=head;

			}
			else{
				delete [](p->artist);
				delete [](p->cd);
				delete [](p->song);
				before->next=p->next;
				delete p;
				p=before->next;
			}
		}
		else{
			before=p;
			p=p->next;
		}

	}
	cout<< "after delete_odd...Contents int the list are:"<<endl;
	print_list(head);
	return head;
}

Song* delete_even(Song* head){
	system("cls");
	Song *p=head;
	Song *before = NULL;
	while(p!=NULL){
		if ((p->rating%2!=0)||(p->rating==1)){
			if(before==NULL){
				head=p->next;

				delete [] (p->artist);
				delete [] (p->cd);
				delete [] (p->song);
				delete p;
				p=head;
			}
			else{
				delete [](p->artist);
				delete [](p->cd);
				delete [](p->song);
				before->next=p->next;
				delete p;
				p=before->next;
			}
		}
		else{
			before=p;
			p=p->next;
		}

	}
	cout<< "after delete_even...Contents int the list are:"<<endl;
	print_list(head);
	return head;
}

void free_node(Song* node){
	delete [](node->artist);
	delete [](node->cd);
	delete [](node->song);
	delete node;
}

Song* free_list(Song *listHead)
{
	Song *node=listHead ;
	cout << "Freeing linkedList...\n";
	while(node!=NULL)
	{
		listHead=listHead->next;
		free_node(node);
		node=listHead ;
	}

	cout << "linkedList freed successfuy!\n";
	return listHead;
}
