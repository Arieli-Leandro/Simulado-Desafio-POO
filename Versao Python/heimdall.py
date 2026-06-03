import datetime
from datetime import timedelta
from abc import ABC, abstractmethod
from enum import Enum

# =- Excessões -=

class ExcessaoUsuarioInativo(Exception):

    def __str__(self):
        return f"Erro: O Usuário está inativo!"

class ExcesssaoChaveIndisponivel(Exception):

    def __str__(self):
        return f"Erro: A chave está indisponível para o emprestimo!"

class ExcessaoUsuarioNaoPodeRetirarChave(Exception):

    def __str__(self):
        return f"Erro: Usuário não tem permissão para retirar a chave!"

class ExcessaoEmprestimoInvalido(Exception):

    def __str__(self):
        return f"Erro: Emprestimo inválido!"
    
class ExcessaoCadastroUsuarioExistente(Exception):

    def __str__(self):
        return f"O Usuário já está cadastrado!"
    
class ExcessaoUsuarioNaoExiste(Exception):

    def __str__(self):
        return f"O Usuário não existe!"

class ExcessaoCadastroChaveExistente(Exception):

    def __str__(self):
        return f"A chave já foi cadastrada anteriormente!"

class ExcessaoChaveNaoExiste(Exception):

    def __str__(self):
        return f"A chave não existe!"
    
class ExcessaoCadastroAmbienteExiste(Exception):

    def __str__(self):
        return f"O ambiente já foi cadastrado anteriormente!"
    
class ExcessaoAmbienteNaoExiste(Exception):

    def __str__(self):
        return f"O ambiente não existe!"
    
class ExcessaoDevolucaoNaoEncontrada(Exception):

    def __str__(self):
        return f"Registro de Emprestimo não encontrado, não foi possível realizar devolução!"
    
class ExcessaoStatusInvalido(Exception):

    def __str__(self):
        return f"O status recebido é inválido!"


# =-- Classes --=

#Classe Usuário finalizada
class Usuario(ABC):
    def __init__(self, id_u, nome_u, matricula_u, email_u, ativo_u):

        self._id = id_u
        self._nome = nome_u
        self._matricula = matricula_u
        self._email = email_u
        self._ativo = ativo_u

    #Métodos getters
    def getId(self):

        return self._id
    
    def getNome(self):

        return self._nome
    
    def getMatricula(self):

        return self._matricula
    
    def getEmail(self):

        return self._email
    
    def getAtivo(self):

        return self._ativo

    #Métodos setters
    def setId(self, id_u):

        self._id = id_u
        return 

    def setNome(self, nome):

        self._nome = nome
        return
    
    def setMatricula(self, matricula):

        self._matricula = matricula
        return
    
    def setEmail(self, email):

        self._email = email
        return
    
    def setAtivo(self, ativo):

        self._ativo = ativo
        return

    #Métodos específicos da classe
    def autenticar(self):

        retorno = False

        if(self._ativo == True):
            retorno = True
        
        return retorno
    
    def podeRetirar(self):

        return False
    
    @abstractmethod
    def prazoHoras(self):

        return 0
        
    
        
#Classe Professor -> Herda de Usuário
class Professor(Usuario):
    def __init__(self, id_u, nome_u, matricula_u, email_u, ativo_u):

        super().__init__(id_u, nome_u, matricula_u, email_u, ativo_u)

    def podeRetirar(self):

        return True
    
    def prazoHoras(self):

        return 24

#Classe Tecnico -> Herda de Usuário
class Tecnico(Usuario):
    def __init__(self, id_u, nome_u, matricula_u, email_u, ativo_u):

        super().__init__(id_u, nome_u, matricula_u, email_u, ativo_u)

    def podeRetirar(self):

        return True
    
    def prazoHoras(self):

        return 8
    
