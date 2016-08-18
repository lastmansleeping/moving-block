#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include<stdio.h>
#include<math.h>//FOR CALCULATING TRIGONOMETRIC FUNCTIONS


GLdouble width, height;   /* window width and height */
int wd;                   /* GLUT window handle */
int animat=0;//FLAG TO REPRESENT IF ANIMATION IS TURNED ON*/
int x=0;//FLAG SHOWING DIRECTION OF MOTION OF ANIMATED BLOCK*/
float xfactor=0.0,yfactor=0.0,angle=0.0,scaleFactor=1.0;

//ONE SINGLE VERTEX IS REPRESENTED BY A
//STRUCTURE CONTAINING ITS X AND Y CO-ORDINATES
struct Point
{
    float x;
    float y;
}a[4],temp[4];

//INITIALIZING SCREEN SIZE
void init(void)
{
    glutInitDisplayMode (GLUT_DOUBLE);//FOR DOUBLE BUFFER
    width  = 600;
    height = 600;
}

//TRANSLATE FUNCTION WRITTEN BY US
// TAKES IN PARAMETERS WHICH SPECIFY
//AMOUNT OF TRANSLATION
void translate(float xf,float yf)
{
    int i,j,k,l;
    float old[3][1],next[3][1],tmatrix[3][3];
    for(i=0;i<4;i++)
    {
        for(j=0;j<3;j++)
            for(k=0;k<3;k++)
                tmatrix[j][k]=0;
        for(j=0;j<3;j++)
            for(k=0;k<1;k++)
                next[j][k]=0;
        for(j=0;j<3;j++)
            for(k=0;k<1;k++)
                old[j][k]=0;
        tmatrix[0][0]=1;
        tmatrix[1][1]=1;
        tmatrix[2][2]=1;
        tmatrix[0][2]=xfactor;
        tmatrix[1][2]=yfactor;
        old[0][0]=a[i].x;
        old[0][1]=a[i].y;
        old[0][2]=1;
        for(j=0;j<3;j++)
        {
            for(k=0;k<1;k++)
            {
                next[j][k]=0;
                for(l=0;l<3;l++)
                    next[j][k]=next[j][k]+(tmatrix[j][l]*old[l][k]);
            }
        }
        temp[i].x=next[0][0];
        temp[i].y=next[0][1];

    }
}

//ROTATE FUNCTION WRITTEN BY US
//PARAMETER SPECIFIES THE ABSOLUTE ANGLE BY WHICH
//THE OBJECT IS ROTATED FROM INITIAL POSITION
void rotation(float ang)
{
    int i,j,k,l;
    float old[3][1],next[3][1],rmatrix[3][3];
    for(i=0;i<4;i++)
    {
        a[i].x=(a[i].x-25.0)*scaleFactor;
        a[i].y=(a[i].y-25.0)*scaleFactor;
    }
    for(i=0;i<4;i++)
    {
        for(j=0;j<3;j++)
            for(k=0;k<3;k++)
                rmatrix[j][k]=0;
        for(j=0;j<3;j++)
            for(k=0;k<1;k++)
                next[j][k]=0;
        for(j=0;j<3;j++)
            for(k=0;k<1;k++)
                old[j][k]=0;
        rmatrix[0][0]=cos(angle*(3.14285/180.00));
        rmatrix[0][1]=-sin(angle*(3.14285/180.00));
        rmatrix[1][0]=sin(angle*(3.14285/180.00));
        rmatrix[1][1]=cos(angle*(3.14285/180.00));
        rmatrix[2][2]=1;
        old[0][0]=a[i].x;
        old[0][1]=a[i].y;
        old[0][2]=1;
        for(j=0;j<3;j++)
        {
            for(k=0;k<1;k++)
            {
                next[j][k]=0;
                for(l=0;l<3;l++)
                    next[j][k]=next[j][k]+(rmatrix[j][l]*old[l][k]);
            }
        }
        temp[i].x+=(next[0][0]-a[i].x);
        temp[i].y+=(next[0][1]-a[i].y);


        //temp[i].x=a[i].x+xf;
        //temp[i].y=a[i].y+yf;

    }
    for(i=0;i<4;i++)
    {
        a[i].x=(a[i].x+25.0)/scaleFactor;
        a[i].y=(a[i].y+25.0)/scaleFactor;
    }
}

