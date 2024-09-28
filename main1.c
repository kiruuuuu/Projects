#include<stdio.h>
#include<string.h>
#include<stdio_ext.h>
struct data{
	char name[30];
	char mobile[11];
	char email[30];
	char address[50];
};
void add_contacts();
void copy(FILE *,FILE *);
void search_contacts();
void print_contacts();
void edit_contacts();
void delete_contacts();
int main(){
	char ch='y';
	int choice;
	while (ch=='y' || ch=='Y')
	{
		printf("1.Add\n 2.search\n 3.print\n 4.edit\n 5.delete\n Enter your choice: ");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				add_contacts();
				break;
			case 2:
				search_contacts();
				break;
			case 3:
				print_contacts();
				break;

			case 4: edit_contacts();
				break;

			case 5: delete_contacts();
				break;

		}
		printf("do you want to continue(y/n): ");
		scanf(" %c",&ch);

	}
}
void add_contacts()
{
	struct data contacts;
	FILE *fdata=fopen("data.csv","r");
	if(fdata== NULL){
		printf("file not opened");
		return;
	}
	int count=0;
	FILE *ftemp=fopen("temp.csv","w");
	fscanf(fdata,"%d\n",&count);
	fprintf(ftemp,"%d\n",count+1);
	for(int i=0;i<count;i++){
		fscanf(fdata,"%[^,],%[^,],%[^,],%[^\n]\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
		fprintf(ftemp,"%s,%s,%s,%s\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
	}
	char str2[30];
	printf("Enter the name without special characters and numbers:");
	scanf(" %[a-z A-Z]",str2);
	printf("%s\n",str2);
	__fpurge(stdin);
n:
	char str1[12];
	printf("Enter the mobile number: ");
	scanf(" %[^\n]",str1);
	fseek(fdata,2,SEEK_SET);
	int flag;
	for(int i=0;i<count;i++)
	{
		flag=0;
		fscanf(fdata,"%[^,],%[^,],%[^,],%[^\n]\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
		if(strcmp(str1,contacts.mobile)==0)
		{
			flag=1;
			break;

		}

	}
	if(flag==1)
	{
		printf("The entered number already exist Try again!!\n");
		goto n;
	}
	int num=strlen(str1);
	if(num>10||num<10)
	{
		printf("Enter the correct mobile number!!\n");
		goto n;
	}
n1:
	char str[30];
	printf("Enter the email: ");
	scanf(" %[^\n]",str);
	fseek(fdata,2,SEEK_SET);
	for(int k=0;k<count;k++)
	{
		flag=2;
		fscanf(fdata,"%[^,],%[^,],%[^,],%[^\n]\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
		if(strcmp(str,contacts.email)==0)
		{
			flag=3;
			break;

		}

	}
	if(flag==3)
	{
		printf("The entered email already exist Try again!!\n");
		goto n1;
	}
	for(int i=0;str[i];i++)
	{
		if(str[i]=='@')
		{
			if(strstr(str,".com")!=NULL)
			{
				if(str[i+1]=='.')
				{
					printf("Enter the correct format of email\n");
					goto n1;
				}
			}
		}
	}
	strcpy(contacts.email,str);
	printf("Enter the address: ");
	scanf(" %[^\n]",contacts.address);
	strcpy(contacts.name,str2);
	strcpy(contacts.mobile,str1);
	fprintf(ftemp,"%s,%s,%s,%s\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
	fclose(fdata);
	fclose(ftemp);
	fdata=fopen("data.csv","w");
	ftemp=fopen("temp.csv","r");
	copy(fdata,ftemp);
	fclose(fdata);
	fclose(ftemp);
}
void copy(FILE *fdata, FILE *ftemp)
{
	char ch;
	while((ch=fgetc(ftemp))!=EOF)
		fputc(ch,fdata);
}
void search_contacts()
{
	int flag=0;
	struct data contacts;
	FILE *fdata=fopen("data.csv","r");
	char new_mobile[30];
	printf("Enter the new_mobile");
	scanf(" %[^\n]",new_mobile);
	int count=0;
	fscanf(fdata," %d\n",&count);
	for(int i=0;i<count;i++)
	{
		fscanf(fdata," %[^,],%[^,],%[^,],%[^\n]\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
		if(strcmp(new_mobile,contacts.mobile)==0)
		{
			flag=1;
			printf("________________________________________________________________________\n");
			printf("Name    : %s\n",contacts.name);
			printf("Mobile  : %s\n",contacts.mobile);
			printf("Email   : %s\n",contacts.email);
			printf("Address : %s\n",contacts.address);
			printf("________________________________________________________________________\n");


		}
	}
	if(flag==0)
	{
		printf("Enter the valid phone number!");
	}
	fclose(fdata);
}
void print_contacts()
{
	struct data contacts;
	FILE *fdata=fopen("data.csv","r");
	int count=0;
	fscanf(fdata,"%d\n",&count);
	while(!feof(fdata))
	{
		for(int i=0;i<count;i++)
		{
			fscanf(fdata," %[^,],%[^,],%[^,],%[^\n]\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
			printf("________________________________________________________________________\n");
			printf("Name    : %s\n",contacts.name);
			printf("Mobile  : %s\n",contacts.mobile);
			printf("Email   : %s\n",contacts.email);
			printf("Address : %s\n",contacts.address);
			printf("________________________________________________________________________\n");

		}
	}
	fclose(fdata);
}
void edit_contacts()
{
	int flag=0;
	struct data contacts;
	FILE *fdata=fopen("data.csv","r");
	if(fdata== NULL){
		printf("file not opened");
		return;
	}
	int count=0;
	FILE *ftemp=fopen("temp.csv","w");
	fscanf(fdata,"%d\n",&count);
	fprintf(ftemp,"%d\n",count);
	char new_mobile[30];
	char str[30];
	char new_address[30];
	char new_name[30];
	char str4[20];
	printf("Enter the new mobile :");
	scanf(" %[^\n]",new_mobile);
	int var1=1;
	for(int i=0;i<count;i++)
	{
		fscanf(fdata,"%[^,],%[^,],%[^,],%[^\n]\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
		if(strcmp(new_mobile,contacts.mobile) ==0)
		{
			flag=1;
			while(var1)
			{
				printf("1.name:\n");
				printf("2.email:\n");
				printf("3.mobile:\n");
				printf("4.address:\n");
				printf("5.exit :\n");
				int opt;
				printf("Enter the choice :\n");
				scanf("%d",&opt);

				switch(opt)
				{
					case 1:printf("Enter the new name:");
					       scanf(" %[^\n]",new_name);
					       strcpy(contacts.name,new_name);
					       break;

					case 2:
n3:
					       printf("Enter the new email:");
					       scanf(" %[^\n]",str);
					       for(int k=0;k<count;k++)
					       {
						       flag=2;
						       if(strcmp(str,contacts.email)==0)
						       {
							       flag=3;
							       break;
						       }

					       }
					       if(flag==3)
					       {
						       printf("The entered email already exist Try again!!\n");
						       goto n3;
					       }
					       for(int i=0;str[i];i++)
					       {
						       if(str[i]=='@')
						       {
							       if(strstr(str,".com")!=NULL)
							       {


								       if(str[i+1]=='.')
								       { 
									       printf("Enter the correct format of email\n");
									       goto n3;
								       }
							       }
						       }
					       }
					       strcpy(contacts.email,str);
					       break;

					case 3:
n2:
					       printf("Enter the new mobile:");
					       scanf(" %[^\n]",str4);
					       //fseek(fdata,2,SEEK_SET);
					       int flag;
					       for(int i=0;i<count;i++)
					       {
						       flag=0;
						       if(strcmp(str4,contacts.mobile)==0)
						       {
							       flag=1;
							       break;

						       }

					       }
					       if(flag==1)
					       {
						       printf("The entered number already exist Try again!!\n");
						       goto n2;
					       }
					       int num=strlen(str4);
					       if(num>10||num<10)
					       {
						       printf("Enter the correct mobile number!!\n");
						       goto n2;
					       }
					       strcpy(contacts.mobile,str4);
					       break;

					case 4:   
					       printf("Enter the new address:");
					       scanf(" %[^\n]",new_address);
					       strcpy(contacts.address,new_address);
					       break;

					case 5: var1=0;
						break;
				}

			}
		}
		fprintf(ftemp,"%s,%s,%s,%s\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
	}
	if(flag==0)
	{
		printf("Enter the valid phone number!");
	}
	fclose(fdata);
	fclose(ftemp);
	fdata=fopen("data.csv","w");
	ftemp=fopen("temp.csv","r");
	copy(fdata,ftemp);
	fclose(fdata);
	fclose(ftemp);

}
void delete_contacts()
{
	int flag=0;
	struct data contacts;
	char new_mobile[20];
	int count=0;
	FILE *fdata=fopen("data.csv","r");
	FILE *ftemp=fopen("temp.csv","w");
	printf("Enter the new mobile number :");
	scanf(" %[^\n]",new_mobile);
	fprintf(ftemp," %c",'\n');
	fscanf(fdata,"%d\n",&count);
	while(!feof(fdata))
	{
		for(int i=0;i<count;i++)
		{
			fscanf(fdata,"%[^,],%[^,],%[^,],%[^\n]\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
			if(strcmp(new_mobile,contacts.mobile)==0)
			{
				printf("Data deleted successfully!\n");
				flag=1;
				continue;
			}
			else
			{
				fprintf(ftemp,"%s,%s,%s,%s\n",contacts.name,contacts.mobile,contacts.email,contacts.address); 
			}
		}
	}
	if(flag==0)
	{
		printf("Enter the valid phone number!");
		count=count+1;
	}

	rewind(ftemp);
	fprintf(ftemp,"%d\n",count-1);
	fclose(fdata);
	fclose(ftemp);
	fdata=fopen("data.csv","w");
	ftemp=fopen("temp.csv","r");
	copy(fdata,ftemp);
	fclose(fdata);
	fclose(ftemp);
}

