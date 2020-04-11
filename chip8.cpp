#include "chip8.h"
#include "extras.h"
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
// Private Methods

void chip8::fetchOpCode(){
    opcode = memory[pc]<<8|memory[pc+1];
    pc+=2;
}

void chip8::decodeOpCode(){
    unsigned short hex[4];
    hex[0]=(opcode&0xF000)>>3;
    hex[1]=(opcode&0x0F00)>>2;
    hex[2]=(opcode&0x00F0)>>1;
    hex[3]=(opcode&0x000F)>>0;

}

void chip8::op0(unsigned short hex[]){
    if(opcode==0x00E0){
        memset((void*)(gfx),0,sizeof(unsigned char)*64*32);
    }
    else if(opcode==0x00EE){
        // WIP
    }

}
void chip8::op1(unsigned short hex[]){
    pc = (hex[1]<<3)|(hex[2]<<2)|(hex[3]<<1);
}
void chip8::op2(unsigned short hex[]){
    // WIP
}
void chip8::op3(unsigned short hex[]){
    if(V[hex[2]]==(hex[2]<<1)|hex[3]){
        pc+=2;
    }
}
void chip8::op4(unsigned short hex[]){
    if(V[hex[1]]!=(hex[2]<<1)|hex[3]){
        pc+=2;
    }
}
void chip8::op5(unsigned short hex[]){
    if(V[hex[3]]!=0){
        throw std::runtime_error("Unknown Opcode");
    }
    if(V[hex[1]]==V[hex[3]]){
        pc+=2;
    }
}
void chip8::op6(unsigned short hex[]){
    V[hex[1]]=(hex[2]<<1)|hex[3];
}
void chip8::op7(unsigned short hex[]){
    V[hex[1]]+=(hex[2]<<1)|hex[3];
}
void chip8::op8(unsigned short hex[]){
    switch (hex[3]){
    case 0:
        V[hex[1]]=V[hex[2]];
        break;
    case 1:
        V[hex[1]]|=V[hex[2]];
        break;
    case 2:
        V[hex[1]]&=V[hex[2]];
        break;
    case 3:
        V[hex[1]]^=V[hex[2]];
        break;
    case 4:
        V[hex[1]]+=V[hex[2]];
        break;
    case 5:
        V[hex[1]]-=V[hex[2]];
        break;
    case 6:
        V[hex[1]]>>=1;
        break;
    case 7:
        V[hex[1]]=V[hex[2]]-V[hex[1]];
        break;
    case 0x000E:
        V[hex[1]]<<=1;
        break;
    default:
        throw std::runtime_error("Unknown Opcode");
        break;
    }
}
void chip8::op9(unsigned short hex[]){
    if(hex[3]!=0){
        throw std::runtime_error("Unknown Opcode");
    }
    if(V[hex[1]]!=V[hex[2]]){
        pc+=2;
    }
}
void chip8::opA(unsigned short hex[]){
    I = (hex[2]<<2)|(hex[3]<<1)|hex[4];
}
void chip8::opB(unsigned short hex[]){
    pc = V[0]+(hex[2]<<2)|(hex[3]<<1)|hex[4];
}
void chip8::opC(unsigned short hex[]){
    V[hex[1]]=rand()&(hex[2]<<1)|hex[3];
}
void chip8::opD(unsigned short hex[]){
    draw(V[1],V[2],V[3]);
}
void chip8::opE(unsigned short hex[]){
    if(hex[2]==0x9&&hex[3]==0xE){
        if(key[V[hex[1]]]){
            pc+=2;
        }
    }
    else if(hex[2]==0xA&&hex[3]==0x1){
        if(!key[V[hex[1]]]){
            pc+=2;
        }
    }
    else{
        throw std::runtime_error("Unknown Opcode");
    }
}
void chip8::opF(unsigned short hex[]){
    if(hex[2]==0x0&&hex[3]==0x7){
        V[hex[1]]=delay_timer;
    }
    else if(hex[2]==0x0&&hex[3]==0xA){
        V[hex[1]]=sound_timer;
    }
    else if(hex[2]==0x1&&hex[3]==0x5){
        delay_timer = V[hex[1]];
    }
    else if(hex[2]==0x1&&hex[3]==0x8){
        sound_timer=V[hex[1]];
    }
    else if(hex[2]==0x1&&hex[3]==0xE){
        I+=V[hex[1]];
    }
    else if(hex[2]==0x2&&hex[3]==0x9){
        I=memory[5*V[hex[1]]];
    }
    else if(hex[2]==0x3&&hex[3]==0x3){
        memory[I]=(V[hex[1]]/100)%10;
        memory[I+1]=(V[hex[1]]/10)%10;
        memory[I+2]=V[hex[1]]%10;
    }
    else if(hex[2]==0x5&&hex[3]==0x5){
        for(int i = 0; i <= hex[1]; i++){
           memory[I+i]=V[i]; 
        }
    }
    else if(hex[2]==0x6&&hex[3]==0x5){
        for(int i = 0; i <= hex[1]; i++){
           V[i]=memory[I+i]; 
        }
    }
}

void chip8::draw(unsigned short x, unsigned short y, unsigned short n){
    // WIP
}

// Public Methods

void chip8::initialise(){
    srand(time(NULL));
    opcode=0;
    memset((void*)(memory),0,sizeof(unsigned char)*4096);
    for(int i = 0; i < 80; i++){
        memory[i] = chip8_fontset[i];
    }
    
    memset((void*)(V),0,sizeof(unsigned char)*16);
    
    I=0;
    pc=0x200;
    
    memset((void*)(gfx),0,sizeof(unsigned char)*64*32);
    
    delay_timer=60;
    sound_timer=60;

    memset((void*)(stack),0,sizeof(unsigned short)*16);

    sp=0;

    memset((void*)(key),0,sizeof(unsigned char)*16);
}

void chip8::loadFile(const char* name){
    FILE* fp = fopen(name,"rb");
    if(fp==nullptr){
        throw std::runtime_error("file does'nt exists.");
    }
    char c;
    int i = 0;
    do{
        c = fgetc(fp);
        memory[512+i]=c;
    }while(c!=EOF);     
    fclose(fp);
}

void chip8::emulateCycle(){
    fetchOpCode();
    decodeOpCode();
    if(delay_timer>0){
        --delay_timer;
    }
    if(sound_timer>0){
        if(sound_timer==1){
            printf("BEEP!\n");
            --sound_timer;
        }
    }
}

void chip8::drawGraphics(){

}
