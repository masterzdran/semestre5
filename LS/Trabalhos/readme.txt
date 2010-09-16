Benfica - O maior
SLB
Estrutura do repositório 
====================================================================================

http://code.deetc.e.ipl.pt/ls/0910v/svn/<IDENTIFICADOR_DO_GRUPO>/ 
   |    
   +-- trunk ...................................	Ramo principal de desenvolvimento
   |   |
   |   +-- build.xml ...........................	Ficheiro de build do ApacheAnt
   |   |
   |   +-- src .................................	Directoria que inclui o código fonte 
   |   |   |	                                    (produzido pela equipa de desenvolvimento)
   |   |   |
   |   |   +-- main	                                Ficheiros fonte com as funcionalidades implementadas
   |   |   |   |
   |   |   |   +-- java	                            Ficheiros Java, organizados por package
   |   |   |   |   +-- <package-root>
   |   |   |   +-- sql	                            Scripts SQL, organizados por etapa e/ou package
   |   |   |   |   +-- <script>.sql
   |   |   |   +-- apps	                            Scripts de lançamento de aplicações
   |   |   |       +-- <app1>.app
   |   |   |       +-- <app2>.app
   |   |   | 
   |   |   +-- test	                                Ficheiros fonte com os testes unitários
   |   |   |   |
   |   |   |   +-- <estrutura equivalente a /trunk/main/java/>
   |   |   |
   |   |   +-- docs ............................	Ficheiros com documentação de projecto
   |   |
   |   +-- vendor ..............................	Ficheiros produzidos por entidades externas...
   |       +-- main	                                   ... necessários ao funcionamento das aplicações
   |       |   +-- lib	
   |       |       +-- sqljdbc4.jar	                Exemplo de library do driver JDBC para SQLServer
   |       +-- test	                                   ... necessários à execução dos testes unitários
   |           +-- lib	
   |               +-- junit-4-8.1.jar	            Exemplo de library do jUnit 4.8.1 (apenas usada nos testes)
   |
   +-- tags ....................................	"Fotografia" do estado do projecto num dado instante
   |   |
   |   +-- stage-0	Conteúdo de /trunk relativo à entrega da etapa 0
   |   +-- stage-1	Conteúdo de /trunk relativo à entrega da etapa 1
   |   
   +-- branches ................................	Ramos alternativos ao desenvolvimento
	                                                Devem ter a mesma estrutura que /trunk

    
Nota: 	
A directoria /target apenas deve existir na máquina de desenvolvimento. 
Devem usar o comando SVN Ignore para evitar que esta directoria seja listada na interface gráfica do comando SVN Commit.