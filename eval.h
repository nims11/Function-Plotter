#include<iostream>
#include<cstring>
#include<cmath>
#include<stdio.h>
using namespace std;
char expr[100];
float var;
float str2Float(char str[100],int start,int end)
{
      if(start==end && str[start]=='x')
      return var;
      int decimal=-1;
      float result=0;
      if(str[start]!='-')
      {
      for(int i=start;i<=end;i++)
      {
              if(str[i]=='.')
              decimal=i;
      }
      if(decimal==-1)
      {
                for(int i=end;i>=start;i--)
                result+= ((int)str[i]-48)*pow(10,(float)(end-i));
      }else
      {
           int tmp=0;
           for(int i=decimal-1;i>=start;i--)
           result+= ((int)str[i]-48)*pow(10,(float)(decimal-i-1));
           for(int i=end;i>decimal;i--)
           tmp += ((int)str[i]-48)*pow(10,(float)(end-i));
           result += tmp/pow(10,(float)(end-decimal));
      }

      return result;
      }else
      return -1*str2Float(str,start+1,end);
}

int isNum(char ch)
{
    if(ch>=48 && ch<=57 || ch==46 || ch==45 || ch=='x')
    return 1;

    return 0;
}

float boperation(float o1,float o2,char o)
{
      switch(o)
      {
             case '^': return pow(o1,o2);
             case '/': return o1/o2;
             case '*': return o1*o2;
             case '+': return o1+o2;
      }
}

float mod(float o1)
{
      if(o1<0)
      return -1*o1;
      return o1;
}

float uoperation(float o1,int o)
{
      switch(o)
      {
               case 0: return sin(o1);
               case 1: return cos(o1);
               case 2: return tan(o1);
               case 3: return 1/tan(o1);
               case 4: return 1/cos(o1);
               case 5: return 1/sin(o1);
               case 6: return mod(o1);
               case 7: if(o1>0)
               return log(o1);
               else
               return 1000;
               case 8: return floor(o1);
               case 9: return ceil(o1);
               case 10:if(mod(o1)<=1) return asin(o1);
               else return 1000;
               case 11:if(mod(o1)<=1) return acos(o1);
               else return 1000;
               case 12:return atan(o1);
      }
}

void solveUnary(char in[100],int size)
{
    char unary[][6]={"sin","cos","tan","cot","sec","cosec","mod","log","floor","ceil","asin","acos","atan"};
    int unasize=13;
    char tmp[6];
    int count=0;
    for(int i=0;i<size;i++)
    {
       if(in[i]>=97 && in[i]<=122 && in[i]!='x')
       {
          tmp[count++]=in[i];
          tmp[count]='\0';
       }

       if(in[i]>=97 && in[i]<=122 && (isNum(in[i+1]) || in[i+1]=='-'))
       {
          for(int j=0;j<unasize;j++)
          {
             if(!strcmp(unary[j],tmp))
             {
               int q;
               for(q=i+1;isNum(in[q+1]) && in[q+1]!='-';q++);
               float o1=str2Float(in,i+1,q);
               float result=uoperation(o1,j);
               char* str = new char[30];
               sprintf(str, "%.2f", result );
               int strsize=strlen(str);
               int start=i+1-strlen(unary[j]);
               size=strlen(in);
               int end;
               for(end=start+strlen(unary[j]);isNum(in[end+1]) && in[end+1]!='-';end++);
               for(int m=start;m<size;m++)
               in[m]=in[end+1+m-start];
               size=strlen(in);

               for(int m=start;m<start+strsize;m++)
               {
                for(int n=size;n>m;n--)
                in[n]=in[n-1];

                in[m]=str[m-start];
                size++;
                in[size]='\0';
               }
               break;

              }
        }
        count=0;
     }
  }
}

float eval(char in[100])
{
    char ch;
    int size=strlen(in);
    for(int i=0;i<size;i++)
    {
      if(in[i]=='-' && in[i+1]=='-')
      {
         in[i]='+';
         for(int j=i+1;j<=size;j++)
         in[j]=in[j+1];
         i--;
         size--;
      }
    }
   size=strlen(in);
   solveUnary(in,size);
   char pref[4]={'^','/','*','+'};
   for(int i=0;i<size;i++)
   {
     if(in[i]=='-' && isNum(in[i-1]) && (in[i-1]<97 || in[i-1]>122 || in[i-1]=='x'))
     {
      for(int j=size;j>i;j--)
      in[j]=in[j-1];
      in[i]='+';
      size++;
      i++;
      in[size]='\0';
     }
   }
   int noOpr=0,noOpd=0;
   char operators[100][2];
   int start=-1,end=-1,mode=-1;
   float opd[100];
   for(int i=0;i<size;i++)
   {
      if(isNum(in[i]))
      {
       if(start==-1)
       start=i,mode=0;
       if(!isNum(in[i+1]) && mode==0)
       {
         end=i;
         opd[noOpd++]=str2Float(in,start,end);
         mode=start=end=-1;
       }
      }else
      {
         operators[noOpr][0]=in[i];
         operators[noOpr++][1]=noOpr-1;}
      }
      for(int i=0;i<4;i++)
      {
         for(int j=0;j<noOpr;j++)
         if(operators[j][0]==pref[i])
         {
            float *o1,*o2;
            int flag=1;
            int t=0,tmp;
            while(flag)
            {
                if(t==operators[j][1]+2)
                {
                   opd[t-1]=boperation(opd[t-1],opd[t],pref[i]);
                   for(int w=t;w<noOpd-1;w++)
                   opd[w]=opd[w+1];
                   for(int w=j+1;w<noOpr;w++)
                   operators[w][1]--;
                   noOpd--;

                   flag=0;
                 }
                 t++;
            }
         }
     }
     return opd[0];
}

void divideSubFunc(int start,int end)   //gets the start and end of the function
{
    int start2=-1,end2=-1;          //start and end of the sub-function
    int count=0;
    for(int i=start+1;i<end;i++)
    {
        if(expr[i]=='(')
        {start2=i;count++;
        break;}
    }

    if(start2!=-1)
    {
        for(int i=start2+1;i<end;i++)   // search for the end of the sub function
        {
            if(expr[i]=='(')
            count++;
            if(expr[i]==')')
            {
                 count--;
                 if(count==0)
                 {
                   end2=i;
                   break;
                 }
            }
        }
    }

    if(start2!=-1 && end2!=-1)
    divideSubFunc(start2,end2);
    if(start2==-1 && end2==-1)  //if there is no sub function
    {
       char subin[100];
       int subsize=end-start-1;
       for(int i=start+1;i<end;i++)
       subin[i-start-1]=expr[i];
       subin[end-start-1]='\0';
       char* str = new char[30];
       float x=eval(subin);
       sprintf(str, "%.2f", x );
       int strsize=strlen(str);
       int size=strlen(expr);
       for(int i=start;i<size;i++)
       expr[i]=expr[end+1+i-start];
       size=strlen(expr);
       for(int i=start;i<start+strsize;i++)
       {
          for(int j=size;j>i;j--)
          expr[j]=expr[j-1];

          expr[i]=str[i-start];
          size++;
       }
       expr[size]='\0';
    }

}

float evalu(char exp[100],float x)
{
  var=x;    // value of x in exp
  strcpy(expr,exp); //  just for ease
  while(expr[0]=='(')   // enclosing the whole exp in a '()'.
  divideSubFunc(0,strlen(expr)-1);  // recursively divides the main function into subfunction
  return str2Float(expr,0,strlen(expr)-1);
}
