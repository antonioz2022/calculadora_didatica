#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ## Autor: Antonio Albuquerque, Turma: 3º B
// Primeira questão: Data = 24/08/2024, 14:06
// Segunda questão: Data = 24/08/2024, 16:39

char *decimalToBinary(int num);
char *decimalToOctal(int num);
char *decimalToHexa(int num);
char *decimalToBCD(int num);
char *decimalTo2Complement(int num);
void reverseString(char *string);

int main()
{
    int numero;
    int opcao;

    printf("Digite um numero: ");
    scanf("%d", &numero);

    printf("----ESCOLHA UMA OPCAO\n");
    printf("1 - Converter para binario.\n");
    printf("2 - Converter para Octal.\n");
    printf("3 - Converter para Hexadecimal. \n");
    printf("4 - Converter Para BCD.\n");
    printf("5 - Converter para complemento a 2 com 16 bits.\n");
    scanf("%d", &opcao);

    if (opcao == 1)
    {
        char *numero_binario = decimalToBinary(numero);
        if (numero_binario != NULL)
        {
            printf("Numero em binario: %s\n", numero_binario);
            free(numero_binario);
        }
    }
    else if (opcao == 2)
    {
        char *numero_octal = decimalToOctal(numero);
        if (numero_octal != NULL)
        {
            printf("Numero em octal: %s\n", numero_octal);
            free(numero_octal);
        }
    }
    else if (opcao == 3)
    {
        char *numero_hexa = decimalToHexa(numero);
        if (numero_hexa != NULL)
        {
            printf("Numero em hexadecimal: %s\n", numero_hexa);
            free(numero_hexa);
        }
    }
    else if (opcao == 4)
    {
        char *numero_bcd = decimalToBCD(numero);
        if (numero_bcd != NULL)
        {
            printf("Numero em BCD: %s\n", numero_bcd);
            free(numero_bcd);
        }
    }
    else if (opcao == 5)
    {
        char *numero_2complement = decimalTo2Complement(numero);
        if (numero_2complement != NULL)
        {
            printf("Numero em complemento de 2 16 bits: %s\n", numero_2complement);
            free(numero_2complement);
        }
    }

    return 0;
}

char *decimalToFloatingPoint(float num)
{
    if (num == 0)
        return "0";

    char *binario = (char *)malloc(33 * sizeof(char));

    if (binario == NULL)
    {
        printf("malloc error.");
        exit(0);
    }

    memset(binario, '\0', 33);


}

char *decimalTo2Complement(int num)
{
    if (num == 0)
        return "0";

    int temp_num = num;
    int negative = 0;

    if (num < 0)
        negative = 1;

    char *binario = (char *)malloc(33 * sizeof(char));

    if (binario == NULL)
    {
        printf("malloc error.");
        exit(0);
    }

    memset(binario, '\0', 33);

    while (num != 0)
    {
        if (num % 2 == 0)
        {
            strcat(binario, "0");
        }
        else
        {
            strcat(binario, "1");
        }
        // printf("%d / 2 = %d, resto = %d\n", num, num / 2, num % 2);
        num = num / 2;
    }

    reverseString(binario);

    printf("%d em binario = %s\n", abs(temp_num), binario);

    int num_len = strlen(binario);

    if (negative == 1)
    {
        for (int i = 0; i < num_len; i++)
        {
            if (binario[i] == '0')
            {
                binario[i] = '1';
            }
            else
            {
                binario[i] = '0';
            }
        }
        printf("Depois de inverter = %s\n", binario);
        for (int i = 1; i <= num_len; i++)
        {
            if (binario[num_len - i] == '0')
            {
                binario[num_len - i] = '1';
                break;
            }
            else
            {
                binario[num_len - i] = '0';
            }
        }
        printf("Depois de somar com 1 = %s\n", binario);
    }

    if (num_len < 16)
    {
        char bits[32] = "";
        for (int i = 0; i < 16 - num_len; i++)
        {
            if (negative == 1)
            {
                strcat(bits, "1");
            }
            else
            {
                strcat(bits, "0");
            }
        }

        printf("Adiciona %d vezes o %c para completar 16 bits.\n", 16 - num_len, bits[0]);
        strcat(bits, binario);
        strcpy(binario, bits);
    }

    return binario;
}

