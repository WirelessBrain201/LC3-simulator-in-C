#include <stdio.h>
#include <stdlib.h>

/*Declares the print function*/
void printstatus(int r0, int r1, int r2, int r3, int r4, int r5, int r6, int r7, int pc, int ir, char *cc);

void main(int argc, char *argv[]){
    /*Declares the registers, pc, ir and cc variables and sets them to 0*/
    unsigned short r0=0, r1=0, r2=0, r3=0, r4=0, r5=0, r6=0, r7=0, pc=0, ir=0;
    char *cc = "Z";

    /*Opens the file as file*/
    FILE *file;
    file = fopen(argv[1] , "rb");

    /*Gets the amount of lines and stores it as linecount*/
    int line[1], linecount = 0;
    while (fread(line, 2, 1, file)!= 0){
        linecount++;
    }

    /*Sets the file position back to the start*/
    fseek(file, 0, SEEK_SET);

    /*Reads each line, and stores the 16 bit version as an element in the numbers array*/
    unsigned char linebytes[2];
    int numbers[linecount], count = 0;
    while (fread(linebytes, 1, 2, file) == 2){
        numbers[count] = linebytes[0] * 256;
        numbers[count] = numbers[count] | linebytes[1];
        count++;
    }

    /*Iterates through all the lines of machine code, executing all of them until it reaches a halt*/
    int i, ldaddress, dstreg, offset, op1, op2, mode, cctest, ccbits;
    for (i = 0; i < linecount; i++ ){

        /*If it's the first line, set the PC*/
        if (i == 0){
            pc = numbers[i];
        }

        /*Else, process the line as machine code*/
        else{
            int opcode = numbers[i] & 0xF000;
            pc++;
            ir = numbers[i];


            switch(opcode){

                /*If the line is a TRAP, end the program*/
                case 0xF000:
                    return;
                    break;

                /*If the opcode is for a LD, perform a LD operation*/
                case 0x2000:
                    ldaddress = i + (numbers[i] & 0x1FF) + 1;
                    dstreg = ((numbers[i] & 0xE00) / 512);
                    switch(dstreg){
                        case 0:
                            r0 = numbers[ldaddress];
                            cctest = r0;
                            break;
                        case 1:
                            r1 = numbers[ldaddress];
                            cctest = r1;
                            break;
                        case 2:
                            r2 = numbers[ldaddress];
                            cctest = r2;
                            break;
                        case 3:
                            r3 = numbers[ldaddress];
                            cctest = r3;
                            break;
                        case 4:
                            r4 = numbers[ldaddress];
                            cctest = r4;
                            break;
                        case 5:
                            r5 = numbers[ldaddress];
                            cctest = r5;
                            break;
                        case 6:
                            r6 = numbers[ldaddress];
                            cctest = r6;
                            break;
                        case 7:
                            r7 = numbers[ldaddress];
                            cctest = r7;
                            break;
                    }

                    if (cctest == 0){
                        cc = "Z";
                    }
                    else if (cctest < 0x7FFF){
                        cc = "P";
                    }

                    else if (cctest > 0x7FFF){
                        cc = "N";
                    }
                    break;

                /*If the opcode is for a LEA, perform a LEA operation*/
                case 0xE000:
                    offset = (numbers[i] & 0x1FF);
                    dstreg = ((numbers[i] & 0xE00) / 512);
                    switch(dstreg){
                        case 0:
                            r0 = pc + offset;
                            cctest = r0;
                            break;
                        case 1:
                            r1 = pc + offset;
                            cctest = r1;
                            break;
                        case 2:
                            r2 = pc + offset;
                            cctest = r2;
                            break;
                        case 3:
                            r3 = pc + offset;
                            cctest = r3;
                            break;
                        case 4:
                            r4 = pc + offset;
                            cctest = r4;
                            break;
                        case 5:
                            r5 = pc + offset;
                            cctest = r5;
                            break;
                        case 6:
                            r6 = pc + offset;
                            cctest = r6;
                            break;
                        case 7:
                            r7 = pc + offset;
                            cctest = r7;
                            break;
                    }

                    if (cctest == 0){
                        cc = "Z";
                    }
                    else if (cctest < 0x7FFF){
                        cc = "P";
                    }

                    else if (cctest > 0x7FFF){
                        cc = "N";
                    }
                    break;

                /*If the opcode is for a LDI, perform a LDI operation*/
                case 0xA000:
                    ldaddress = i + (numbers[i] & 0x1FF) + 1;
                    ldaddress = numbers[ldaddress] - numbers[0] + 1;
                    dstreg = ((numbers[i] & 0xE00) / 512);
                    switch(dstreg){
                        case 0:
                            r0 = numbers[ldaddress];
                            cctest = r0;
                            break;
                        case 1:
                            r1 = numbers[ldaddress];
                            cctest = r1;
                            break;
                        case 2:
                            r2 = numbers[ldaddress];
                            cctest = r2;
                            break;
                        case 3:
                            r3 = numbers[ldaddress];
                            cctest = r3;
                            break;
                        case 4:
                            r4 = numbers[ldaddress];
                            cctest = r4;
                            break;
                        case 5:
                            r5 = numbers[ldaddress];
                            cctest = r5;
                            break;
                        case 6:
                            r6 = numbers[ldaddress];
                            cctest = r6;
                            break;
                        case 7:
                            r7 = numbers[ldaddress];
                            cctest = r7;
                            break;
                    }
                    if (cctest == 0){
                        cc = "Z";
                    }
                    else if (cctest < 0x7FFF){
                        cc = "P";
                    }

                    else if (cctest > 0x7FFF){
                        cc = "N";
                    }
                    break;

                /*If the opcode is for a AND, perform a AND operation*/
                case 0x5000:
                    dstreg = ((numbers[i] & 0xE00) / 512);
                    op1 = ((numbers[i] & 0x1C0) / 64);
                    mode = ((numbers[i] & 0x20) / 32);
                    switch(op1){
                        case 0:
                            op1 = r0;
                            break;
                        case 1:
                            op1 = r1;
                            break;
                        case 2:
                            op1 = r2;
                            break;
                        case 3:
                            op1 = r3;
                            break;
                        case 4:
                            op1 = r4;
                            break;
                        case 5:
                            op1 = r5;
                            break;
                        case 6:
                            op1 = r6;
                            break;
                        case 7:
                            op1 = r7;
                            break;
                    }
                    switch(mode){
                        case 0:
                            op2 = (numbers[i] & 0x7);
                            switch(op2){
                                case 0:
                                op2 = r0;
                                break;
                            case 1:
                                op2 = r1;
                                break;
                            case 2:
                                op2 = r2;
                                break;
                            case 3:
                                op2 = r3;
                                break;
                            case 4:
                                op2 = r4;
                                break;
                            case 5:
                                op2 = r5;
                                break;
                            case 6:
                                op2 = r6;
                                break;
                            case 7:
                                op2 = r7;
                                break;
                            }
                            break;
                        case 1:
                            op2 = (numbers[i] & 0x1F);
                            break;
                    }
                    switch(dstreg){
                        case 0:
                            r0 = op1 & op2;
                            cctest = r0;
                            break;
                        case 1:
                            r1 = op1 & op2;
                            cctest = r1;
                            break;
                        case 2:
                            r2 = op1 & op2;
                            cctest = r2;
                            break;
                        case 3:
                            r3 = op1 & op2;
                            cctest = r3;
                            break;
                        case 4:
                            r4 = op1 & op2;
                            cctest = r4;
                            break;
                        case 5:
                            r5 = op1 & op2;
                            cctest = r5;
                            break;
                        case 6:
                            r6 = op1 & op2;
                            cctest = r6;
                            break;
                        case 7:
                            r7 = op1 & op2;
                            cctest = r7;
                            break;
                    }
                    if (cctest == 0){
                        cc = "Z";
                    }
                    else if (cctest < 0x7FFF){
                        cc = "P";
                    }

                    else if (cctest > 0x7FFF){
                        cc = "N";
                    }
                    break;

                /*If the opcode is for a NOT, perform a NOT operation*/
                case 0x9000:
                    dstreg = ((numbers[i] & 0xE00) / 512);
                    op1 = ((numbers[i] & 0x1C0) / 64);
                    switch(op1){
                        case 0:
                            op1 = r0;
                            break;
                        case 1:
                            op1 = r1;
                            break;
                        case 2:
                            op1 = r2;
                            break;
                        case 3:
                            op1 = r3;
                            break;
                        case 4:
                            op1 = r4;
                            break;
                        case 5:
                            op1 = r5;
                            break;
                        case 6:
                            op1 = r6;
                            break;
                        case 7:
                            op1 = r7;
                            break;
                    }
                    switch(dstreg){
                        case 0:
                            r0 = ~op1;
                            cctest = r0;
                            break;
                        case 1:
                            r1 = ~op1;
                            cctest = r1;
                            break;
                        case 2:
                            r2 = ~op1;
                            cctest = r2;
                            break;
                        case 3:
                            r3 = ~op1;
                            cctest = r3;
                            break;
                        case 4:
                            r4 = ~op1;
                            cctest = r4;
                            break;
                        case 5:
                            r5 = ~op1;
                            cctest = r5;
                            break;
                        case 6:
                            r6 = ~op1;
                            cctest = r6;
                            break;
                        case 7:
                            r7 = ~op1;
                            cctest = r7;
                            break;
                    }
                    if (cctest == 0){
                        cc = "Z";
                    }
                    else if (cctest < 0x7FFF){
                        cc = "P";
                    }

                    else if (cctest > 0x7FFF){
                        cc = "N";
                    }
                    break;

                /*If the opcode is for a ADD, perform a ADD operation*/
                case 0x1000:
                    dstreg = ((numbers[i] & 0xE00) / 512);
                    op1 = ((numbers[i] & 0x1C0) / 64);
                    mode = ((numbers[i] & 0x20) / 32);
                    switch(op1){
                        case 0:
                            op1 = r0;
                            break;
                        case 1:
                            op1 = r1;
                            break;
                        case 2:
                            op1 = r2;
                            break;
                        case 3:
                            op1 = r3;
                            break;
                        case 4:
                            op1 = r4;
                            break;
                        case 5:
                            op1 = r5;
                            break;
                        case 6:
                            op1 = r6;
                            break;
                        case 7:
                            op1 = r7;
                            break;
                    }
                    switch(mode){
                        case 0:
                            op2 = (numbers[i] & 0x7);
                            switch(op2){
                                case 0:
                                op2 = r0;
                                break;
                            case 1:
                                op2 = r1;
                                break;
                            case 2:
                                op2 = r2;
                                break;
                            case 3:
                                op2 = r3;
                                break;
                            case 4:
                                op2 = r4;
                                break;
                            case 5:
                                op2 = r5;
                                break;
                            case 6:
                                op2 = r6;
                                break;
                            case 7:
                                op2 = r7;
                                break;
                            }
                            break;
                        case 1:
                            op2 = (numbers[i] & 0x1F);
                            break;
                    }
                    switch(dstreg){
                        case 0:
                            r0 = op1 + op2;
                            cctest = r0;
                            break;
                        case 1:
                            r1 = op1 + op2;
                            cctest = r1;
                            break;
                        case 2:
                            r2 = op1 + op2;
                            cctest = r2;
                            break;
                        case 3:
                            r3 = op1 + op2;
                            cctest = r3;
                            break;
                        case 4:
                            r4 = op1 + op2;
                            cctest = r4;
                            break;
                        case 5:
                            r5 = op1 + op2;
                            cctest = r5;
                            break;
                        case 6:
                            r6 = op1 + op2;
                            cctest = r6;
                            break;
                        case 7:
                            r7 = op1 + op2;
                            cctest = r7;
                            break;
                    }
                    if (cctest == 0){
                        cc = "Z";
                    }
                    else if (cctest < 0x7FFF){
                        cc = "P";
                    }

                    else if (cctest > 0x7FFF){
                        cc = "N";
                    }
                    break;

                /*If the opcode is for a BRZ, perform a BRZ operation*/
                case 0x0000:
                    offset = (numbers[i] & 0x1FF);
                    ccbits = (numbers[i] & 0xE00);
                    if (((ccbits & 0x800) == 0x800) && (cc == "N")){
                        i = i + offset;
                        pc = pc + offset;
                    }
                    else if (((ccbits & 0x400) == 0x400) && (cc == "Z")){
                        i = i + offset;
                        pc = pc + offset;
                    }
                    else if (((ccbits & 0x200) == 0x200) && (cc == "P")){
                        i = i + offset;
                        pc = pc + offset;
                    }
                    break;
            }
            }
            printf("after executing instruction\t0x%04x\n", ir);
            printstatus(r0, r1, r2, r3, r4, r5, r6, r7, pc, ir, cc);
    }

    /*Closes the file*/
    fclose(file);
}

/*The print function*/
void printstatus(int r0, int r1, int r2, int r3, int r4, int r5, int r6, int r7, int pc, int ir, char *cc){
    printf("R0\t0x%04x\n", r0);
    printf("R1\t0x%04x\n", r1);
    printf("R2\t0x%04x\n", r2);
    printf("R3\t0x%04x\n", r3);
    printf("R4\t0x%04x\n", r4);
    printf("R5\t0x%04x\n", r5);
    printf("R6\t0x%04x\n", r6);
    printf("R7\t0x%04x\n", r7);
    printf("PC\t0x%04x\n", pc);
    printf("IR\t0x%04x\n", ir);
    printf("CC\t%s\n", cc);
    printf("==================\n");
}
