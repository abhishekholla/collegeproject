#include<iostream.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include<dos.h>
#include<fstream.h>
#include <stdio.h>


struct node
{
 char word[20],meaning[100],synonym[100],antonym[100];
 node *left,*right;
};

class Project
{
	public:
		node *maketree(char[],char[],char[],char[]);
		node* treefromfile();
		void filefromtree(node*);
		void addword(node*,char[],char[],char[],char[]);
		void seperateword(char[],char[],char[]);
		void displayall(node*);
		node* bsearch(node*,char[]);
		void showmenu();
		void prog();
		void intro();
		void travandwrite(node *);
};

void Project::prog()
{
 clrscr();
 char word[20],meaning[100],synonym[100],antonym[100];
 int menuchoice;
 node *temp;
 temp=treefromfile();

 while(1)
 {
  clrscr();
  cout<<"\nCOMPUTER DICTIONARY";
 cout<<"\n[1].	Add a word.";
 cout<<"\n[2].	Find meaning.";
 cout<<"\n[3].	Display all.";
 cout<<"\n[4].  Save.";
 cout<<"\n[5].  Exit.";
 cout<<"\nEnter Choice:";
  cin>>menuchoice;
  switch(menuchoice)
  {
   case 1:cout<<"\nEnter word : ";
	  gets(word);
	  cout<<"\nEnter meaning : " ;
	  gets(meaning);
	  cout<<"\nEnter synonym : ";
	  gets(synonym);
	  cout<<"\nEnter antonym : ";
	  gets(antonym);
	  flushall();

	  if(temp==NULL)
	   temp=maketree(word,meaning,synonym,antonym);
	  else
	   addword(temp,word,meaning,synonym,antonym);
	  break;
   case 2:if(temp==NULL)
	   cout<<"\nThe dictionary is empty...";
	  else
	  {
	   cout<<"\nFind meaning of : ";
	   flushall();
	   gets(word);
  //	   strcat(word,":");
	   node *t;
	   t=bsearch(temp,word);
	   if(t==NULL)
	    cout<<"\nWord not found...";
	   else
	   {
	    cout<<t->word<<":";
	    puts(t->meaning);
	    cout<<"\nSynonym: "<<t->synonym;
	    cout<<"\nAntonym: "<<t->antonym;
	   }
	  }
	  getch();
	  break;
   case 3:if(temp==NULL)
	   cout<<"\nDictionary is empty...";
	  else
	   displayall(temp);
	  getch();
	  break;
   case 4:delete("dict.txt");
	  filefromtree(temp);

	  break;
   case 5:exit(0);
	  break;
   default:cout<<"\nEnter Again:";

	   //prog();
	   break;
  }
 }
}



node* Project::treefromfile()
{

	 node *ptree=NULL;
 char word[20],meaning[100],str[5000],synonym[100],antonym[100];
 int flags=0;
 ifstream ifs("dict.txt",ios::beg);
 if(ifs==NULL)
  ptree=NULL;
 else
 {

	long begin = ifs.tellg();
	ifs.seekg (0, ios::end);
	long end = ifs.tellg();
	// end=myfile.gcount();
	 ifs.seekg(0,ios::beg);
	 long pos=(end-begin);
	 ifs.read(str,pos);
	if(str==NULL)
	  return NULL;

	int j=0,i=0,l,f=0,p=0,q=0,flags=0;
	char str1[5000],w[50],m[50],s[50],a[50];
	l=strlen(str);
	while(i<l)
	{
		if(str[i]!='|')
		{
			str1[j]=str[i];

			j++;
		}
		else
		{
			//flags=0;
			str1[j]='\0';
			j=0;
		       //	i++;
			strcpy(w,"");
			strcpy(m,"");
			strcpy(s,"");
			strcpy(a,"");
		       //char w[40],m[40];
			cout<<str1;
			f=q=p=0;
			for(int k=0;str1[k]!='\0';k++)
			{
				if(str1[k]!=':' && f==0)
				{
					w[p]=str1[k];
					p++;
				}
				else
				{
					if(f==0)
						k++;
					m[q]=str1[k];
					q++;
					f=1;
				}
			}
			w[p]='\0';
			m[q]='\0';
			cout<<"\n\n";
			cout<<"Word:"<<w<<"Meaning:"<<m<<"Synonym:"<<s<<"Antonym "<<a<<"\n";
			strcpy(str1,"");
			if(flags==0)
			{
			   ptree=maketree(w,m,s,a);
			   flags=1;
			}
			else
				addword(ptree,w,m,s,a);

		}
		i++;

	}
  }
  ifs.close();
  return ptree;
}
node* Project::maketree(char w[],char m[],char s[],char a[])
{
 node *p;
 p=new node;
// strcat(w,":");
 strcpy(p->word,w);
// strcat(m,"|");
 strcpy(p->meaning,m);
 strcpy(p->synonym,s);
 strcpy(p->antonym,a);
 p->left=NULL;
 p->right=NULL;
 return p;
}

void Project::addword(node *tree,char word[],char meaning[],char synonym[],char antonym[])
{
 node *p,*q;
 p=q=tree;
 while(strcmp(word,p->word)!=0 && p!=NULL)
 {
  q=p;
  if(strcmp(word,p->word)<0)
   p=p->left;
  else
   p=p->right;
 }
 if(strcmp(word,q->word)==0)
 {
  cout<<"This word already exists...";
  //delay(1000);
 }
 else if(strcmp(word,q->word)<0)
  q->left=maketree(word,meaning,synonym,antonym);
 else
  q->right=maketree(word,meaning,synonym,antonym);
}
node* Project::bsearch(node *tree,char word[])
{
 node *q;
 q=tree;
 while(q!=NULL)
 {
  //p=q;
  if(strcmp(word,q->word)<0)
   q=q->left;
  else if(strcmp(word,q->word)>0)
   q=q->right;
  if(strcmp(word,q->word)==0)
   break;
 }
 return q;
}
void Project::filefromtree(node *tree)
{

  if(tree!=NULL)
  {
   travandwrite(tree);
  }
}

void Project::travandwrite(node *tree)
{
  ofstream ofs("dict.txt",ios::ate);
  if(ofs==NULL)
 {
  cout<<"Cannot open file for writing data...";
 }
 if(tree!=NULL)
 {


  ofs<<tree->word<<":"<<tree->meaning<<"\n"<<"Synonym: "<<tree->synonym<<"\nAntonym: "<<tree->antonym;
  ofs.close();
  travandwrite(tree->left);
  travandwrite(tree->right);
 }
}
void Project::displayall(node *tree)
{
 if(tree!=NULL)
 {
  displayall(tree->left);
  cout<<"\n"<<tree->word<<":"<<tree->meaning<<"\nSynonym: "<<tree->synonym<<"\nAntonym "<<tree->antonym<<"\n";
  displayall(tree->right);
 }
}

void Project::intro()
{
int i;
clrscr();
gotoxy(10,10);
cout<<"DICTIONARY LOADING";
for(i=0;i<50;i++)
{
 gotoxy(10+i,12);
 cout<<"***";
 gotoxy(13,13);
 cout<<2*i<<"% completed";
 delay(150);
}
gotoxy(13,13);
cout<<"DICTIONARY LOADING COMPLETED";
clrscr();
}
void main()
{
Project p;

clrscr();
p.intro();
p.prog();
}