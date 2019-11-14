#include<windows.h>
#include<GL/glut.h>
#include<math.h>
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
clock_t time1, time2;
char str[100];


int counter=0;
///Counter for how many polygons are vanished
int arr[5]={0,0,0,0,0}; //to count how many objects are vanished.
int counts;
int flag[5]={0,0,0,0,0};    // to count if the object is vanished previous change of distance
///Vanished in how many steps
int steps=0;
//Dynamic obj
float xa=0.05,ya=0.05,xb=0.05,yb=-0.05,xc=-0.05,yc=-0.05,xd=-0.05,yd=0.05;
float xr=0,yr=0;
float t1,t2,t3,t4;

//1st Static obj
float x11=0.3,y11=0.0,x22=0.5,y22=0.0,x33=0.5,y33=0.2,x44=0.3,y44=0.2;
float xMax=0.5,yMax=0.2,xMin=0.3,yMin=0.0;

//2nd Static obj
float x111=0.8,y111=0.0,x222=0.9,y222=0.0,x333=0.9,y333=0.1,x444=0.8,y444=0.1;
float xMax2=0.9,yMax2=0.1,xMin2=0.8,yMin2=0.0;

//3rd Static obj
float x1111=-0.5,y1111=0.2,x2222=-0.4,y2222=0.2,x3333=-0.4,y3333=0.3,x4444=-0.5,y4444=0.3;
float xMax3=-0.4,yMax3=0.3,xMin3=-0.5,yMin3=0.2;

//4th obj
float X1=0.0, Y1=0.5;
float r=0.1;

//5th obj
float X2=0.0, Y2=-0.5;
float rr=0.15;

void createObj(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float r, float g, float b)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(r,g,b);
    glBegin(GL_QUADS);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
    glVertex2f(x4,y4);
}
void createObjCir(float X, float Y, float rad, float r, float g, float b)
{
    glColor3f(r,g,b);
    glBegin(GL_POLYGON);
    float x,y;
    for(float i=0;i<=360;i+=0.001)
    {
        x=rad*cos(i)+X;
        y=rad*sin(i)+Y;
        glVertex2f(x,y);
    }
    glEnd();
    glFlush();
}

