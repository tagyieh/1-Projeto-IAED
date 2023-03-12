/*
Tomas Fonseca   ist1103726

Este projeto simula um sistema interativo via standard input (stdin) de gestao
de voos entre varios aeroportos
*/

#include "defs.h"

/* VARIAVEIS GLOBAIS DO SISTEMA */

aeroporto aeroportos [MAX_AEROPORTOS];
int num_aeroportos = NUM_AEROPORTOS_INICIO, num_voos = NUM_VOOS_INICIO;
voo lista_voos[MAX_VOOS];
data data_sistema = {PRIMEIRO_DIA,PRIMEIRO_MES,PRIMEIRO_ANO};

/*==============================Funcoes Comuns==================================
verifica_aeroporto_existe(char[]) -> int
Esta funcao recebe uma string, correspondente ao id de um aeroporto, e itera
sobre o vetor de aeroportos para confirmar se existe um aeroporto com o mesmo
id.
*/
int verifica_aeroporto_existe(char id[])
{
  int contador;
  for (contador=0;contador<num_aeroportos;contador++)
  {
    if (strcmp(aeroportos[contador].id,id)==IGUAL)
      return contador;
  }
  return FALSO;
}

/*
compara_data(data, data) -> int
Esta funcao recebe duas datas e compara-as. Se a primeira data for menor que a
segunda, devolve verdadeiro. Se forem iguais, devolve que sao iguais. Caso
contrario, devolve falso.
*/
int compara_data(data data_comparar, data data_menor)
{
  if (data_comparar.ano<data_menor.ano)
    return VERDADEIRO;
  else if(data_comparar.ano==data_menor.ano && data_comparar.mes<data_menor.mes)
    return VERDADEIRO;
  else if(data_comparar.ano==data_menor.ano&&data_comparar.mes==data_menor.mes
          && data_comparar.dia<data_menor.dia)
    return VERDADEIRO;
  else if(data_comparar.ano==data_menor.ano&&data_comparar.mes==data_menor.mes
          && data_comparar.dia==data_menor.dia)
      return MESMA_DATA;
  return FALSO;
}

/*
verifica_data(data, data) -> int
Esta funcao recebe duas datas, a do sistema e a de um voo, e verifica se a data
do voo nao e anterior ou mais de um ano a frente da data do sistema.
*/
int verifica_data(data data_sistema, data data_voo)
{
  /*verifica se é no passado*/
  if(compara_data(data_voo,data_sistema)==VERDADEIRO)
    return VERDADEIRO;
  /*verifica se é mais que um ano no futuro*/
  if (data_sistema.ano+1==data_voo.ano)
  {
    if (data_sistema.mes<data_voo.mes)
      return VERDADEIRO;
    else if (data_sistema.dia<data_voo.dia && data_sistema.mes==data_voo.mes)
      return VERDADEIRO;
  }
  return FALSO;
}

/*
imprime_data_voo(data, hora) -> void
Esta funcao recebe uma data e uma hora e imprime-as no formato correto no
standard output (stdout).
*/
void imprime_data_voo (data data_imprimir, hora hora_imprimir)
{
  printf("%02d-%02d-%d ",data_imprimir.dia,data_imprimir.mes,data_imprimir.ano);
  printf("%02d:%02d\n",hora_imprimir.hora,hora_imprimir.minuto);
}

/*
compara_hora(hora, hora) -> int
Esta funcao recebe duas horas e compara-as. Se a primeira hora for menor que a
segunda, devolve verdadeiro. Caso contrario, devolve falso.
*/
int compara_hora(hora hora_comparar, hora hora_menor)
{
  if (hora_comparar.hora<hora_menor.hora)
    return VERDADEIRO;
  else if (hora_comparar.hora==hora_menor.hora && hora_comparar.minuto<
    hora_menor.minuto)
    return VERDADEIRO;
  return FALSO;
}

