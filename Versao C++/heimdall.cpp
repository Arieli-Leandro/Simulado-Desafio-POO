#include <iostream>
#include <string>
#include <chrono>
#include <vector>
using namespace std;


class Usuario{

    protected:
        long id;
        string nome;
        int matricula;
        string email;
        bool ativo;

    public:
        bool autenticar(){

            if(ativo == false){
                ativo = true;
            }

            return ativo;

        };

        bool virtual podeRetirarChave() = 0;

        //Esse método virtual é pq professor e tecnico tem prazos diferentes para devolver as chaves
        int virtual prazoHoras() = 0;


};

class Professor: public Usuario{

    //unico método é o override de podeRetirar()
    int prazoHoras() override {

        return 24;

    }


};

class Tecnico: public Usuario{

    //unico método é o override de podeRetirar()
    int prazoHoras() override {

        return 8;

    }


};

class Administrador: public Usuario{

    public:
        bool podeRetirar(){

        }

        void cadastrarChave(){

        }

        void cadastrarUser(){

        }

};

//status é um atributo de um enum que é o StatusChave
enum StatusChave {
    DISPONIVEL,
    EMPRESTADA,
    EM_ATRASO
};

class Chave{

    private:
        long id;
        string codigo;
        StatusChave status;
        Ambiente ambiente;

        //fiz no private porque não é interessante acessar o menu por fora
        int menu(){
    
        }

    public:
        bool disponivel(){

            bool retorno;

            if(status == DISPONIVEL){
                cout << "A chave esta disponivel!" << endl;
                retorno = true;
            }else{

                cout << "A chave nao esta disponivel!" << endl;
                retorno = false;
            }

            return retorno;

        }

        void exibeChavesCondicao(){

            //vou fazer um menu -> O usuário vai escolher qual condição, e eu vou exibir essa condição

        }

        void exibeTodasChaves(){

        }


};

//quero fazer uma função que gere um id para que a pessoa não tenha que ficar digitando manualmente
vector<long>incializaVetorRegistros(){

    vector <long> vetorInicializadoFuncao = {0, 0, 0, 0};
    return vetorInicializadoFuncao;
}

long geradorId(int cod_id, long registros[]){

    //Guia da função geradorID: pelo cod_id ele cai nos casos e gera um id para o respectivo valor de acordo com um contador, e guarda esse contador numa variável

    /*Aonde temos id?
        -> Usuario cod 1
        -> Emprestimo cod 2
        -> Chave cod 3
        -> Ambiente cod 4
    
    */

    long valorIdGerado;

    int contadorUsuario = registros[0];
    int contadorEmprestimo = registros[1];
    int contadorChave = registros[2];
    int contadorAmbiente = registros[3];

    switch (cod_id){

        case 1: // Usuario

            contadorUsuario += 1;
            valorIdGerado = contadorUsuario;

            //Atualiza o valor nos registros
            registros[0] = contadorUsuario;        

        break;

        case 2: // Emprestimo

            contadorEmprestimo += 1;
            valorIdGerado = contadorEmprestimo;

            //atualiza
            registros[1] = contadorEmprestimo;

        break;

        case 3: // Chave

            contadorChave += 1;
            valorIdGerado = contadorChave;

            //atualiza
            registros[2] = contadorChave;

        break;

        case 4: //Ambiente

            contadorAmbiente += 1;
            valorIdGerado = contadorAmbiente;

            //atualiza
            registros[3] = contadorAmbiente;

        break;

    }

    return valorIdGerado;

}


class Ambiente{
    //não temos métodos em ambiente
    private:
        long id;
        string nome;
        string bloco;
        string descricao;
    public:

        //Métodos setters
        void setId(long valor){
            this->id = valor;
        }

        void setNome(string valor_nome){
            this->nome = valor_nome;
        }

        void setBloco(string valor_bloco){
            this->bloco = valor_bloco;
        }

        void setDescricao(string valor_descricao){
            this->descricao = valor_descricao;
        }

        //Métodos getters
        long getId(){
            return id;
        }

        string getNome(){
            return nome;
        }

        string getBloco(){
            return bloco;
        }

        string getDescricao(){
            return descricao;
        }

    
        Ambiente(){

        }

        ~Ambiente(){
            //ambiente nn tem ponteiro, ent nn precisa desalocar

        }

};

class Emprestimo{

    private:
        long id;
        Usuario *usuario;
        Chave *chave; // é um ponteiro pq chave existe sem a necessidade de emprestimo, mas emprestimo precisa da chave a sintaxe pode ser Chave& chave; (também)   
        std::chrono::system_clock::time_point dataRetirada;
        std::chrono::system_clock::time_point dataPrevista;
        std::chrono::system_clock::time_point dataDevolucao;
        string justificativa;
    public:
        void encerrarEmprestimo(){

        }

        bool verificarAtraso(){


        }


};



int main(){

    //inicializa o vetor

    //isso não pode ficar aqui -> Ir pra main ou ir pra global?
    vector <long> registros = incializaVetorRegistros();
    /* -> Primeira posição do vetor Referente á Usuarios
       -> Segunda posição do vetor Referente á Emprestimo
       -> Terceira posição do vetor Referente á Chave
       -> Ambiente posição do vetor Referente á Ambiente
    */



    return 0;
    
}
