#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<vector>
#include<fstream>
using namespace std;
vector<int> lsp;
vector<string> lines;
void computeLPSArray(string P)

{

	lsp.clear();
	int i,j,n;
	n = P.length();
	i = 0;
	j = 1;
	lsp.push_back(0);

	while( j < n)

	{
		if(P[i] == P[j])
		{
			i++;
			lsp.push_back(i);
			j++;
		}
		else
		{
			if(i != 0)
			{
				i = lsp[i - 1];

			}
			else
			{
				lsp.push_back(0);

				j++; 

			}

		}

	}

}

int KMPSearch(string txt, string Pat)                 //searching for the query in the text

{
	int i,j,count = 0;

	computeLPSArray(Pat);
	i = 0;

	j = 0;
	while(i < txt.length())

   {

       if(txt[i]==Pat[j])

	   {  i++;
	      j++;
	   }

	   else
	   {
	       if(j != 0)
		   {
		       j = lsp[j - 1];
		   }
		   else
		       i++;
	   }

	   int M=Pat.size();
       int N=Pat.size();
	   if(j == M)

	   {

	       if((txt[i - M - 1] ==' ' && txt[i] == ' ') ||( (i - M) == 0  && txt[i] ==' ')|| (i == N && txt[i -M - 1] == ' ' )) 

		   count++;

	       j = lsp[j - 1];
       } 
   }
   return count;
}
void readPage(char name[30])      //reads the whole page and stores the lines

 {
	 ifstream page;
	 int index = 0;
     strcat(name,".txt");
     string l;
	 page.open(name);
	 if(!page)             
	 cout<<"ERROR";
	 else
	 {
	     while(!page.eof())
		 {  getline(page,l);
		    if(!page.eof())
		 	    lines.push_back(l);
	     }
	     page.close();
     }
}  

int main()
{ 
   	string P,txt;
   	ifstream quer;
   	int flag = -1;int a;
   	quer.open("queries.txt");
   	char str[15],number[2];
   	strcpy(str,"page_");
   	while(quer>>P)
   	{
	    cout<<"Word:"<<P<<"\n";
	    cout<<"Occurances:"<<"\n";
	    flag = -1;
	   	for(int pgno = 1; pgno <= 25; pgno++)
	   	{
	   	    itoa(pgno,number,10);

			strcat(str,number);

			readPage(str);

			for(int k = 0; k < lines.size(); k++)  
			{  
				a = KMPSearch(lines[k],P);            
				if(a != -1)
				{
				    for(int j = 1; j <= a; j++)     // number of times the query is found on line k+1
					cout<<"Page: "<<pgno<<", "<<"line: "<<k + 1<<"\n";
				flag = 1;
			    }
		    }
		    strcpy(str,"page_");
	    }
		if(flag == -1)
		cout<<"Nil";
    }
   	quer.close();
}