/*
sort_data_voos_partida(voos[], int, char) -> void
Esta funcao recebe um vetor de voos, o respetivo tamanho e o tipo de voo
(partida ou chegada).Organiza-o por ordem da data (do mais antigo para o mais
recente), recorrendo a um selection sort, de acordo com o tipo de voo.
*/
void sort_data_voos(voo voos_aero[], int tamanho, char tipo)
{
  int contador, contador2, ind, cond=FALSO, cond2=FALSO;
  voo voo_atual, voo_ind;
  for (contador=0;contador<tamanho-1;contador++)
  {
    ind = contador;
    for (contador2=contador+1;contador2<tamanho;contador2++)
    {
      voo_atual = voos_aero[contador2];
      if (tipo==PARTIDA)
      {
        cond=compara_data(voo_atual.data_partida,voos_aero[ind].data_partida);
        cond2=compara_hora(voo_atual.hora_partida,voos_aero[ind].hora_partida);
      }
      else
      {
        cond=compara_data(voo_atual.data_chegada,voos_aero[ind].data_chegada);
        cond2=compara_hora(voo_atual.hora_chegada,voos_aero[ind].hora_chegada);
      }
      if (cond==VERDADEIRO)
        ind = contador2;
      else if(cond==MESMA_DATA && cond2==VERDADEIRO)
        ind = contador2;
    }
    voo_ind = voos_aero[ind];
    voos_aero[ind] = voos_aero[contador];
    voos_aero[contador] = voo_ind;
  }
}

/*=================================COMANDO A====================================
verifica_id_errado(char[]) -> int
Esta funcao recebe uma string, o id, e avalia se todas as letras sao maiusculas.
Se alguma nao for, devolve VERDADEIRO (1), caso contrario, FALSO (0).
*/
int verifica_id_errado(char id[])
{
  int contador;
  char letra;
  for (contador=0;contador<TAMANHO_ID;contador++)
  {
    letra = id[contador];
    if (islower(letra))
      return VERDADEIRO;
  }
  return FALSO;
}

/*
comando_a() -> void
Esta funcao ira ler do standard input (stdin) tres strings: um id, um pais e
uma cidade, todas pertencentes a um aeroporto. Se o id nao tiver letras
minusculas, nenhum aeroporto tiver o mesmo id e se o sistema nao tiver atingido
o seu limite de 40 aeroports, adiciona um novo aeroporto ao sistema e incrementa
o numero de aeroportos. Caso contrario, gera um erro.
*/
void comando_a()
{
  char id[TAMANHO_ID], pais[TAMANHO_PAIS], cidade[TAMANHO_CIDADE], letra;
  int contador, nome_cidade=FALSO;
  aeroporto novo_aero;
  scanf("%s%s",id,pais);
  while (nome_cidade==FALSO) /*ignora os espacos antes do nome da cidade*/
  {
    letra = getchar();
    if (letra!=' ' && letra!='\t')
    {
      contador = 0;
      cidade[contador] = letra;
      contador++;
      nome_cidade=VERDADEIRO;
      while (contador<TAMANHO_CIDADE && (letra=getchar())!='\n')
      {
        cidade[contador] = letra;
        contador++;
      }
      cidade[contador] = '\0';
    }
  }
  if (verifica_id_errado(id)==VERDADEIRO)
  {
    printf("invalid airport ID\n");
    return;
  }
  if (verifica_aeroporto_existe(id)!=FALSO)
  {
    printf("duplicate airport\n");
    return;
  }
  if (num_aeroportos==MAX_AEROPORTOS)
  {
    printf("too many airports\n");
    return;
  }
  strcpy(novo_aero.id, id);
  strcpy(novo_aero.pais, pais);
  strcpy(novo_aero.cidade, cidade);
  aeroportos[num_aeroportos] = novo_aero;
  printf("airport %s\n",novo_aero.id);
  num_aeroportos++;
}

/*=================================COMANDO L====================================
sort_alfabetico(aeroporto[],int) -> void
Esta funcao recebe um vetor de aeroportos e o numero de aeroportos no sistema
e organiza o vetor por ordem alfebetica dos ID's dos aeroports, via selection
sort.
*/
void sort_alfabetico(aeroporto aeroportos[], int num_aeroportos)
{
  int pos_mais_pequeno, contador1, contador2;
  aeroporto aero_aux;
  for (contador1=0;contador1<num_aeroportos-1;contador1++)
  {
    pos_mais_pequeno = contador1;
    for (contador2=contador1+1;contador2<num_aeroportos;contador2++)
    {
      if (strcmp(aeroportos[pos_mais_pequeno].id,aeroportos[contador2].id)>
          IGUAL)
        pos_mais_pequeno=contador2;
    }
    aero_aux = aeroportos[contador1];
    aeroportos[contador1] = aeroportos[pos_mais_pequeno];
    aeroportos[pos_mais_pequeno] = aero_aux;
  }
}

/*
conta_voos(voo[], int, aeroporto) -> int
Esta funcao itera sobre a lista de voos e conta o numero de voos que partem do
aeroporto dado como argumento, devolvendo o seu total
*/
int conta_voos(aeroporto aero)
{
  int contador, total=0;
  voo voo_comparar;
  for (contador=0;contador<num_voos;contador++)
  {
    voo_comparar = lista_voos[contador];
    if (strcmp(voo_comparar.aero_partida,aero.id)==IGUAL)
      total++;
  }
  return total;
}

