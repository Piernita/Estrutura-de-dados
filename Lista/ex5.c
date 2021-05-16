#include <iostream>

using namespace std;

typedef int dado; // para facilitar a troca por outros tipos

class noh {
    friend class lista;
    private:
        dado valor;
        noh* proximo;
    public:
        noh(dado d);
};

// construindo noh com um valor
noh::noh(dado d) {
    valor = d;
    proximo = NULL;
}

// lista dinamicamente encadeada
class lista {
    private:
        noh* primeiro;
    public:
        // construtores e destrutor
        lista();
        ~lista();
        // inserção e remoção
        void insereNoInicio(dado valor);
        void insereNoFim(dado valor);
        dado retiraNoInicio();
        dado retiraNoFim();
        // impressão e tamanho
        void imprime();
        unsigned tamanho();
};


// constrói uma lista inicialmente vazia
lista::lista() {
    primeiro = NULL;
}

// destrutor da lista
lista::~lista( ) {
    noh* aux = primeiro;
    noh* temp;

    while (aux != NULL) {
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }
}

// insere no início da lista
void lista::insereNoInicio(dado valor) {
  if(primeiro == NULL){
    noh* NovoNoh = new noh(valor);
    primeiro = NovoNoh;
  }
  else{
    noh* NovoNoh = new noh(valor);
    NovoNoh->proximo = primeiro;
    primeiro = NovoNoh;
  }
}

// insere no final da lista
void lista::insereNoFim(dado valor) {
  if(primeiro == NULL){
    noh* NovoNoh = new noh(valor);
    primeiro = NovoNoh;
  }
  else{
    noh* NovoNoh = new noh(valor);
    noh* aux = primeiro;
    while(aux->proximo != NULL){
        aux = aux->proximo;
    }
    aux->proximo = NovoNoh;
  }
}

// retira no início da lista
dado lista::retiraNoInicio() {
  dado valor = 0;
  noh* aux = primeiro;
  valor = aux->valor;
  primeiro = aux->proximo;
  delete aux;
  return valor;
}

// retira no fim da lista
dado lista::retiraNoFim() {
  dado valor = 0;
  noh* aux = primeiro;
  noh* anterior = NULL;
  while(aux->proximo != NULL){
    anterior = aux;
    aux = aux->proximo;
  }
  valor = aux->valor;
  if(anterior == NULL){
    primeiro = NULL;
  }
  else{
    anterior->proximo = NULL;
  }
  delete aux;
  return valor;
}

// tamanho da lista
unsigned lista::tamanho() {
  noh* aux = primeiro;
  unsigned cont = 0;
    while(aux != NULL){
      cont++;
      aux = aux->proximo;
    }
    return cont;
}

// método básico que *percorre* uma lista, imprimindo seus elementos
void lista::imprime() {
    noh* aux = primeiro;

    while (aux != NULL) {
        cout << aux->valor << " ";
        aux = aux->proximo;
    }

    cout << endl;
}

int main() {
    lista minhaLista;

    char opcao;
    dado valor;

    cin >> opcao;
    while (opcao != 'Q') {
        switch(opcao) {
            case 'I':
                cin >> valor;
                minhaLista.insereNoInicio(valor);
                break;
            case 'F':
                cin >> valor;
                minhaLista.insereNoFim(valor);
                break;
            case 'X':
                cout << minhaLista.retiraNoInicio() << endl;
                break;
            case 'Z':
                cout << minhaLista.retiraNoFim() << endl;
                break;
            case 'T':
                cout << minhaLista.tamanho() << endl;
                break;
            case 'P':
                minhaLista.imprime();
                break;
        }
        cin >> opcao;
    }

    return 0;
}
