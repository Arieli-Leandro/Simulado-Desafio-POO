import datetime
from datetime import timedelta
from abc import ABC, abstractmethod
from enum import Enum

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
    
    def cadastrarChave(self):
        #Chama o sistema Heimdall
        pass

    def cadastrarUsuario(self):
        #Chama o sistema Heimdall
        pass

    def gerarRelatorio(self):
        #Pega o vetor de registros e cria um arquivo com ele
        pass

#Classe Emprestimo
class Emprestimo:
    def __init__(self, id_u, usuario, chave_u, justificativa):
        self._id = id_u
        self._usuario = usuario
        self._chave = chave_u

        self._dataRetirada = datetime.time()
        horas_usuario = usuario.prazoHoras()
        self._dataPrevista =  self._dataPrevista + timedelta(hours=horas_usuario)
        self._dataDevolucao

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
        self._dataDevolucao = datetime.time()

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
        if isinstance(status, StatusChave):
            raise TypeError("Tipo de chave inválida!")
        
        self._status = status

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
        pass

if __name__ == "__main__":
    pass
