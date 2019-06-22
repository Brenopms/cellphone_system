#ifndef TP1_H
#define TP1_H

#include <iostream>
#include <cstring>
#include <vector> 
#include <iomanip>
using namespace std;

// essa classe foi feita exclusivamente para as condiçoes do TP2 
class Datah{
	unsigned int dia, mes, ano;
	unsigned int hora, min, seg;
	public:
	Datah(int d=1, int m=1, int a=2019, int h=0, int mi=0, int s=0){ dia=d; mes=m; ano=a; hora=h; min=mi; seg=s; }//o ano começa em 2019 (nao necessita construtor de copia)
	const bool valid();//testa se a dataé uma numero valido
	const bool antiga(const Datah &);//testa se data fornecida é mais atiga que a atual
	void somad(int d=180);//soma dias a data (valor padrão de recarga de creditos)
	void somam(int m=1);//soma meses a data(valor padrão para o plano pos pago)
	void datahora() {cout<<dia<<"/"<<mes<<"/"<<ano<<"-"<<hora<<":"<<min<<":"<<seg<<endl;}// imprime na tela data e hora
	friend ostream &operator<<(ostream &, const Datah &);// impriome a data e a hora
};


class Plano{
	string name;
	double valorMin;//valor do minuto de ligação
	double velocidade;// em MB/s
	double velocAlem;// em MB/s
	double franquia;// franquia cheia do plano em GB
	protected:
		double Dados;// franquia atual do plano em GB
	public:
		Plano(string s, double vm, double v, double f, double va){name=s; valorMin=vm; velocidade=v; franquia=f; Dados=f; velocAlem=va; }//contrutor
		
		Plano(const Plano &p) {name=p.name; valorMin=p.valorMin; velocidade=p.velocidade; franquia=p.franquia; Dados=p.Dados; velocAlem=p.velocAlem;}//construtor de copia
		
		void muda(double vm, double v, double f, double va) {valorMin=vm; velocidade=v; franquia=f; velocAlem=va; }//muda caracteristicas do polano
		
		void spend_D(const double &c){Dados-=c;}//gasta dados da franquia
	
		virtual void spend(const double &)=0;//contabilisa o gasto da ligação
		
		void renova_D(){Dados=franquia;}//renova a fraquia de dados
		
		const double veloc(){ if(f_valida())return velocidade; return velocAlem; }//retorna a velocidade de conexão dependendo da franquia de dados
		
		const double ValorMin(){ return valorMin; }//retorna o valor do minuto
				
		const bool f_valida(double f=0){if(Dados>=f){if(Dados==0)return false; return true;} return false;}//testa se ha dados disponiveis
		
		void info(){//imprime na tela as informações do plano
		cout<<"Plano:"<<name<<endl<<"Valor do min:R$"<<valorMin<<endl;
		cout<<"Velociodade:"<<velocidade<<"MB/s\n";
		cout<<"Franquuia de dados:"<<franquia<<"GB\n";
		cout<<"Velocidade alem da franquia:"<<velocAlem*1000<<"KB/s\n"; }
		
		virtual void checa()=0;
};

class PrePago: public Plano{//conciderei que a franquia de dados não custa creditos e é renovada quando ha compra creditos
	double credito;
	Datah validade;
	public:
		PrePago(string s, double vm, double v, double f, double va, double c, Datah val):Plano(s, vm, v, f, va) { credito=c; validade=v; }// construtor
	
		void spend(const double &c){ credito-=c;}//gasta creditos
	
		void add_cred(const double &c) { credito+=c; validade.somad();renova_D(); }// compra creditos aumenta a validade dels em 18 dias e renova a franquia
	
		const bool c_valido(double c, const Datah &val){ if((credito>=c)&&(!validade.antiga(val)))return true;return false; }//testa se o cridtoé sufuciente e/ou não venceu
		
		void checa(){//imprime na tela a quantidade de creditos e sua data de validade e  os dados disponivies 
			cout<<"Creaditos:R$"<<credito<<endl<<"Validade:";
			validade.datahora();
			cout<<"Franquia de dados:"<<Dados<<"GB\n";
		}
};

class PosPago: public Plano{
	double conta;// valor a se pagar no final do mes
	double vbase;// valor base da conta
	Datah vencimento;// a data de vencimentyo sera estabeliceda entre os dias 1° ao 15° di do mes
	public:
		PosPago(string s, double vm, double v, double f, double va,double con, Datah ven):Plano(s, vm, v, f, va) {vbase=con; conta=vbase; vencimento=ven; }//construtor
		
