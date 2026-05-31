#include <iostream>
#include <string>
#include <chrono>
#include <vector>
using namespace std;

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

        //o destrutor tem que ser virtual pq temos herança
        virtual ~Usuario(){

            cout << "Usuario:" << nome << "deletado" << endl;

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

            cout << "Professor:" << "deletado" << endl;

        }

        //unico método é o override de podeRetirar()
        bool podeRetirarChave() override {
            return true;
        }

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

            cout << "Tecnico: " << "deletado" << endl;

        }

        //unico método é o override de podeRetirar()
        int prazoHoras() override {
            return 8;
        }

        bool podeRetirarChave() override {
            return true;
        }


};

//getters e setter vão vir por padrão na classe Mãe
class Administrador: public Usuario{

    public:

        //finalizar dps -> Chamar o super
        Administrador(){


        }

        ~Administrador(){

            cout << "Administrador: " << "deletado" << endl;

        }

        bool podeRetirar(){

        }

        void cadastrarChave(){

        }

        void cadastrarUser(){

        }

        bool podeRetirarChave() override {
            return true;
        }

};

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
            cout << "Ambiente: " << nome << "deletado" << endl;
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
    public:

        Chave(){


        }

        ~Chave(){
            cout << "Chave: " << codigo << "deletada" << endl;
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

    return 0;
    
}
