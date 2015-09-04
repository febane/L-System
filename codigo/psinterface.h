


// Qualquer símbolo que não seja parte desta string
// será eliminada na string final que é passada para
// o Postscript
#define TURTLE_GRAPHICS_SYMBOLS "FG+-!|@><c[]/\\"

// avalia, se símbolo é do conjunto acima
boolean is_valid_turtle_command( char c );


//
// Input:
// Preâmbulo da gramatica
//	angle
//	order
//	rotateimage
// string final gerada pelo L-Sistema
// nome do arquivo de saida
void genps( double angle, uint order, double rotimage,
		const char *finalstr, const char *psfname );


//
// Input:
// Preâmbulo da gramatica
//	angle
//	order
//	rotateimage
// string convertido do L-Sistema para comandos básicos da tartaruga
// nome do arquivo de saida


/*
   Um comando básico tem a seguinte sintaxe:
   n x0 y0 m x1 x2 l s
   onde (x0,y0) e (x1,y1) são os pontos iniciais e finais de uma reta 
   'n' significa newpath, 'l' lineto, 'm' moveto e 's' stroke
   e são diretamente interpretado pelo Postscript.
   
   Exemplo que desenha um triângulo 

	n   0   0 m 100 100 l s
	n 100 100 m 200   0 l s
	n 200   0 m   0   0 l s

  A quebra de linha não precisa aparecer na string, portanto
  a seguinte chamada da função 'genpsTurtle' com a combinação de comandos acima 
  desenha o triângulo:
  
  genpsTurtle( 4.0, 2, 0.0,
	"n 0 0 m 100 100 l s n 100 100 m 200 0 l s n 200 0 m 0 0 l s", "triangulo.ps" );
 
 

 */
void genpsTurtle( double angle, uint order, double imagerotate,
		const char *turtlestr, const char *psfname );