
# CI 218 - Sistemas de Banco de Dados
## Escalonamento de transações
2022-1
### Objetivo:
Implementar dois algoritmos de detecção de conflitos de escalonamento de transações concorrentes. Estes algoritmos permitem o aluno compreender gargalos no processamento de transações.
### 
### Algoritmo de teste de seriabilidade quanto ao conflito:
 

- Crie um nó para cada T do escalonamento S
- Aresta T<sub>i</sub> -&gt; T<sub>j</sub> para cada r(x) em T<sub>j</sub> depois de w(x) em T<sub>i</sub>
- Aresta T<sub>i</sub> -&gt; T<sub>j</sub> para cada w(x) em T<sub>j</sub> depois de r(x) em T<sub>i</sub>
- Aresta T<sub>i</sub> -&gt; T<sub>j</sub> para cada w(x) em T<sub>j</sub> depois de w(x) em T<sub>i</sub>
- S é serial se não existe ciclo no grafo 


### Algoritmo de visão equivalente

Dois agendamentos S e S' são ditos visão equivalentes, se atenderem as seguintes condições:


- O mesmo conjunto de transações e operações participam em S e S'
- Para cada r(x) de T<sub>i</sub>, se o valor de x lido ja foi escrito por w(x) de T<sub>j</sub>, ou seja, houve W(x) antes de R(x) em transações distintas, o mesmo deve permanecer para r(x) de T<sub>i</sub> em S'
- Se o operador w(y) em T<sub>k</sub> é a ultima escrita de y em S, então w(y) em T<sub>k</sub> deve ser a última escrita em S'


Por exemplo (mais exemplos serão vistos em sala):

<table class="plain" border="1">
<tbody>
<tr>
<th>
Escalonamento S1
<p>T1:r(x), T2:r(x), T2:w(x), T1:w(x)</p>
<img src="https://www.inf.ufpr.br/eduardo/fig/S1.jpg" height="63" width="129"></p>
</th><th>
Escalonamento S2
<p>T3:r(x), T3:r(y), T4:r(x), T3:w(y)</p>
<img src="https://www.inf.ufpr.br/eduardo/fig/S2.jpg" height="49" width="147"></p>
</th>
</tr>
<tr>
<td>escalonamento não é serial</td>
<td>escalonamento é serial</td>
</tr>
<tr>
<td>escalonamento não é equivalente</td>
<td>escalonamento é equivalente</td>
</tr>
</tbody>
</table>

 
### Entrada:
A entrada deve ser feita pela entrada padrão (`stdin`). O  arquivo é formado por uma sequência de linhas, onde cada linha  representa uma transação chegando. Cada linha tem 4 campos: o primeiro é o  tempo de chegada, o segundo é o identificador da transação, o terceiro é a operação (R=read, W=write, C=commit) e o quarto o atributo que será lido/escrito. Estas linhas estão ordenadas pelo  primeiro campo (tempos menores no início indicando a linha do tempo).
### Saída:
A saída deve ser feita pela saída padrão (`stdout`). O  arquivo será composto por uma sequência de linhas. Uma linha para cada escalonamento. Cada linha tem 4 campos  separados por espaço (um único espaço entre cada par de campos). O  primeiro campo é o identificador do escalonamento. O segundo campo é a lista de transações. E o terceiro apresenta o resultado do algoritmo da garantia da seriabilidade, onde SS e NS significam respectivamente serial (SS) ou não serial (NS). O quarto campo é o resultado do algoritmo de teste de equivalência de visão, onde SV e NV significam respectivamente equivalente (SV) ou não equivalente (NV) .

