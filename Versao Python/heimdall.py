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
        pass

    def cadastrarUsuario(self):
        pass

    def gerarRelatorio(self):
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



    def encerrarEmprestimo(self):
        pass

    def verificaAtraso(self):
        pass

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

    #Não tem métodos, a não ser q eu queira fazer um exibe_Ambiente

if __name__ == "__main__":
    pass
