#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lsystem.h"
#include "psinterface.h"


static char buf[201];
static FILE *ps = NULL;


boolean is_valid_turtle_command( char c )
{
	boolean validTurtleSymbol =
		strchr(TURTLE_GRAPHICS_SYMBOLS,(int)c) != NULL;
	return validTurtleSymbol;
}

// Analyze symbol. If special convert or substitute
static void psconvert( const char *s, int *pos )
{
	int i = *pos;
	
	buf[0] = s[i]; buf[1] = '\0'; (*pos)++;
	
	if( !is_valid_turtle_command(s[i]) )	{
		// eliminate character
		buf[0] = '\0'; 
		return;
	}
	
	if( s[i] == '[' )  { buf[0] = 'S'; return; }
	if( s[i] == ']' )  { buf[0] = 'R'; return; }
}

static void finalStringPrint( FILE *ps, const char *finalstr )
{
	uint cnt = 0, i;
	size_t flen = strlen(finalstr);

	i = 0;
	while( i < flen )	{
//	for( i = 0; i < flen; i++ )	{
		psconvert( finalstr, &i );
//		fprintf(ps,"%c ", finalstr[i] );
		if( buf[0] != '\0' )
			fprintf(ps,"%s ", buf );
		if( cnt == 30 )	{
			fprintf(ps,"\n");
			cnt = 0;
		}
	}
	fprintf(ps,"\n");
}



static void preambulo( double angle, uint order, double rotimage,const char *psfname )
{
	ps = fopen( psfname, "w" );
	if( ps == NULL )	{
		fprintf(stderr,"Erro: Impossivel abrir arq de saida '%s'.\n", psfname );
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "Gerando arquivo de saida PostScript '%s'.\n", psfname );
	// PS header
	fprintf(ps,"%%!PS-Adobe-2.0 EPSF-2.0\n");
	fprintf(ps,"%%%%BoundingBox: 0 0 800 1000\n");
	fprintf(ps,"\n\n\n");
	fprintf(ps,"%% Preambulo\n\n");
	fprintf(ps,"\n");
	fprintf(ps,"/angle %.2lf def\n", angle);
	fprintf(ps,"/order %d def\n", order);
	fprintf(ps,"/rotateimage %.2lf def\n", rotimage);
	fprintf(ps,"\n");
	fprintf(ps,"/a { 360 angle div } def\n");

	fprintf(ps,"/scal { 2 order neg exp } def\t%% 1/2^order\n");
	fprintf(ps,"/sinv { 2 order exp } def\t%% 2^order\n");
	fprintf(ps,"\n");
	fprintf(ps,"/len 72 def\n");
	fprintf(ps,"\n");
	fprintf(ps,"\n");
	fprintf(ps,"/F { len 0 rlineto } def\n");
	fprintf(ps,"/G   { len 0 rmoveto } def\n");
	fprintf(ps,"/+ {a rotate} def\n");
	fprintf(ps,"/- {a neg rotate} def\n");
	fprintf(ps,"\n");
	fprintf(ps,"/S { gsave } def\n/R { stroke grestore } def\n");
	fprintf(ps,"\n");
	fprintf(ps,"/n {newpath} def\n");
	fprintf(ps,"/l {lineto} def\n");
	fprintf(ps,"/m {moveto} def\n");
	fprintf(ps,"/s {stroke} def\n");
	fprintf(ps,"\n");
	fprintf(ps,"/pageLetterCenter { 297.72 421.2 } def\n");
	fprintf(ps,"/linewidth 0.1 def\n");
	fprintf(ps,"\n");
	fprintf(ps,"gsave\n");
	fprintf(ps,"\n");
	fprintf(ps,"pageLetterCenter translate\n");
	fprintf(ps,"rotateimage rotate\n");
	fprintf(ps,"scal scal scale\n");
	fprintf(ps,"linewidth setlinewidth\n");
	fprintf(ps,"newpath 0 0 moveto\n");
}


void genps( double angle, uint order, double rotimage,
		const char *finalstr, const char *psfname )
{
	preambulo( angle, order, rotimage, psfname );
	
	fprintf(stdout, "String final='%s'\n", finalstr );
	finalStringPrint(ps,finalstr);
	
	fprintf(ps,"stroke\n\ngrestore\n\nshowpage\n");
	fprintf(ps,"quit\n");
	
	fclose( ps );
}



static void finalStringPrintTurtle( FILE *ps, const char *turtlestr )
{
	uint cnt = 0, i;
	size_t flen = strlen(turtlestr);

	
	fprintf(stdout, "Turtle string=\n'%s'\n", turtlestr );
	for( i=0; i<flen; i++ )	{
		char c = turtlestr[i];
		fprintf(ps,"%c", c );
		if( c == 's' )	{
			fprintf(ps,"\n");
		}
	}
	fprintf(ps,"\n");
}


void genpsTurtle( double angle, uint order, double imagerotate,
		const char *turtlestr, const char *psfname )
{
	preambulo( angle, order, imagerotate, psfname );
	
	finalStringPrintTurtle(ps,turtlestr);
	
	fprintf(ps,"stroke\n\ngrestore\n\nshowpage\n");
	fprintf(ps,"quit\n");
	
	fclose( ps );
}



#if 0
#endif
