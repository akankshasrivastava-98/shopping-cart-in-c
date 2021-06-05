#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product
{
    int id;
    char name[20];
    int price;
    int qty;

};
struct Bill
{
    int pid;
    char pname[20];
    int pprice;
};


int getID();//rak
void manageProduct();//anu
void purchaseProduct();//rak
void generateBill();//aka
void addProduct();//anu
void displayProduct();//anu
struct Product findProduct(int id);//aka
void updateProduct(int id,int qty);//aka
void choice();//rak

int total=0;

int main()
{
    int ch1;

    system("clear");
    while (1)
    {
        system("clear");
        printf("Welcome to shopping\n\n ");
        printf("1.Seller\n\n2. Customer\n\n3.Exit");
        printf("\nEnter your choice:\n");
        scanf("%d",&ch1);
        switch(ch1)
        {
            case 1: printf("\nYou can update your products");
                    manageProduct();
                    break;
            case 2: printf("\n\nWelcome to the store\n\n");
                    choice();
                    break;

            case 3: exit(0);
                    break;
        }



    }
    return 0;
}

void choice()

{
        system("clear");
        int ch;
        printf("1. Add item to your cart\n\n");
        printf("2. Generate Bill\n\n");
        printf("3. back\n\n");

        printf("Please enter your choice:\n");
        scanf("%d",&ch);

        switch(ch)
        {

            case 1: purchaseProduct();
                    break;
            case 2: generateBill();
                    break;

           // case 3: deleteProduct();
             //       break;

            case 3: exit(0);
        }
        getchar();
}
int getID()
{
    FILE *fp;
    int value=0;
    fp=fopen("prodid.txt","r");

    if(fp==NULL)
    {
        fp=fopen("prodid.txt","w");
        fprintf(fp,"%d",0);
        fclose(fp);
        fp=fopen("prodid.txt","r");
    }
    fscanf(fp,"%d",&value);
    fclose(fp);

    fp=fopen("prodid.txt","w");
    fprintf(fp,"%d",value+1);
    fclose(fp);

    return(value+1);

}

void manageProduct()
{
    int ch;
    int back=0;
    while(1)
    {
        system("clear");
        printf("=======================================================\n\n");
        printf("\t\tWelcome to product management System\n\n");
        printf("=======================================================\n\n");
        printf("1. Add new procuct\n\n");
        printf("2. Display all products\n\n");
        printf("3. Back\n\n");
        printf("=======================================================\n\n");
        printf("Please enter your choice:");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1: addProduct();
                    break;
            case 2: displayProduct();
                    getchar();
                    break;
            case 3: back=1;
                    break;

        }

        if(back==1)
            break;
        else
            getchar();

    }
}

void addProduct()
{
    FILE *fp;
    struct Product t1;
    system("clear");

    fp=fopen("product.dat","ab");

    t1.id=getID();

    printf("\nEnter the product name:");
    scanf("%s",t1.name);
    printf("\nEnter product price: ");
    scanf("%d",&t1.price);
    printf("\nEnter product quantity:");
    scanf("%d",&t1.qty);

    fwrite(&t1,sizeof(t1),1,fp);

    fclose(fp);


}

void displayProduct()
{
    FILE *fp;
    struct Product t;


    system("clear");

    printf("\n================================================================\n\n");
    printf("\t\tProduct Details\n\n");
    printf("\n================================================================\n\n");

    printf("ID\t\tName\t\tQty\t\tPrice\n\n");
    fp= fopen("product.dat","rb");


    while(1)
    {
        fread(&t,sizeof(t),1,fp);

        if(feof(fp))
        {
            break;
        }

        printf("%d\t\t",t.id);
        printf("%s\t\t",t.name);
        printf("%d\t\t",t.qty);
        printf("%d\t\t\n",t.price);




    }
    printf("\n================================================================\n\n");
    fclose(fp);

}

void purchaseProduct()
{
    char ch1,ch2;
    int id;
    system("clear");
    printf("\n================================================================\n\n");

    printf("\t\tWelcome Product Management Sysytem\n\n");

    while(1)
    {
        displayProduct();
        //__fpurge(stdin);

        printf("\n\n\nDo you want to purchase[Y/N]:");
        scanf("%c",&ch1);
        getchar();


        if(ch1=='Y')
        {
            FILE *fp;
            struct Bill t1;
            struct Product t2;

            fp=fopen("bill.dat","ab");

            printf("\n\nEnter the product ID to purchase:");
            scanf("%d",&id);

            t2=findProduct(id);

            t1.pid=t2.id;
            strcpy(t1.pname,t2.name);
            t1.pprice=t2.price;

            fwrite(&t1,sizeof(t1),1,fp);

            fclose(fp);



        }
        getchar();
      //  __fpurge(stdin);
        printf("\n\n\nDo you want to continue[Y/N]:");
        scanf("%c",&ch2);

        if(ch2=='N')
        {
            break;
        }
        getchar();
    }

}

struct Product findProduct(int id)
{
    FILE *fp;
    struct Product t;

    fp=fopen("product.dat","rb");

    while(1)
    {
        fread(&t,sizeof(t),1,fp);

        if(feof(fp))
        {
            break;
        }
        if(t.id==id)
        {
            updateProduct(id,t.qty-1);
            break;
        }
    }
    fclose(fp);
    return t;
}


void updateProduct(int id,int qty)
{
    FILE *fp,*fp1;
    struct Product t;
    int found=0;

    fp=fopen("product.dat","rb");
    fp1=fopen("temp.dat","wb");

    while(1)
    {
        fread(&t,sizeof(t),1,fp);

        if(feof(fp))
        {
            break;
        }
        if(t.id==id)
        {
            found=1;
            t.qty=qty;
            fwrite(&t,sizeof(t),1,fp1);
        }
        else
        {
            fwrite(&t,sizeof(t),1,fp1);
        }

    }
    fclose(fp);
    fclose(fp1);

    if(found==0)
    {
        printf("Sorry Record Not Found");
    }
    else
    {
        fp=fopen("product.dat","wb");
        fp1=fopen("temp.dat","rb");
        while(1)
        {
            fread(&t,sizeof(t),1,fp1);

            if(feof(fp1))
            {
                break;
            }
            fwrite(&t,sizeof(t),1,fp);
        }
    }
    fclose(fp);
    fclose(fp1);
}

void generateBill()
{
    FILE *fp;
    struct Bill t;
    //int id, found=0;
    char ch1;
   // int brel=0;
   // char billname[20];

    system("clear");

    fp=fopen("bill.dat","rb");

    printf("\n================================================================\n\n");
    printf("\t\tBill Details \n\n");
    printf("\n================================================================\n\n");

    printf("Pro-ID\tPro-Name\tPro-Price\n\n");

    while(1)
    {
        fread(&t,sizeof(t),1,fp);

        if(feof(fp))
        {
            break;
        }
        printf("%d\t",t.pid);
        printf("%s\t",t.pname);
        printf("%d\t\t\t\n",t.pprice);
        total=total+t.pprice;
     }

    printf("\n\n================>>>>>>>>>>> Total Bill [Rs. : %d]\n\n",total);

    fclose(fp);

    if(total!=0)
    {



        printf("\n\n DO YOU WANT TO EMPTY YOUR CART [Y/N]:");
        scanf(" %c",&ch1);


        if(ch1==89)
        {

            remove("bill.dat");

        }
    }

    else
    {
        printf("\n\nSorry NO item selected\n\n");

    }



}

