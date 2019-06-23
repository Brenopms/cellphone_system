#include <iostream>
#include <cstring>
#include "Classtp2.h"
#include <vector>
#include <iomanip>
using namespace std;

int main(){
	Datah a(2,1,2019), b(1,12,2020), c(1,1,2019,24,31,60);
	LigacaoS s(40,a,0);
	LigacaoD d(25,b,DOWLOAND);
	PrePago K("a",1,1,1,.1,25,b);
	PosPago G("a",.5,3,10,.4,10,b);
	Cliente R("123.456.789","jorge","r.",&K,900000000 );
	Celular C(995314581, &R, &K);
	R.info();
	C.ligar_S(40,a,900000001);
	C.ligar_S(40,a,900000002);
	C.ligar_S(40,a,900000008);
	C.ligar_S(40,a,900000015);
	C.print_l();
	C.info_C();
	s.calcula(K.ValorMin());
	K.spend(s.valor());
	s.calcula(G.ValorMin());
	G.spend(s.valor());
	K.checa();
	G.checa();
	d.calcula(K.veloc());
	K.spend_D(d.valor());
	d.calcula(G.veloc());
	G.spend_D(d.valor());
	K.checa();
	G.checa();
return 0;
}

