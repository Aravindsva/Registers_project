//ssh for git: git@github.com:Aravindsva/Registers_project.git 
#include <stdio.h>
#include<stdint.h>
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
void freelist(struct registers**);
void write_in_file(struct registers*,const char*);
void input_check();
void existing_files();
int assert_number_list_check(struct registers*,int);
uint8_t file_name_compare(const char*,uint8_t);
void write_assert_number_file(struct registers*);
void clear_buffer();
int check_assert_number_file(int);
int main(int argc,char* argv[]) 
{
	int choice;
	char proceed='y';
	uint8_t choice_try=0;
	uint8_t file_length;
	struct registers *head = NULL;
	uint8_t file_trial=0;
	char file_name[50];
	if(argc==1)
	{
		printf("Existing files: \n");
		existing_files();
		printf("Enter a .txt file to store the register information.\n");
		while(file_trial<3)
		{
			printf("Chance number %d/3.",file_trial+1);
			printf("Enter a .txt file: ");
			//fgets(file_name,sizeof(file_name),stdin);
			scanf("%s",file_name);
			input_check();
			file_length=strlen(file_name);
			/*if(file_name[file_length-1]=='\n')
			{
				file_name[file_length-1]='\0';
			}*/
			uint8_t match=file_name_compare(file_name,file_length);
			if(match==1)
			{
				break;
			}
			else if(match==0)
			{
				file_trial++;
				if(file_trial<3)
					printf("Please enter a valid text file name with .txt.\n");
			}
		}
		if(file_trial==3)
		{
			printf("The file will be stored in the default file- file.txt.\n");
		}
	}
	else if(argc==2)
	{
		if(strcmp(argv[1],"-h")==0)
		{
			printf("(execution command) (enter a file name you want to add the register to.)\n");
			printf("If there is no file name try to enter while in code, otherwise it will be added to the default file- ""file.txt""\n");
			return 0;
		}
		else //if(strcmp(argv[1],
		{
			file_length=strlen(argv[1]);
			uint8_t match=file_name_compare(argv[1],file_length);
                        while(file_trial<3)
			{
			if(match==1)
                        {
                                break;
                        }
                        else if(match==0)
                        {
				file_trial++;
                                printf("Please enter a valid text file name with .txt.\n");
			}
			}
		}

	}
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
		    clear_buffer();
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
	    //proceed=getchar();
	    choice_try=0;
	    while(choice_try<3)
	    {
		    printf("Do you want to continue?(y or n)");
		    proceed=getchar();
		    //while(getchar()!='\n');
		    if(proceed=='\n')
		    {
			    printf("Enter only y or n.\n");
			    choice_try++;
		    }
		    else if((proceed!='y')&&(proceed!='n'))
		    {
			    clear_buffer();
			    printf("Please enter only y or n.\n");
			    choice_try++;
		    }
		    else if((proceed=='y')||(proceed=='n'))
		    {
			    break;
		    }
	    }
	    if(proceed=='n')
	    {
		    write_assert_number_file(head);
		    printf("Before comapring");
		    if((argc==2)&&(file_trial==3))
		    {
			    write_in_file(head,"file.txt");
		    }
		    else if((argc==1)&&(file_trial<3))
		    {
			    write_in_file(head,file_name);
		    }
		    else if(argc>1)
		    {
			    write_in_file(head,argv[1]);
		    }
		    printf("After writing in file");
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
    struct registers *prev=NULL;
    int flag=1,try=0;
    int temp_value;
    printf("Enter the size for value (1 or 2): ");
    scanf("%c",&new_register->size);
    if(getchar()!='\n')
    {
	    printf("Enter a valid input 1 or 2. \n");
	    clear_buffer();
	    return;
    }
    if (new_register->size == '1') 
    {
        printf("Enter a 1 byte value(0 to  255): ");
	scanf("%d",&temp_value);
	input_check();
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
	if(getchar()!='\n')
	{
		printf("Enter a valid input. \n");
		clear_buffer();
		return;
	}
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
    while(try<3)
    {
	    temp=*head;
	    flag=1;
	    printf("Chance number (%d/3).",(try+1));
	    printf("Enter assert number: ");
	    scanf("%d",&new_register->assert_number);
	    input_check();
	    while(temp!=NULL)
	    {
		    if(temp->assert_number==new_register->assert_number)
		    {
			    printf("Assert number already exists in the current list. ");
			    printf("Enter a unique assert number.\n");
			    flag=0;
			    break;
		    }
		    prev=temp;
		    temp=temp->next;
	    }
	    if(flag==1)
	    {
	    flag=check_assert_number_file(new_register->assert_number);
	    }
	    /*if(flag)
            {
		    FILE *assert_file_ptr=fopen("assert_number.txt","a+");
		    if(assert_file_ptr==NULL)
		    {
			    printf("Assert number file not opened");
			    return;
		    }
		    fseek(assert_file_ptr,0,SEEK_END);
		    fprintf(assert_file_ptr,"%d\n",new_register->assert_number);
		    fclose(assert_file_ptr);
	    }*/
		if(flag)
	    {
			    new_register->next=NULL;
		    
			    if(*head==NULL)
			    {
				    *head=new_register;
			    }
			    else
			    {
				    prev->next=new_register;
			    }
			    printf("Register added successfully. \n");
			    return;
	    }
	    try++;
    }
	    printf("Maximum number of tries reahced. \n");
	    free(new_register);
	    return;
}
    /*if (*head == NULL) {
        *head = new_register;
    } else {
	 while(temp->next!=NULL)
    	 {
			 if(temp->assert_number==new_register->assert_number)
			 {
				 printf("Please enter a unique assert number. \n");
				 return;
			 }
			 printf("temp:%p Next:%p", temp, temp->next);
			 temp=temp->next;
		 temp->next = new_register;
	 }
	 printf("Register added successfully.\n");
	}*/
void display(struct registers* head)
{
	struct registers *temp=head;
	if(temp==NULL)
	{
		printf("The register is empty.\n");
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
	input_check();
	if(temp==NULL)
	{
		printf("The list is empty.\n");
		return;
	}
	if(temp->assert_number==key)
	{
		*head=temp->next;
		free(temp);
		printf("The register has sucessfully been removed.\n");
		return;
	}
	while(temp->next!=NULL)
	{
		if(temp->next->assert_number==key)
		{
			free_temp=temp->next;
			temp->next=temp->next->next;
			free(free_temp);
			printf("The register has been sucessfully removed.");
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
	input_check();
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
	int bit,key,flag;
	printf("Enter the asset number of the register to select: ");
	scanf("%d",&key);
	//clear_buffer();
	flag=assert_number_list_check(temp,key);
	if(flag==1)
	{
		clear_buffer();
		printf("The assert number does not exist.\n");	
		return;
	}
	input_check();
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
			//getchar();
		}
		temp=temp->next;
	}
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
	int key,bit,flag;
	printf("Enter the assert number; ");
	scanf("%d",&key);
	flag=assert_number_list_check(temp,key);
	if(flag==1)
	{
		clear_buffer();
		printf("Assert number does not exist.\n");
		return;
	}
	input_check();
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
	struct registers *temp=*head;
	struct registers *next_node;
	while(temp!=NULL)
	{
		next_node=temp->next;
		free(temp);
		temp=next_node;
	}
}
void input_check()
{
	if(getchar()!='\n')
	{
		printf("Enter a valid input. \n");
		while(getchar()!='\n');
		return;
	}
}
void write_in_file(struct registers *temp,const char* str)
{
	printf("Opening file");
	FILE *fptr=fopen(str,"a+");
	if(fptr==NULL)
	{
		fprintf(stderr,"There has been an error in opening the file.");
		return;
	}
	fseek(fptr,0,SEEK_END);
	if(ftell(fptr)==0)
	{
		FILE *file_list_ptr=fopen("file_list.txt","a+");
		fseek(file_list_ptr,0,SEEK_END);
		fprintf(file_list_ptr,"%s\n",str);	
		fprintf(fptr,"Size Value Assert number\n"); 
		fclose(file_list_ptr);
	}
	while(temp!=NULL)
	{
		if(temp->size=='1')
		{
			fprintf(fptr,"%c %5d %4d\n",temp->size,temp->value.data_1,temp->assert_number);
		}
		else if(temp->size=='2')
		{
			fprintf(fptr,"%c %5d %4d\n",temp->size,temp->value.data_2,temp->assert_number);
		}
		temp=temp->next;
	}
	fclose(fptr);
}
uint8_t file_name_compare(const char* file_name,uint8_t file_length)
{
	const char *text_compare=".txt";
	uint8_t text_compare_length=strlen(text_compare);
	if(file_length<text_compare_length)
	{
		return 0;
	}
	printf("File name: '%s', Length: %d\n", file_name, file_length);
	for(int i=0;i<text_compare_length;i++)
	{
		if(file_name[file_length-text_compare_length+i]!=text_compare[i])
		{
			return 0;
		}
	}
	return 1;
}
void existing_files()
{
	int character;
	FILE *files=fopen("file_list.txt","r");
	fseek(files,0,SEEK_SET);
	while((character=fgetc(files))!=EOF)
	{
		putchar(character);
	}
	fclose(files);
}
int check_assert_number_file(int assert_number)
{
	uint8_t flag=1;
	//uint8_t try=3;
	int file_assert_number;
	FILE *file_ptr=fopen("assert_number.txt","r");
	if(file_ptr==NULL)
	{
		printf("Assert number File not opened.");
		return 0;
	}
	//while(try>0)
	//{
		fseek(file_ptr,0,SEEK_SET);
		while(fscanf(file_ptr,"%d",&file_assert_number)!=EOF)
		{
			if(assert_number==file_assert_number)
			{
				printf("Assert number already exist for a register in the file.\n");
				flag=0;
				break;
			}
		}
		//printf("Ypu have %d tries left",(try-1));
		//try--;
	//}
	fclose(file_ptr);
	if(flag==1)
		return 1;
	else 
		return 0;
}
int assert_number_list_check(struct registers* assert_number_temp,int key)
{
	uint8_t flag=1;
	while(assert_number_temp!=NULL)
	{
		if(assert_number_temp->assert_number==key)
		{
			flag=0;
		}
		assert_number_temp=assert_number_temp->next;
	}
	if(flag==1)
		return 1;
	else
		return 0;
}
void write_assert_number_file(struct registers* temp)
{
                    FILE *assert_file_ptr=fopen("assert_number.txt","a+");
                    if(assert_file_ptr==NULL)
                    {
                            printf("Assert number file not opened");
                            return;
                    }
                    fseek(assert_file_ptr,0,SEEK_END);
                    while(temp!=NULL)
		    {
		    	fprintf(assert_file_ptr,"%d\n",temp->assert_number);
			temp=temp->next;
		    }
		    fclose(assert_file_ptr);
		    return;
}
void clear_buffer()
{
	while(getchar()!='\n');
}
