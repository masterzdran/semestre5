Benfica - O maior
SLB
Estrutura do reposit�rio 
====================================================================================

http://code.deetc.e.ipl.pt/ls/0910v/svn/<IDENTIFICADOR_DO_GRUPO>/ 
   |    
   +-- trunk ...................................	Ramo principal de desenvolvimento
   |   |
   |   +-- build.xml ...........................	Ficheiro de build do ApacheAnt
   |   |
   |   +-- src .................................	Directoria que inclui o c�digo fonte 
   |   |   |	                                    (produzido pela equipa de desenvolvimento)
   |   |   |
   |   |   +-- main	                                Ficheiros fonte com as funcionalidades implementadas
   |   |   |   |
   |   |   |   +-- java	                            Ficheiros Java, organizados por package
   |   |   |   |   +-- <package-root>
   |   |   |   +-- sql	                            Scripts SQL, organizados por etapa e/ou package
   |   |   |   |   +-- <script>.sql
   |   |   |   +-- apps	                            Scripts de lan�amento de aplica��es
   |   |   |       +-- <app1>.app
   |   |   |       +-- <app2>.app
   |   |   | 
   |   |   +-- test	                                Ficheiros fonte com os testes unit�rios
   |   |   |   |
   |   |   |   +-- <estrutura equivalente a /trunk/main/java/>
   |   |   |
   |   |   +-- docs ............................	Ficheiros com documenta��o de projecto
   |   |
   |   +-- vendor ..............................	Ficheiros produzidos por entidades externas...
   |       +-- main	                                   ... necess�rios ao funcionamento das aplica��es
   |       |   +-- lib	
   |       |       +-- sqljdbc4.jar	                Exemplo de library do driver JDBC para SQLServer
   |       +-- test	                                   ... necess�rios � execu��o dos testes unit�rios
   |           +-- lib	
   |               +-- junit-4-8.1.jar	            Exemplo de library do jUnit 4.8.1 (apenas usada nos testes)
   |
   +-- tags ....................................	"Fotografia" do estado do projecto num dado instante
   |   |
   |   +-- stage-0	Conte�do de /trunk relativo � entrega da etapa 0
   |   +-- stage-1	Conte�do de /trunk relativo � entrega da etapa 1
   |   
   +-- branches ................................	Ramos alternativos ao desenvolvimento
	                                                Devem ter a mesma estrutura que /trunk

    
Nota: 	
A directoria /target apenas deve existir na m�quina de desenvolvimento. 
Devem usar o comando SVN Ignore para evitar que esta directoria seja listada na interface gr�fica do comando SVN Commit.