//SCALING FUNCTION WRITTEN BY US
//PARAMETER SPECIFIES THE SCALING FACTOR
//THE RELATIVE SIZE WITH RESPECT TO INITIAL STATE
void scale(float sc)
{
    int i,j,k,l;
    float old[3][1],next[3][1],smatrix[3][3];
    for(i=0;i<4;i++)
    {
        a[i].x=(a[i].x-25.0);
        a[i].y=(a[i].y-25.0);
    }
    for(i=0;i<4;i++)
    {
        for(j=0;j<3;j++)
            for(k=0;k<3;k++)
                smatrix[j][k]=0;
        for(j=0;j<3;j++)
            for(k=0;k<1;k++)
                next[j][k]=0;
        for(j=0;j<3;j++)
            for(k=0;k<1;k++)
                old[j][k]=0;
        smatrix[0][0]=sc;
        smatrix[1][1]=sc;
        smatrix[2][2]=1;
        old[0][0]=a[i].x;
        old[0][1]=a[i].y;
        old[0][2]=1;
        for(j=0;j<3;j++)
        {
            for(k=0;k<1;k++)
            {
                next[j][k]=0;
                for(l=0;l<3;l++)
                    next[j][k]=next[j][k]+(smatrix[j][l]*old[l][k]);
            }
        }
        temp[i].x+=(next[0][0]-a[i].x);
        temp[i].y+=(next[0][1]-a[i].y);


        //temp[i].x=a[i].x+xf;
        //temp[i].y=a[i].y+yf;

    }
    for(i=0;i<4;i++)
    {
        a[i].x=(a[i].x+25.0)*scaleFactor;
        a[i].y=(a[i].y+25.0)*scaleFactor;
    }
    for(i=0;i<4;i++)
    {
        a[i].x=(a[i].x+25.0);
        a[i].y=(a[i].y+25.0);
    }
}

