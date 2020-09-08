#include<GLTools.h>
#include<glew.h>
#include<GLShaderManager.h>
#include<GLUT/GLUT.h>
#define FREEGLUT_STATIC
#define GL_SILENCE_DEPRECATION

GLBatch triangleBatch;
GLShaderManager shaderManager;

void ChangeSize(int w,int h)
{
    glViewport(0,0,w,h);
    //glViewport（float x,float y,GLsizei width,GLsizei herght）其中，x，y代表窗口左下角坐标，宽度和高度参数是用像素表示，利用这个函数，我们可以在一个窗口渲染不同区域的多个图形，一定注意x,y是左下角的点的坐标。
}

void SetupRC()
{
    glClearColor(0.0f,0.0f,1.0f,1.0f);
    //用来窗口清除的颜色，四个参数依次为 red,green,blue,alpah
    shaderManager.InitializeStockShaders();
    GLfloat vVerts[]={-0.5f,0.0f,0.0f,
        0.5f,0.0f,0.0f,
        0.0f,0.5f,0.0f}
    //以下三行代码创建了一个三角形的批次，仅包含三个顶点
    triangleBatch.Begin(GL_TRIANGLES,3);
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.End();
}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    //glclear函数清除一个或一组缓冲区（颜色缓冲区，深度缓冲区，模板缓冲区）
    GLfloat vRed[]={1.0f,0.0f,0.0f,1.0f};
    //设置一组浮点数表示红色
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY,vRed);
    //使用glt_shader_identity着色器，并将颜色传递进去
    triangleBatch.Draw();
    //将几何图形提交到着色器
    glutSwapBuffers();
    //指定一个双缓冲区渲染环境。
}

int main(int argc,char*argv[])
{
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc,argv);
    //传输命令行参数，并初始化glut库
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
    //创建窗口时使用的显示模式，glut_double双缓冲窗口，glut_rgba使用rgba颜色模式，glut_depth将一个深度缓冲          区分配为显示的一部分，glut_stencil确保有一个可用的缓冲模版区。
    glutInitWindowSize(800,600);
    //窗口大小
    glutCreateWindow("Triangle");
    //窗口标题
    glutReshapeFunc(ChangeSize);
    //改变窗口大小的回调函数
    glutDisplayFunc(RenderScene);
    GLenum err=glewInit();
    //检查驱动初始化过程没有出现任何问题
    if(GLEW_OK!=err)
    {
        fprintf(stderr,"GLEW Error:%s\n",glewGetErrorString(err));
        return 1;
    }
    SetupRC();//rc表示渲染环境（render context）
    glutMainLoop();//负责处理所有操作系统特定的消息，按键，直到关闭程序。
    return 0;
}





