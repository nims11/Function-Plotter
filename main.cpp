/*
Author          NIMESH GHELANI (nims)
Project Name    Function Plotter
Description     Enter a Mathematical function and the program plots it in a cartesian plane

*/

#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <ctype.h>
#include "eval.h"  //evaluates mathematical expressions in a string
using namespace std;
int GraphDriver = DETECT;    //requests the compiler for auto-detection of graphics driver
int GraphMode;
void func_gen(char expr[100],float precision,int color); //the main plotter
void drawAxis();    //draws the x and y axis
int xres=1000;      //xresolution
int yres=700;       //yresolution
int xby2=xres/2;
int yby2=yres/2;
int zoom_factor=10,xshift=0,yshift=0;
class function{         //class function whose objects are individual plots
private:
char expression[100];   //the mathematical function represented by the plot
int color;      //color of the function curve
float precision;    //the difference between consecutive values of x for which f(x) is evaluated
public:
int active;         //if plotted in the graph
function()
{
    precision=0.02;
    active=0;
}
char * exprOut()
{
    return expression;
}
void getexpr(); //gets expression
void incPre()   //increases precision(weird, but actually decreases the value of the variable)
{
    precision /= 5;
}
void decPre()
{
    precision *= 5;
}
void draw()     // plots f(x)
{
    active=1;
    char tmp[100];
    strcpy(tmp,expression);
    func_gen(tmp,precision,color);
}
void reset()
{
    precision=0.02;
}
void erase()        //erases f(x), basically replots the function with the backgraound color.
{
    active=0;
    char tmp[100];
    strcpy(tmp,expression);
    func_gen(tmp,precision,0);
    reset();
}
}plot[10];
void function::getexpr()
{
    cout<<"Enter A valid Mathematical function - ";

    cin>>expression;
    int size=strlen(expression);
    for(int i=size;i>0;i--)
    expression[i]=expression[i-1];
    expression[0]='(';
    expression[++size]=')';
    expression[++size]='\0';
    cout<<"Enter a Color Code - ";
    cin>>color;
}
void getStatus();      //outputs the status of all the objects of class function
void graphManip();
int main()
{
    initwindow (xres,yres,"Function Plotter By Nimesh Ghelani");    //initialises the graph window
setbkcolor(0);  //sets bgcolor
cleardevice();
drawAxis();
    int count=0;
    char ch;
    system("cls");
    cout<<"2-d function plotter by NIMESH GHELANI (nims)"<<endl;
    cout<<"Function evaluator by NIMESH GHELANI (nims)"<<endl<<endl;
    cout<<"Status :\n";
    (count==0)?cout<<"No function plotted!!\n":cout<<count+1<<" function(s) currently plotted!!\n";
    do{
    system("cls");
    cout<<"\n1. Add a plot\n";  //done
    cout<<"2. Erase a plot\n";  //done
    cout<<"3. Get Status\n";    //done
    cout<<"4. Reset the Graph\n";   //done
    cout<<"5. Redraw\n";            //done
    cout<<"6. Graph Manipulation Mode\n";   //pending
    cout<<"7. Manipulate Individual Plot\n";    //pending
    cout<<"x. Exit\nChoice - ";             //done
    cin>>ch;
    switch(ch)
    {
        case '1':
        for(int i=0;i<10;i++)
        {
            if(plot[i].active==0)
            {
                plot[i].getexpr();
                plot[i].draw();
                break;
            }
            if(i==9)
            cout<<"No Available Slots! erase any other plot first.\n";
        }
        break;

        case '2':
        getStatus();
        cout<<"Select a plot you want to erase-\n";
        int choice;
        cin>>choice;
        if((choice>=0 && choice<10)&&(plot[choice].active))
        plot[choice].erase();
        else cout<<"invalid choice!!\n";

        break;
        case '3':
        getStatus();
        cout<<"Press Any Key to Continue...";
        getch();
        break;
        case '4':
        for(int i=0;i<10;i++)
        {plot[i].active=0;plot[i].reset();}
        cleardevice();
        drawAxis();
        zoom_factor=10;
        break;
        case '5':
        cleardevice();
        drawAxis();
        for(int i=0;i<10;i++)
        if(plot[i].active)plot[i].draw();
        break;
        case '6':
        graphManip();
        break;
    }
    }while(tolower(ch)!='x');
    closegraph();
}
void graphManip()
{
    cout<<"\nGraph Manipulation Options - \n";
    cout<<"ON THE GRAPH WINDOW-\npress '+' or '-' to zoom in/out\npress 'e' to increase precision of all the plots and 'q' to decrease precision of all the plots\n";
    cout<<"press x to exit graph manipulation mode\n";
    char ch;
    while(ch!='x'&&ch!='X')
    {
        ch=getch();
        switch(ch)
        {
            case '+':
            zoom_factor*=2;
            cleardevice();
            drawAxis();
            for(int i=0;i<10;i++)
            if(plot[i].active)
            plot[i].draw();
            break;

            case '-':
            zoom_factor/=2;
            cleardevice();
            drawAxis();
            for(int i=0;i<10;i++)
            if(plot[i].active)
            plot[i].draw();
            break;

            case 'e':
            cleardevice();
            drawAxis();
            for(int i=0;i<10;i++)
            {plot[i].incPre();
            if(plot[i].active)
                plot[i].draw();}
            break;

            case 'q':
            cleardevice();
            drawAxis();
            for(int i=0;i<10;i++)
            {plot[i].decPre();
            if(plot[i].active)
                plot[i].draw();}
            break;
        }
    }

}
void getStatus()
{
    for(int i=0;i<10;i++)
    {
        cout<<i<<". ";
        if(plot[i].active==1)
        cout<<plot[i].exprOut();
        cout<<endl;
    }
}
void drawAxis()
{
     int i=0;
     while(i!=yres)
     {
          putpixel(xby2,i,1);
          i++;
     }
	 i=0;
     while(i!=xres)
     {
          putpixel(i,yby2,1);
          i++;
     }
}
void func_gen(char expr[100],float precision,int color)
{
     float x=-(xres/2)/(float)zoom_factor;
     float max_range=-x;
     while(x<=max_range)
     {
        float y;
        y = evalu(expr,x);	    //evaluates the expression using evalu which i have defined in eval.h
        //y=pow(x,sin(x));
        float xcord=xby2+zoom_factor*x+xshift;
        float ycord=yby2-zoom_factor*y+yshift;
        if(xcord<=xres && xcord>=0 && ycord>=0 && ycord<=yres)
	    putpixel(xcord,ycord,color);
	    x=x+precision;
     }
}
