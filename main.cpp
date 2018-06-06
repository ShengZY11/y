#include <iostream>
#include <GL/glut.h>

#include "class/Et.h"
#include "class/Aet.h"

Et et;

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
    glBegin(GL_POINTS);


    Aet aet = Aet(et);
    while(aet.isEmpty())
        aet.update();
    int R = 500;
    int G = 0;
    while (!aet.isEmpty()){
        //aet.output();
        AetHead aetHead = aet.getAet();
        AetNode *p = aetHead;
        while (p->next != nullptr){
            p = p->next;
            auto fp = (int)p->x;
            p = p->next;
            auto ep = (int)p->x;
            G++;
            while(fp <= ep){
                glColor3f(((R%500)/500.0), ((aet.getnum()%500)/500.0), ((fp%500)/500.0));
                //std::cout<<num2<<std::endl;
                glVertex2i(fp, aet.getnum());
                fp++;
            }
        }
        aet.update();
        R--;
    }
    glEnd();
    glFlush();
}


int main(int argc, char** argv)
{
    et = Et();
    et.creatEt();
    et.output();
    //opengl初始化
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(500, 250);
    glutInitWindowSize(500, 500);
    glutCreateWindow("0.0");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glutDisplayFunc(&myDisplay);
    glutMainLoop();
    return 0;
}
