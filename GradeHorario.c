/***************************************************************************
*  $MCI M�dulo de implementa��o: GRA  Grade de Hor�rio
*
*  Arquivo gerado:              GradeHorario.c
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: cgln - Cristiane - Guilherme - Leonardo - Nath�lia
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     3       cgln  04/out/2017 manuten��o das fun��es do m�dulo
*     2       cgln  03/out/2017 unifica��o de todos os m�dulos em um s� projeto
*     1       cgln  02/out/2017 in�cio desenvolvimento
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "turma.h"
#include "disciplina.h"
#include "lista.h"
#include "GradeHorario.h"

/***********************************************************************
*
*  $TC Tipo de dados: GRA Info Grade Horario
*
*
***********************************************************************/

	struct infoGradeHorario {

		Disciplina * disp ;
			/* Disciplina em que o aluno esta cursando */

		Turma * tur ;
			/* Turma da disciplina em que o aluno esta cursando */

		float nota[4] ;
			/* Notas do aluno */

		int faltas ;
			/* Quantidade de faltas do aluno */
    
	} ;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Grade Horario
*
*
***********************************************************************/

	struct gradehorario {

		List * Grade ;
			/* Cabe�a da lista de grade hor�rio */

	} ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
* Fun��o: GRA  &Cria Grade Horario
*  ****/

	GRA_tpCondRet GRA_CriaGradeHorario ( GradeHorario ** GradeHor )
	{
		LIS_tpCondRet ret ;

		* GradeHor = ( GradeHorario * ) malloc( sizeof( GradeHorario )) ;

		ret = createList( &(( *GradeHor )->Grade )) ;

		if ( ret == LIS_CondRetFaltouMemoria )
		{
			return GRA_CondRetFaltouMemoria ;
		} /* if */

		return GRA_CondRetOk;

	} /* Fim fun��o: GRA  &Cria Grade Horario */

/***************************************************************************
* Fun��o: GRA  &Exibe Grade Horario
*  ****/

	GRA_tpCondRet GRA_ExibeGradeHorario ( GradeHorario *GradeHorario )
	{
	
		InfoGradeHorario * no ;
		unsigned int size ;
		LIS_tpCondRet ret ;

		ret = list_size( GradeHorario->Grade, &size ) ;

		if ( ret == LIS_CondRetListaVazia ) 
		{
			return GRA_CondRetGradeVazia ;
		} /* if */

		puts( "\n\n****** GRADE DE HORARIO ******\n" ) ;
		first( GradeHorario->Grade ) ;
		get_val_cursor( GradeHorario->Grade,( void ** )&no ) ;

  		while ( ret != LIS_CondRetCursorNoFinal )
		{			
			DIS_exibe( no->disp ) ;
			TUR_ExibeTurma( no->tur ) ;
			printf( "Notas: G1: %.1f\tG2: %.1f\tG3: %.1f\tG4: %.1f\n Faltas: %d\n",
				no->nota[0], no->nota[1], no->nota[2], no->nota[3], no->faltas) ;
	    
			ret = next( GradeHorario->Grade ) ;
			get_val_cursor( GradeHorario->Grade, (void ** )&no ) ;
		} /* while */

		return  GRA_CondRetOk ;

	} /* Fim fun��o: GRA  &Exibe Grade Horario */

/***************************************************************************
* Fun��o: GRA  &Insere Grade Horario
*  ****/
	  
	GRA_tpCondRet GRA_InsereGradeHorario( InfoGradeHorario * i, Disciplina * d, 
		Turma * t, GradeHorario * GradeHorario)
	{
		
			i = ( InfoGradeHorario * ) malloc( sizeof( InfoGradeHorario )) ;
			i->disp = d ;
			i->tur = t ;
			i->nota[0] = -1 ;
			i->nota[1] = -1 ;
			i->nota[2] = -1 ;
			i->nota[3] = -1 ;
			i->faltas = -1 ;
			push_back( GradeHorario->Grade, (void * ) i ) ;

		return GRA_CondRetOk ;

	} /* Fim fun��o: GRA  &Insere Grade Horario */

