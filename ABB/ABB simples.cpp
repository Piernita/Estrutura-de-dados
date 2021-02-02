/* Changed by Perninha, Janeiro de 2021 (pandemic) - Aluno de Estrutura de Dados (GCC216)
*  ABB com encadeamento simples, inserção e busca.
*/

#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

class Info {
    friend class Noh;
    friend class ABB;
    friend ostream& operator<< (ostream& saida, const Info& info);
    public:
        bool operator == (const Info& i) { return chave == i.chave; }
        bool operator < (const Info& i) { return chave < i.chave; }
        void setChave(int& c);
        void setValor(string& v);
        int getChave() { return this->chave; }
        string getValor() { return this->valor; }
    private:
        int chave;
        string valor;
};

void Info::setChave(int& c){
    this->chave = c;
}

void Info::setValor(string& v){
    this->valor = v;
}


class Noh {
    friend class ABB;
    public:
        Noh(int& chave, string& dado);
    private:
        int chave;
        string dado;
        Noh* PtEsq;
        Noh* PtDir;
};

Noh::Noh(int& chave, string& dado){
    this->chave = chave;
    this->dado = dado;
    PtEsq = NULL;
    PtDir = NULL;
}

class ABB {
    public:
        ABB();
        ~ABB();
        void Inserir(Info& info);
        void percorreEmOrdem();
        string Busca(int& chave);
    private:
        void destruirRecursivamente(Noh* umNoh);
        void percorreEmOrdemAux(Noh* umNoh);
        Noh* BuscaAux(int& chave);
        Noh* Raiz;
};

ABB::ABB(){
    Raiz = NULL;
}

// destrutor
ABB::~ABB(){
    destruirRecursivamente(Raiz);
}

// destrutor recursivo, fazendo percorrimento pos-ordem
void ABB::destruirRecursivamente(Noh* umNoh){
    if(umNoh != NULL){
        destruirRecursivamente(umNoh->PtEsq);
        destruirRecursivamente(umNoh->PtDir);
        delete umNoh;
    }
}

void ABB::Inserir(Info& info){
    Noh* NovoNoh = new Noh(info.chave, info.valor);
    if(Raiz == NULL){
        Raiz = NovoNoh;
    }
    else{
        Noh* atual = Raiz;
        Noh* anterior = NULL;
        while(atual != NULL){
            anterior = atual;
            if(atual->chave >= NovoNoh->chave){
                atual = atual->PtEsq;
            }
            else{
                atual = atual->PtDir;
            }
        }
        if(anterior->chave > NovoNoh->chave){
            anterior->PtEsq = NovoNoh;
        }
        else{
            anterior->PtDir = NovoNoh;
        }

    }
}

void ABB::percorreEmOrdem(){
    percorreEmOrdemAux(Raiz);
}

void ABB::percorreEmOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        percorreEmOrdemAux(umNoh->PtEsq);
        cout << umNoh->chave << endl;
        percorreEmOrdemAux(umNoh->PtDir);
    }
}

string ABB::Busca(int& chave){
    Noh* Aux = BuscaAux(chave);
    if(Aux == NULL){
        return "INEXISTENTE";
    }
    else{
        return Aux->dado;
    }
}

Noh* ABB::BuscaAux(int& chave){
    Noh* atual = Raiz;
    while(atual != NULL){
        if(atual->chave == chave){
            return atual;
        }
        else if(atual->chave > chave){
            atual = atual->PtEsq;
        }
        else{
            atual = atual->PtDir;
        }
    }
    return atual;
}

ostream& operator << (ostream& saida, const Info& info) {
    saida << '(' << info.chave << ',' << info.valor << ')';
    return saida;
}

int main() {
    ABB arvore;
    Info info;
    char operacao;
    int chave;
    string valor;

    do {
        cin >> operacao;
        switch (operacao) {
            case 'i': // Inserir
                cin >> chave >> valor;
                info.setChave(chave);
                info.setValor(valor);
                arvore.Inserir(info);
                break;
            case 'b': // Buscar
                cin >> chave; // ler a chave
                info.setChave(chave);
                valor = arvore.Busca(chave);
                info.setValor(valor);
                cout << info.getValor() << endl;
                break;
            case 'e': // Escrever tudo
                arvore.percorreEmOrdem();
                break;
            case 'f': // Finalizar execução
                break;
            default:
                cerr << "Comando invalido!\n";
        }
    } while (operacao != 'f');
    return 0;
}

//Little D. Legs, 31/01/2021
