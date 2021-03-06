/* Group 58 parser Code
Yash Amin - 2018B5A71044H
Geet Sahitya Dulam - 2018B4A70797H
Harshit Bansal - 2018B5A70601H
Soumit Mishra - 2018B5A70429H */




#include<bits/stdc++.h>
#include "parser_final.h"
using namespace std;


int inc4=0,inc5=0,inc6=0,inc7=0;
void parsetree(struct node* root, struct node* newnode[1000], unordered_map<string, int> &indexer, vector<string> &productions, string ids[], string nums[],string nxt,int ct)
{
	ct=0;
	/*cout<<root->data<<"ROOT "<<endl;
    for(int i=0;i<productions.size();i++)
    {
    	cout<<productions[i]<<endl;
    }*/
    nxt="";
	if(root->term==1 || root->data=="NULL")
	{
	    if(root->data=="id")
        {
            newnode[inc5]=create(ids[inc6],indexer);
            root->adj.push_back(newnode[inc5]);
            inc5++;
            inc6++;
        }
        if(root->data=="num")
        {
            newnode[inc5]=create(nums[inc7],indexer);
            root->adj.push_back(newnode[inc5]);
            inc5++;
            inc7++;
        }
		return;
	}
	else
	{
		nxt="";
		for(int i=0;i<productions[inc4].length();i++)
		{
			if(productions[inc4][i]==' ')
			{
				ct++;
				if(ct>2)
				{
                    newnode[inc5]=create(nxt,indexer);
					root->adj.push_back(newnode[inc5]);
                    inc5++;
				}
				nxt="";
			}
			else
			{
				nxt+=productions[inc4][i];
			}
		}
        newnode[inc5]=create(nxt,indexer);
        root->adj.push_back(newnode[inc5]);
        inc5++;
		nxt="";
		inc4++;
		for(int i=0;i<root->adj.size();i++)
		{
			parsetree(root->adj[i],newnode,indexer,productions,ids,nums,nxt,ct);
		}
	}
}

int main()
{
	unordered_map<string, string[50]> follows;
	unordered_map<string, int> indexer;
	unordered_map<string, string[50]> table;
	stack<string> st;
	int c=0,inc=0,inc2=0,inc3=0;
	int checker=0;
	string terms[41] = {"#", "include", "<", ">", "stdio.h", "math.h", "bits/stdc++.h", "id", "(", ")", "{", "return", ";", "}", ",", "[", "]", "num", "int", "float", "char", "boolean", "string", "=", "+", "-", "*", "/", "%", "true", "false", "&&", "||", "?", "!", "!=", "if", "else", "while", "for", "$"};
	string inp[1000];
	vector<string> productions;
	string ids[1000];
	string nums[1000];
	ofstream output("parser_output6.txt");
	ifstream input("parse6.txt");
	struct node* newnode[1000];
	int k=0;


	follow_init(follows);
	indexer_init(c,indexer,terms);
	table_init(table,indexer);
	string s;
	string s1;
	int ch=0;
	int id1=0,num1=0;
    struct node* root;
    root=create("program",indexer);
	while(getline(input,s))
	{
		s1.clear();
		id1=0;
		num1=0;
		for(int i=0;i<s.length();i++)
		{
			if(s[i]==' ')
			{
				if(s1=="string:")
				{
					ch=1;
				}
				else if(s1=="Identifier,")
				{
					id1=1;
				}
				else if(s1=="Integer" || s1=="Floating")
				{
					num1=1;
				}
				else
				{
					if(ch==1)
					{
						if(id1==1 || s1=="main")
						{
							ids[inc2]=s1;
							inc2++;
						}
						if(num1==1)
						{
							nums[inc3]=s1;
							inc3++;
						}
						if(id1==1 || s1=="main")
						{
							inp[inc]="id";
						}
						else if(num1==1)
						{
							inp[inc]="num";
						}
						else
						{
							inp[inc]=s1;
						}
						inc++;
						ch=0;
					}
				}
				s1.clear();
			}
			else
			{
				if(ch!=1 || s[i]!=',' || s[i+1]!=' ')
				{
					s1+=s[i];
				}
			}
		}
	}
	inp[inc]="$";
	inc++;
	stack<string> st1;
	string add;
	string prod;
	string adders[1000];
	int inc1=0,search=0,curr=0,search1=0;
	parse(terms,1,root,st,st1,inc,inp,indexer,table,productions,checker,follows,add,prod,adders,inc1,search,search1,curr,output);
	if(checker==0)
	{
		string nxt="";
		int ct=0;
		parsetree(root,newnode,indexer,productions,ids,nums,nxt,ct);
		queue<struct node*>q;
		levelorder(root,q,output);
	}
	return 0;
}