/***************************************************************************
* Fun��o: GRA  &Busca Grade Horario
*  ****/
	  
	InfoGradeHorario * GRA_BuscaGradeHorario( GradeHorario * GradeHorario, char * codDigitado )
	{

		int ret = 0 ;
		char * codProcurado ;
		InfoGradeHorario * no ;

		get_val_cursor( GradeHorario->Grade, (void ** ) &no) ;
		DIS_get_codigo( no->disp, &codProcurado) ;

		while ( ret!= LIS_CondRetCursorNoFinal )
		{
			if( strcmp( codDigitado, codProcurado ) == 0 ) 
			{	
				return no ; 
			} /* if */
			
			ret = next( GradeHorario->Grade ) ;
			get_val_cursor(GradeHorario->Grade,(void**)&no) ;	
			DIS_get_codigo(no->disp,&codProcurado) ;
		} /* while */
	
			return NULL ;

	} /* Fim fun��o: GRA  &Busca Grade Horario */

/***************************************************************************
* Fun��o: GRA  &Altera Faltas
*  ****/

	GRA_tpCondRet GRA_AlteraFaltas ( GradeHorario *GradeHorario,char *codBuscado,int novFalta )
	{

		InfoGradeHorario * noAlterado = NULL ;
		noAlterado = GRA_BuscaGradeHorario( GradeHorario, codBuscado ) ;

		if( noAlterado==NULL )
		{
			return GRA_CondRetDisciplinaNaoEncontrada ;
		} /* if */

		noAlterado->faltas = novFalta ;
		return GRA_CondRetOk ;

	} /* Fim fun��o: GRA  &Altera Faltas */

/***************************************************************************
* Fun��o: GRA  &Altera Nota
*  ****/

	GRA_tpCondRet GRA_AlteraNota( GradeHorario * GradeHorario, char * codBuscado, float g[4] )
	{

		int i ;
		InfoGradeHorario * noAlterado=NULL ;
		noAlterado = GRA_BuscaGradeHorario( GradeHorario, codBuscado) ;

		if( noAlterado == NULL )
		{
			return GRA_CondRetDisciplinaNaoEncontrada ;
		} /* if */

		for( i=0; i<4; i++ )
		{
				if( g[i]<0 || g[i]>10 )
				{
					return 	GRA_CondRetFormatoInvalido ;
				} /* if */

				noAlterado->nota[i] = g[i] ;
		} /* for */

		return GRA_CondRetOk ;

	} /* Fim fun��o: GRA  &Altera Nota */

/***************************************************************************
* Fun��o: GRA  &Elimina No
*  ****/

	GRA_tpCondRet GRA_EliminaNo( GradeHorario * GradeHorario, char * codBuscado )
	{

		InfoGradeHorario * noAlterado = NULL ;

		noAlterado = GRA_BuscaGradeHorario( GradeHorario, codBuscado) ;

		if( noAlterado == NULL )
		{
			return GRA_CondRetDisciplinaNaoEncontrada ;
		} /* if */

		pop_cursor( GradeHorario->Grade, ( void ** ) noAlterado ) ;
		GRA_LiberaInfo ( noAlterado ) ;

		return GRA_CondRetOk ;

	} /* Fim fun��o: GRA  &Elimina No */

/***************************************************************************
* Fun��o: GRA  &Libera Grade Horario
*  ****/

	GRA_tpCondRet GRA_LiberaGradeHorario( GradeHorario * GradeHorario )
	{

		free( GradeHorario ) ;
		return GRA_CondRetOk ;

	} /* Fim fun��o: GRA  &Libera Grade Horario */

/***************************************************************************
* Fun��o: GRA  &Libera Info
*  ****/

	GRA_tpCondRet GRA_LiberaInfo ( InfoGradeHorario * Info )
	{
		free( Info ) ;
		return GRA_CondRetOk ;

	} /* Fim fun��o: GRA  &Libera Info */

/********** Fim do m�dulo de implementa��o: GRA  Grade de Horario **********/