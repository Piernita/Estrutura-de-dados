/* Implementar uma Lista duplamente encadeada - Operações basicas em conjuntos,
Possui uma estrutura de dados do tipo conjunto, uma coleção de elementos na lista.
Funcionando como um vetor de Listas;
By: Little D. Legs, 28/08/2020 */

#include <iostream>
#include <cmath>

using namespace std;

////////////////////////////////////// DECLARACAO DE CLASSES //////////////////////////////////

class Noh{
	friend class Lista;
	private:
		Noh* PtProximo;
		Noh* PtAnterior;
		int Comando;
	public:
		Noh(int Comando);
};

class Lista{
    friend class conjunto;
	private:
		unsigned Tam;
		Noh* PtPrimeiro;
		Noh* PtUltimo;
		bool Vazia();
		void InserirOrdenado(int &Dado);
		void InserirEmListaVazia(int &Dado);
		void Imprimir();
		void Remover(int &Dado);
		bool Busca(int &Dado);
		void CopiarLista(Noh* C);
		void Comparar(Lista* A, Lista* B, bool Joker);
		void DepurarLista();
	public:
		Lista();
		~Lista();
};

class conjunto {
    private:
        Lista* Raiz;
    public:
        conjunto();
        ~conjunto();
        void insere(int &Elemento);
        void imprime();
        void remover(int &elemento);
        unsigned tamanho();
        bool membro(int &elemento);
        void uniao(conjunto &C1, conjunto &C2);
        void intersecao(conjunto &C1, conjunto &C2);
        void diferenca(conjunto &C1, conjunto &C2);
        void depura();
};

// CONTRUTOR DO NOH

Noh::Noh(int c){
	Comando = c;
	PtProximo = NULL;
	PtAnterior = NULL;
}

////////////////////////// DECLARACAO DOS METODOS DA CLASSE CONJUNTO /////////////////////////

conjunto::conjunto(){
    Raiz = new Lista();
}

conjunto::~conjunto(){
    delete Raiz;
}

void conjunto::insere(int &Elemento){
    Raiz->InserirEmListaVazia(Elemento);
}

void conjunto::imprime(){
    Raiz->Imprimir();
}

void conjunto::remover(int &Elemento){
    Raiz->Remover(Elemento);
}
unsigned conjunto::tamanho(){
    return Raiz->Tam;
}

bool conjunto::membro(int &Elemento){
    return Raiz->Busca(Elemento);
}

void conjunto::uniao(conjunto &C1, conjunto &C2){
    if(C1.Raiz->Vazia() or C2.Raiz->Vazia()){
        cout << "Impossivel realizar a uniao" << endl;
    }
    else{
        Raiz->CopiarLista(C1.Raiz->PtPrimeiro);
        Raiz->CopiarLista(C2.Raiz->PtPrimeiro);
    }
}

void conjunto::intersecao(conjunto &C1, conjunto &C2){
    if(C1.Raiz->Vazia() or C2.Raiz->Vazia()){
        cout << "Impossivel realizar a intesecao" << endl;
    }
    else{
        Raiz->Comparar(C1.Raiz, C2.Raiz, true);
    }
}

void conjunto::diferenca(conjunto &C1, conjunto &C2){
    if(C1.Raiz->Vazia() or C2.Raiz->Vazia()){
        cout << "Impossivel realizar a diferenca" << endl;
    }
    else{
        Raiz->Comparar(C1.Raiz, C2.Raiz, false);
    }
}

void conjunto::depura(){
    cout << "{ ";
    Raiz->DepurarLista();
    cout << '}' << endl;
}

////////////////////////// DECLARACAO DOS METODOS DA CLASSE LISTA ////////////////////////////

Lista::Lista(){
	Tam = 0;
	PtPrimeiro = NULL;
	PtUltimo = NULL;
}

Lista::~Lista(){
	Noh* Del = PtPrimeiro;
	Noh* ProximoAux = NULL;
	while(Del != NULL){
		ProximoAux = Del->PtProximo;
		delete Del;
		Del = ProximoAux;
	}
	Del = NULL;
	ProximoAux = NULL;
	delete Del;
	delete ProximoAux;
}

bool Lista::Vazia(){
	return(Tam==0);
}

void Lista::InserirEmListaVazia(int &Dado){
	if(Vazia()){
		Noh* NovoNoh = new Noh(Dado);
		PtPrimeiro = NovoNoh;
		PtUltimo = NovoNoh;
		Tam++;
	}
	else{
		InserirOrdenado(Dado);
	}
}

