#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Estrutura responsável por receber os dados dos pilotos 
struct f1_pilotos {
    char Nome_piloto[60];
    int id;
    int idade;
    char sexo;
    char pais[20];
};
struct f1_pilotos piloto[20];

// Estrutura resposável por receber dados de melhores voltas, para posterior amazenamento
// dentro da estrutura de dados dos circuitos

struct melhor_volta{
    int id_piloto;
    char nome_equipe[40];
    char tempo_volta[12];
    char data_melhor[10];
    int id_do_circuito;
};


// Estrutura Resposável por Amazenar os Dados dos Circuitos
struct circuitos{
    int id;
    char nome[60];
    char pais[40];
    char distancia[12];
    struct melhor_volta fastest;
};
struct circuitos pistas[22];

struct historico{
    struct melhor_volta dados;
};
struct historico pilotos_f1[600];

// Função Para Cadastrar um Novo Piloto
void cadastro_piloto(int* pos){
	int i=0;
    int validacao;

    do{

        validacao=0;
        printf("\nId do piloto: ");
        fflush(stdin);

        scanf("%d",&piloto[*pos].id);
        if(piloto[*pos].id < 100 || piloto[*pos].id > 500){
        	validacao = 1;
        	printf("ID invalido\nO ID do piloto deve estar entre 100 e 500");
		}else{		
	        if(*pos>0){
	            for(i=0;i<*pos;i++){
	                if(piloto[*pos].id == piloto[i].id){
	                    printf("Um piloto com esse id ja foi registrado\n");
	                    validacao = 1;
	                }
	            }
	        }
	    }

    }while(validacao==1);

    do{

        validacao=0;
        printf("\nDigite o nome do piloto: ");
        fflush(stdin);
        scanf("%[^\n]s",&piloto[*pos].Nome_piloto);

        if(*pos>0){

            for(i=0;i<*pos;i++){

                if(strcmp(piloto[*pos].Nome_piloto,piloto[i].Nome_piloto)==0){

                    printf("Um piloto com esse nome ja foi registrado\n");
                    validacao = 1;

                }
            }
        }

    }while(validacao==1);

    printf("\nIdade do piloto: ");
    fflush(stdin);
    scanf("%d",&piloto[*pos].idade);
    
    printf("\nDigite o sexo do(a) piloto(a): ");
    fflush(stdin);
    scanf("%c",&piloto[*pos].sexo);
    
    printf("\nDigite o pais do(a) piloto(a): ");
    fflush(stdin);
    scanf("%[^\n]s",&piloto[*pos].pais);
}

