#include <iostream>

using namespace std;

class Noh{
	friend class Hash;
	private:
		Noh* PtProximo;
		string Palavra;
		string Significado;
	public:
		Noh(string &Palavra, string &Significado);
};

class Hash{
	private:
		unsigned Cap;
		Noh** Blocos;
	public:
		Hash();
		~Hash();
		void Inserir(string &Palavra, string &Significado);
		string Buscar(string &Palavra);
};

Noh::Noh(string &Palavra, string &Significado){
	Palavra = Palavra;
	Significado = Significado;
	PtProximo = NULL;
}

Hash::Hash(){
	Cap = 23;
	Blocos = new Noh*[Cap];
	for(unsigned i = 0; i < Cap; i++){
		Blocos[i] = NULL;
	}
}

Hash::~Hash(){
	for(unsigned i = 0; i < Cap; i++){
		Noh* Aux = Blocos[i];
		while(Aux != NULL){
			Noh* Anterior = Aux;
			Aux = Aux->PtProximo;
			delete Anterior;
		}
	}
	delete[] Blocos;
}

unsigned FuncaoHash(string &Palavra){      // Funcão hash com tamanho 23;
	return (Palavra.length() % 23);
}

void Hash::Inserir(string &Palavra, string &Significado){
	unsigned Pos = FuncaoHash(Palavra);
	Noh* NovoNoh = Blocos[Pos];
	if(Blocos[Pos] == NULL){
		Blocos[Pos] = new Noh(Palavra, Significado);
	}
	else{
		while(NovoNoh->PtProximo != NULL){
			NovoNoh = NovoNoh->PtProximo;
		}
		NovoNoh->PtProximo = new Noh(Palavra, Significado);
	}
}

string Hash::Buscar(string &Palavra){
	unsigned Pos = FuncaoHash(Palavra);
	if (Blocos[Pos] != NULL){
		Noh* Aux = Blocos[Pos];
		while(Aux->PtProximo != NULL and Aux->Palavra != Palavra){
			Aux = Aux->PtProximo;
		}
		if(Aux->Palavra == Palavra){
			return Aux->Significado;
		}
	}
	return "NULL";
}

int main(){
	Hash Perninha;
	unsigned quant;
	cin >> quant;
	string palavra, significado;
	for(unsigned i = 0; i < quant; i++)
	{
		cin >> palavra;
		cin.ignore();
		getline(cin, significado);
		Perninha.Inserir(palavra, significado);
	}
	string busca;
	cin >> busca;
	do
	{
		cout << "[" << busca << "]" << " => " << Perninha.Buscar(busca) << endl;
		cin >> busca;
	}
	while(busca != "-1");

	
	return 0;
}