char *decimalToBinary(int num)
{
    if (num == 0)
        return "0";

    if (num < 0)
    {
        printf("Essa opcao nao aceita numeros negativos.");
        exit(0);
    }

    char *binario = (char *)malloc(33 * sizeof(char));

    if (binario == NULL)
    {
        printf("malloc error.");
        exit(0);
    }

    memset(binario, '\0', 33);

    while (num > 0)
    {
        if (num % 2 == 0)
        {
            strcat(binario, "0");
        }
        else
        {
            strcat(binario, "1");
        }
        printf("%d / 2 = %d, resto = %d\n", num, num / 2, num % 2);
        num = num / 2;
    }

    reverseString(binario);

    return binario;
}

char *decimalToBCD(int num)
{
    if (num == 0)
        return "0000";

    if (num < 0)
    {
        printf("Essa opcao nao aceita numeros negativos.");
        exit(0);
    }

    char *BCD = (char *)malloc(129 * sizeof(char));

    if (BCD == NULL)
    {
        printf("malloc error.");
        exit(0);
    }
    memset(BCD, '\0', 129);

    char number[64];
    sprintf(number, "%d", num);
    int len = strlen(number);

    for (int i = 0; i < len; i++)
    {
        char bcd_digit[8] = "";
        int int_digit = number[i] - '0';

        while (int_digit > 0)
        {
            if (int_digit % 2 == 0)
            {
                strcat(bcd_digit, "0");
            }
            else
            {
                strcat(bcd_digit, "1");
            }
            int_digit = int_digit / 2;
        }
        int bcd_len = strlen(bcd_digit);
        if (bcd_len < 4)
        {
            for (int i = 0; i < 4 - bcd_len; i++)
            {
                strcat(bcd_digit, "0");
            }
        }

        reverseString(bcd_digit);
        strcat(BCD, bcd_digit);
        printf("%c = %s em binario\n", number[i], bcd_digit);
        if (i != len - 1)
            strcat(BCD, " ");
    }

    return BCD;
}

char *decimalToOctal(int num)
{
    if (num == 0)
        return "0";

    if (num < 0)
    {
        printf("Essa opcao nao aceita numeros negativos.");
        exit(0);
    }

    char *octal = (char *)malloc(33 * sizeof(char));

    if (octal == NULL)
    {
        printf("malloc error.");
        exit(0);
    }

    memset(octal, '\0', 33);

    while (num > 0)
    {
        if (num % 8 == 0)
        {
            strcat(octal, "0");
        }
        else
        {
            char digit[16];
            sprintf(digit, "%d", num % 8);
            strcat(octal, digit);
        }
        printf("%d / 8 = %d, resto = %d\n", num, num / 8, num % 8);
        num = num / 8;
    }

    reverseString(octal);

    return octal;
}

char *decimalToHexa(int num)
{
    if (num == 0)
        return "0";

    if (num < 0)
    {
        printf("Essa opcao nao aceita numeros negativos.");
        exit(0);
    }

    char *hexa = (char *)malloc(33 * sizeof(char));

    if (hexa == NULL)
    {
        printf("malloc error.");
        exit(0);
    }

    memset(hexa, '\0', 33);
    printf("Em hexadecimal,\n");
    printf("10 = A\n");
    printf("11 = B\n");
    printf("12 = C\n");
    printf("13 = D\n");
    printf("14 = E\n");
    printf("15 = F\n");
    while (num > 0)
    {
        if (num % 16 == 0)
        {
            strcat(hexa, "0");
        }
        else
        {
            char digit[16];
            if (num % 16 < 10)
            {
                sprintf(digit, "%d", num % 16);
            }
            else
            {
                if (num % 16 == 10)
                {
                    strcpy(digit, "A");
                }
                else if (num % 16 == 11)
                {
                    strcpy(digit, "B");
                }
                else if (num % 16 == 12)
                {
                    strcpy(digit, "C");
                }
                else if (num % 16 == 13)
                {
                    strcpy(digit, "D");
                }
                else if (num % 16 == 14)
                {
                    strcpy(digit, "E");
                }
                else if (num % 16 == 15)
                {
                    strcpy(digit, "F");
                }
            }

            strcat(hexa, digit);
        }
        printf("%d / 16 = %d, resto = %d\n", num, num / 16, num % 16);
        num = num / 16;
    }

    reverseString(hexa);

    return hexa;
}
void reverseString(char *string)
{
    int count = 0;
    int index = strlen(string) - 1;

    char *temp = (char *)malloc((index + 2) * sizeof(char));

    if (temp == NULL)
    {
        printf("malloc error.");
        exit(0);
    }

    strcpy(temp, string);

    while (index >= 0)
    {
        string[count] = temp[index];
        count += 1;
        index -= 1;
    }

    free(temp);
}