void Lista::InserirOrdenado(int &Dado){
    Noh* Aux = PtPrimeiro;
    Noh* Aux2 = NULL;
    // Inserindo no Inicio;
    if((Aux->Comando > Dado) and (Aux == PtPrimeiro)){
        Noh* NovoNoh = new Noh(Dado);
        NovoNoh->PtProximo = PtPrimeiro;
        PtPrimeiro->PtAnterior = NovoNoh;
        PtPrimeiro = NovoNoh;
        Tam++;
    }
    // Inserindo no Fim;
    else if(PtUltimo->Comando < Dado){
        Noh* NovoNoh = new Noh(Dado);
        NovoNoh->PtAnterior = PtUltimo;
        PtUltimo->PtProximo = NovoNoh;
        PtUltimo = NovoNoh;
        Tam++;
    }
    else{
        // Inserindo em Posicao;
        while((Aux != NULL) and (Aux->Comando < Dado)){
            Aux = Aux->PtProximo;
        }
        if(Aux->Comando == Dado){
            // Ja Existe;
        }
        else if((Aux->Comando > Dado) and (Aux != NULL)){;
            Noh* NovoNoh = new Noh(Dado);
            Aux2 = Aux->PtAnterior;
            NovoNoh->PtProximo = Aux;
            NovoNoh->PtAnterior = Aux2;
            Aux->PtAnterior = NovoNoh;
            Aux2->PtProximo = NovoNoh;
            Tam++;
        }
        else{
            // È PARA NUNCA ENTRAR AQUI
            cout << "VISH O BATMAN CHEGOU" << endl;
        }
    }
}

void Lista::Imprimir(){
    if(Vazia()){
    }
    else{
        Noh* Aux = PtPrimeiro;
        while(Aux!=NULL){
            cout << Aux->Comando << " ";
            Aux = Aux->PtProximo;
        }
    }
    cout << endl;
}

void Lista::Remover(int &Dado){
    if(Vazia() or Busca(Dado) == false){
    }
    else{
        Noh* Aux = PtPrimeiro;
        Noh* Aux2 = NULL;
        Noh* Aux3 = NULL;
        // Removendo Elemento Unico;
        if((PtPrimeiro->Comando == Dado) and (PtPrimeiro==PtUltimo)){
            PtPrimeiro = NULL;
            PtUltimo = NULL;
            delete Aux;
            Tam--;
        }
        // Removendo no Inicio;
        else if(PtPrimeiro->Comando == Dado){
            PtPrimeiro = PtPrimeiro->PtProximo;
            PtPrimeiro->PtAnterior = NULL;
            delete Aux;
            Tam--;
        }
        // Removendo no Fim
        else if(PtUltimo->Comando == Dado){
            Aux = PtUltimo;
            PtUltimo = PtUltimo->PtAnterior;
            PtUltimo->PtProximo = NULL;
            delete Aux;
            Tam--;
        }
        else{
            // Removendo em Posicao
            while((Aux != NULL) and (Aux->Comando != Dado)){
                Aux = Aux->PtProximo;
            }
            if((Aux->Comando == Dado) and (Aux != NULL)){
                Aux2 = Aux->PtAnterior;
                Aux3 = Aux->PtProximo;
                Aux2->PtProximo = Aux3;
                Aux3->PtAnterior = Aux2;
                Aux2 = NULL;
                Aux3 = NULL;
                delete Aux;
                delete Aux2;
                delete Aux3;
                Tam--;
            }
            else{
                // NAO ENCONTRADO É PARA NUNCA ENTRAR AQUI
                Aux = NULL;
                Aux2 = NULL;
                Aux3 = NULL;
                delete Aux;
                delete Aux2;
                delete Aux3;
            }
        }
    }
}

bool Lista::Busca(int &Dado){
    if(Vazia()){
        return false;
    }
    else{
        Noh* Aux = PtPrimeiro;
        while(Aux != NULL){
            if(Aux->Comando == Dado){
                return true;
            }
            else{
                Aux = Aux->PtProximo;
            }
        }
        return false;
    }
}

void Lista::CopiarLista(Noh* C){
    while(C!=NULL){
        InserirEmListaVazia(C->Comando);
        C = C->PtProximo;
    }
}