void display(void)
{
    //INITIAL FOUR POINT CO-ORDIANTES
    a[0].x=0.0;a[1].x=50.0;a[2].x=50.0;a[3].x=0.0;
    a[0].y=0.0;a[1].y=0.0;a[2].y=50.0;a[3].y=50.0;

    int i,j,k,l;


    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0, 0.0, 0.0, 0.0);//BLACK BACKGROUND
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    //CALLING translate() written by us similar to glTranslatef()
    translate(xfactor,yfactor);

    //CALLING rotation() written by us similar to glRotatef()
    rotation(angle);

    //CALLING scale() written by us similar to glScalef()
    scale(scaleFactor);

    glColor3f(0.6,0.6,0.6);//DARK GREY SHADOW
    glBegin(GL_QUADS);

        glVertex2f(temp[0].x-5.0,temp[0].y-5.0);
        glVertex2f(temp[1].x-5.0,temp[1].y-5.0);   //SHADOW
        glVertex2f(temp[2].x-5.0,temp[2].y-5.0);   //SQUARE
        glVertex2f(temp[3].x-5.0,temp[3].y-5.0);

    glEnd();

    // a[] IS DIVIDED INTO FOUR DIFFERENT SQUARES FOR
    // MORE PRESENTABLE NATURE
    glColor3f(1.0,1.0,0.0);
    //YELLOW SQUARE
    glBegin(GL_QUADS);

        glVertex3f((temp[0].x+temp[0].x)/2,(temp[0].y+temp[0].y)/2,0);
        glVertex3f((temp[1].x+temp[0].x)/2,(temp[1].y+temp[0].y)/2,0);
        glVertex3f((temp[2].x+temp[0].x)/2,(temp[2].y+temp[0].y)/2,0);
        glVertex3f((temp[3].x+temp[0].x)/2,(temp[3].y+temp[0].y)/2,0);

    glEnd();

    //BLUE SQUARE
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);

        glVertex3f((temp[0].x+temp[1].x)/2,(temp[0].y+temp[1].y)/2,0);
        glVertex3f((temp[1].x+temp[1].x)/2,(temp[1].y+temp[1].y)/2,0);
        glVertex3f((temp[2].x+temp[1].x)/2,(temp[2].y+temp[1].y)/2,0);
        glVertex3f((temp[3].x+temp[1].x)/2,(temp[3].y+temp[1].y)/2,0);

    glEnd();

    //GREEN SQUARE
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_QUADS);

        glVertex3f((temp[0].x+temp[2].x)/2,(temp[0].y+temp[2].y)/2,0);
        glVertex3f((temp[1].x+temp[2].x)/2,(temp[1].y+temp[2].y)/2,0);
        glVertex3f((temp[2].x+temp[2].x)/2,(temp[2].y+temp[2].y)/2,0);
        glVertex3f((temp[3].x+temp[2].x)/2,(temp[3].y+temp[2].y)/2,0);

    glEnd();

    //RED SQUARE
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);

        glVertex3f((temp[0].x+temp[3].x)/2,(temp[0].y+temp[3].y)/2,0);
        glVertex3f((temp[1].x+temp[3].x)/2,(temp[1].y+temp[3].y)/2,0);
        glVertex3f((temp[2].x+temp[3].x)/2,(temp[2].y+temp[3].y)/2,0);
        glVertex3f((temp[3].x+temp[3].x)/2,(temp[3].y+temp[3].y)/2,0);

    glEnd();

    //BLACK LINES SEPERATING THE FOUR COLOURED SQUARES
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);

        glVertex2f((temp[0].x+temp[1].x)/2,(temp[0].y+temp[1].y)/2);
        glVertex2f((temp[3].x+temp[2].x)/2,(temp[3].y+temp[2].y)/2);

        glVertex2f((temp[0].x+temp[3].x)/2,(temp[0].y+temp[3].y)/2);
        glVertex2f((temp[1].x+temp[2].x)/2,(temp[1].y+temp[2].y)/2);

    glEnd();

    glPopMatrix();
    //glFlush();
    glutSwapBuffers();//HELPS IN DOUBLE BUFFERING
}

void update(int value)
{
    //IF ANGLE GOES ABOVE 360, IT IS REINITIALISED TO A VALUE
    //LESS THAN 360
    if(angle>360.f)
    {
        angle-=360.0f;
    }

    //IF OBJECT BECOMES TWO SMALL
    //OR TOO LARGE IT IS RESET TO ORIGINAL SIZE
    if(scaleFactor>=2.0||scaleFactor<=0.5)
        scaleFactor=1.0;
    //CALLING display() AGAIN
    glutPostRedisplay();

}

//FOR MOUSE ACTIONS
void mouseControl(int button, int state,int x, int y)
{
    if(button==GLUT_LEFT_BUTTON&&state==GLUT_UP)
    {//GLUT_UP IS TO ENSURE THAT ACTION IS PERFORMED ONLY
        //ON RELEASING MOUSE BUTTON
        angle+=15.0f;//CHANGING ABSOLUTE ANGLE DIFFERENCE
        update(0);
    }
    if(button==GLUT_RIGHT_BUTTON&&state==GLUT_UP)
    {
        angle-=15.0f;
        update(0);
    }


}

//FOR KEYBOARD INTERACTION
void keyPressed(unsigned char key, int x, int y)
{
    int i;
    //for(i=0;i<4;i++)
    //    printf("\n%d\t%.2f\t%.2f",xfactor,temp[i].x,temp[i].y);


    if(key == '8')
    {
        scaleFactor+=0.2;
        update(0);
    }
    if(key == '2')
    {
        scaleFactor-=0.2;
        update(0);
    }
    if(key == 'a'||key == 'A')
    {
        animat=1;
    }
    if(key == 's' || key == 'S')
    {
        animat=0;
    }
}