// Função Para Cadastrar Uma Pista Nova
void cadastro_circuito(int* qtd,int *id_cad, int* pos, int* n_h){

    char volta_temporaria[12]; 
    int id_temporario;
    int validacao;
    int i=0;
    
    do{

        validacao = 0;
        printf("\nDigite o nome do GP: ");
        fflush(stdin);
        scanf("%[^\n]s",&pistas[*qtd].nome);

        if(*qtd>0){

            for(i=0;i<*qtd;i++){

                if(strcmp(pistas[*qtd].nome,pistas[i].nome)==0){

                    printf("Nao e possivel cadastrar uma pista mais de duas vezes\n");
                    validacao = 1;

                }
            }
        }

    }while(validacao==1);

    pistas[*qtd].id = *id_cad;
    printf("Tamanho do circutio em Kms: ");
    scanf("%d",&pistas[*qtd].distancia);
    printf("Qual o pais do Circuito: ");
    fflush(stdin);
    scanf("%[^\n]s",&pistas[*qtd].pais);

    if(*pos>0){

        printf("Cadastrar volta mais rapida atual: ");
        fflush(stdin);
        scanf("%[^\n]s",&volta_temporaria);
        printf("Digite o ID do piloto que fez a volta atual: ");
        fflush(stdin);
        scanf("%d",&id_temporario);

        for(i=0;i<*pos;i++){

            if(id_temporario==piloto[i].id){

                printf("Piloto encontrado!\n");
                printf("Digite a data da volta (DD/MM/YYYY): ");
                fflush(stdin);
                scanf("%[^\n]s",&pistas[*qtd].fastest.data_melhor);
                printf("Digite o nome da equipe do piloto: ");
                fflush(stdin);
                scanf("%[^\n]s",&pistas[*qtd].fastest.nome_equipe);
                printf("Dados da volta mais rapida e piloto foram registrados\n");
                fflush(stdin);
                pistas[*qtd].fastest.id_piloto = id_temporario;
                fflush(stdin);
                strcpy(pistas[*qtd].fastest.tempo_volta,volta_temporaria);

                pilotos_f1[*n_h].dados.id_do_circuito = *id_cad;
                fflush(stdin);
                pilotos_f1[*n_h].dados.id_piloto = id_temporario;
                fflush(stdin);
                strcpy(pilotos_f1[*n_h].dados.data_melhor,pistas[*qtd].fastest.data_melhor);
                fflush(stdin);
                strcpy(pilotos_f1[*n_h].dados.nome_equipe,pistas[*qtd].fastest.nome_equipe);
                fflush(stdin);
                strcpy(pilotos_f1[*n_h].dados.tempo_volta,volta_temporaria);

            }else{
                
                fflush(stdin);
                strcpy(pistas[*qtd].fastest.tempo_volta,"7.12.256");
                fflush(stdin);
                pistas[*qtd].fastest.id_piloto = NULL;
                fflush(stdin);
                strcpy(pistas[*qtd].fastest.data_melhor,"00/00/0000");
                printf("Piloto não encontrado\n");

            } 
        }
    }else{

        fflush(stdin);
        strcpy(pistas[*qtd].fastest.tempo_volta,"7.12.256");
        fflush(stdin);
        pistas[*qtd].fastest.id_piloto = NULL;
        fflush(stdin);
        strcpy(pistas[*qtd].fastest.data_melhor,"00/00/0000");
        printf("\nNao e possivel atribuir uma volta rapida pois\nnenhum piloto foi cadastrado ate o momento\n");

    }
}

