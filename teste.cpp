#include <iostream>
#include <cstring>
#include "Classtp2.h"
#include <vector> 
#include <iomanip>
using namespace std;

void Datah::somad(int d){//soma dias a data
	dia+=d;
	while((dia>31)||(((mes==4)||(mes==6)||(mes==9)||(mes==11))&&(dia>30))){
		if((mes==2)&&(ano%4==0)){
			if(dia>29){
				dia-=29;
				mes++;
			}
		}else if((mes==2)&&(dia>28)){
			dia-=28;
				mes++;;
		}	
		if(((mes==4)||(mes==6)||(mes==9)||(mes==11))&&(dia>30)){
			dia-=30;
			mes++;
		}
		if((dia>31)&&(mes!=2)){
			dia-=31;
			mes++;
			if(mes>12){
				mes=1;
				ano++;
			}
		}
	}
}

void Datah::somam(int m){//soma meses
	mes+=m;
	if(mes>12){
			mes=1;
			ano++;
	}
}

const bool Datah::valid(){//testa se a dataé uma numero valido
	if((ano<2019)||(dia>31)||(mes>12))return false;//qualquer data antes de 2019 não faz parte do sistema, ja que a operadora começou esse ano 
	if((dia<1)||(mes<1))return false;
	if(mes==2){
		if((ano%4==0)&&(dia>29))return false;
		if(dia>28)return false;
	}
	if(((mes==4)||(mes==6)||(mes==9)||(mes==11))&&(dia>30))return false;
	if((hora>24)||(min>60)||(seg>60))return false;
	return true;
}
 
const bool Datah::antiga(const Datah &D){//testa se data fornecida é mais atiga que a atual
		if(ano==D.ano){
			if(mes==D.mes){
				if(dia==D.dia){
					return false;
				}else if(dia>D.dia)return true;
			}else if(mes>D.mes)return true;
		}else if (ano>D.ano)return true;
		return false;
}

ostream &operator<<(ostream &out, const Datah &ref){
	out<<ref.dia<<"/"<<ref.mes<<"/"<<ref.ano<<"-"<<ref.hora<<":"<<ref.min<<":"<<ref.seg<<endl;
	return out;
}


Celular::Celular(const Celular &cell){//contrutor de copia
	numero=cell.numero;
	cliente=cell.cliente;
	for(int i=0; i<cell.lista.size(); i++){
		lista[i]=cell.lista[i];
	}
}

void Celular::info_C(){//imprime informacoes sobre o cliente e o celular
	cout<<"Numero do celular:"<<fixed<<setprecision(0)<<numero<<endl<<"Cliente:"<<endl; 
	cliente->info();
	cout<<"Plano:"<<endl;
	plano->checa();
	}
	
void Celular::print_l(){//imprime historico de ligacões do celular
	for(int i=0; i<lista.size(); i++){
		lista[i]->info();
	}
}

void Celular::ligar_S(double dura, Datah Dh, double nt){//realiza ligação simples ERRO
	const LigacaoS ls(dura, Dh, nt);
	lista.push_back(new LigacaoS(ls));
	lista.back()->calcula(plano->ValorMin());
	//plano->spend(lista.back()->valor);// (problema)
}

void Celular::ligar_D(double dura, Datah Dh, TipoDeDados tdd){//realiza ligação de dados ERRO
	const LigacaoD ld(dura, Dh, tdd);
	lista.push_back(new LigacaoD(ld));
	lista.back()->calcula(plano->veloc());
	//plano->spend_D(lista.back()->valor);// (problema)
}


Cliente::Cliente(string cpf, string n, string end, Plano *P,const double &num){//construtor
	CPF=cpf; nome=n; endereco=end;
	const Celular cell( num, this, P );
	celulares;
	CPF=cpf; nome=n; endereco=end; 
}

Cliente::Cliente(const Cliente &C){//contrutor de copia
	CPF=C.CPF; nome=C.nome; endereco=C.endereco;
		for(int i=0; i<C.celulares.size(); i++){
			celulares[i]=C.celulares[i];
		}
}

void Cliente::info(){//imprime as informaçoes dobre o quiente
		cout<<"CPF:"<<CPF<<endl<<"Nome:"<<nome<<endl;
		cout<<"Endereco:"<<endereco<<endl;
	}
	
int main(){
	Datah a(2,1,2019), b(1,12,2020), c(1,1,2019,24,31,60);
	LigacaoS s(40,a,0);
	LigacaoD d(25,b,DOWLOAND);
	PrePago K("a",1,1,1,.1,25,b);
	PosPago G("a",.5,3,10,.4,10,b);
	Cliente R("123.456.789","jorge","r.",&K,900000000 );
	/*C.ligar_S(40,a,900000001);
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
	G.checa();*/
return 0;
}

