#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack
{
  char bracket;
	struct stack *next;
};

void push(struct stack **head, char ch)
{
    struct stack *current=*head;
    current=(struct stack*)calloc(1,sizeof(struct stack));
    current->bracket=ch;
    current->next=(*head);
    *head=current;
}

void pop(struct stack **head)
{
    struct stack *current;
    current=*head;
    *head=current->next;
    free(current);
}

int control(char ch,char ch_next)
{
    static struct stack *head=NULL;
    int i;
    if(ch=='(' || ch=='{' || ch=='[')
    {
        push(&head,ch);
        return 1;
    }
    if(ch==')' || ch=='}' || ch==']')
    {
        if(head==0)
        {
            puts("INCORRECT ARRENGEMENT");
            return 2;
        }
        i=0;
        switch(ch)
        {
            case ')': if(head->bracket=='(') i=1; break;
            case ']': if(head->bracket=='[') i=1; break;
            case '}': if(head->bracket=='{') i=1; break;
        }
        if(i)
          pop(&head);
        else
        {
            while(head!=NULL)
                pop(&head);
            puts("INCORRECT ARRENGEMENT");
            return 2;
        }
    }
    if(ch_next=='\0' && !head)
    {
        puts("CORRECT ARRANGEMENT");
        return 1;
    }
    else if(ch_next=='\0' && head!=NULL)
    {
        while(head!=NULL)
            pop(&head);
        puts("INCORRECT ARRANGEMENT");
        return 2;
    }
    return 0;
}

char* check_input(int length)
{
    char *string=(char*)calloc(length,sizeof(char));
    do {
        fgets(string,length, stdin);
        if(strlen(string)==length-1)
            while(getchar()!='\n');
    } while (string[0] == '\n');
    return string;
}

void show_help(void)
{
    puts("enter strings");
}

int main(int argc, char *argv[])
{
    if(argc>1)
    {
        if(strcmp(argv[1],"-h"))
            show_help();
    }
	int i,j,length,number;
	char **strings,string[5],ch;
    do{
		while(1)
		{
			puts("Enter the number of strings");
			fgets(string,5,stdin);
            if(!(number=atoi(string)))
			{
			    while(getchar()!='\n');
				puts("error");
				continue;
			}
			else break;
		}
        while(1)
		{
			puts("Enter the length of one string");
			fgets(string,5,stdin);
			if((length=atoi(string))>200 || !length)
			{
			    while(getchar()!='\n');
                puts("error");
                continue;
			}
			else break;
		}
        if(!(strings=(char**)calloc(number,sizeof(char*))))
            puts("error");
		for(i=0;i<number;)
        {
            if(!(strings[i]=(char*)calloc(length+1,sizeof(char))))
            {
                puts("error");
                for(j=0;j<number;j++)
                {
                    free(strings[j]);
                    free(strings);
                    strings=NULL;
                }
            }
            else i++;
        }
	}while(!strings);
	for(i=0;i<number;i++)
	{
        printf("\nenter %d string ",i+1);
		strings[i]=check_input(length);
    }
	for(i=0;i<number;i++)
	    puts(strings[i]);
    for(i=0;i<number;i++)
    {
        printf("\nstring %d:\n",i+1);
        for(j=0;strings[i][j]!='\0';)
        {
            if(control(ch=strings[i][j],strings[i][j+1])==2)
                break;
            j++;
        }
    }
    return 0;
}