void cadastro_volta_mais_rapida(int* pos, int* n_list_c, int* n_h){

    char tempo_volta_temporario[12], data[12];
    int id_temp_piloto;
    int id_temp_circuito;
    int verificacao,verificacao2;
    int i=0,j=0,k=0,l=0;
    
        do{

            verificacao = 0;
            printf("\nDigite o ID do circuito: ");
            fflush(stdin);
            scanf("%d",&id_temp_circuito);

            for(i=0;i<*n_list_c;i++){

                if(id_temp_circuito==pistas[i].id){

                    printf("\nDados do circuito encontrado"); 
                    printf("\nDigite o tempo de volta: ");
                    fflush(stdin);
                    scanf("%[^\n]s",&tempo_volta_temporario);

                    for(j=0;j<*n_list_c;j++){

                        if(strcmp(tempo_volta_temporario,pistas[i].fastest.tempo_volta)<0){

                            do{

                                verificacao2 = 0;

                                printf("\nDigite o ID do piloto: ");
                                fflush(stdin);
                                scanf("%d",&id_temp_piloto);

                                for(k=0;k<*pos;k++){

                                    if(id_temp_piloto==piloto[i].id){

                                        printf("\nOs Dados do piloto foram encontrados");
                                        printf("\nDigite a data da volta (DD/MM/YYYY): ");
                                        fflush(stdin);
                                        scanf("%[^\n]s",&data);
                                        
                                        for(l = 0; l < *n_list_c; l++){

                                            if(strcmp(data,pistas[l].fastest.data_melhor) == 0){

                                                printf("\nUm piloto so pode ter melhor volta em um circuito em datas diferentes\n");

                                            }else{
                                                
                                                printf("Digite o nome da equipe do piloto: ");
                                                fflush(stdin);
                                                scanf("%[^\n]s",&pistas[i].fastest.nome_equipe);
                                                fflush(stdin);
                                                strcpy(pistas[i].fastest.data_melhor,data);
                                                fflush(stdin);
                                                pistas[i].fastest.id_piloto = id_temp_piloto;
                                                fflush(stdin);
                                                pistas[i].fastest.id_do_circuito = id_temp_circuito;
                                                fflush(stdin);
                                                strcpy(pistas[i].fastest.tempo_volta, tempo_volta_temporario);

                                                fflush(stdin);
                                                pilotos_f1[*n_h].dados.id_do_circuito = id_temp_circuito;
                                                fflush(stdin);
                                                pilotos_f1[*n_h].dados.id_piloto = id_temp_piloto;
                                                fflush(stdin);
                                                strcpy(pilotos_f1[*n_h].dados.data_melhor,data);
                                                fflush(stdin);
                                                strcpy(pilotos_f1[*n_h].dados.nome_equipe,pistas[i].fastest.nome_equipe);
                                                fflush(stdin);
                                                strcpy(pilotos_f1[*n_h].dados.tempo_volta,tempo_volta_temporario);

                                                printf("Dados registrados\n");
                                            }
                                        }

                                    }else{
                                        verificacao2 = 1;
                                        printf("\nNao foi encontrado nenhum piloto com esse ID");
                                        printf("\nDigite o ID corretamente\n");
                                    }
                                }

                            }while(verificacao2==1);

                        }else{

                            do{

                                verificacao2 = 0;

                                printf("\nDigite o ID do piloto: ");
                                fflush(stdin);
                                scanf("%d",&id_temp_piloto);

                                for(k=0;k<*pos;k++){

                                    if(id_temp_piloto==piloto[i].id){

                                        printf("\nOs Dados do piloto foram encontrados");
                                        printf("\nDigite a data da volta (DD/MM/YYYY): ");
                                        fflush(stdin);
                                        scanf("%[^\n]s",&data);
                                        
                                        for(l = 0; l < *n_list_c; l++){

                                            if(strcmp(data,pistas[l].fastest.data_melhor) == 0){

                                                printf("\nUm piloto so pode ter melhor volta em um circuito em datas diferentes\n");

                                            }else{
                                                
                                                printf("Digite o nome da equipe do piloto: ");
                                                fflush(stdin);
                                                scanf("%[^\n]s",&pilotos_f1[*n_h].dados.nome_equipe);
                                                fflush(stdin);
                                                pilotos_f1[*n_h].dados.id_do_circuito = id_temp_circuito;
                                                fflush(stdin);
                                                pilotos_f1[*n_h].dados.id_piloto = id_temp_piloto;
                                                fflush(stdin);
                                                strcpy(pilotos_f1[*n_h].dados.data_melhor,data);
                                                fflush(stdin);
                                                strcpy(pilotos_f1[*n_h].dados.tempo_volta,tempo_volta_temporario);

                                                printf("Dados registrados\n");
                                            }
                                        }

                                    }else{
                                        verificacao2 = 1;
                                        printf("\nNao foi encontrado nenhum piloto com esse ID");
                                        printf("\nDigite o ID corretamente\n");
                                    }
                                }

                            }while(verificacao2 == 1);

                        }
                    }

                }else{
                    
                    printf("\nNão foi encontrado nenhum circuito com esse ID");
                    printf("\nDigite o ID corretamente");

                }
            }

        }while(verificacao==1);
}

void lista_circuitos(int *list_circuits){
	int i=0;
    for(i=0; i<*list_circuits;i++){
        printf("---------------------------\n");
        printf("\nNome do Circuito: %s",pistas[i].nome);
        printf("\nID do circuito: %d\n",pistas[i].id);
    }
}

void lista_pilotos(int* n_pilot){
	int i=0;
    if(*n_pilot>0){
        printf("Pilotos Cadastrados no sistema");
        for(i = 0; i < *n_pilot; i++){
            printf("\n--------------------------------------\n");
            printf("\nNome do(a) piloto(a): %s",piloto[i].Nome_piloto);
            printf("\nID do(a) piloto(a): %d",piloto[i].id);
        }
    }
}

