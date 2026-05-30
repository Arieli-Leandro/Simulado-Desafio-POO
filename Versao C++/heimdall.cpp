// Bloco de notas de -A -> Fazer tds os getters e setters e dps eu vejo oq eu faço no resto -> Básico -> Médio -> Finaliza

#include <iostream>
#include <string>
#include <chrono>
#include <vector>
using namespace std;
/*
-> Estrutura Base
-> Construtores e Destrutores
-> Getters e Setters
-> Interfaces
-> Métodos de Herança e Polimorfos
-> Funcionamento geral (LINKAR AS COISAS [via main? (talvez)])
-> Aplicações

*/



//getters e setter finalizado
class Usuario{

    protected:
        long id;
        string nome;
        int matricula;
        string email;
        bool ativo;

    public:

        //finalizar o construtor e destrutor dps
        Usuario(){

        }

        ~Usuario(){

        }

        //Metodos setter's
        void setId(long valor){
            this->id = valor;
            return;
        }

        void setNome(string valor_nome){
            this->nome = valor_nome;
            return;
        }

        void setMatricula(int valor_ma){
            this->matricula = valor_ma;
            return;
        }

        void setEmail(string valor_email){
            this->email = valor_email;
            return;
        }

        void setAtivo(bool valor_ativo){
            this->ativo = valor_ativo;
            return;
        }

        //Metodos getter's
        long getId(){
            return id;
        }

        string getNome(){
            return nome;
        }

        int getMatricula(){
            return matricula;
        }

        string getEmail(){
            return email;
        }

        bool getAtivo(){
            return ativo;
        }



        bool autenticar(){

            //Estou interpretando ativo como se o Usuário esteja empregado ou não na empresa. -> Se ativo: tem acesso -> Se não: não tem acesso
            bool retorno = false;

            if(ativo == true){
                retorno = true;
            }

            return retorno;

        };

        bool virtual podeRetirarChave() = 0;

        //Esse método virtual é pq professor e tecnico tem prazos diferentes para devolver as chaves
        int virtual prazoHoras() = 0;


};


//getters e setters vão vir por padrão no classe Mãe
class Professor: public Usuario{

    public:

        //finalizar dps o construtor e o destrutor ->Chamar o super
        Professor(){


        }

        ~Professor(){

        }

        //unico método é o override de podeRetirar()
        int prazoHoras() override {

            return 24;

        }


};


//getters e setters vão vir por padrão na classe Mãe
class Tecnico: public Usuario{

    public:

        //finalizar dps->Chamar o super
        Tecnico(){


        }

        ~Tecnico(){


        }

        //unico método é o override de podeRetirar()
        int prazoHoras() override {

            return 8;

        }


};

//getters e setter vão vir por padrão na classe Mãe
class Administrador: public Usuario{

    public:

        //finalizar dps -> Chamar o super
        Administrador(){


        }

        ~Administrador(){


        }

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

//getter e setters finalizados (verificar dps se o ponteiro tá para o lugar correto)
class Chave{

    private:
        long id;
        string codigo;
        StatusChave status;
        Ambiente *ambiente;

        //fiz no private porque não é interessante acessar o menu por fora
        int menu(){
    
        }

    public:

        //finalizar dps -> DESALOCA NO DESTRUTOR
        Chave(){


        }

        ~Chave(){


        }

        //métodos getters
        long getId(){
            return id;
        }

        string getCodigo(){
            return codigo;
        }

        StatusChave getStatus(){
            return status;
        }

        Ambiente *getAmbiente(){
            return ambiente;
        }

        //métodos setters
        void setId(long valor){
            this->id = valor;
            return;
        }

        void setCodigo(string valor){
            this->codigo = valor;
            return;
        }

        void setStatusCodigo(StatusChave status_valor){
            this->status = status_valor;
            return;
        }

        void setAmbiente(Ambiente *valor_ambiente){
            this->ambiente = valor_ambiente;
        }
        
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

//getter e setter finalizado
class Ambiente final{
    //não temos métodos em ambiente
    private:
        long id;
        string nome;
        string bloco;
        string descricao;
    public:

        //Finalizar dps
        Ambiente(){

        }

        ~Ambiente(){
            //ambiente nn tem ponteiro, ent nn precisa desalocar

        }

        //Métodos setters
        void setId(long valor){
            this->id = valor;
            return;
        }

        void setNome(string valor_nome){
            this->nome = valor_nome;
            return;
        }

        void setBloco(string valor_bloco){
            this->bloco = valor_bloco;
            return;
        }

        void setDescricao(string valor_descricao){
            this->descricao = valor_descricao;
            return;
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


};

//métodos getters e setter quase finalizados, falta ver a sintaxe da chrono
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

        //finalizar dps -> DESTRUTOR VAI TER Q DESALOCAR PONTEIRO
        Emprestimo(){


        }

        ~Emprestimo(){


        }

        //Métodos getters
        long getId(){
            return id;
        }

        Usuario *getUsuario(){
            return usuario;
        }

        Chave *getChave(){
            return chave;
        }

        //-> getters do chrono (ver a sintaxe no docs da chrono.h cpp)

        string getJustificativa(){
            return justificativa;
        }



        //Métodos setters
        void setId(long valor){
            this->id = valor;
            return;
        }

        void setUsuario(Usuario *usuario_valor){
            this->usuario = usuario_valor;
            return;
        }

        void setChave(Chave *chave_valor){
            this->chave = chave_valor;
            return;
        }

        //setter da chrono -> tenho q ver a sintaxe no docs

        void setJustificativa(string valor){
            this->justificativa = valor;
            return;
        }

        void encerrarEmprestimo(){

        }

        bool verificarAtraso(){


        }


};



int main(){

    //inicializa o vetor
    //[isso não pode ficar aqui -> Ir pra main ou ir pra global?]
    vector <long> registros = incializaVetorRegistros(); // dps tenho q garatir que isso rode apenas 1 vez e dps nunca mais ao longo do código em execução,
    /* -> Primeira posição do vetor Referente á Usuarios
       -> Segunda posição do vetor Referente á Emprestimo
       -> Terceira posição do vetor Referente á Chave
       -> Ambiente posição do vetor Referente á Ambiente
    */



    return 0;
    
}
