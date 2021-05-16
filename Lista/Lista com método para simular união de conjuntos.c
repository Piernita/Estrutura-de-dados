#include <iostream>

using namespace std;

typedef int dado;

class Noh{
  friend class Lista;
  private:
    dado valor;
    Noh* PtProximo;
  public:
    Noh(dado d);
};

Noh::Noh(dado d) {
  valor = d;
  PtProximo = NULL;
}

class Lista{
  private:
    Noh* PtPrimeiro;
    Noh* PtUltimo;
  public:
    Lista();
    ~Lista();
    void InsereNoFim(dado& d);
    void Uniao(Lista& B);
    void imprime();
};

Lista::Lista(){
  PtPrimeiro = NULL;
  PtUltimo = NULL;
}

Lista::~Lista(){
  Noh* Aux = PtPrimeiro;
  Noh* Temp;
  while(Aux != NULL){
    Temp = Aux;
    Aux = Aux->PtProximo;
    delete Temp;
  }
}

void Lista::InsereNoFim(dado& d){
  if(PtPrimeiro == NULL){
    Noh* NovoNoh = new Noh(d);
    PtPrimeiro = NovoNoh;
    PtUltimo = NovoNoh;
  }
  else{
    bool achei = false;
    Noh* busca = PtPrimeiro;
    while(busca != NULL and achei == false){
        if(busca->valor == d){
            achei = true;
        }
        busca = busca->PtProximo;
    }
    if(achei == false){
      Noh* NovoNoh = new Noh(d);
      PtUltimo->PtProximo = NovoNoh;
      PtUltimo = NovoNoh;
    }
  }
}

void Lista::Uniao(Lista& B){
    if(this->PtPrimeiro == NULL){
        Noh* aux = B.PtPrimeiro;
        while(aux != NULL){
            this->InsereNoFim(aux->valor);
            aux = aux->PtProximo;
        }
    }
    else{
        Noh* aux = PtPrimeiro;
        Noh* auxb = B.PtPrimeiro;
        bool encontrei = false;

        while (auxb != NULL){
            while (aux != NULL and encontrei == false){
                if(aux->valor == auxb->valor){
                    encontrei = true;
                }
                else{
                    aux = aux->PtProximo;
                }
            }
            if(encontrei == false){
                this->InsereNoFim(auxb->valor);
            }
            auxb = auxb->PtProximo;
            aux = PtPrimeiro;
            encontrei = false;
        }
    }
}

void Lista::imprime() {
  Noh* aux = PtPrimeiro;

  while (aux != NULL) {
    cout << aux->valor << " ";
    aux = aux->PtProximo;
  }

  cout << endl;
}

int main() {
  Lista A;
  Lista B;
  dado TamA, TamB;
  dado d;

  cin >> TamA;
  for(int i = 0; i < TamA; i++){
    cin >> d;
    A.InsereNoFim(d);
  }
  cin >> TamB;
  for(int i = 0; i < TamB; i++){
    cin >> d;
    B.InsereNoFim(d);
  }
  A.imprime();
  B.imprime();
  A.Uniao(B);
  A.imprime();
  return 0;
}
