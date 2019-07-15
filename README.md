# MorphingMenace

**"The Morphing Menace!" é um jogo 2D do tipo plataforma-metroidvania do gênero ação e exploração desenvolvido como projeto da disciplina "Intrução ao Desenvolvimento de Jogos" da Universidade de Brasília durante o semestre 2019/1.**

O jogo segue a exploração de uma espécie parasita-transmorfa que possui a incrível habilidade de possuir seus inimigos e adquirir suas características. Esta espécie foi enviada a um planeta alienígena por seus criadores para que domine a espécie e o planeta possa ser utilizado na obtenção de recursos. 
O que não era esperado, era que a espécie dominante deste planeta é controlada por uma consciência coletiva *hivemind*, exercendo influencia sob os seres vivos deste planeta. Desde modo, a espécie transmorfa vê seus poderes de transformação limitados, não podendo permanecer muito tempo nas formas transformadas já que passa a sofrer influência da consciência.
O parasita então se vê desafiado a usar seus poderes com inteligência e estratégia para que todo seu poder não seja todo gasto e ele fique preso no planeta.

### Aspectos Fundamentais:
* O jogador ganha se chegar à consciência *hivemind*, destruir seus *cores* e absorvê-la.
* O jogador que chegar à 0 de vida morrerá e perderá o jogo.

#### Mecânica de Influência 
Enquanto o jogador estiver em alguma forma transformada, ele perderá aos poucos sua habilidade de transformação. Esta quantidade é controlada pela espinha dorsal da caveira no canto superior esquerdo da tela. Essa espinha diminuirá e piscará conforme for consumida.

A velocidade com que nosso personagem principal sofre influência é proporcional com a proximidade da *hivemind*.

#### Controles de menu:
* ESPAÇO: entra no jogo (existe uma tela de loading entre o menu e o jogo em si)
* ESC: Sai do jogo

#### Controles de jogo:
* ESPAÇO: pulo (não disponível na forma aquática)
* O: ataque (apenas disponível na forma de ataque)
* P: absorção (se transformado, regride para forma inicial)
* WASD: movimentação pelo mapa de acordo com ambiente (em terra apenas é permitido movimentação horizontal)

#### Dicas:
* Você pode regredir para a forma inicial a qualquer momento apertando "P" a partir de uma forma transformada.
* A barra de influência é FINITA, não gaste ela toda de uma vez. Tente explorar o mapa na forma inicial.
* Formas não aquáticas levam DANO na água.
* A influência diminui mais rapidamente conforme a proximidade do jogador com o Boss. Tente vencê-lo rapidamente.
* Existe uma passagem secreta no fundo do mar que leva a caverna da *hivemind* mais rapidamente.

### Instalação 
#### Dependências:
* Bibliotecas SDL (img, mixer, ttf, etc)
#### Compilação:
* Faça *clone* deste repositório em seu diretório de preferência
* Vá para este diretório e abra a pasta raiz do jogo "MorphingMenace" e dê o comando "make"
#### Execução :
* Após compilado, execute o jogo neste mesmo diretório com o comando ./MorphingMenace.out

### Desenvolvimento:
* Igor R. O. Beduin - 14/143882:
  * Modelos de classe 
  * Física, colisões, ambiente
  * Transformação
  * Absorção
  * Interfaces de dano
  * Lógica da influência da *hivemind*
  * GUI de de vida e influência
  * Controles
  * Autômato de estado do personagem (jumping, walking, etc)

* Raphael R. C. Barbosa - 14/0160281:
  * Animações 
  * Inimigos (básico de ataque e aquático)
  * Animação de absorção
  * Boss (*hivemind*) e seus *cores*
  * Máquina de estados dos inimigos
  * Inimigos mortos no chão
  * Menu e tela de loading 
  * Tela final (derrota ou vitória)
  * Animação da GUI
  * Implementação de sons e músicas

### BUGS CONHECIDOS:
* Colisões invisíveis no mapa
* Personagem "entrando" no chão
* Forma aquática perdendo sprite a tentar sair da água
* Pulo dos personagens pode sofrer diminuição de altura em um segundo loop de jogo, após a morte do personagem.
* Renderização incompleta dos cenários e/ou fundos


### Link para este repositório: https://github.com/igorbeduin/MorphingMenace