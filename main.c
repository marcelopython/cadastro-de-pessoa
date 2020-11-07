#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


#define typeof(var) _Generic( (var),\
char: "Char",\
int: "Integer",\
float: "Float",\
char *: "String",\
void *: "Pointer",\
default: "Undefined")


int main()
{
    int item;

	if(login()){
        while(true){
            item = menu();
            printf("%u", item);
            if(item == 1){
                formPeople();
            }else if(item == 3){
                exit(0);
                break;
            }
         }
    }

    return 1;
}

int menu()
{
    int item;
    printf("Menu\n");
    printf("1) Cadastrar pessoa.\n");
    printf("2) Ver pessoas.\n");
    printf("3) Sair.\n");

    printf("\nDigite a opção: ");
    scanf("%u", &item);
    flush_in();
    return item;
}
void flush_in()
{
   int ch;

   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}
formPeople()
{
    const char *convenience[5] = {"Diabete","Obesidade","Hipertensão","Tuberculose","Outros"};
    char nome[60];
    int i, convenience_selected;
    struct Pessoa{
        char name[60];
        char address[120];
        char email[60];
        char date_diagnosis[10];
        char birthday[10];
        char convenience[30];
        int cpf;
        int phone;
    };

    struct Pessoa pessoa;
    printf("\nCADASTRO DE PACIENTE\n");

    /*nome*/
    printf("Nome: ");
    fflush(stdin);
    fgets(pessoa.name, 60, stdin);
    flush_in();

    /*CPF*/
    printf("CPF: ");
    scanf("%u", &pessoa.cpf);
    flush_in();

    /*Endereço*/
    printf("Endereço: ");
    fflush(stdin);
    fgets(pessoa.address, 120, stdin);
    flush_in();

    /*telefone*/
    printf("Telefone: ");
    scanf("%u", &pessoa.phone);
    flush_in();

    /*Data de nascimento*/
    printf("Data de nascimento: ");
    scanf("%s", &pessoa.birthday);
    flush_in();

    /*Email*/
    printf("E-mail: ");
    scanf("%s", &pessoa.email);
    flush_in();

    /*Data de dagnostico*/
    printf("Data de diagnostico: ");
    scanf("%s", &pessoa.date_diagnosis);
    flush_in();

    printf("Selecione a comodidade!\n");
    for(i = 1; i < strlen(convenience); i++){
        printf("%u) %s \n", i, convenience[i-1]);
    }

    /*Comodidade*/
    printf("Comodidade ");
    scanf("%i", &convenience_selected);
    strcpy(pessoa.convenience, convenience[convenience_selected-1]);

    /*Salva novo pessoa*/
    FILE *persons;

    persons = fopen("persons.txt", "at");

    fprintf(persons, "\n{%s %s %s %s %s %s %u %u}", pessoa.name, pessoa.address, pessoa.email, pessoa.date_diagnosis, pessoa.birthday, pessoa.convenience,
    pessoa.cpf, pessoa.phone);

    /**/
    calcIdade(pessoa.birthday);

    fclose(persons);
}
/*calcular a idade da pessoa cadastrada*/
int calcIdade(char idade[10])
{

    time_t current_time;
	struct tm *time_info;
	char year[5], birthday[5];
	current_time = time(NULL);
	time_info = localtime(&current_time);

	strftime(year, 5, "%Y", time_info);
    birthday[0] = idade[6];
    birthday[1] = idade[7];
    birthday[2] = idade[8];
    birthday[3] = idade[9];

    //printf("%s", birthday);
	//year;
	int teste = birthday;

    printf("idade %s\n\n", teste);
}

login()
{

   FILE *user;
   char data[15], dataLoginInFile[60], dataPasswordInFile[60], login[60], password[60];
   int i = 0;

   printf("Digitel o login: ");
   scanf("%s", &login);
   flush_in();

   printf("Digite a senha: ");
   scanf("%s", &password);
   flush_in();

   user = fopen("users.txt", "rt");//Se ouver erro o pontero apontara para NULL

   if(user == NULL){
        printf("Não foi possivel abrir o arquivo!");
        exit(0);
   }
    while(fscanf(user, "%s", &data)){

        if(i == 0){
            strcpy(dataLoginInFile, data);
        }else if(i == 1){
            strcpy(dataPasswordInFile, data);
            break;
        }
        i++;
    }

    fclose(user);

    if(strcmp(login, dataLoginInFile) != 0 || strcmp(password, dataPasswordInFile) != 0){
        printf("Dados invalido!");
        exit(0);
    }
    return true;
}
