#ifndef CHIP8_H
#define CHIP8_H
class chip8{
    private:
        unsigned short opcode;

        unsigned char memory[4096];

        unsigned char V[16];

        unsigned short I;
        unsigned short pc;

        unsigned char gfx[64][32];

        unsigned char delay_timer;
        unsigned char sound_timer;

        unsigned short stack[16];
        unsigned short sp;


        void fetchOpCode();
        void decodeOpCode();
        void draw(unsigned short x, unsigned short y, unsigned short n);

        void op0(unsigned short[]);
        void op1(unsigned short[]);
        void op2(unsigned short[]);
        void op3(unsigned short[]);
        void op4(unsigned short[]);
        void op5(unsigned short[]);
        void op6(unsigned short[]);
        void op7(unsigned short[]);
        void op8(unsigned short[]);
        void op9(unsigned short[]);
        void opA(unsigned short[]);
        void opB(unsigned short[]);
        void opC(unsigned short[]);
        void opD(unsigned short[]);
        void opE(unsigned short[]);
        void opF(unsigned short[]);

    public:
        bool drawFlag;
        unsigned char key[16];
        void initialise();
        void loadFile(const char*);
        void emulateCycle();
        void drawGraphics();
        void setKeys();


};

#endif