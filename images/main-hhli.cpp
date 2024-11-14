#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<vector>
#include "stb_image.h"
#include "Shader.hpp"

using namespace std;
void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void proccessInput(GLFWwindow*window,vector<float*>numberArgs);
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

    int width,height,nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data=stbi_load("D:\\LearnOpenGL\\Lesson_3_Texture\\container.jpg",&width,&height,&nrChannels,0);

    

   float vertices[] = {

     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.f, 1.f,   
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.f, 0.f,   
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.f, 0.f,   
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.f, 1.f    
    };
    //四笑脸texture坐标
    float texcoord[]={
        2.f,2.f,
        2.f,0.f,
        0.f,0.f,
        0.f,2.f
    };
    //中间笑脸texture坐标
    float texcoord2[]={
        0.75f,0.75f,
        0.75f,0.25f,
        0.25f,0.25f,
        0.25f,0.75f
    };

    unsigned int indics[]={
        0,1,3,
        3,2,1
    };
    //顶点缓存
    unsigned int VAO,VBO,EBO,VBO_tex,VBO_tex2;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    glGenBuffers(1,&VBO_tex);
    glGenBuffers(1,&VBO_tex2);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_tex);
    glBufferData(GL_ARRAY_BUFFER,sizeof(texcoord),texcoord,GL_STATIC_DRAW);
    glVertexAttribPointer(3,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_tex2);
    glBufferData(GL_ARRAY_BUFFER,sizeof(texcoord2),texcoord2,GL_STATIC_DRAW);
    glVertexAttribPointer(4,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
    glEnableVertexAttribArray(4);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indics),indics,GL_STATIC_DRAW);
    glBindVertexArray(0);
    //Texture
    unsigned int texture;
    glGenTextures(1,&texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    if(data){
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        cout<<"TEXUTRE0 LOAD FAILED..."<<endl;
    }
    stbi_image_free(data);

    //Texture_AwesomeFace
    data=stbi_load("D:\\LearnOpenGL\\Lesson_3_Texture\\awesomeface.png",&width,&height,&nrChannels,0);
    unsigned int texture2;
    glGenTextures(1,&texture2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,texture2);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    if(data){
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        cout<<"TEXUTRE1 LOAD FAILED..."<<endl;
    }
    stbi_image_free(data);

    //Shader

    Shader myshader("D:\\LearnOpenGL\\Lesson_3_Texture\\shaders\\vertex.glsl","D:\\LearnOpenGL\\Lesson_3_Texture\\shaders\\fragment.glsl");
    myshader.use();
    glUniform1i(glGetAttribLocation(myshader.ID,"myTexture"),0);
    myshader.setInt("myTexture2",1);
    float mixvalue=0.f;
    vector<float*>numberArs;
    numberArs.push_back(&mixvalue);
    //渲染循环
    while(!glfwWindowShouldClose(window)){
        glfwSwapBuffers(window);

        proccessInput(window,numberArs);

        //渲染区域
        glClearColor(0.2f,0.3f,0.3f,1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // glBindTexture(GL_TEXTURE_2D,texture);
        myshader.use();
        myshader.setFloat("mixvalue",mixvalue);
       
        glBindVertexArray(VAO);
        
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
void framebuffer_size_callback(GLFWwindow* window,int width,int height){
    glViewport(0,0,width,height);
}
void proccessInput(GLFWwindow*window,vector<float*>numberArgs){
    const unsigned int FPS=144;
    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }
    if(glfwGetKey(window,GLFW_KEY_UP)==GLFW_PRESS){
        *numberArgs[0]+=(0.3f/FPS*1.0f);
        if(*numberArgs[0]>1.f)*numberArgs[0]=1.f;
    }
    if(glfwGetKey(window,GLFW_KEY_DOWN)==GLFW_PRESS){
        *numberArgs[0]-=(0.3f/FPS*1.0f);
        if(*numberArgs[0]<0.f)*numberArgs[0]=0.f;
    }
}