#Classe Administrador -> Herda de Usuário mas ela tem métodos adicionais como (Cadastrar Chave e CadastrarUser)
# O administrador tbm gera relatório
class Administrador(Usuario):
    def __init__(self, id_u, nome_u, matricula_u, email_u, ativo_u):

        super().__init__(id_u, nome_u, matricula_u, email_u, ativo_u)

    def podeRetirar(self):
        return True
    
    def prazoHoras(self):
        return 12
    
    def cadastrarChave(self, chave):
        #Chama o sistema Heimdall
        GerenciadorDeSistemaHeimdall.cadastrarChave(chave)
        return
        

    def cadastrarUsuario(self, usuario):
        #Chama o sistema Heimdall
        GerenciadorDeSistemaHeimdall.cadastrarUsuario(usuario)
        return

    def gerarRelatorio(self):
        #Pega o vetor de registros e cria um arquivo com ele
        lista_registros = GerenciadorDeSistemaHeimdall._retornaVetorRegistros()

        with open("Relatorio.txt", "w", encoding="utf-8") as arq:
            for i in lista_registros:
                arq.write(i)

        return

#Classe Emprestimo
class Emprestimo:
    def __init__(self, id_u, usuario, chave_u, justificativa):

        self._id = id_u
        self._usuario = usuario
        self._chave = chave_u

        self._dataRetirada = datetime.datetime.now()
        horas_usuario = usuario.prazoHoras()
        self._dataPrevista =  self._dataRetirada + timedelta(hours=horas_usuario)
        self._dataDevolucao = None

        self._justificativa = justificativa

    #Métodos getters
    def getId(self):

        return self._id
    
    def getUsuario(self):

        return self._usuario
    
    def getChave(self):

        return self._chave
    
    def getDataRetirada(self):

        return self._dataRetirada
    
    def getDataPrevista(self):

        return self._dataPrevista
    
    def getDataDevolucao(self):

        return self._dataDevolucao
    
    def getJustificativa(self):

        return self._justificativa

    #Métodos setters
    def setId(self, id_u):

        self.id = id_u
        return
    
    def setUsuario(self, usuario):

        self._usuario = usuario
        return
    
    def setChave(self, chave):

        self._chave = chave
        return
    
    def setJustificativa(self, justificativa):

        self._justificativa = justificativa
        return

    #Métodos da classe
    def encerrarEmprestimo(self):

        self._dataDevolucao = datetime.datetime.now()

        return

    def verificaAtraso(self):

        retorno = False

        if(self._dataDevolucao > self._dataPrevista):
            print("A chave foi devolvida com atraso!")
            retorno = True

        return retorno

class StatusChave(Enum):

    DISPONIVEL = 1
    EMPRESTADA = 2
    EM_ATRASO = 3


class Chave:
    def __init__(self, id_u, cod_u, ambiente):

        self._id = id_u
        self._codigo = cod_u
        self._ambiente = ambiente
        self._status = StatusChave.DISPONIVEL

    #Métodos getters
    def getId(self):

        return self._id
    
    def getCodigo(self):

        return self._codigo
    
    def getAmbiente(self):

        return self._ambiente
    
    def getStatus(self):

        return self._status

    #Métodos setters
    def setId(self, id_u):

        self._id = id_u
        return
    
    def setCodigo(self, codigo):

        self._codigo = codigo
        return
    
    def setAmbiente(self, ambiente):

        self._ambiente = ambiente
        return
    
    def setStatus(self, status):
        #A ideia é lançar um erro aqui se não foi do tipo StatusChave
        #Depois fazer uma classe de erro para chave inválida      

        if((status != StatusChave.DISPONIVEL) and (status != StatusChave.EMPRESTADA) and (status != StatusChave.EM_ATRASO)):
            raise ExcessaoStatusInvalido()
        else:
            self._status = status

        return

    #Métodos da Classe
    def verificaChaveDisponivel(self, chave):

        retorno = False

        if(chave._status == StatusChave.DISPONIVEL):
            retorno = True

        return retorno

