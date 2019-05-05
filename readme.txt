<< PROTÓTIPO - VERSÃO ALFA - DESENVOLVIMENTO >>

CODE - C (Writing)

MAIN CODE DIR: Aparelho-RLB/arduino/rfid_and_led

PROCESSO (MAIN CODE(Arduino Wiring language)):

- defino as bibliotecas 
- defino as pinagens do RFID
- coloco as tags autorizadas
- defino as pinagens do RGB

no setup:

- inicio a serial
- inicio conexão SPI
- inicia MFRC522 que é o disp RFID
- inicia os pin RGB como saída OUTPUT
- chamo função "mensageminicial( )"

no loop: 

- mensageminicial( ) faz:
- serial printa "Aproxime seu cartão"
- (ainda não implementei mas vou codar pra manter LED verde nesse momento de inicialização pra simbolizar que a baia está livre por mais que tecnicamente ela seria permanente e estaria laranja)
- crio estrutura condicional IF que faz ele aguardar aproximação do cartão
- e selecionar o cartão

- a partir disso ele mostra a UID
- define string pra armazenar UID (conteudo)
- cria variável pra coletar o UID
- loop FOR pra ARMAZENAR byte por byte e concatena-los na váriavel que coleta o UID
- crio variável booleana pra validar como autorizada ou não a UID lida
- coloco valor da variável "conteudo" em maiusculo (porque sim)
- outro loop FOR pra verificar se a UID lida coincide com uma das UID declaradas no array lá no início
- se true: na serial aparece: "Olá, Carlos!" e depois "Acesso liberado!"
- se true: acende led azul
- 10 segundos depois o processo é repetido limpando as váriaveis para nova leitura
> coloquei Carlos e Janaína nos exemplos porque sim, quem é que avalia a gente pra eu colocar de exemplo? além de Ferraz. Carlos é o Sampaio, obviamente.
- caso o conteúdo não seja "" (vazio) e a UID == false, informamos que o user não tem acesso
- "Usuário Desconhecido!"
- "Acesso Negado!!"
- Led vermelho é aceso
- 10 segundos e processo se repete da mesma forma que anteriormente


