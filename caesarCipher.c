#include<stdio.h>
void encryptCipher(char str[], int shift){
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] >= 'a' && str[i] <= 'z'){
            str[i] = str[i] + shift;
            if(str[i] > 'z'){
                str[i] = str[i] - 26;
            }
        }
        else if(str[i] >= 'A' && str[i] <= 'Z'){
            str[i] = str[i] + shift;
            if(str[i] > 'Z'){
                str[i] = str[i] - 26;
            }
        }
    }
}

void decryptCipher(char str[], int shift) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - shift;
            if (str[i] < 'a') {
                str[i] = str[i] + 26;
            }
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] - shift;
            if (str[i] < 'A') {
                str[i] = str[i] + 26;
            }
        }
    }
}

int main(){
    char str[100];
    int shift;
    int choice;
    do{
        printf("1. Encrypt\n2. Decrypt\n3.Exit\n>>>");
        scanf("%d", &choice);
        getchar();
        switch(choice){
            case 1:
                printf("Enter the string: ");
                scanf("%[^\n]s", str);
                getchar();
                printf("Enter the shift: ");
                scanf("%d", &shift);
                getchar();
                encryptCipher(str, shift);
                printf("Encrypted string: %s\n", str);
                break;
            case 2:
               printf("Enter the string: ");
                scanf("%[^\n]s", str);
                getchar();
                printf("Enter the shift: ");
                scanf("%d", &shift);
                getchar();
                decryptCipher(str, shift);
                printf("Encrypted string: %s\n", str);
                break;
            case 3:
                return 0;
                break;
            default:
            printf("Invalid choice\n");
            break;
        }
    }while(choice != 3);
    return 0;
}

