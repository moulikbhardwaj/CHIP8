#include <GLFW/glfw3.h>
#include <iostream>
#include "chip8.h"

chip8 emulator;
void input(GLFWwindow * window, int wkey, int scancode, int action, int mods){

    if(wkey==GLFW_KEY_A && action==GLFW_PRESS){
        emulator.key[0xA]=1;
    }
    else if(wkey==GLFW_KEY_A && action==GLFW_RELEASE){
        emulator.key[0xA]=0;
    }
    if(wkey==GLFW_KEY_B && action==GLFW_PRESS){
        emulator.key[0xB]=1;
    }
    else if(wkey==GLFW_KEY_B && action==GLFW_RELEASE){
        emulator.key[0xB]=0;
    }
    if(wkey==GLFW_KEY_C && action==GLFW_PRESS){
        emulator.key[0xC]=1;
    }
    else if(wkey==GLFW_KEY_C && action==GLFW_RELEASE){
        emulator.key[0xC]=0;
    }
    if(wkey==GLFW_KEY_D && action==GLFW_PRESS){
        emulator.key[0xD]=1;
    }
    else if(wkey==GLFW_KEY_D && action==GLFW_RELEASE){
        emulator.key[0xD]=0;
    }
    if(wkey==GLFW_KEY_E && action==GLFW_PRESS){
        emulator.key[0xE]=1;
    }
    else if(wkey==GLFW_KEY_E && action==GLFW_RELEASE){
        emulator.key[0xE]=0;
    }
    if(wkey==GLFW_KEY_F && action==GLFW_PRESS){
        emulator.key[0xF]=1;
    }
    else if(wkey==GLFW_KEY_F && action==GLFW_RELEASE){
        emulator.key[0xF]=0;
    }
    if(wkey==GLFW_KEY_KP_0 && action==GLFW_PRESS){
        emulator.key[0x0]=1;
    }
    else if(wkey==GLFW_KEY_KP_0 && action==GLFW_RELEASE){
        emulator.key[0x0]=0;
    }
    if(wkey==GLFW_KEY_KP_1 && action==GLFW_PRESS){
        emulator.key[0x1]=1;
    }
    else if(wkey==GLFW_KEY_KP_1 && action==GLFW_RELEASE){
        emulator.key[0x1]=0;
    }
    if(wkey==GLFW_KEY_KP_2 && action==GLFW_PRESS){
        emulator.key[0x2]=1;
    }
    else if(wkey==GLFW_KEY_KP_2 && action==GLFW_RELEASE){
        emulator.key[0x2]=0;
    }
    if(wkey==GLFW_KEY_KP_3 && action==GLFW_PRESS){
        emulator.key[0x3]=1;
    }
    else if(wkey==GLFW_KEY_KP_3 && action==GLFW_RELEASE){
        emulator.key[0x3]=0;
    }
    if(wkey==GLFW_KEY_KP_4 && action==GLFW_PRESS){
        emulator.key[0x4]=1;
    }
    else if(wkey==GLFW_KEY_KP_4 && action==GLFW_RELEASE){
        emulator.key[0x4]=0;
    }
    if(wkey==GLFW_KEY_KP_5 && action==GLFW_PRESS){
        emulator.key[0x5]=1;
    }
    else if(wkey==GLFW_KEY_KP_5 && action==GLFW_RELEASE){
        emulator.key[0x5]=0;
    }
    if(wkey==GLFW_KEY_KP_6 && action==GLFW_PRESS){
        emulator.key[0x6]=1;
    }
    else if(wkey==GLFW_KEY_KP_6 && action==GLFW_RELEASE){
        emulator.key[0x6]=0;
    }
    if(wkey==GLFW_KEY_KP_7 && action==GLFW_PRESS){
        emulator.key[0x7]=1;
    }
    else if(wkey==GLFW_KEY_KP_7 && action==GLFW_RELEASE){
        emulator.key[0x7]=0;
    }
    if(wkey==GLFW_KEY_KP_8 && action==GLFW_PRESS){
        emulator.key[0x8]=1;
    }
    else if(wkey==GLFW_KEY_KP_8 && action==GLFW_RELEASE){
        emulator.key[0x8]=0;
    }
    if(wkey==GLFW_KEY_KP_9 && action==GLFW_PRESS){
        emulator.key[0x9]=1;
    }
    else if(wkey==GLFW_KEY_KP_9 && action==GLFW_RELEASE){
        emulator.key[0x9]=0;
    }
}

int main(){
    glfwInit();
    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE,GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(64,32,"CHIP8 EMULATOR",nullptr,nullptr);

    emulator.initialise();
    emulator.loadFile("PONG");
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
    }
}