//Pegamos de A e buscamos em B para fins comparativos
void Lista::Comparar(Lista* A, Lista* B, bool Joker){
    Noh* Aux = A->PtPrimeiro;
    bool Encontrei = B->Busca(Aux->Comando);
    while(Aux != NULL){
        Encontrei = B->Busca(Aux->Comando);
        // se ENCONTREI e é INTERSECAO: inserir;
        if((Encontrei ==  true) and (Joker == true)){
            this->InserirEmListaVazia(Aux->Comando);
            Aux = Aux->PtProximo;
        }
        // se NAO ENCONTREI e é INTERSECAO: proximo;
        else if((Encontrei ==  false) and (Joker == true)){
            Aux = Aux->PtProximo;
        }
        // se NAO ENCONTREI e é DIFERENCA: Inserir
        else if((Encontrei == false) and (Joker ==  false)){
            this->InserirEmListaVazia(Aux->Comando);
            Aux = Aux->PtProximo;
        }
        // se ENCONTREI e é DIFERENCA: proximo;
        else if((Encontrei == true) and (Joker == false)){
            Aux = Aux->PtProximo;
        }
    }
}

void Lista::DepurarLista(){
    if(Vazia()){
    }
    else{
        Noh* Aux = PtPrimeiro;
        while(Aux!=PtUltimo){
            cout << Aux->Comando << "<->";
            Aux = Aux->PtProximo;
        }
        if(Aux==PtUltimo){
            cout << Aux->Comando << " ";
        }
    }
}

// Função que retorna uma posição no vetor para um dado caracter maiúsculo
inline unsigned char2pos(char c) {
    return unsigned(c)- 65;
}

// *** não altere a função principal sem antes consultar os professores ***
int main( ) {
    conjunto meusConjuntos[26];
    char operacao;
    // conjuntos são representados por letras maiúsculas
    char conjunto1, conjunto2, conjunto3;
    int elemento;
    unsigned pos1, pos2, pos3;

    do {
        cin >> operacao;
        switch (operacao) {
            case 'i': // inserir
                cin >> conjunto1 >> elemento;
                pos1 = char2pos(conjunto1);
                meusConjuntos[pos1].insere(elemento);
                break;
            case 'r': // remover
                cin >> conjunto1 >> elemento;
                pos1 = char2pos(conjunto1);
                meusConjuntos[pos1].remover(elemento);
                break;
            case 'm': // checa pertinência
                cin >> conjunto1 >> elemento;
                pos1 = char2pos(conjunto1);
                cout << meusConjuntos[pos1].membro(elemento) << endl;
                break;
            case '+': // efetua união
                // conjunto1 terá o resultado da união de conjunto2 com conjunto3
                cin >> conjunto1 >> conjunto2 >> conjunto3;
                pos1 = char2pos(conjunto1);
                pos2 = char2pos(conjunto2);
                pos3 = char2pos(conjunto3);
                meusConjuntos[pos1].uniao(meusConjuntos[pos2],meusConjuntos[pos3]);
                break;
            case '*': // efetua interseção
                // conjunto1 terá o resultado da interseção de conjunto2 com conjunto3
                cin >> conjunto1 >> conjunto2 >> conjunto3;
                pos1 = char2pos(conjunto1);
                pos2 = char2pos(conjunto2);
                pos3 = char2pos(conjunto3);
                meusConjuntos[pos1].intersecao(meusConjuntos[pos2],meusConjuntos[pos3]);
                break;
            case '-': // efetua diferença
                // conjunto1 terá o resultado da diferença de conjunto2 para o conjunto3
                cin >> conjunto1 >> conjunto2 >> conjunto3;
                pos1 = char2pos(conjunto1);
                pos2 = char2pos(conjunto2);
                pos3 = char2pos(conjunto3);
                meusConjuntos[pos1].diferenca(meusConjuntos[pos2],meusConjuntos[pos3]);
                break;
            case 't': // tamanho
                cin >> conjunto1;
                pos1 = char2pos(conjunto1);
                cout << meusConjuntos[pos1].tamanho() << endl;
                break;
            case 'd': // mostrar estrutura
                cin >> conjunto1;
                pos1 = char2pos(conjunto1);
                meusConjuntos[pos1].depura();
                break;
            case 'p': // imprimir dados
                cin >> conjunto1;
                pos1 = char2pos(conjunto1);
                meusConjuntos[pos1].imprime();
                break;
            case 's': // sair
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    } while (operacao != 's');

    return 0;
}