/*
comando_l() -> void
Esta funcao inicia o comando l. Se nao tiver parametros, lista todos os
aeroportos por ordem alfabetica. Caso contrario, lista os aeroportos que recebeu
como parametros pela ordem de aparecimento no terminal.
*/
void comando_l()
{
  char id_imprimir[TAMANHO_ID], espaco;
  int contador1, ind, voos_partem_aero, imprimir_todos=VERDADEIRO;
  aeroporto aero;
  while ((espaco=getchar())!='\n')
  {
    imprimir_todos = FALSO;
    scanf("%s",id_imprimir);
    if ((ind=verifica_aeroporto_existe(id_imprimir))!=FALSO)
    {
      aero = aeroportos[ind];
      voos_partem_aero = conta_voos(aero);
      printf("%s %s %s %d\n",aero.id,aero.cidade,aero.pais,voos_partem_aero);
    }
    else
      printf("%s: no such airport ID\n",id_imprimir);
  }
  if (imprimir_todos==VERDADEIRO)
  {
    sort_alfabetico(aeroportos, num_aeroportos);
    for (contador1=0;contador1<num_aeroportos;contador1++)
    {
      aero = aeroportos[contador1];
      voos_partem_aero = conta_voos(aero);
      printf("%s %s %s %d\n",aero.id,aero.cidade,aero.pais,voos_partem_aero);
    }
  }
  return;
}

/*=================================COMANDO V====================================
verifica_cod_voo(char[]) -> int
Esta funcao recebe uma string correspondente ao codigo de voo e verifica se
respeita as regras de criacao de codigos de voo: 2 letras maiusculas seguidas
por quatro numeros.
*/
int verifica_cod_voo(char cod_voo[])
{
  int contador, tamanho = strlen(cod_voo);
  for (contador=0;contador<tamanho;contador++)
  {
    if (contador<TAMANHO_LETRAS_COD_VOO)
    {
      if(!(isalpha(cod_voo[contador])) || islower(cod_voo[contador]))
        return VERDADEIRO;
    }
    else if ('0'>cod_voo[contador] || cod_voo[contador] >'9')
      return VERDADEIRO;
  }
  return FALSO;
}

/*
verifica_cod_unico(voo) -> int
Esta funcao recebe a lista de voos, o numero de voos e uma string, correspon-
dente ao codigo de voo, e itera sobre a lista de voos para verificar se este
codigo ja esta associado a outro voo no mesmo dia.
*/
int verifica_cod_unico(voo novo_voo)
{
  int contador;
  voo voo_comparar;
  for (contador=0;contador<=num_voos;contador++)
  {
    voo_comparar = lista_voos[contador];
    if (strcmp(voo_comparar.cod_voo,novo_voo.cod_voo)==IGUAL &&
    compara_data(voo_comparar.data_partida,novo_voo.data_partida)==MESMA_DATA)
      return VERDADEIRO;
  }
  return FALSO;
}

/*
calcula_novo_dia(data) -> data
Esta funcao recebe uma data e devolve a data que corresponde ao dia seguinte.
*/
data calcula_novo_dia(data data_partida)
{
  data data_chegada;
  int mes=data_partida.mes, dia, ano=data_partida.ano,
  dias_meses[]={MES_31,FEV,MES_31,MES_30,MES_31,MES_30,MES_31,MES_31,MES_30,
                MES_31,MES_30,MES_31};
  dia = (data_partida.dia%dias_meses[mes-IND_MES]+DIA_SEGUINTE);
  if (dia==PRIMEIRO_DIA)
    mes++;
  if (mes>ULTIMO_MES)
  {
    mes=PRIMEIRO_MES;
    ano++;
  }
  data_chegada.dia=dia;
  data_chegada.mes=mes;
  data_chegada.ano=ano;
  return data_chegada;
}

/*
cria_hora_chegada(voo) -> void
Esta funcao cria, a partir da hora de partida e da duracao de um voo, a sua
hora de chegada, somando a primeira à segunda.
*/
hora cria_hora_chegada(voo voo_atual)
{
  hora hora_chegada;
  int hora, minuto, extra;
  extra = (voo_atual.hora_partida.minuto+voo_atual.duracao.minuto) /
            MINUTOS_NUMA_HORA;
  /*extra corresponde à conversão de minutos para horas após a sua soma*/
  minuto = voo_atual.hora_partida.minuto+voo_atual.duracao.minuto -
            extra*MINUTOS_NUMA_HORA;
  hora = voo_atual.hora_partida.hora+voo_atual.duracao.hora+extra;
  if (hora>=HORAS_NUM_DIA)
    hora-=HORAS_NUM_DIA;
    /*se as horas forem maiores que 24, entao estamos num novo dia*/
  hora_chegada.hora=hora;
  hora_chegada.minuto=minuto;
  return hora_chegada;
}

