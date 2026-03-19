#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

void generateKey(int length) {
    srand(time(NULL));
    FILE *kptr = fopen("key.bin", "wb");
    if (kptr == NULL) {
        printf("Error creating key file.\n");
        return;
    }

    for (int i = 0; i < length; i++) {
        int keyByte = rand();
        fwrite(&keyByte, sizeof(int), 1, kptr);
    }
    fclose(kptr);
}
int main() 
{
    int ch;
    FILE *fptr = fopen("file.txt", "r");
    if (fptr == NULL) 
    {
        printf("Error opening file.\n");
        return 1;
    }

    fseek(fptr, 0, SEEK_END); // Move the pointer to the end of the file   
    long fileSize = ftell(fptr);
    fseek(fptr, 0, SEEK_SET); // Move the pointer back to the beginning of the file

    generateKey(fileSize);

    FILE *kptr = fopen("key.bin", "rb");
    if (kptr == NULL) {
        printf("Error opening key file.\n");
        fclose(fptr);
        return 1;
    }

    FILE *eptr = fopen("encrypted_file.bin", "wb");
    if (eptr == NULL) {
        printf("Error creating encrypted file.\n");
        fclose(fptr);
        fclose(kptr);
        return 1;
    }

    while((ch = fgetc(fptr)) != EOF) 
    {
        // Encryption logic would go here, using the generated key
        int  keyByte = fgetc(kptr);
        ch = ch ^ keyByte; // Simple XOR encryption
        fputc(ch, eptr);
    }
    fclose(fptr);
    fclose(kptr);
    fclose(eptr);

    return 0;
}





