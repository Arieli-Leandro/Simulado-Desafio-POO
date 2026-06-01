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

        //finalizar o construtor e destrutor dps
        Usuario(long id_user, string nome_user, int matricula_user, string email_user, bool ativo_user){
            this->id = id_user;
            this->nome = nome_user;
            this->matricula = matricula_user;
            this->email = email_user;
            this->ativo = ativo_user;
        }

        //o destrutor tem que ser virtual pq temos herança
        // não tem nada para desalocar
        virtual ~Usuario(){}

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

        bool virtual podeRetirar() = 0;

        //Esse método virtual é pq professor e tecnico tem prazos diferentes para devolver as chaves
        int virtual prazoHoras() = 0;


};


//getters e setters vão vir por padrão no classe Mãe
class Professor: public Usuario{

    public:

        Professor(long id, string nome, int matricula, string email, bool ativo):Usuario(id,nome,matricula,email,ativo){}

        ~Professor(){
            cout << "Professor:" << "deletado" << endl;
        }

        //unico método é o override de podeRetirar()
        bool podeRetirar() override {
            return true;
        }

        int prazoHoras() override {
            return 24;
        }


};


//getters e setters vão vir por padrão na classe Mãe
class Tecnico: public Usuario{

    public:

        Tecnico(long id, string nome, int matricula, string email, bool ativo):Usuario(id, nome,matricula, email, ativo){}

        //não tem nada para desalocar
        ~Tecnico(){}

        //unico método é o override de podeRetirar()
        int prazoHoras() override {
            return 8;
        }

        bool podeRetirar() override {
            return true;
        }


};

//getters e setter vão vir por padrão na classe Mãe
class Administrador: public Usuario{

    public:

        Administrador(long id, string nome, int matricula, string email, bool ativo):Usuario(id,nome,matricula,email,ativo){}

        //não tem nada para desalocar
        ~Administrador(){}

        bool podeRetirar() override {
            return true;
        }

};

//Classe finalizada
class Ambiente final{
    //não temos métodos em ambiente
    private:
        long id;
        string nome;
        string bloco;
        string descricao;
    public:
        Ambiente(long id_user, string nome_user, string bloco_user, string descricao_user){
            this->id = id_user;
            this->nome = nome_user;
            this->bloco = bloco_user;
            this->descricao = descricao_user;
        }

        //não tem nada para desalocar
        ~Ambiente(){}

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