		void spend(const double &c) {conta+=c;}//aumenta o valor da conta 
		
		void paga(){ vencimento.somam(); renova_D(); conta=vbase; }// paga a conta . adia a data de vencimento em um mes, renoma a franquia de dados
		
		const bool vencida(Datah ven){//retorna se a conta esta vencida
			if(vencimento.antiga(ven))return true;
			return false;}	

		void checa(){
			cout<<"Conta:R$"<<conta<<endl<<"Vencimento:";
			vencimento.datahora();
			cout<<"Franquia de dados:"<<Dados<<"GB\n";}
};

class Ligacao{
	protected:
		double duracao;//duração da ligação em segundos
		double custo;//custo da ligação
		Datah DataHora;//Data e hora em que a liagação foi feita
	public:
		Ligacao(double dura, Datah Dh){duracao=dura; DataHora=Dh;}//contrutor
		
		Ligacao(const Ligacao &l){duracao=l.duracao; custo=l.custo; DataHora=l.DataHora; }
		
		virtual void calcula(const double &)=0; 
		
		const double valor(){return custo;}//retorna o valor da ligação
		
		virtual void info()=0;
		
		friend ostream &operator<<(ostream &, const Ligacao &);// impriome a ligaçao;
};

class LigacaoS:public Ligacao{//ligação simples
	double numTelefone;
	public:
		LigacaoS(double dura, Datah Dh, double nt): Ligacao(dura, Dh) { numTelefone=nt; }//contrutor
		
		LigacaoS(const LigacaoS &ls): Ligacao(ls) {numTelefone=ls.numTelefone;}// construtor de copia
		
		void calcula(const double &V){ custo=duracao*V/60; }// dividir por 60 pois o valor do plano é por minuto e aduração é por segundo
		
		void info() {
		cout<<"Numero:"<<fixed<<setprecision(0)<<numTelefone<<endl<<"Duracao:"<<duracao<<"s\nCusto:"<<setprecision(1)<<custo<<"\nData:"<<DataHora; }//imprime na tela os detalhes da ligação
		
		
}; 

enum TipoDeDados{//enumerador para classe LigacaoD
		DOWLOAND,
		UPLOAD
	};
class LigacaoD:public Ligacao{//igação de dados'
	TipoDeDados TDD;//tipo de dados da ligação
	public:
		LigacaoD(double dura, Datah Dh, TipoDeDados D): Ligacao(dura, Dh) { TDD=D; }//construtor
		
		LigacaoD(const LigacaoD &ld): Ligacao(ld) { TDD=ld.TDD; }// contrrutor de copia
		
		void calcula(const double &V){
			if(TDD==0) custo=duracao*V/1000;//dividi por mil pois a velocidade de dados esta em MB e a franquia em GB
			custo=duracao*V/10000; }// didivid por 10000 pois a velocodade de upload é 10x menor d=que a de download
		
		void info() {//imprime na tela os detalhes da ligação
		cout<<fixed<<setprecision(0);
		cout<<"Tipo:"<<TDD<<endl<<"Duração:"<<duracao<<"s\nDados:"<<custo*1000<<"MB"; }
};


class Cliente;

class Celular {
	double numero;
	Cliente *cliente;
	Plano *plano;
	vector <Ligacao*> lista;
	static double proxNumCelular;
	public:
		Celular( const double &n, Cliente *C, Plano *P) {numero=n; cliente=C; plano=P; }//construtor viencula cliente e ploano ao celular (proxNumCelular=n++;)
		
		Celular(const Celular &);//contrutor de copia
		
		void ligar_S(double, Datah, double);//realiza ligação simples ERRO
		
		void ligar_D(double, Datah , TipoDeDados );//realiza ligação de dados ERRO
		
		void num(){cout<<"Numero:"<<numero<<endl;}//impri,me na tela o numero do telefone
		
		void info_C();//imprime informacoes sobre o cliente e o celular
		
		void print_l();//imprime historico de ligacões do celular
};

class Cliente {
	string CPF, nome, endereco;
	vector<Celular*> celulares;
	public:
		Cliente(string , string , string , Plano* , const double &);//construtor
		
		Cliente(const Cliente &);//contrutor de copia
		
		void getcell(const Celular&, const Plano*);//veincula UM celular ao cliente
		
		pay(const double &);//paga as contas ou poe credito
		
		void info();//imprime as informaçoes dobre o quiente
};


#endif