/*
voo_errado(novo_voo) -> int
Esta funcao recebe um voo e verifica se todos os seu parametros estao corretos.
Caso esteja bem, devolve FALSO (0), VERDADEIRO (1), caso contrario.
*/
int voo_errado(voo novo_voo)
{
  if (verifica_cod_voo(novo_voo.cod_voo)==VERDADEIRO)
  {
    printf("invalid flight code\n");
    return VERDADEIRO;
  }
  else if (verifica_cod_unico(novo_voo)==VERDADEIRO)
  {
    printf("flight already exists\n");
    return VERDADEIRO;
  }
  else if (verifica_aeroporto_existe(novo_voo.aero_partida)==FALSO)
  {
    printf("%s: no such airport ID\n",novo_voo.aero_partida);
    return VERDADEIRO;
  }
  else if (verifica_aeroporto_existe(novo_voo.aero_chegada)==FALSO)
  {
    printf("%s: no such airport ID\n",novo_voo.aero_chegada);
    return VERDADEIRO;
  }
  else if (num_voos==MAX_VOOS)
  {
    printf("too many flights\n");
    return VERDADEIRO;
  }
  else if (verifica_data(data_sistema,novo_voo.data_partida)==VERDADEIRO)
  {
    printf("invalid date\n");
    return VERDADEIRO;
  }
  else if ((novo_voo.duracao.hora>MAX_TEMPO_VOO_HORAS) ||
          (novo_voo.duracao.hora==MAX_TEMPO_VOO_HORAS &&
          novo_voo.duracao.minuto>MAX_TEMPO_VOO_MINUTOS))
  {
    printf("invalid duration\n");
    return VERDADEIRO;
  }
  else if (novo_voo.passageiros<MIN_CAPACIDADE ||
          novo_voo.passageiros>MAX_CAPACIDADE)
  {
    printf("invalid capacity\n");
    return VERDADEIRO;
  }
  return FALSO;
}

/*
cria_novo_voo() -> voo
Esta funcao le o input fornecido e cria um novo voo.
*/
voo cria_novo_voo()
{
  voo novo_voo;
  char id_partida[TAMANHO_ID], id_chegada[TAMANHO_ID], cod_voo[TAMANHO_COD_VOO];
  hora hora_partida, duracao;
  int dia, mes, ano, capacidade, partida_horas, partida_minutos,
  duracao_horas, duracao_minutos;
  scanf("%s",cod_voo);
  scanf("%s%s",id_partida,id_chegada);
  scanf("%d-%d-%d",&dia,&mes,&ano);
  scanf("%d:%d",&partida_horas,&partida_minutos);
  scanf("%d:%d",&duracao_horas,&duracao_minutos);
  scanf("%d",&capacidade);

  hora_partida.hora = partida_horas;
  hora_partida.minuto = partida_minutos;

  duracao.hora = duracao_horas;
  duracao.minuto = duracao_minutos;

  strcpy(novo_voo.cod_voo,cod_voo);
  strcpy(novo_voo.aero_partida,id_partida);
  strcpy(novo_voo.aero_chegada,id_chegada);
  novo_voo.data_partida.dia = dia;
  novo_voo.data_partida.mes = mes;
  novo_voo.data_partida.ano = ano;
  novo_voo.hora_partida = hora_partida;
  novo_voo.duracao = duracao;
  novo_voo.passageiros = capacidade;
  novo_voo.hora_chegada = cria_hora_chegada(novo_voo);
  return novo_voo;
}

/*comando_v() -> int
Esta le o input do terminal e verifica se ha algum erro. Caso exista,
reporta-o e termina a funcao. Caso contrario, cria um novo voo e insere-o
no sistema
*/
void comando_v()
{
  char caracter = getchar();
  int contador;
  voo novo_voo;
  /* imprimir todos os voos*/
  if (caracter=='\n')
  {
    for (contador=0;contador<num_voos;contador++)
    {
      novo_voo = lista_voos[contador];
      printf("%s %s %s ",novo_voo.cod_voo,novo_voo.aero_partida,
        novo_voo.aero_chegada);
      imprime_data_voo(novo_voo.data_partida,novo_voo.hora_partida);
    }
    return;
  }
  novo_voo = cria_novo_voo();
  /*verifica se o voo chega no dia seguinte*/
  if (novo_voo.hora_chegada.hora<novo_voo.hora_partida.hora ||
      (novo_voo.hora_chegada.hora==novo_voo.hora_partida.hora &&
      novo_voo.hora_chegada.minuto<novo_voo.hora_partida.minuto))
    novo_voo.data_chegada = calcula_novo_dia(novo_voo.data_partida);
  else
    novo_voo.data_chegada=novo_voo.data_partida;
  if (voo_errado(novo_voo)==FALSO)
  {
    lista_voos[num_voos] = novo_voo;
    num_voos++;
  }
}

