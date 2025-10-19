#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#define BYTE_1 8
#define BYTE_2 16
struct registers 
{
    char size;
    union 
    {
        unsigned char data_1;
        unsigned short int data_2;
    } value;
    int assert_number;
    struct registers *next;
};
void add_register(struct registers **head);
void remove_register(struct registers **head);
void toggle_value(struct registers **head);
void toggle(int, struct registers **);
void pull_down(struct registers **);
void down(int, struct registers **);
void pull_up(struct registers **);
void up(int,struct registers **);
void display(struct registers* );
void freelist(struct registers **);
int main() 
{
    int choice;
    char proceed='y';
    struct registers *head = NULL;
    while(proceed=='y')
    {
	    printf("1- Add a register.\n");
	    printf("2- Remove a register.\n");
	    printf("3- Toggle value.\n");
	    printf("4- Pull down.\n");
	    printf("5- Pull up.\n");
	    printf("6- Display the registers.\n");
	    printf("Enter your choice: ");
	    if(scanf("%d",&choice)!=1)
	    {
		    printf("Enter a valid choice.\n");
		    while(getchar()!='\n');
	    }
	    else if(getchar()!='\n')
	    {
		    printf("Enter a valid choice.\n");
	    }
	    else
	    {
		    switch(choice) 
		    {
		    case 1:
			    add_register(&head);
			    break;
		    case 2:
			    remove_register(&head);
			    break;
		    case 3:
			    toggle_value(&head);
			    break;
		    case 4:
			    pull_down(&head);
			    break;
		    case 5:
			    pull_up(&head);
			    break;
		    case 6:
			    display(head);
			    break;
		    default:
			    printf("Please enter a valid choice.\n");
			    break;
	    }
	    }
	    printf("Do you want to continue?(y or n)");
	    proceed=getchar();
	    while(getchar()!='\n');
	    if(proceed=='n')
	    {
		    freelist(&head);
		    printf("The list is emptied.\n");
		    return 0;
	    }
    }
    return 0;
}
void add_register(struct registers **head) 
{
    struct registers *new_register = (struct registers *)malloc(sizeof(struct registers));
    struct registers *temp=*head;
    int temp_value;
    printf("Enter the size for value (1 or 2): ");
    scanf("%c",&new_register->size);
    if(getchar()!='\n')
    {
	    printf("Enter a valid input 1 or 2. \n");
	    while(getchar()!='\n');
	    return;
    }
    if (new_register->size == '1') 
    {
        printf("Enter a 1 byte value(0 to  255): ");
	scanf("%d",&temp_value);
	getchar();
	if((temp_value>255)||(temp_value<0))
	{
		printf("Enter a 1 byte value(0 to 255).\n");
		free(new_register);
		return;
	}
	else
	{
		new_register->value.data_1=(unsigned char)temp_value;
	}
    } 
    else if (new_register->size == '2') 
    {
        printf("Enter a 2 byte value(0 to 65535): ");
        scanf("%d",&temp_value);
	getchar();
	if((temp_value>65535)||(temp_value<0))
        {
                printf("Enter a 1 byte value(0 to 65535).\n");
                free(new_register);
                return;
        }
	else
	{
	new_register->value.data_2=(unsigned short int)temp_value;
	}
    } 
    else if((new_register->size!='1')&&(new_register->size!='2')) 
    {
        printf("Invalid size. Please enter 1 or 2.\n");
	return;
    }
    printf("Enter assert number: ");
    scanf("%d",&new_register->assert_number);
    if(getchar()!='\n')
    {
	    printf("Enter a valid number.\n");
	    return;
    }
    while(temp!=NULL)
    {
	    if(temp->assert_number==new_register->assert_number)
	    {
		    printf("Please enter a unique assert number. \n");
		    free(new_register);
		    return;
	    }
	    temp=temp->next;
    }
    new_register->next = NULL;
    if (*head == NULL) {
        *head = new_register;
    } else {
        struct registers *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_register;
    }
    printf("Register added successfully.\n");
}
void display(struct registers* head)
{
	struct registers *temp=head;
	if(temp==NULL)
	{
		printf("The register is empty.");
		return;
	}
	while(temp!=NULL)
	{
		printf("The size of data is: %c\n",temp->size);
		if(temp->size=='1')
		{
			printf("The value of data is: %d\n",temp->value.data_1);
		}
		else if(temp->size=='2')
		{
			printf("The value of data is: %d\n",temp->value.data_2);
		}
		printf("The assert number of the register is: %d\n",temp->assert_number);
		temp=temp->next;
	}
}
void remove_register(struct registers **head)
{
	int key;
	struct registers *free_temp;
	struct registers *temp=*head;
	printf("Enter the assert number of the register to remove: ");
	scanf("%d",&key);
	while(getchar()!='\n');
	if(temp==NULL)
	{
		printf("The list is empty.\n");
		return;
	}
	if(temp->assert_number==key)
	{
		*head=temp->next;
		free(temp);
		return;
	}
	while(temp->next!=NULL)
	{
		if(temp->next->assert_number==key)
		{
			free_temp=temp->next;
			temp->next=temp->next->next;
			free(free_temp);
			return;
		}
		temp=temp->next;
	}
	printf("Resiter not found.\n");
}
void toggle_value(struct registers **head)
{
	struct registers *temp=*head;
	int key;
	printf("Enter the assert number of the register to toggle: ");
	scanf("%d",&key);
	while(getchar()!='\n');
	if(temp==NULL)
	{
		printf("The list is empty.\n");
		return;
	}
	while(temp!=NULL)
	{
		while(temp!=NULL)
		{
			if(temp->assert_number==key)
			{
				toggle(key,&temp);
				return;
			}
			temp=temp->next;	
		}
	}
	printf("Assert number not found. Enter a valid number.\n");
}
void toggle(int key, struct registers **temp)
{
	int position=0;
	if((*temp)->size=='1')
	{
		printf("Before toggle: ");
		for(int index=0;index<BYTE_1;index++)
		{
			position=((*temp)->value.data_1>>index)&1;
			printf("%d",position);
		}
		printf("\nAfter toggle: ");
		for(int index=0;index<BYTE_1;index++)
		{
			(*temp)->value.data_1=(((*temp)->value.data_2)^(1<<index));
			position=((*temp)->value.data_1>>index)&1;
			printf("%d",position);
		}
		printf("\n");
	}
	else if((*temp)->size=='2')
	{
		printf("Before toggle: ");
		for(int index=0;index<BYTE_2;index++)
                {
			position=((*temp)->value.data_2>>index)&1;
			printf("%d",position);
		}
		printf("\nAfter toggle: ");
		for(int index=0;index<BYTE_2;index++)
		{
			(*temp)->value.data_2=(((*temp)->value.data_2)^(1<<index));
			position=((*temp)->value.data_2>>index)&1;
			printf("%d",position);
		}
		printf("\n");
        }
}
void pull_down(struct registers **head)
{
	struct registers *temp=*head;
	int bit,key;
	printf("Enter the asset number of the register to select: ");
	scanf("%d",&key);
	while(getchar()!='\n');
	if(temp==NULL)
	{
		printf("The list is empty.\n");
		return;
	}
	printf("Enter the bit to be pulled down: ");
	scanf("%d",&bit);
	getchar();
	while(temp!=NULL)
	{
		if(temp->assert_number==key)
		{
			down(bit,&temp);
			getchar();
		}
		temp=temp->next;
	}
		printf("Assert number not found.\n");
}
void down(int bit,struct registers **temp)
{
	int result;
	if((*temp)->size=='1')
	{
		if((bit<0)||(bit>BYTE_1-1))
		{
			printf("Enter a valid bit value(0 to 7.\n");
			return;
		}
		else
		{
			printf("Before pull down: ");
			for(int index=BYTE_1-1;index>=0;index--)
			{
				printf("%d",(((*temp)->value.data_1>>index)&1));
			}
			(*temp)->value.data_1=(((*temp)->value.data_1)&(~(1<<bit)));
			printf("\nAfter pulldown: ");
			for(int index=BYTE_1-1;index>=0;index--)
			{
				printf("%d",(((*temp)->value.data_1>>index)&1));
			}
			printf("\n");
		}
	}
	else if((*temp)->size=='2')
        {
                if((bit<0)||(bit>BYTE_2-1))
                {
                        printf("Enter a valid bit value(0 to 15).\n");
                        return;
                }
                else
                {
                        printf("Before pull down: ");
                        for(int index=BYTE_2-1;index>=0;index--)
                        {
                                printf("%d",(((*temp)->value.data_2>>index)&1));
                        }
                        (*temp)->value.data_2=(((*temp)->value.data_2)&(~(1<<bit)));
                        printf("\nAfter pulldown: ");
                        for(int index=BYTE_2-1;index>=0;index--)
                        {
                                printf("%d",(((*temp)->value.data_2>>index)&1));
                        }
		 printf("\n");	
                }
        }
}
void pull_up(struct registers **head)
{
	struct registers *temp=*head;
	int key,bit;
	printf("Enter the assert number; ");
	scanf("%d",&key);
	while(getchar()!='\n');
	if(temp==NULL)
	{
		printf("The list is empty.\n");
		return;
	}
	printf("Enter the bit position to pull up: ");
	scanf("%d",&bit);
	getchar();
	while(temp!=NULL)
	{
		if(temp->assert_number==key)
		{
			up(bit,&temp);
		}
		temp=temp->next;
	}
	printf("Assert number not found.\n");
}
void up(int bit,struct registers **temp)
{
	if((*temp)->size=='1')
	{
		if((bit<0)||(bit>BYTE_1-1))
		{
			printf("Enter a valid bit number(0 to 7).\n");
		}
		else
		{
			printf("Before pull up: ");
			for(int index=BYTE_1-1;index>=0;index--)
			{
				printf("%d",(((*temp)->value.data_1>>index)&1));
			}
			(*temp)->value.data_1=(((*temp)->value.data_1)|(1<<bit));
			printf("\nAfter pull up: ");
			for(int index=BYTE_1-1;index>=0;index--)
			{
				printf("%d",(((*temp)->value.data_1>>index)&1));
			}
			printf("\n");
		}
	}
	else if((*temp)->size=='2')
	{
		if((bit<0)||(bit>BYTE_2-1))
		{
			printf("Enter a valid but number(0 to 15).\n");
			return;
		}
		else
		{
			printf("Before pull up: ");
			for(int index=BYTE_2-1;index>=0;index--)
			{
				printf("%d",(((*temp)->value.data_2>>index)&1));
			}
			(*temp)->value.data_2=(((*temp)->value.data_2)|(1<<bit));
			printf("\nAfter pull up: ");
			for(int index=BYTE_2-1;index>=0;index--)
			{
				printf("%d",(((*temp)->value.data_2>>index)&1));
			}
			printf("\n");
		}
	}
}
void freelist(struct registers **head)
{
	struct registers *temp;
	while(*head!=NULL)
	{
		temp=(*head);
		(*head)=(*head)->next;
		free(temp);
	}
}
