/*
	Creada por Danilo Diaz T, 27 de Agosto, 2014
	Para FutBot USB y de dominio público
	*/

	#include Arduino.h
	#include Protocolo_Serial.h

/*
pX is a pointer to another type X; this contains very little semantic information.
d is a prefix meaning difference between two values; for instance, 
dY might represent a distance along the Y-axis of a graph, while a variable just called y might be an absolute position. This is entirely semantic in nature.
sz is a null- or zero-terminated string. In C, this contains some semantic information because it is not clear whether a variable of type char* is a pointer to a single character, an array of characters or a zero-terminated string.
w marks a variable that is a word. This contains essentially no semantic information at all, and would probably be considered Systems Hungarian.
b marks a byte, which in contrast to w might have semantic information, because in C the only byte-sized data type is the char, so these are sometimes used to hold numeric values. This prefix might clear ambiguity between whether the variable is holding a value that should be treated as a character or a number.
fp means floating point (Punto Flotante)
i means integer (entero)
U means union
*/


/*
 Los tipo union te permiten tomar un espacio de la memoria y verla de formas distintas, en el caso 
 que sigue a continuación, se tiene un arreglo de 2 bytes (********!********) y ese mismo espacio de memoria,
	 se puede ver como una palabra (word) de 16 bits (2 bytes) (********!********)

 De esta manera, se pueden tomar palabras y enviarlas como bytes de manera cómoda. De manera análoga, se realiza el punto flotante, sólo
 que cambia la manera de interpretarse el dato en el que recibe
 */

 typedef union{
 	byte bData[2];
 	word wData;
 	}UiData;

/*
análogo a lo anterior
*/
typedef union{
	float fpData;
	word wData;
	}UfpData;

