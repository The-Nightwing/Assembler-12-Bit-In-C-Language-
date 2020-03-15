#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

void check (char) ;  
void multi_line () ;   
void single_line () ;

FILE *fold , *fnew;

struct mnemonics {
    char name[20];
    char opcode[20];
};
struct mnemonics op[14]={

      {"CLA","0000"},
      {"LAC","0001"},
      {"SAC","0010"},
      {"ADD","0011"},
      {"SUB","0100"},
      {"BRZ","0101"},
      {"BRN","0110"},
      {"BRP","0111"},
      {"INP","1000"},
      {"DSP","1001"},
      {"MUL","1010"},
      {"DIV","1011"},
      {"STP","1100"}

};



int find(char finder[20])
{
    int index=-1;
    for(int i=0;i<14;i++)
    {
        if(strcmp(finder,op[i].name)==0)
        {
            index=i;
        }
    }
    return index;
}

int findingOp(char find[20])
{
   int index=-1;
    for (int i = 0; i < 14; i++)
    {
        if (strcmpi(op[i].name,find)==0)
        {
            index=0;
            return index;
        }
        else continue;
        
    }
return index;
}

int isNumber(char s[20])
{
    int index1=-1;
    for (int i=0; s[i]!= '\0'; i++) 
    { 
       if (isalpha(s[i]) != 0) 
           { 
               index1=0;
           return index1;
           }
        else continue;
    } 
    return index1;
}

int findiComma(char findi[20])
{
    for(int i=0;findi[i]!='\0';i++)
    {
        if(findi[i]==',')
          return 0;
    }
    return -1;
}


void check(char c)
{
    char d;

    if( c == '/')  
    {
        if((d=fgetc(fold))=='*')  
         multi_line(); 

        else if( d == '/')  
        {
          single_line();

        }
        else
        {
            fputc(c,fnew);
            fputc(d,fnew);
        }
    }
    else
        fputc(c,fnew);
}

void single_line()
{
 char c;
    while((c=fgetc(fold))!=EOF)  
    {
        if(c=='\n')   
            return;

    }
}

void multi_line()
{
 char a,b;
    while((a=fgetc(fold))!=EOF)   
    {
        if(a=='*')  
        {
            b=fgetc(fold); 
            if(b=='/')  
                return;
        }
 }
}