void display(void)
{
    //Static objects
    createObj(x11,y11,x22,y22,x33,y33,x44,y44,1.0,0.0,0.0);
    createObj(x1111,y1111,x2222,y2222,x3333,y3333,x4444,y4444,1.0,1.0,0.0);
    createObj(x111,y111,x222,y222,x333,y333,x444,y444,0.0,1.0,1.0);
    glEnd();

    //glColor3f(0.0,0.0,1.0);
    createObjCir(X1,Y1,r,0.0,1.0,1.0);
    createObjCir(X2,Y2,rr,1.0,0.0,1.0);

    //Obj Dynamically change position
    glColor3f(0.6,0.6,0.6);
    glBegin(GL_QUADS);
    glVertex2f(xa+xr,ya+yr);
    glVertex2f(xb+xr,yb+yr);
    glVertex2f(xc+xr,yc+yr);
    glVertex2f(xd+xr,yd+yr);

    glEnd();
    glutSwapBuffers();//as it is not static.
}
void isInsideCir(void)
{
    ///for first Circle
    float dis1,dis2,dis3,dis4,dis5,dis6,dis7,dis8;
    float avg1,avg11,   avg2,avg22,     avg3,avg33,    avg4,avg44;
    dis1=sqrt((((xa+xr)-X1)*((xa+xr)-X1)) + (((ya+yr)-Y1)*((ya+yr)-Y1)));
    dis2=sqrt((((xb+xr)-X1)*((xb+xr)-X1)) + (((yb+yr)-Y1)*((yb+yr)-Y1)));
    dis3=sqrt((((xc+xr)-X1)*((xc+xr)-X1)) + (((yc+yr)-Y1)*((yc+yr)-Y1)));
    dis4=sqrt((((xd+xr)-X1)*((xd+xr)-X1)) + (((yd+yr)-Y1)*((yd+yr)-Y1)));

    avg1=(((xd+xr)+(xa+xr))/2);
    avg11=ya+yr;

    avg2=xa+xr;
    avg22=(((ya+yr)+(yb+yr))/2);

    avg3=(((xb+xr)+(xc+xr))/2);
    avg33=ya+yr;

    avg4=xa+xr;
    avg44=(((yd+yr)+(yc+yr))/2);


    dis5=sqrt(((avg1-X1)*(avg1-X1)) + ((avg11-Y1)*(avg11-Y1)));
    dis6=sqrt(((avg2-X1)*(avg2-X1)) + ((avg22-Y1)*(avg22-Y1)));
    dis7=sqrt(((avg3-X1)*(avg3-X1)) + ((avg33-Y1)*(avg33-Y1)));
    dis8=sqrt(((avg4-X1)*(avg4-X1)) + ((avg44-Y1)*(avg44-Y1)));

    if(dis1<r || dis2<r || dis3<r || dis4<r || dis5<r || dis6<r || dis7<r || dis8<r)
    {
        r=0.0;
        counts=0;
        arr[0]=1;
        for(int i=0;i<5;i++)
        {
            if(arr[i]==1)
            {
                counts++;
            }
        }
        if(flag[0]==0)
        {

            ///--------------------------------------
            time1=clock();
            double diff = (double)time1;
            diff /= CLOCKS_PER_SEC;
            gcvt(diff,4,str);
            cout<<"     "<<"Score: "<<counts<<" --> Time: "<<str<<" seconds"<<" --> Steps: "<<steps<<endl;
            ///--------------------------------------
            flag[0]=1;
        }
    }


    ///2nd Circle obj
    dis1=sqrt((((xa+xr)-X2)*((xa+xr)-X2)) + (((ya+yr)-Y2)*((ya+yr)-Y2)));
    dis2=sqrt((((xb+xr)-X2)*((xb+xr)-X2)) + (((yb+yr)-Y2)*((yb+yr)-Y2)));
    dis3=sqrt((((xc+xr)-X2)*((xc+xr)-X2)) + (((yc+yr)-Y2)*((yc+yr)-Y2)));
    dis4=sqrt((((xd+xr)-X2)*((xd+xr)-X2)) + (((yd+yr)-Y2)*((yd+yr)-Y2)));

    avg1=(((xd+xr)+(xa+xr))/2);
    avg11=ya+yr;

    avg2=xa+xr;
    avg22=(((ya+yr)+(yb+yr))/2);

    avg3=(((xb+xr)+(xc+xr))/2);
    avg33=ya+yr;

    avg4=xa+xr;
    avg44=(((yd+yr)+(yc+yr))/2); //


    dis5=sqrt(((avg1-X2)*(avg1-X2)) + ((avg11-Y2)*(avg11-Y2)));
    dis6=sqrt(((avg2-X2)*(avg2-X2)) + ((avg22-Y2)*(avg22-Y2)));
    dis7=sqrt(((avg3-X2)*(avg3-X2)) + ((avg33-Y2)*(avg33-Y2)));
    dis8=sqrt(((avg4-X2)*(avg4-X2)) + ((avg44-Y2)*(avg44-Y2)));

    if(dis1<rr || dis2<rr || dis3<rr || dis4<rr || dis5<rr || dis6<rr || dis7<rr || dis8<rr)
    {
        rr=0.0;
        arr[1]=1;
        counts=0;
        for(int i=0;i<5;i++)
        {
            if(arr[i]==1)
            {
                counts++;
            }
        }
        if(flag[1]==0)
        {

            ///--------------------------------------
            time1=clock();
            double diff = (double)time1;
            diff /= CLOCKS_PER_SEC;
            gcvt(diff,4,str);
            cout<<"     "<<"Score: "<<counts<<" --> Time: "<<str<<" seconds"<<" --> Steps: "<<steps<<endl;
            ///--------------------------------------
            flag[1]=1;
        }
    }
}
void isInside(void)
{
    if( (((xa+xr)>=xMin && (xa+xr)<=xMax) && ((ya+yr)>=yMin && (ya+yr)<=yMax))
           || (((xb+xr)>=xMin && (xb+xr)<=xMax) && ((yb+yr)>=yMin && (yb+yr)<=yMax))
           || (((xc+xr)>=xMin && (xc+xr)<=xMax) && ((yc+yr)>=yMin && (yc+yr)<=yMax))
           || (((xd+xr)>=xMin && (xd+xr)<=xMax) && ((yd+yr)>=yMin && (yd+yr)<=yMax))  )
    {
        counter++;
        x11=0.0,y11=0.0,x22=0.0,y22=0.0,x33=0.0,y33=0.0,x44=0.0,y44=0.0;
        arr[2]=1;
        counts=0;
        for(int i=0;i<5;i++)
        {
            if(arr[i]==1)
            {
                counts++;
            }
        }
        if(flag[2]==0)
        {
            ///--------------------------------------
            time1=clock();
            double diff = (double)time1;
            diff /= CLOCKS_PER_SEC;
            gcvt(diff,4,str);
            cout<<"     "<<"Score: "<<counts<<" --> Time: "<<str<<" seconds"<<" --> Steps: "<<steps<<endl;
            ///--------------------------------------
            flag[2]=1;
        }
    }
    else if( (((xa+xr)>=xMin2 && (xa+xr)<=xMax2) && ((ya+yr)>=yMin2 && (ya+yr)<=yMax2))
           || (((xb+xr)>=xMin2 && (xb+xr)<=xMax2) && ((yb+yr)>=yMin2 && (yb+yr)<=yMax2))
           || (((xc+xr)>=xMin2 && (xc+xr)<=xMax2) && ((yc+yr)>=yMin2 && (yc+yr)<=yMax2))
           || (((xd+xr)>=xMin2 && (xd+xr)<=xMax2) && ((yd+yr)>=yMin2 && (yd+yr)<=yMax2))  )
    {
        counter++;
        x111=0.0,y111=0.0,x222=0.0,y222=0.0,x333=0.0,y333=0.0,x444=0.0,y444=0.0;
        arr[3]=1;
        counts=0;
        for(int i=0;i<5;i++)
        {
            if(arr[i]==1)
            {
                counts++;
            }
        }
        if(flag[3]==0)
        {
            ///--------------------------------------
            time1=clock();
            double diff = (double)time1;
            diff /= CLOCKS_PER_SEC;
            gcvt(diff,4,str);
            cout<<"     "<<"Score: "<<counts<<" --> Time: "<<str<<" seconds"<<" --> Steps: "<<steps<<endl;
            ///--------------------------------------
            flag[3]=1;
        }
    }
    else if( (((xa+xr)>=xMin3 && (xa+xr)<=xMax3) && ((ya+yr)>=yMin3 && (ya+yr)<=yMax3))
           || (((xb+xr)>=xMin3 && (xb+xr)<=xMax3) && ((yb+yr)>=yMin3 && (yb+yr)<=yMax3))
           || (((xc+xr)>=xMin3 && (xc+xr)<=xMax3) && ((yc+yr)>=yMin3 && (yc+yr)<=yMax3))
           || (((xd+xr)>=xMin3 && (xd+xr)<=xMax3) && ((yd+yr)>=yMin3 && (yd+yr)<=yMax3))  )
    {
        counter++;
        x1111=0.0,y1111=0.0,x2222=0.0,y2222=0.0,x3333=0.0,y3333=0.0,x4444=0.0,y4444=0.0;
        arr[4]=1;
        counts=0;
        for(int i=0;i<5;i++)
        {
            if(arr[i]==1)
            {
                counts++;
            }
        }
        if(flag[4]==0)
        {
            ///--------------------------------------
            time1=clock();
            double diff = (double)time1;
            diff /= CLOCKS_PER_SEC;
            gcvt(diff,4,str);
            cout<<"     "<<"Score: "<<counts<<" --> Time: "<<str<<" seconds"<<" --> Steps: "<<steps<<endl;
            ///--------------------------------------
            flag[4]=1;
        }
    }
}
///Function to use Move object
void keyboard(unsigned char key,int x,int y)
{
    switch(key)
    {
    case 'w':
        {
        yr=yr+0.01;
        steps++;
        isInside();
        isInsideCir();
        glutPostRedisplay();
        break;
        }
    case 's':
        {
        yr=yr-0.01;
        steps++;
        isInside();
        isInsideCir();
        glutPostRedisplay();
        break;
        }
    case 'a':
        {
        xr=xr-0.01;
        steps++;
        isInside();
        isInsideCir();
        glutPostRedisplay();
        break;
        }
    case 'd':
        {
        xr=xr+0.01;
        steps++;
        isInside();
        isInsideCir();
        glutPostRedisplay();
        break;
        }

    //Cases for left-right rotation
    case 'R':
        {
        t1=xa;
        xa=xa*cos(45)-ya*sin(45);   //-----------------------------
        ya=t1*sin(45)+ya*cos(45);

        t2=xb;
        xb=xb*cos(45)-yb*sin(45);
        yb=t2*sin(45)+yb*cos(45);

        t3=xc;
        xc=xc*cos(45)-yc*sin(45);
        yc=t3*sin(45)+yc*cos(45);

        t4=xd;
        xd=xd*cos(45)-yd*sin(45);
        yd=t4*sin(45)+yd*cos(45);
        //glFlush();
        glutPostRedisplay();
        break;
        }
    case 'L':
        {
        t1=xa;
        xa=xa*cos(-45)-ya*sin(-45);   //-----------------------------
        ya=t1*sin(-45)+ya*cos(-45);

        t2=xb;
        xb=xb*cos(-45)-yb*sin(-45);
        yb=t2*sin(-45)+yb*cos(-45);

        t3=xc;
        xc=xc*cos(-45)-yc*sin(-45);
        yc=t3*sin(-45)+yc*cos(-45);

        t4=xd;
        xd=xd*cos(-45)-yd*sin(-45);
        yd=t4*sin(-45)+yd*cos(-45);
        //glFlush();
        glutPostRedisplay();
        break;
        }
    }
}

int main(int argc, char **argv)
{
    cout<<"_______________________________________________________________________"<<endl;
    cout<<"                            Md. Imrul Hasan                              "<<endl;
    cout<<"                             Reg: 16101034                               "<<endl;
    cout<<" ____________________________________________________________________"<<endl;
    cout<<"                   Move the dynamic obj: w,s,a,d"<<endl;
    cout<<"                    Rotate the dynamic obj: L,R"<<endl;
    cout<<" _____________________________________________________________________"<<endl<<endl;


    glutInit(&argc, argv); //glut package initialization
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(500,500);//graphics window er console size
    glutInitWindowPosition(100,100);
    glutCreateWindow("----Final Project----");
    glutDisplayFunc(display);//display fuction calling
    glutKeyboardFunc(keyboard);


    glutMainLoop();
    return 0;
}