void list_driver_circuit_time(int *n_h, int *circuits){
    int contador = 0,i=0;
    char tempo_volta[12];

    printf("Digite o tempo de volta que deseja buscar: ");
    fflush(stdin);
    scanf("%[^\n]s",&tempo_volta);

    printf("\n\nPilotos com tempo de volta menores que o informado");

    for(i = 0; i < *n_h; i++){

        if((strcmp(tempo_volta,pilotos_f1[i].dados.tempo_volta)>0 || strcmp(tempo_volta,pilotos_f1[i].dados.tempo_volta) == 0)){
            printf("\n-------------------------------------");
            printf("\nID do piloto: %d",pilotos_f1[i].dados.id_piloto);
            printf("\nID do circuito: %d",pilotos_f1[i].dados.id_do_circuito);
            printf("\nTempo de volta do piloto: %s",pilotos_f1[i].dados.tempo_volta);
            printf("\nData da volta: %s",pilotos_f1[i].dados.data_melhor);
            contador++;
        }
    }
    if(contador<=0){
        printf("\nNenhum piloto foi encontrado com um tempo de volta menor do que o informado\n");
    }

    printf("\n\nCircuitos com tempo de volta menores do que o informado");
    contador = 0;
    for(i=0; i< *circuits; i++){
        if(strcmp(tempo_volta,pistas[i].fastest.tempo_volta)  > 0 || strcmp(tempo_volta,pistas[i].fastest.tempo_volta) == 0){
            printf("\n-------------------------------------");
            printf("\nNome do circuito: %s",pistas[i].nome);
            printf("\nID do circuito: %d",pistas[i].id);
            printf("\nTempo de volta: %s",pistas[i].fastest.tempo_volta);
            printf("\nData da volta: %s",pistas[i].fastest.data_melhor);
            contador++;
        }
    }
    if(contador<=0){
        printf("\nNenhum circuito foi encontrado com um tempo de volta menor do que o informado\n");
    }
    contador = 0;
    printf("\n\nEquipe(s) com tempo de volta menores que o informado");
    for(i = 0; i < *n_h; i++){

        if(strcmp(tempo_volta,pilotos_f1[i].dados.tempo_volta) > 0 || strcmp(tempo_volta,pilotos_f1[i].dados.tempo_volta) == 0){
            printf("\n-------------------------------------");
            printf("\nNome da equipe: %s",pilotos_f1[i].dados.nome_equipe);
            printf("\nID do circuito: %d",pilotos_f1[i].dados.id_do_circuito);
            printf("\nTempo de volta: %s",pilotos_f1[i].dados.tempo_volta);
            printf("\nData da volta: %s\n",pilotos_f1[i].dados.data_melhor);
            contador++;
        }
    }
    if(contador<=0){
        printf("\nNenhuma equipe foi encontrada com um tempo de volta menor do que o informado\n");
    }

}

void todos_os_dados(int* n_circuits, int* history, int* drivers){

    int i=0;

	if(*n_circuits>0){
		printf("Pistas Cadastradas\n");
	    for(i = 0; i < *n_circuits; i++){
	    	printf("\n-------------------------------");
	        printf("\nNome da pista: %s",pistas[i].nome);
	        printf("\nID da pista: %d",pistas[i].id);
	        printf("\nPais da pista: %s", pistas[i].pais);
	        printf("\nVolta Mais rapida da pista: %s",pistas[i].fastest.tempo_volta);
	    }
	}else{
		printf("\nNenhuma pista foi cadastrada\n");
	}
	if(*drivers>0){
	    printf("Pilotos Cadastrados\n");
	    for(i = 0; i < *drivers; i++){
	    	printf("\n-------------------------------");
	        printf("\nNome do piloto: %s",piloto[i].Nome_piloto);
	        printf("\nID do piloto: %d",piloto[i].id);
	        printf("\nIdade do Piloto: %d",piloto[i].idade);
	        printf("\nSexo do(a) piloto(a): %c",piloto[i].sexo);
            printf("\nPais do(a) piloto(a): %s",piloto[i].pais);
	    }
	}else{
		printf("\nNenhum piloto foi cadastrado\n");
	}
	if(*history>0){	
	    printf("Dados de voltas\n");
	    for(i = 0;i<*history;i++){
	    	printf("\n--------------------------");
	    	printf("\nID do piloto: %d",pilotos_f1[i].dados.id_piloto);
	    	printf("\nID do circuito: %d",pilotos_f1[i].dados.id_do_circuito);
	    	printf("\nNome da Equipe: %s",pilotos_f1[i].dados.nome_equipe);
	    	printf("\nTempo de volta: %s",pilotos_f1[i].dados.tempo_volta);
	    	printf("\nData de volta: %s",pilotos_f1[i].dados.data_melhor);
		}
	}else{
		printf("\nNao e possivel mostrar os dados do historico\nPelo menos um dado tem que ser registrado\n");
	}
}