Exemplo de arquivos com uma entrada e uma saída válida:
<div class="visualClear">
<table class="plain" border="1">
<tbody>
<tr>
<td>Entrada</td>
<td>Saída</td>
</tr>
<tr>
<td><b>
<div class="visualClear" style="text-align: left;">1 1 R X</div>
<div class="visualClear" style="text-align: left;"><b>2 2 R X</b></div>
<div class="visualClear" style="text-align: left;"><b>3 2 W X</b></div>
<div class="visualClear" style="text-align: left;"><b>4 1 W X</b></div>
<div class="visualClear" style="text-align: left;"><b>5 2 C -<br></b></div>
</b><b>
<div class="visualClear" style="text-align: left;"><b>6 1 C -<br></b></div>
<div class="visualClear" style="text-align: left;"><b>7 3 R X</b></div>
<div class="visualClear" style="text-align: left;"><b>8 3 R Y<br></b></div>
</b><b>
<div class="visualClear" style="text-align: left;"><b>9 4 R X</b></div>
<div class="visualClear" style="text-align: left;"><b>10 3 W Y<br></b></div>
<div class="visualClear" style="text-align: left;"><b>11 4 C -</b><b>
<div class="visualClear" style="text-align: left;"><b>12 3 C -<br></b></div>
</b></div>
</b></td>
<td>
<div class="visualClear">1 1,2 NS NV</div>
<div class="visualClear">2 3,4 SS SV</div>
<div class="visualClear">
<div class="visualClear" style="text-align: left;"></div>
</div>
</td>
</tr>
</tbody>
</table>
</div>

Casos de teste: [Aqui](https://www.inf.ufpr.br/eduardo/ensino/ci218/trabalhos/escalona/) 

## Requisitos mínimos:
O trabalho deve ser implementado em linguagem de programação C de forma que possa ser compilado e executado nas servidoras de computação do Departamento de Informática.

O nome do executável deve ser `escalona`.

Não deve ter nenhuma opção de linha comando.
### *** ALUNOS DA ESTATÍSTICA ***
Os alunos da estatística possuem a opção de implementar o trabalho em linguagem de programação R. Contudo, o requisito de criar o script executável `escalona` é o mesmo dos outros alunos.
Vejam abaixo o que deve ser entregue em conjunto com o script em R.

 
## O que deve ser entregue:
Além dos arquivos fonte, deve acompanhar um `makefile` e um relatório com no máximo 2 páginas contendo a documentação sintetizada do sistema implementado. Qualquer particularidade deve estar descrita neste texto, como: algoritmo de detecção de ciclo em grafo.

Para compilar será usado o comando `make` (sem nenhum parâmetro), portanto preparem o Makefile para a compilação. (<b>ALUNOS DA ESTATÍSTICA:</b> o `makefile`  deverá contar as bibliotecas que julgarem necessárias para a exeução do programa R nas servidoras do DINF. Portanto, testem seus trabalhos nas servidoras do DINF antes da submissão do trabalho.)

Para testar será executado um script como o abaixo.
<pre>$ ./escalona &lt; teste.in &gt; teste.out
$ diff teste.sol teste.out
</pre>
Onde `teste.in` é o arquivo de entrada do teste e `teste.sol` é o esperado como saída.  

Caso o teste seja positivo (não imprime nada) será analisado o código fonte e o relatório.  

Os fontes também devem ser comentados e a qualidade do codigo vale nota (e.g., Doxygen, Javadoc). 
## Equipe:
O trabalho pode ser em equipes de até 2 alunos.
## Forma de entrega:
O trabalho deve ser empacotado em um arquivo GRR<sub>1</sub>_GRR<sub>2</sub>.tar.gz, onde "GRR<sub>1</sub>" é uma string com a matricula de um dos alunos nas servidoras do DInf. Ao descompactar este arquivo deverá ser criado um diretório de nome "GRR<sub>1</sub>_GRR<sub>2</sub>" que conterá todos os demais arquivos. O `make` e o script acima deverão funcionar dentro deste diretório (não em subdiretórios). Por exemplo, a equipe com GRR2000 e GRR2001 enviará o arquivo GRR2000_GRR2001.tar.gz que deverá descompactar seus arquivos e subdiretorios no diretorio "GRR2000_GRR2001/"

O arquivo "...tar.gz" deve ser enviado por e-mail ao endereço do professor com o assunto "CI218-trab2 " (exatamente).  IMPORTANTE: Minha caixa de email usa o assunto do email como filtro.




<app-weava-root id="weava-root" class="weava" ng-version="12.2.16"></app-weava-root>