class Ambiente:

    def __init__(self, id_u, nome, bloco_u, desc):

        self._id = id_u
        self._nome = nome
        self._bloco = bloco_u
        self._descricao = desc

    #Métodos getters
    def getId(self):

        return self._id
    
    def getNome(self):

        return self._nome
    
    def getBloco(self):

        return self._bloco
    
    def getDescricao(self):

        return self._descricao

    #Métodos setters
    def setId(self, id_u):

        self._id = id_u
        return
    
    def setNome(self, nome):

        self._nome = nome
        return
    
    def setBloco(self, bloco):

        self._bloco = bloco
        return
    
    def setDescricao(self, desc):

        self._descricao = desc
        return
    
    #Não tem métodos, a não ser q eu queira fazer um exibe_Ambiente


class GerenciadorDeSistemaHeimdall:

    def __init__(self):

        self._lista_usuarios = []
        self._lista_chaves = []
        self._lista_emprestimos = []
        self._lista_ambientes = []

    def _verificaSeUsuarioExiste(self, usuario):

        retorno = False

        for i in self._lista_usuarios:
            if(i == usuario):
                retorno = True
                break

        return retorno
    
    def _verificaSeChaveExiste(self, chave):
        
        retorno = False

        for i in self._lista_chaves:
            if(i == chave):
                retorno = True
                break

        return retorno

    def _verificaSeAmbienteExiste(self, ambiente):
        
        retorno = False

        for i in self._lista_ambientes:
            if(i == ambiente):
                retorno = True
                break

        return retorno

    def cadastrarUsuario(self, usuario):

        if(self._verificaSeUsuarioExiste(usuario) == False):
            self._lista_usuarios.append(usuario)
        else:
            raise ExcessaoCadastroUsuarioExistente()
        return

    def deletarUsuario(self, usuario):

        if(self._verificaSeUsuarioExiste(usuario) == True):
            #encontra o indide, tira da lista e depois deleta o obj
            for indice, x in enumerate(self._lista_usuarios):
                if(x == usuario):
                    self._lista_usuarios.pop(indice)
                    del usuario
                    break
        else:
           raise ExcessaoUsuarioNaoExiste()

    def cadastrarChave(self, chave):

        if(self._verificaSeChaveExiste(chave) == False):
            self._lista_chaves.append(chave)
        else:
            raise ExcessaoCadastroChaveExistente()

        return

    def deletarChave(self, chave):

        if(self._verificaSeChaveExiste(chave) == True):

            for indice, x in enumerate(self._lista_chaves):
                if(x == chave):
                    self._lista_chaves.pop(indice)
                    del chave
                    break
        else:
            raise ExcessaoChaveNaoExiste()

        return

    def cadastrarAmbiente(self, ambiente):

        if(self._verificaSeAmbienteExiste(ambiente) == False):
            self._lista_ambientes.append(ambiente)
        else:
            raise ExcessaoCadastroAmbienteExiste()

        return
        

    #Transformar o else em Exception
    def deletarAmbiente(self, ambiente):

        if(self._verificaSeAmbienteExiste(ambiente) == True):

            for indice, x in enumerate(self._lista_ambientes):
                if(x == ambiente):
                    self._lista_ambientes.pop(indice)
                    del ambiente
                    break
        else:
            raise ExcessaoAmbienteNaoExiste()

        return

    #Transformar o else em Exception
    def _verificaUsuarioPodeRetirar(self, usuario):

        retorno = False

        if(usuario.podeRetirar() == True):
            retorno = True
        else:
            raise ExcessaoUsuarioNaoPodeRetirarChave()

        return retorno

    #Transformar o else em Exception
    def _verificaChaveDisponivel(self, chave):
        
        retorno = False

        if(chave.getStatus() == StatusChave.DISPONIVEL):
            retorno = True
        else:
            raise ExcesssaoChaveIndisponivel()

        return retorno
    
    #Transformar o else em Exception
    def _verificaUsuarioAtivo(self, usuario):
        
        retorno = False

        if(usuario.getAtivo() == True):
            retorno = True
        else:
            raise ExcessaoUsuarioInativo()

        return retorno

    #Transformar o else em Exception
    def cadastraEmprestimo(self, usuario, chave, justificativa):

        #Preciso verificar se o usuário está ativo
        #Preciso verificar se o usuário podeRetirar
        #Preciso verificar se a chave está disponível

        #Preciso calcular o indice que vai ser o id
        #Preciso criar o objeto do tipo Emprestimo
        #Preciso dar append na lista de registro
        #Preciso acessar e mudar o estado da chave

        if((self._verificaUsuarioAtivo(usuario) == True) and (self._verificaUsuarioPodeRetirar(usuario) == True) and (self._verificaChaveDisponivel(chave) == True)):
            
            indice_id = len(self._lista_emprestimos)
            obj = Emprestimo(indice_id, usuario,chave, justificativa)
            
            #Append na lista de registros
            self._lista_emprestimos.append(obj)
        
            #Acessando e mudando o estado da chave
            chave.setStatus(StatusChave.EMPRESTADA)
        else:
            raise ExcessaoEmprestimoInvalido()

        return
        

    def registraDevolucao(self, chave):

        #Vai ser capaz de informar se existe a chave no registro para "devolver"
        verificador = -1
        
        #-> Muda o estado da chave para disponivel novamente
        for emprestimo in self._lista_emprestimos:
            #Significa que achei a chave referente
            if(emprestimo.getChave() == chave):
                #Encerro o emprestimo dessa chave X
                emprestimo.encerrarEmprestimo()

                #Troca o estado 
                verificador = 1

                #Mudo o estado da chave X para disponivel
                chave.setStatus(StatusChave.DISPONIVEL)
                break

        if(verificador == -1):
            raise ExcessaoDevolucaoNaoEncontrada()

        return

    def exibeChavesDisponiveis(self):
        
        for chave in self._lista_chaves:
            if(chave.getStatus() == StatusChave.DISPONIVEL):
                print(f"|Chave Disponível: {chave.getCodigo()}|")

        return

    def exibeChavesEmprestadas(self):
        
        for chave in self._lista_chaves:
            if(chave.getStatus() == StatusChave.EMPRESTADA):
                print(f"|Chave Emprestada: {chave.getCodigo()}|")

        return

    def exibeChavesEmAtraso(self):
        
        for chave in self._lista_chaves:
            if(chave.getStatus() == StatusChave.EM_ATRASO):
                print(f"|Chave Em Atraso: {chave.getCodigo()}|")

        return

    #Transformar o else em Exception
    def exibeTodasChaves(self):
        
        for i in self._lista_chaves:
            print(i)

        return
    
    #A ideia é que essa função tenha conexão com o gerarRelatório do Adm
    def _retornaVetorRegistros(self):
        return self._lista_emprestimos

if __name__ == "__main__":

    try:
        sistema = GerenciadorDeSistemaHeimdall()

        laboratorio = Ambiente(1,"Laboratório de Informática","Bloco A","Laboratório com computadores")

        sistema.cadastrarAmbiente(laboratorio)

        chave_lab = Chave(1,"LAB-001",laboratorio)

        sistema.cadastrarChave(chave_lab)

        professor = Professor(1,"Carlos Silva","12345","carlos@ifpr.edu.br",True)

        tecnico = Tecnico(2,"Maria Souza","54321","maria@ifpr.edu.br",True)

        admin = Administrador(3,"João Admin","99999","admin@ifpr.edu.br",True)

        sistema.cadastrarUsuario(professor)
        sistema.cadastrarUsuario(tecnico)
        sistema.cadastrarUsuario(admin)

        sistema.exibeChavesDisponiveis()

        sistema.cadastraEmprestimo(professor,chave_lab,"Aula de Programação Orientada a Objetos")

        print("Empréstimo realizado com sucesso!")

        sistema.exibeChavesEmprestadas()

        sistema.registraDevolucao(chave_lab)

        print("Devolução realizada com sucesso!")

        sistema.exibeChavesDisponiveis()
    except Exception as erro:
        print(erro)