void list_diver_per_circuit(int* n_h){
	
	int i=0;
    int id_pesquisa;
    int contador=0;

    printf("Digite o id do circuito: ");
    fflush(stdin);
    scanf("%d",&id_pesquisa);

    printf("\nPilotos que realizaram voltas neste circuito\n");

    for(i=0; i < *n_h ; i++){

        if(id_pesquisa==pilotos_f1[i].dados.id_do_circuito){

            printf("\n--------------------------------");
            printf("\nID do piloto: %d",pilotos_f1[i].dados.id_piloto);
            printf("\nTempo de volta: %s",pilotos_f1[i].dados.tempo_volta);
            printf("\nData da volta: %s",pilotos_f1[i].dados.data_melhor);
            contador++;
        }
    }
    if(contador<=0){
        printf("O ID foi digitado incorretmente ou um\ncircuito com esse ID ainda não foi cadastrado\n");
    }

}

void apresentacao_menu(){
    printf("\n[a] Cadastrar Piloto");
    printf("\n[b] Cadastrar Circuito");
    printf("\n[c] Cadastrar Volta Mais Rapida de Um Circuito");
    printf("\n[d] Listar circuitos cadastrados");
    printf("\n[e] Listar pilotos cadastrados no sistema");
    printf("\n[f] Listar pilotos, equipes e circuitos com\nvoltas abaixo de uma volta informada");
    printf("\n[g] Listar todos os dados");
    printf("\n[h] Listar pilotos que realizaram voltas em um circuito");
    printf("\n[j] Sair do sistema");
    printf("\nDigite a opcao desejada: ");
}

void menu(){

    char opcao;
    int i = 0, c = 0, n_h=0;
    srand(time(NULL));
    int id_circuito = rand() % 151;

    do{
        system("cls");
        apresentacao_menu();
        fflush(stdin);
        scanf("%c",&opcao);
        
        switch(opcao)
        {
        case 'a':

            if(i<20){

                cadastro_piloto(&i);
                i++;

            }else{

                printf("Limite de pilotos atingido\napenas 20 pilotos correm\nno formato atual da F1");

            }
            break;

        case 'b':

            if(c<22){

                cadastro_circuito(&c,&id_circuito,&i,&n_h);
                c++;
                id_circuito++;
                n_h++;
                
            }else{

                printf("Limite de cadastro de circuitos Atingido");
                printf("A atual temporada tem apenas 22\netapas a serem disputadas");

            }
            break;

        case 'c':
            if(c>0 && i>0){
                cadastro_volta_mais_rapida(&i,&c,&n_h);
                n_h++;
            }else{
                printf("\nNao e possivel cadastrar volta mais rapida\nse nenhum circuito e piloto foram cadastrados\n");
            }
            break;

        case 'd':

            if(c>0){
                lista_circuitos(&c);
            }else{
                printf("\nNao e possivel mostrar a lista de circuitos\ncadastrados pois nenhum circuito\nfoi cadastrado ate o momento\n");
            }
            break;
        case 'e':

            if(i>0){
                lista_pilotos(&i);
            }else{
                printf("\nNao e possivel visualizar os pilotos cadastrados no sistema\npois nenhum piloto foi cadastrado ate o momento\n");
            }
            break;
        case 'f':
            if(n_h > 0 || c>0 && i>0){
                list_driver_circuit_time(&n_h,&c);
            }else{
                printf("\nNao e possivel listar pilotos, equipes e circuitos\ncom tempo de volta menor do que o tempo de volta a\nser informado, pois nenhum piloto e circuito foram\n");
                printf("cadastrados ate o presente momento\n");
            }
        case 'g':
            if(n_h > 0 || c > 0 || i>0){
            	todos_os_dados(&c,&n_h,&i);
            }else{
               printf("Nao e possivel mostrar dados\nnenhum dado foi registrado ate o momento\n");
            }
            break;   
        case 'h':
        	list_diver_per_circuit(&n_h);
        	break;
        }
        system("\npause");
    }while(opcao!='j');
}

int main(){

    menu();


}
