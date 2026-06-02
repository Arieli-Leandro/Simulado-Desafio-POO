
#Classe Usuário finalizada
class Usuario:
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
    
        






if __name__ == "__main__":
    pass
