#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

using namespace std;
void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void proccessInput(GLFWwindow*window);
void switchGraphics(GLFWwindow* window,int*flag);
int main(){
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window=glfwCreateWindow(800,600,"LearnOpenGL",NULL,NULL);
    if(window==NULL){
        cout<<"Failed to Create GLFW Window"<<endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<<"Failed to initialize GLAD"<<endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    unsigned int* VAO_arrays=NULL;
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glGenVertexArrays(2,VAO_arrays);
    glBindVertexArray(VAO);
    // glBindVertexArray(VAO_arrays[0]);

    float vertices[]={
        -0.5f,-0.5f,0.f,
        0.5f,-0.5f,0.f,
        0.f,0.5f,0.f
    };

    float rectangle[]={
        0.5f,0.5f,0.f,  
        0.5f,-0.5f,0.f, 
        -0.5f,-0.5f,0.f, 
        -0.5f,0.5f,0.f  
    };

    unsigned int indices[]={
        0,1,3,
        1,2,3
    };


    unsigned int VBO;//顶点缓冲对象

    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);//GL_STATIC_DRAW数据不会变，GL_DYNAMIC_DRAW数据会变改变很多，GL_STREAM_DRAW数据每次绘制都会改变

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);

    unsigned int VAO_rec;
    unsigned int VBO_rec;
    glGenBuffers(1,&VBO_rec);
    glGenVertexArrays(1,&VAO_rec);
    // glBindVertexArray(VAO_arrays[1]);
    glBindVertexArray(VAO_rec);
    unsigned int EBO;
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_rec);
    glBufferData(GL_ARRAY_BUFFER,sizeof(rectangle),rectangle,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    //顶点着色器
    const char* vertexShaderSource="#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    unsigned int vertexShader;
    vertexShader=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        cout<<"VertexShader Compliation Failed..."<<endl;
        cout<<infoLog<<endl;
        return -1;
    }

    //片段着色器
    const char* fragmentShaderSource="#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor=vec4(1.f,0.5f,0.2f,1.f);\n"
    "}\0";

    const char* fragmentShaderSource2="#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor=vec4(1.f,1.0f,0.0f,1.f);\n"
    "}\0";

    unsigned int fragmentShader;
    fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);

    unsigned int fragmentShader2;
    fragmentShader2=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2,1,&fragmentShaderSource2,NULL);
    glCompileShader(fragmentShader2);

    //着色器程序
    unsigned int shaderProgram;
    shaderProgram=glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    //黄色着色器
    unsigned int shaderProgram2;
    shaderProgram2=glCreateProgram();
    glAttachShader(shaderProgram2,vertexShader);
    glAttachShader(shaderProgram2,fragmentShader2);
    glLinkProgram(shaderProgram2);

    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
        cout<<"ShaderProgram Link Failed..."<<endl;
        cout<<infoLog<<endl;
        return -1;
    }
    glGetProgramiv(shaderProgram2,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(shaderProgram2,512,NULL,infoLog);
        cout<<"ShaderProgram2 Link Failed..."<<endl;
        cout<<infoLog<<endl;
        return -1;
    }


    // glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);


    //渲染循环
    int flag=0;
    while(!glfwWindowShouldClose(window)){
        glfwSwapBuffers(window);

        proccessInput(window);
        switchGraphics(window,&flag);

        //渲染区域
        glClearColor(0.2f,0.3f,0.3f,1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        if(flag==0){
            glUseProgram(shaderProgram);
            // glBindVertexArray(VAO_arrays[0]);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES,0,3);
            
        }
        if(flag==1){
            glUseProgram(shaderProgram2);
            //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);   //是否启用线框模式
            // glBindVertexArray(VAO_arrays[1]);
            glBindVertexArray(VAO_rec);
            glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,(void*)0);
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        }
        

        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteVertexArrays(1,&VAO_rec);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&VBO_rec);
    glDeleteBuffers(1,&EBO);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgram2);
    glfwTerminate();

    return 0;
}
void framebuffer_size_callback(GLFWwindow* window,int width,int height){
    glViewport(0,0,width,height);
}
void proccessInput(GLFWwindow*window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }
}
void switchGraphics(GLFWwindow* window,int*flag){
    if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS){
        *flag=0;
    }
    if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS){
        *flag=1;
    }
}