/*=================================COMANDO P====================================
p(aeroporto) -> void
Esta funcao recebe um aeroporto e ira reter todos os voos que partem do mesmo,
devolvendo erro se nao existir tal aeroporto. De seguida, ira fazer um sort pela
data dos voos e, por fim, ira fazer print dos voos.
*/
void comando_p()
{
  char aero_id[TAMANHO_ID];
  voo voos_partem_aero[MAX_VOOS], voo_atual;
  int contador, ind=0;
  scanf("%s",aero_id);
  if(verifica_aeroporto_existe(aero_id)==FALSO)
  {
    printf("%s: no such airport ID\n",aero_id);
    return;
  }
  for (contador=0;contador<num_voos;contador++)
  {
    voo_atual = lista_voos[contador];
    if (strcmp(voo_atual.aero_partida,aero_id)==IGUAL)
    {
      voos_partem_aero[ind] = voo_atual;
      ind++;
    }
  }
  sort_data_voos(voos_partem_aero,ind,PARTIDA);
  for (contador=0;contador<ind;contador++)
  {
    voo_atual = voos_partem_aero[contador];
    printf("%s %s ", voo_atual.cod_voo, voo_atual.aero_chegada);
    imprime_data_voo(voo_atual.data_partida,voo_atual.hora_partida);
  }
  return;
}

/*=================================COMANDO C====================================
comando_c() -> void
Esta funcao recebe um aeroporto e ira reter todos os voos que chegam ao mesmo,
devolvendo erro se nao existir tal aeroporto. De seguida, ira fazer um sort pela
data dos voos e, por fim, ira fazer print dos voos.
*/
void comando_c()
{
  char aero_id[TAMANHO_ID];
  voo voos_chegam_aero[MAX_VOOS], voo_atual;
  int contador, ind=0;
  scanf("%s",aero_id);
  if(verifica_aeroporto_existe(aero_id)==FALSO)
  {
    printf("%s: no such airport ID\n",aero_id);
    return;
  }
  for (contador=0;contador<num_voos;contador++)
  {
    voo_atual = lista_voos[contador];
    if (strcmp(voo_atual.aero_chegada,aero_id)==IGUAL)
    {
      voos_chegam_aero[ind] = voo_atual;
      ind++;
    }
  }
  sort_data_voos(voos_chegam_aero,ind,CHEGADA);
  for (contador=0;contador<ind;contador++)
  {
    voo_atual = voos_chegam_aero[contador];
    printf("%s %s ", voo_atual.cod_voo, voo_atual.aero_partida);
    imprime_data_voo(voo_atual.data_chegada,voo_atual.hora_chegada);
  }
}

/*=================================COMANDO T====================================
comando_t() -> void
Esta funcao le uma data e, caso esteja mais de um ano no futuro ou esteja
no passado erro, devolve erro. Caso contrario, muda a data do sistema para a
data que leu.
*/
void comando_t()
{
  int dia, mes, ano;
  data nova_data;
  scanf("%d-%d-%d",&dia,&mes,&ano);
  nova_data.dia = dia;
  nova_data.mes = mes;
  nova_data.ano = ano;
  if(verifica_data(data_sistema,nova_data)==VERDADEIRO)
  {
    printf("invalid date\n");
    return;
  }
  printf("%02d-%02d-%d\n",dia,mes,ano);
  data_sistema = nova_data;
}

/*===================================MAIN=======================================
main() -> int
Esta funcao e responsavel por ler os comandos escritos pelo utilizador no
standard input, sendo que cada um inicia uma funcao diferente. Caso o utilizador
insira o comando 'q' o programa termina.
*/
int main()
{
  char comando;
  while ((comando=getchar())!='q')
  {
    if (comando=='a')
      comando_a();
    else if (comando=='l')
      comando_l();
    else if (comando=='v')
      comando_v();
    else if (comando=='p')
      comando_p();
    else if (comando=='c')
      comando_c();
    else if (comando=='t')
      comando_t();
  }
  return 0;
}
