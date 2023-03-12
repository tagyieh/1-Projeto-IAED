/*INCLUDES E DEFINES NECESSARIOS*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
/* LOGICA */
#define VERDADEIRO 1
#define FALSO -1
#define IGUAL 0
#define MESMA_DATA 2
#define PARTIDA 'P'
#define CHEGADA 'C'
/* TEMPO */
#define MINUTOS_NUMA_HORA 60
#define HORAS_NUM_DIA 24
#define MES_31 31
#define MES_30 30
#define FEV 28
#define PRIMEIRO_DIA 1
#define PRIMEIRO_MES 1
#define PRIMEIRO_ANO 2022
#define IND_MES 1
#define DIA_SEGUINTE 1
#define ULTIMO_MES 12
/* REFERENTE A DATA DE INICIO */
#define DIA_INICIO 1
#define MES_INICIO 1
#define ANO_INICIO 2022
/* REFERENTE AO AEROPORTO */
#define NUM_AEROPORTOS_INICIO 0
#define TAMANHO_ID 4
#define TAMANHO_PAIS 31
#define TAMANHO_CIDADE 51
#define MAX_AEROPORTOS 40
#define CARACTERES_ID 3
/* REFERENTE AOS VOOS */
#define NUM_VOOS_INICIO 0
#define TAMANHO_COD_VOO 7
#define MAX_VOOS 30000
#define TAMANHO_LETRAS_COD_VOO 2
#define MAX_TEMPO_VOO_HORAS 12
#define MAX_TEMPO_VOO_MINUTOS 00
#define MIN_CAPACIDADE 10
#define MAX_CAPACIDADE 100

/* ESTRUTURA DATA
A data e identificada por 3 ints: o dia, o mes e o ano
*/
typedef struct
{
  int dia;
  int mes;
  int ano;
} data;

/* ESTRUTURA HORA
A hora e identificada por 2 ints: a hora e o minuto
*/
typedef struct
{
  int hora;
  int minuto;
} hora;

/* ESTRUTURA AEROPORTO
O aeroporto e identificado por 3 strings: o id, o pais e a cidade
*/
typedef struct
{
  char id[TAMANHO_ID];
  char pais[TAMANHO_PAIS];
  char cidade[TAMANHO_CIDADE];
} aeroporto;

/* ESTRUTURA VOO
O voo e identificado por 3 strings: o codigo de voo e os ID's de aeroporto de
partida e de chegada. Adicionalmente, tem 2 datas e 3 horas, correspondentes
a data e hora de partida e de chegada e ainda a duracao. Por fim, tem ainda um
int que e o numero de passageiros.
*/
typedef struct
{
  char cod_voo[TAMANHO_COD_VOO];
  char aero_partida[TAMANHO_ID];
  char aero_chegada[TAMANHO_ID];
  data data_partida;
  hora hora_partida;
  data data_chegada;
  hora hora_chegada;
  hora duracao;
  int passageiros;
} voo;