        //só para exibir o Ambiente
        void exibeAmbiente(){
            cout << "|ID: " << id << "|Nome: " << nome << "|Bloco: " << bloco << "|Descricao: " << descricao << "|" << endl;
            return;
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

        Chave(long id_u, string cod_u, Ambiente *ambiente_u){

            //por que no construtor nn tem status? Porque quando criarmos a chave, ela tem que estar disponível
            this->id = id_u;
            this->codigo = cod_u;
            this->ambiente = ambiente_u;

            status = DISPONIVEL;

        }

        ~Chave(){}

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

        Emprestimo(long id_user, Usuario *user, Chave *chave_u, string justi){
            this->id = id_user;
            this->usuario = user;
            this->chave = chave_u;
            this->justificativa = justi;

            //dataRetirada / dataPrevista / dataDevolucao nn seta eles no construtor, a gnt só inicializa aqui no construtor e a data da devolução vai ser por um método
            dataRetirada = chrono::system_clock::now();

            //a data prevista é a data da retirada + o tempo que o usuário tem
            //Tem que pegar o prazo e transformar para horas com o chrono::hours
            dataPrevista = dataRetirada + chrono::hours(usuario->prazoHoras());

        }

        ~Emprestimo(){
            //Não vamos desalocar nada pq o emprestimo nn é o dono de usuário e nem de chave
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

        void setJustificativa(string valor){
            this->justificativa = valor;
            return;
        }

        void encerrarEmprestimo(){

            dataDevolucao = chrono::system_clock::now();

        }

        bool verificarAtraso(){

            bool retorno = false;

            if(dataDevolucao > dataPrevista){
                retorno = true;
                chave->setStatusCodigo(EM_ATRASO);
                cout << "Devolucao atrasada!" << endl;
            }

            return retorno;

        }


};

class ExcecaoChaveIndisponivel: public exception{

    public:
        const char * what() const noexcept override{
            return "A chave esta indisponivel!";
        }
};

class ExcecaoInativo: public exception{

    public:
        const char *what() const noexcept override{
            return "O usuario nao esta ativo!";
        }
};

class ExcecaoUsuarioNaoPodeRetirar: public exception{
    public:
        const char *what() const noexcept override{
            return "O usuario nao tem permissao para retirar uma chave!";
        }
};


//Vai ter um método que vai controlar tudo isso
class GerenciadorDeChaves{

    private:
        vector<Usuario*> usuarios;
        vector<Chave*> chaves;
        vector<Emprestimo*> emprestimos;
        vector<Ambiente*> ambientes;

    public:
        //precisamos cadastrar o usuário
        void cadastraUsuario(Usuario *user){

            usuarios.push_back(user);
            return;

        }

        void cadastraChave(Chave *chave_u){

            chaves.push_back(chave_u);
            return;

        }

        void cadastrarAmbiente(Ambiente *amb){
            ambientes.push_back(amb);
            return;
        }

        //A ideia é transformar isso em uma Exception
        bool verificaUsuarioPodeRetirar(Usuario *user){
            bool retorno = false;

            if(user->podeRetirar() == true){
                retorno = true;
            }else{
                throw ExcecaoUsuarioNaoPodeRetirar();
            }

            return retorno;
        }

        //A ideia é transformar isso em uma Exception
        bool verificaUsuarioAtivo(Usuario *user){
            bool retorno = false;

            if(user->getAtivo() == true){
                retorno = true;
            }else{
                throw ExcecaoInativo();
            }
            
            return retorno;
        }

        //a ideia é depois transformar isso em uma Exception
        bool verificarChaveDisponivel(Chave *chave){
            bool retorno = false;

            if(chave->getStatus() == DISPONIVEL){
                retorno = true;
            }else{
                throw ExcecaoChaveIndisponivel();
            }

            return retorno;
        }

        void CadastraEmprestimo(Usuario *user, Chave *chave, string justificativa){

            if((verificaUsuarioAtivo(user) == true) && (verificarChaveDisponivel(chave) == true) && (verificaUsuarioAtivo(user) == true)){

                //O que eu preciso fazer?
                // Preciso realizar um emprestimo usando a classe emprestimo, e preciso colocar esse registro no meu vetor de emprestimos
                // e preciso atualizar o status da chave

                //1) Realizando o emprestimo
                //emprestimos.size() + 1 é o id do nosso emprestimo, pq ai ele se refere ao registro do vetor de emprestimos
                Emprestimo *emp = new Emprestimo((emprestimos.size() +1), user, chave, justificativa);

                //02) Colocando o registro de emprestimo no vetor de emprestimo
                emprestimos.push_back(emp);

                //03) Atualizando o Status da chave
                chave->setStatusCodigo(EMPRESTADA);
                
            }

        }

        void registraDevolucao(Chave *chave){

            //O que eu preciso fazer?
            //Encontrar a chave referente desse emprestimo
            // remover do vetor
            // colocar a chave em disponivel
            // não podemos dar um free no ponteiro pq é pra ficar registrado de quando o usuário x pegou a chave y e devolveu hora z

            for(int i = 0; i<emprestimos.size(); i++){
                if(emprestimos[i]->getChave() == chave){

                    emprestimos[i]->encerrarEmprestimo();
                    chave->setStatusCodigo(DISPONIVEL);

                    break;

                }
            }

            return;
            
        }

        void exibeChaveDisponivel(){

            cout << "Chaves Disponiveis: " << endl;

            for(int i = 0; i<chaves.size(); i++){
                if(chaves[i]->getStatus() == DISPONIVEL){
                    cout << chaves[i]->getCodigo() << endl;
                }
            }

            return;

        }

        void exibeChaveEmprestada(){

            cout << "Chaves Emprestadas: " << endl;

            for(int i = 0; i<chaves.size(); i++){
                if(chaves[i]->getStatus() == EMPRESTADA){
                    cout << chaves[i]->getCodigo() << endl;
                }
            }

            return;

        }

        void exibeChaveAtrasada(){

            cout << "Chaves Atrasadas: " << endl;

            for(int i = 0; i<chaves.size(); i++){
                if(chaves[i]->getStatus() == EM_ATRASO){
                    cout << chaves[i]->getCodigo() << endl;
                }
            }

            return;

        }
};


int main(){

    //depois eu preciso fazer a main para testar o código todo
    // transformar as funções em excessões

    //ver + vídeos de poo e fazer + exercícios e fazer a versão dele em python

    // 1a coisa) Quem vai controlar tudo?
    // Quem vai controlar tudo é a classe gerenciadora, então vamos criar um objeto tipo Gerenciador
    GerenciadorDeChaves sistema;

    //2a coisa) Para fazer o emprestimo, precisa existir o ambiente (laboratório)
    //Então vamos criar os ambientes

    //Criei somente o ponteiro 
    Ambiente* obj1 = new Ambiente(1, "Lab 01", "N", "Laboratorio Padrao 01");
    Ambiente* obj2 = new Ambiente(2, "Lab 02", "N", "Laboratorio Padrao 02");
    Ambiente* obj3 = new Ambiente(3, "Lab 03", "N", "Laboratorio Padrao 03");
    Ambiente* obj4 = new Ambiente(4, "Lab 04", "N", "Laboratorio Padrao 04");
    Ambiente* obj5 = new Ambiente(5, "Lab 05", "N", "Laboratorio Padrao 05");
    Ambiente* obj6 = new Ambiente(6, "Lab 06", "N", "Laboratorio Padrao 06");

    //Como só criei o ponteiro, agora preciso associar ele ao sistema
    sistema.cadastrarAmbiente(obj1);
    sistema.cadastrarAmbiente(obj2);
    sistema.cadastrarAmbiente(obj3);
    sistema.cadastrarAmbiente(obj4);
    sistema.cadastrarAmbiente(obj5);
    sistema.cadastrarAmbiente(obj6);

    //3a coisa) Já tenho um ambiente, pela regra de negócio 1 ambiente está associado a 1 chave
    //Então agora eu preciso criar a chave que linke o ambiente com a chave

    Chave * chave_obj1 = new Chave(1, "Lab01", obj1);
    Chave * chave_obj2 = new Chave(2, "Lab02", obj2);
    Chave * chave_obj3 = new Chave(3, "Lab03", obj3);
    Chave * chave_obj4 = new Chave(4, "Lab04", obj4);
    Chave * chave_obj5 = new Chave(5, "Lab05", obj5);
    Chave * chave_obj6 = new Chave(6, "Lab06", obj6);

    //dnv como só criei o ponteiro, tenho que mandar para o sistema
    sistema.cadastraChave(chave_obj1);
    sistema.cadastraChave(chave_obj2);
    sistema.cadastraChave(chave_obj3);
    sistema.cadastraChave(chave_obj4);
    sistema.cadastraChave(chave_obj5);
    sistema.cadastraChave(chave_obj6);

    //4a coisa) Já tenho ambiente e chave, mas ainda preciso de professores
    //Então agr eu preciso criar o ponteiro de um obj do tipo Professor, e dps mandar para o gerenciador do sistema
    Usuario* prof1 = new Professor(1, "Prof1", 1, "email.com", true);
    Usuario* prof2 = new Professor(2, "Prof2", 2, "email.com", true);
    Usuario* prof3 = new Professor(3, "Prof3", 3, "email.com", true);
    Usuario* prof4 = new Professor(4, "Prof4", 4, "email.com", true);
    Usuario* prof5 = new Professor(5, "Prof5", 5, "email.com", false);

    sistema.cadastraUsuario(prof1);

    try{

        sistema.CadastraEmprestimo(prof1, chave_obj1, "Aula tal");
        cout << "Emprestimo realizado!" << endl;


    }catch(exception& e){
        cout << e.what() << endl;
    }

    sistema.exibeChaveEmprestada();
    sistema.exibeChaveDisponivel();

    sistema.registraDevolucao(chave_obj1);

    return 0;
    
}
