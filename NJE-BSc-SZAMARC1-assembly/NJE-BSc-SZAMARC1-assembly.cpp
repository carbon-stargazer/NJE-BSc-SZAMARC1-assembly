#include <iostream>

using namespace std;

int main()
{
    int N;                          // storing decimal
    int countC, countX, countI;     // 100s, 10s, 1s

    int saveesp;

    const char* txtinput = "Please enter a DECIMAL number between 1-4999!\n";      // printf
    const char* txtoutput = "\nThe ROMAN number:\n";
    const char* newline = "\n";

    const char* formati = "%d";     // scanf
    const char* _pause = "pause";   // system pause

    char rom[20] = "";              // storing roman numeral
    int count[13] = { 0 };          // storing the count of each roman numeral character, from 1000 to 1 (left to right)


    _asm
    {
        mov saveesp, esp;
    }

    // SETUP
    _asm
    {
        push txtinput;
        call dword ptr printf;


    input:
        lea eax, N;             // N to eax
        push eax;
        push formati;           // format
        call dword ptr scanf;   // input request

        // double check input
        cmp N, 1;
        jl input;
        cmp N, 4999;
        jle onward;
        jmp input;

    onward:
    }

    /*
    _asm
    {
        push N;
        push formati;
        call dword ptr printf;
    }
    */

    // CONVERTING DECIMAL
    _asm
    {
        // divide (1000)
        mov eax, N;         // N -> eax
        mov ebx, 1000;      // 1000 -> ebx
        xor edx, edx;
        div ebx;            // divide by 1000
        mov N, edx;         // N = remainder
        lea ebx, count;
        mov[ebx], eax;      // count[0] = result of division

        // divide (100)
        mov eax, N;
        mov ebx, 100;
        xor edx, edx;
        div ebx;
        mov countC, eax;    // countC = result of division
        mov N, edx;

        // divide (10)
        mov eax, N;
        mov ebx, 10;
        xor edx, edx;
        div ebx;
        mov countX, eax;
        mov N, edx;

        // divide (1)
        mov eax, N;
        mov ebx, 1;
        xor edx, edx;
        div ebx;
        mov countI, eax;
    }

    // (100) COUNT
    _asm
    {
        mov eax, countC;
        cmp eax, 4;
        jl C;       // countC < 4
        je CD;      // countC == 4
        jg DC;      // countC > 4

        // (100-300)
    C:
        lea ebx, count;
        mov eax, countC;
        mov[ebx + 16], eax;         // (C) = countC
        mov countC, 0;              // countC = 0
        jmp tens;                   // exit and jump to count (10)

        // (400)
    CD:
        lea ebx, count;
        mov dword ptr[ebx + 12], 1; // (CD) +1
        mov countC, 0;
        jmp tens;


        // (500-900)
    DC:
        cmp countC, 9;
        je CM;
        lea ebx, count;
        mov dword ptr[ebx + 8], 1;  // (V) +1
        sub countC, 5;
        mov eax, countC;
        mov[ebx + 16], eax;         // (C) = countC
        mov countC, 0;
        jmp tens;

        // (900)
    CM:
        lea ebx, count;
        mov dword ptr[ebx + 4], 1;  // (CM) +1
        mov countC, 0;
        jmp tens;
    }

    // (10) COUNT
    _asm
    {
    tens:
        mov eax, countX;
        cmp eax, 4;
        jl X;       // countX < 4
        je XL;      // countX == 4
        jg LX;      // countX > 4

        // (10-30)
    X:
        lea ebx, count;
        mov eax, countX;
        mov[ebx + 32], eax;         // (X) = countX
        mov countX, 0;              // countX = 0
        jmp ones;                   // exit and jump to count (10)

        // (40)
    XL:
        lea ebx, count;
        mov dword ptr[ebx + 28], 1; // (XL) +1
        mov countX, 0;
        jmp ones;

        // (50-90)
    LX:
        cmp countX, 9;
        je XC;
        lea ebx, count;
        mov dword ptr[ebx + 24], 1;  // (L) +1
        sub countX, 5;
        mov eax, countX;
        mov[ebx + 32], eax;         // (X) = countX
        mov countX, 0;
        jmp ones;

        // (90)
    XC:
        lea ebx, count;
        mov dword ptr[ebx + 20], 1; // (XC) +1
        mov countX, 0;
        jmp ones;
    }

    // (1) COUNT
    _asm
    {
    ones:
        mov eax, countI;
        cmp eax, 4;
        jl I;       // countI < 4
        je IV;      // countI == 4
        jg VI;      // countI > 4

        // (1-3)
    I:
        lea ebx, count;
        mov eax, countI;
        mov[ebx + 48], eax;         // (I) = countI
        mov countI, 0;              // countX = 0
        jmp done;                   // exit

        // (4)
    IV:
        lea ebx, count;
        mov dword ptr[ebx + 44], 1; // (IV) +1
        mov countI, 0;
        jmp done;

        // (5-9)
    VI:
        cmp countI, 9;
        je IX;
        lea ebx, count;
        mov dword ptr[ebx + 40], 1;  // (V) +1
        sub countI, 5;
        mov eax, countI;
        mov[ebx + 48], eax;          // (I) = countI
        mov countI, 0;
        jmp done;

        // (9)
    IX:
        lea ebx, count;
        mov dword ptr[ebx + 36], 1;  // (IX) +1
        mov countI, 0;
        jmp done;
    }

    _asm
    {
    done:
    }


    // double check indexing
    //printf("\ncountC: %d\n", countC);
    //printf("countX: %d\n", countX);
    //printf("countI: %d\n\n", countI);
    //printf("1000:\t %d\n", count[0]);
    //printf("900:\t %d\n", count[1]);
    //printf("500:\t %d\n", count[2]);
    //printf("400:\t %d\n", count[3]);
    //printf("100:\t %d\n", count[4]);
    //printf("90:\t %d\n", count[5]);
    //printf("50:\t %d\n", count[6]);
    //printf("40:\t %d\n", count[7]);
    //printf("10:\t %d\n", count[8]);
    //printf("9:\t %d\n", count[9]);
    //printf("5:\t %d\n", count[10]);
    //printf("4:\t %d\n", count[11]);
    //printf("1:\t %d\n", count[12]);

    // PUTTING CHARS INTO ARRAY
    _asm {
        xor ebx, ebx;                       // set ebx register to zero
        xor eax, eax;                       // set eax register to zero

    add1000:
        // count[0] = 1000
        cmp dword ptr[count], 0;            // count[0] =? 0
        jle add900;                         // exit count[0] <= 0

        mov esi, ebx;
        lea edi, [rom];                     // rom -> edi

        mov byte ptr[edi + esi], 'M';       // rom[ebx] = 'M'

        sub dword ptr[count], 1;            // count[0] - 1
        add ebx, 1;                         // ebx++ 

        jmp add1000;

    add900:
        // count[1] = 900
        cmp dword ptr[count + 4], 0;        // count[1] =? 0
        jle add500;
        mov esi, ebx;
        lea edi, [rom];
        mov byte ptr[edi + esi], 'C';
        mov byte ptr[edi + esi + 1], 'M';
        sub dword ptr[count + 4], 1;
        add ebx, 2;                         // because 900 consists of CM, ebx needs to be incremented by 2!
        je add90;                           // because apart from 900, there can't be any more 100s, jump to 10s!

    add500:
        cmp dword ptr[count + 8], 0;
        jle add400;
        mov esi, ebx;
        lea edi, [rom];
        mov byte ptr[edi + esi], 'D';
        sub dword ptr[count + 8], 1;
        add ebx, 1;
        je add100;                          // having 500 can still result in having 100s

    add400:
        cmp dword ptr[count + 12], 0;
        jle add100;
        mov esi, ebx;
        lea edi, [rom];
        mov byte ptr[edi + esi], 'C';
        mov byte ptr[edi + esi + 1], 'D';
        sub dword ptr[count + 12], 1;
        add ebx, 2;
        je add90;

    add100:
        cmp dword ptr[count + 16], 0;
        jle add90;
        mov esi, ebx;
        lea edi, [rom];
        mov byte ptr[edi + esi], 'C';
        sub dword ptr[count + 16], 1;
        add ebx, 1;
        jmp add100;

    add90:
        cmp dword ptr[count + 20], 0;
        jle add50;
        mov esi, ebx;
        lea edi, [rom];
        mov byte ptr[edi + esi], 'X';
        mov byte ptr[edi + esi + 1], 'C';
        sub dword ptr[count + 20], 1;
        add ebx, 2;
        je add10;

    add50:
        cmp dword ptr[count + 24], 0;
        jle add40;
        mov esi, ebx;
        lea edi, [rom];
        mov byte ptr[edi + esi], 'L';
        sub dword ptr[count + 24], 1;
        add ebx, 1;
        je add10;

    add40:
        cmp dword ptr[count + 28], 0;
        jle add10;
        mov esi, ebx;
        lea edi, [rom];
        mov byte ptr[edi + esi], 'X';
        mov byte ptr[edi + esi + 1], 'L';
        sub dword ptr[count + 28], 1;
        add ebx, 2;
        je add9;

    add10:
        cmp dword ptr[count + 32], 0;
        jle add9;
        mov esi, ebx;
        lea edi, [rom];
        mov byte ptr[edi + esi], 'X';
        sub dword ptr[count + 32], 1;
        add ebx, 1;
        jmp add10;

    add9:
        cmp dword ptr[count + 36], 0;
        jle add5;
        mov esi, ebx;
        lea edi, [rom];
        mov byte ptr[edi + esi], 'I';
        mov byte ptr[edi + esi + 1], 'X';
        sub dword ptr[count + 36], 1;
        add ebx, 2;
        je add1;

    add5:
        cmp dword ptr[count + 40], 0;
        jle add4;
        mov esi, ebx;
        lea edi, [rom];
        mov byte ptr[edi + esi], 'V';
        sub dword ptr[count + 40], 1;
        add ebx, 1;
        je add1;

    add4:
        cmp dword ptr[count + 44], 0;
        jle add1;
        mov esi, ebx;
        lea edi, [rom];
        mov byte ptr[edi + esi], 'I';
        mov byte ptr[edi + esi + 1], 'V';
        sub dword ptr[count + 44], 1;
        add ebx, 2;
        je addend;

    add1:
        cmp dword ptr[count + 48], 0;
        jle addend;
        mov esi, ebx;
        lea edi, [rom];
        mov byte ptr[edi + esi], 'I';
        sub dword ptr[count + 48], 1;
        add ebx, 1;
        jmp add1;
    }

    // OUTPUT
    _asm
    {
    addend:
        push txtoutput;
        call dword ptr printf;

        lea eax, rom;           // Load the address of the text into EAX
        push eax;               // Push the address onto the stack
        push eax;               // Push the address again (required by printf)
        call dword ptr printf;  // Push the format string onto the stack
        add esp, 12;
    }

    // SYS PAUSE
    _asm
    {
        push newline;
        call dword ptr printf;

        push _pause;
        call dword ptr system;
    }

    _asm
    {
        mov esp, saveesp;
    }

    return 0;
}