int main()
{
    char word[20];
    int lc;
    int c1=-1;
    int c2=0;
    int time=0;
    int sad=0;
    int sad1=0;
    int address=0;
    FILE *f1,*f2,*f3,*f4,*f5,*f6,*f7;
    FILE *fin,*fin1,*fin2,*fin3,*fout,*fin4;
    f2=fopen("symtab.txt","w");
    f3=fopen("labtab.txt","w");
    f4=fopen("literal.txt","w");
    f6=fopen("symtab2.txt","w");
    fout=fopen("ObjectFile.txt","w");
    f7=fopen("ErrorFile.txt","w");

     char c;
    fold = fopen ("test1.txt","r") ;   
    fnew= fopen ("mynewfile.txt","w") ;   

    while((c=fgetc(fold))!=EOF)     
        {check(c);}   
    fclose(fold);
    fclose(fnew);
    f1=fopen("mynewfile.txt","r");


    while(fscanf(f1,"%s",word) != EOF)
    {  
        int n;
        n=findingOp(word);
        if(n==-1)
        {
            char temp[20];
            strcpy(temp,word);
            fscanf(f1,"%s",word);
            if(strcmp(word,op[0].name)==0)
            {
                fprintf(f3,"%s",temp);
                fprintf(f3,"%s"," ");
                fprintf(f3,"%d",address);
                fprintf(f3,"\n");
                address++;
                goto repeat;
            }
            if(strcmp(word,op[12].name)==0)
            {
                fprintf(f3,"%s",temp);
                fprintf(f3,"%s"," ");
                fprintf(f3,"%d",address);
                fprintf(f3,"\n");
                address++;
                goto repeat;
            }
            //////////////////////////////////
            
            ///////////////////////////////
            if(findingOp(word)!=-1)
            {
             fprintf(f3,"%s",temp);
            fprintf(f3,"%s"," ");
            fprintf(f3,"%d",address);
            fprintf(f3,"\n");
            fscanf(f1,"%s",word);
            if(findiComma(word)==0)
            {    
                fprintf(f7,"%s","Fatal Error,More than One Operand Passed");
                printf("Fatal Error,More than One Operand Passed");
                printf("\n");
                exit(0);
            }

            if(isNumber(word)!=-1)
            {
                fprintf(f2,"%s",word);
                fprintf(f2,"%s"," ");
                fprintf(f2,"%d",sad);
                fprintf(f2,"\n");
                sad++;
            }
            else
            {  
            if(word[0]=='=')
            {

            fprintf(f4,"%d",word);
            fprintf(f4,"%s"," ");
            fprintf(f4,"%d",sad1);
            fprintf(f4,"\n");
            sad1++;
            }
            else{
            int lc1=atoi(word);
            if(lc1>=256)
            {
                fprintf(f7,"%s","Memory Address Out of Bounds(>256)");
                fprintf(f7,"\n");
                printf("Memory Address Out of Bounds(>256)");
                exit(0);
            }
            fprintf(f4,"%d",lc1);
            fprintf(f4,"%s"," ");
            fprintf(f4,"%d",sad1);
            fprintf(f4,"\n");
            sad1++;
            }
            }
            }
            
            else 
            {
                fprintf(f7,"%s","Given Opcode doesn't exist");
                fprintf(f7,"%s",":");
                fprintf(f7,"%s",temp);
                fprintf(f7,"\n");
                time--;
                address--;
                goto repeat;
                }
        }
        else
        {
             if(strcmp(word,op[0].name)==0)
            {
                goto repeat;
            }
            else if(strcmp(word,op[12].name)==0)
            {
                c1++;
                goto repeat;
            }
            else{
              fscanf(f1,"%s",word);
              if(findiComma(word)==0)
            {
                fprintf(f7,"&s","Fatal Error,More than One Operand Passed.");
                printf("%s","Fatal Error,More than One Operand Passed.");
                printf("\n");
                exit(0);
            }
                if(isNumber(word)!=-1)
                {
                   fprintf(f2,"%s",word);
                   fprintf(f2,"%s"," ");
                   fprintf(f2,"%d",sad);
                   fprintf(f2,"\n");
                   sad++;
                       }
               else
               {
                    if(word[0]=='=')
                 {
                    for(int i=0;word[i]!='\0';i++)
                    {
                        fprintf(f4,"%c",word[i]);
                    }
                    
                    fprintf(f4,"%s"," ");
                    fprintf(f4,"%d",sad1);
                    fprintf(f4,"\n");
                    sad1++;
                }
                else{
                   int lc2=atoi(word);
                   if(lc2>=256)
                {
                fprintf(f7,"%s","Memory Out of Bounds(>256)");
                fprintf(f7,"\n");
                printf("Memory Out of Bounds(>256)");
                exit(0);
                 }
                    fprintf(f4,"%d",lc2);
                    fprintf(f4,"%s"," ");
                    fprintf(f4,"%d",sad1);
                    fprintf(f4,"\n");
                    sad1++;
               }
               }
        }
    }
        //address++;
        repeat:
            address++;
            c2++;
            time++;
    }
    fclose(f2);
    f5=fopen("symtab.txt","r");
    fin2=fopen("symtab2.txt","r");
    
    int number=0;
   while(fscanf(f5,"%s",word) != EOF)
   {
       fprintf(f6,"%s",word);
       fprintf(f6,"%s"," ");
       fscanf(f5,"%s",word);
       int n1=atoi(word);
       fprintf(f6,"%d",n1+time);
       fprintf(f6,"\n");
       number++;
    }
    fclose(f4);
    FILE *ff,*fff;
    fff=fopen("literal.txt","r");
    ff=fopen("literal2.txt","w");
      char new[20];
        while(fscanf(fff,"%s",new)!=EOF)
        {
            fprintf(ff,"%s",new);
            fprintf(ff,"%s"," ");
            fscanf(fff,"%s",new);
            int n22=atoi(new);
            fprintf(ff,"%d",n22+number+time);
            fprintf(ff,"\n");
                    }

    
    fclose(ff);
    fclose(fff);
    

    if(c1==-1)
    {
        fprintf(f7,"%s","No STP Command Found");
        fprintf(f7,"\n");
    }
    fclose(f3);
    ;
    fclose(f5);
    fclose(f1);
    fclose(f6);
    fin=fopen("mynewfile.txt","r");
    fin1=fopen("labtab.txt","r");
    fin3=fopen("literal2.txt","r");
   
     while(fscanf(fin,"%s",word)!=EOF)
     {
         int n;
        n=findingOp(word);
        if(n==-1)
        {
            fscanf(fin,"%s",word);
            if(strcmp(word,op[0].name)==0)
            {
                fprintf(fout,"%s",op[0].opcode);
                fprintf(fout,"\n");
                goto repeat2;
            }
            if(strcmp(word,op[12].name)==0)
            {
                fprintf(fout,"%s",op[12].opcode);
                fprintf(fout,"\n");
                goto repeat2;
            }
            if(findingOp(word)!=-1)
            {
            int f=find(word);
            if(f!=-1)
            {
            fprintf(fout,"%s",op[f].opcode);}
            fscanf(fin,"%s",word);

            if(isNumber(word)!=-1)
            { 
                char tempr1[20];
                ///////////////
                  while(fscanf(fin1,"%s",tempr1)!=EOF)
                  {
                    if(strcmp(word,tempr1)==0)
                    {
                       fscanf(fin1,"%s",tempr1);
                        int n=atoi(tempr1);
        int binaryNum[1000] = {};
        int i = 0;
        char ch;
        while (n > 0) 
        {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
        }
        int bits = 8;
        if ( i > 8 )
            bits = 8*((i + 7)/8);

        for (int j = bits-1; j >= 0; j--)
        {
            fprintf(fout,"%d",binaryNum[j]);
        }
                        fprintf(fout,"\n");
                    goto repeat2;
                  }
                }
                rewind(fin1);
                //////////////
                while(fscanf(fin2,"%s",tempr1)!=EOF)
                {
                    if(strcmp(word,tempr1)==0)
                    {
                        fscanf(fin2,"%s",tempr1);
                        int n=atoi(tempr1);
        int binaryNum[1000] = {};
        int i = 0;
        char ch;
        while (n > 0) 
        {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
        }
        int bits = 8;
        if ( i > 8 )
            bits = 8*((i + 7)/8);

        for (int j = bits-1; j >= 0; j--)
        {
            fprintf(fout,"%d",binaryNum[j]);
        }
                        fprintf(fout,"\n");
                    break;
                  }
                }
                rewind(fin2);
            }
            else
            {  
            if(word[0]=='=')
            {
                char temper[20];
                    while(fscanf(fin3,"%s",temper)!=EOF)
                      {
                          if(strcmp(word,temper)==0)
                          {
                              fscanf(fin3,"%s",temper);
                              int q3=atoi(temper);
                              if(q3>=256)
                             {
                fprintf(f7,"%s","Memory Address Out of Bounds(>256)");
                fprintf(f7,"\n");
                exit(0); }
        int binaryNum2[1000] = {};
        int i2 = 0;
        char ch2;
        while (q3 > 0) {
        binaryNum2[i2] = q3 % 2;
        q3 = q3 / 2;
        i2++;
        }
        int bits2 = 8;
        if ( i2 > 8 )
            {bits2 = 8*((i2 + 7)/8);}

        for (int j = bits2-1; j >= 0; j--)
        {
         fprintf(fout,"%s",binaryNum2[j]);
        }
                 fprintf(fout,"\n");
                 goto repeat2;
                              
                          }
                      }
                      rewind(fin4);
                
              }
         //
    else
    {
         int lc1=atoi(word);
          if(lc1>=256)
                {
                fprintf(f7,"%s","Memory Address Out of Bounds(>256)");
                fprintf(f7,"\n");
                exit(0);
                 }
        char str3[20];
        char str13[20];
        char *s_ptr13 = str13;
        int binaryNum3[1000] = {};
        int i3 = 0;
        char ch3;
        while (lc1 > 0) {
        binaryNum3[i3] = lc1 % 2;
        lc1 = lc1 / 2;
        i3++;
        }
        int bits3 = 8;
        if ( i3 > 8 )
           { bits3 = 8*((i3 + 7)/8);}

        for (int j = bits3-1; j >= 0; j--)
        {
        fprintf(fout,"%s",binaryNum3[j]);
        }
             fprintf(fout,"\n");
            }
        
            }
     }//
            else 
            {
                /*fprintf(f7,"%s","Given Opcode doesn't exist");
                fprintf(f7,"%s",":");
                fprintf(f7,"%s",temp);
                fprintf(f7,"\n");*/
                goto repeat2;
                }
         
        }
        else
        {
             if(strcmp(word,op[0].name)==0)
            {
                fprintf(fout,"%s",op[0].opcode);
                fprintf(fout,"\n");
                goto repeat2;
            }
            if(strcmp(word,op[12].name)==0)
            {
                fprintf(fout,"%s",op[12].opcode);
                fprintf(fout,"\n");
                goto repeat2;
            }
            else {
              //fscanf(fin,"%s",word);
              int ind=find(word);
              if(ind!=-1){
              fprintf(fout,"%s",op[ind].opcode);}
              fscanf(fin,"%s",word);
                if(isNumber(word)!=-1)
                {

                  ////////////////////
                    char tempr1[20];
                  while(fscanf(fin1,"%s",tempr1)!=EOF)
                  {
                    if(strcmp(word,tempr1)==0)
                    {
                       fscanf(fin1,"%s",tempr1);
                        int n=atoi(tempr1);
        int binaryNum[1000] = {};
        int i = 0;
        char ch;
        while (n > 0) 
        {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
        }
        int bits = 8;
        if ( i > 8 )
            bits = 8*((i + 7)/8);

        for (int j = bits-1; j >= 0; j--)
        {
            fprintf(fout,"%d",binaryNum[j]);
        }
                        fprintf(fout,"\n");
                    goto repeat2;
                  }
                }
                rewind(fin1);
                  ///////////////
                    char temp4[20];
                   while(fscanf(fin2,"%s",temp4)!=EOF)
                   {
                       if(strcmp(word,temp4)==0)
                       {
                           fscanf(fin2,"%s",temp4);
                           int nn = atoi(temp4);
        
        int binaryNumn[1000] = {};
        int in = 0;
        char chn;
        while (nn > 0) 
        {
        binaryNumn[in] = nn % 2;
        nn = nn / 2;
        in++;
        }
        int bitsn = 8;
        if ( in > 8 )
            bitsn = 8*((in + 7)/8);

        for (int jn = bitsn-1; jn >= 0; jn--)
        {
             fprintf(fout,"%d",binaryNumn[jn]);
        
        } 
               fprintf(fout,"\n");

                 break;
                 
                           }

                   }
                   rewind(fin2);
               }
               else
               {
                    if(word[0]=='=')
                 {///////////////
                     char temper[20];
                    while(fscanf(fin3,"%s",temper)!=EOF)
                      {
                          if(strcmp(word,temper)==0)
                          {
                              fscanf(fin3,"%s",temper);
                              int q3=atoi(temper);
                               if(q3>=256)
                {
                fprintf(f7,"%s","Memory Address Out of Bounds(>256)");
                fprintf(f7,"\n");
                exit(0);
                 }
        int binaryNum2[1000] = {};
        int i2 = 0;
        char ch2;
        while (q3 > 0) {
        binaryNum2[i2] = q3 % 2;
        q3 = q3 / 2;
        i2++;
        }
        int bits2 = 8;
        if ( i2 > 8 )
            bits2 = 8*((i2 + 7)/8);

        for (int j = bits2-1; j >= 0; j--)
        {
         fprintf(fout,"%d",binaryNum2[j]); 
        }
                 fprintf(fout,"\n");
                 goto repeat2;
                          }
                          
                      }
                      rewind(fin4);

                     ////////////////////
               }
        else{
        int lc1=atoi(word);
         if(lc1>=256)
                {
                fprintf(f7,"%s","Memory Address Out of Bounds(>256)");
                fprintf(f7,"\n");
                exit(0);
                 }
        int binaryNum3[1000] = {};
        int i3 = 0;
        char ch3;
        while (lc1 > 0) {
        binaryNum3[i3] = lc1 % 2;
        lc1 = lc1 / 2;
        i3++;
        }
        int bits3 = 8;
        if ( i3 > 8 )
            bits3 = 8*((i3 + 7)/8);

        for (int j = bits3-1; j >= 0; j--)
        {
        fprintf(fout,"%d",binaryNum3[j]);
        }
                     fprintf(fout,"\n");
               }
            }
     }
        }
    //
    repeat2:
       c2++;
}

if(c1==-1)
{
    fprintf(fout,"%s",op[12].opcode);
    fprintf(fout,"\n");
}

return 0;

}