//FOR SPECIAL CHARACTERS ON THE KEYBOARD
void keySpecial(int key, int x, int y)
{
    int i=0;
    //for(i=0;i<4;i++)
    //    printf("\n%d\t%.2f\t%.2f",xfactor,temp[i].x,temp[i].y);
    if(key == GLUT_KEY_LEFT)
    {
        if(xfactor>=5)
            xfactor+=-5;

        //angle+=5.0;
        update(0);
    }
    if(key == GLUT_KEY_RIGHT)
    {
        if(xfactor<550)
            xfactor+=5;

        //angle-=5.0;
        update(0);
    }
    if(key == GLUT_KEY_DOWN)
    {
        if(yfactor>=5)
            yfactor+=-5;
        //angle-=5.0;
        update(0);
    }
    if(key == GLUT_KEY_UP)
    {
        if(yfactor<550)
            yfactor+=5;
        //angle+=5.0;
        update(0);
    }
}

//THIS IS A TIMED FUNCTION CALLED EVERY 10 msec
void animate(int value)
{
    if(animat==1)
    {
        if(xfactor<540&&x==0)
            xfactor+=3;
        if(xfactor>=540)
            x=1;

        if(yfactor<540&&x==1)
            yfactor+=3;
        if(yfactor>=540)
            x=2;

        if(xfactor>15&&x==2)
            xfactor+=-3;
        if(xfactor<=15)
            x=3;

        if(yfactor>15&&x==3)
            yfactor+=-3;
        if(yfactor<=15)
            x=0;

        angle-=2;
        //printf("\n%.2f\t %d",xfactor,x);

    }
    update(0);
    glutTimerFunc(10,animate,0);
}

//SETTING VIEWPORT AND OTHER VARIABLES
void reshape(int w, int h)
{
  width = (GLdouble) w;
  height = (GLdouble) h;
  glViewport(0, 0, (GLsizei) width, (GLsizei) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, width, 0.0, height);
}

int main(int argc, char *argv[])
{

  init();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
  glutInitWindowSize((int) width, (int) height);
  wd = glutCreateWindow("CG PROJECT : Animated Object");//GIVE NAME TO WINDOW
  //PRINT INSTRUCTIONS FOR USER'S HELP
  printf("\nINSTRUCTIONS\n\n");
  printf("\nLEFT MOUSE BUTTON   : AntiClockWise Rotate");
  printf("\nRIGHT MOUSE BUTTON  : ClockWise Rotate");
  printf("\n\n........................................\n\n");
  printf("\nLEFT ARROW          : Translate Left");
  printf("\nRIGHT ARROW         : Translate Right");
  printf("\nUP ARROW            : Translate Up");
  printf("\nDOWN ARROW          : Translate Down");
  printf("\n\n........................................\n\n");
  printf("\nNUMBER KEY 8        : Scale Object Big");
  printf("\nNUMBER KEY 2        : Scale Object Small");
  printf("\n\n........................................\n\n");
  printf("\na : ANIMATE    s:STOP");
  printf("\n\n\n\t\t!! ENJOY PLAYING WITH THE OBJECT");

  glutReshapeFunc(reshape);//LINKING THE RESHAPE FUNCTION
  glutDisplayFunc(display);//LINKING THE DISPLAY FUNCTION
  glutIdleFunc(display);//TELLING display() IS THE IDLE FUNCTION
  glutKeyboardFunc(keyPressed);//TELL SYSTEM TO INVOKE keyPressed() WHEN A KEY IS PRESSED
  glutSpecialFunc(keySpecial);//TELL SYSTEM TO INVOKE keySpecial() WHEN A SPECIAL KEY IS PRESSED
  glutMouseFunc(mouseControl);//TELL SYSTEM TO INVOKE mouseControl() WHEN MOUSE BUTTON IS PRESSED
  glutTimerFunc(10,animate,0);//LINKING THE TIMER FUNCTION AND SETTING REPEAT TIME TO 10 msec
  glutMainLoop();
  return 0;
}
