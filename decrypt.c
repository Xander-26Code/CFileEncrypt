#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main () {
    int ch;
    FILE *kptr = fopen("key.bin", "rb");
    if (kptr == NULL) {
        printf("Error opening key file.\n");
        return 1;
    }

    FILE *eptr = fopen("encrypted_file.bin", "rb");

    FILE *dptr = fopen("decrypted_file.txt", "w");
    if (eptr == NULL || dptr == NULL) {
        printf("Error opening encrypted or decrypted file.\n");
        fclose(kptr);
        if (eptr) fclose(eptr);
        if (dptr) fclose(dptr);
        return 1;
    }
    while((ch = fgetc(eptr)) != EOF) 
    {
        int keyByte = fgetc(kptr);
        ch = ch ^ keyByte; // Simple XOR decryption
        fputc(ch, dptr);
    }
    fclose(kptr);
    fclose(eptr);
    fclose(dptr);
    return 0;
}