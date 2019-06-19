
# criando mini bancos de dados fake
# aprender multiprocessamento


def begin():

    while True:
        print('-=' * 30)
        card_id = input('passe o cartão: ')
        print('-=' * 30)
        
        if 'r' in card_id:
            
            card_id = card_id.strip('r')
            print(f'CARD ID: {card_id}')
            print(f'Olá, {nome}!')
            print('Sua baia lhe aguarda.')
            print('Você tem: 59:55:00 minutos disponíveis.')

            # ao apertar ENTER o valor
            # cid é enviado para lista
            # que é relacionado à um nome:

        break
                        
    while True:
        
        print('-=' * 30)
        print('ou digite a baia (OPÇÃO 2).')
        print('-=' * 30)
        print(f'baias disponíveis: {baias}')
        print('-=' * 30)
        print(f'Escolha uma baia: 1){baias[0]} 2){baias[1]}, 3){baias[2]}')
        print('-=' * 30)
        user_a = input('Escolha: ').lower()

        if user_a in 'b':
            print(f'A baia {user_a} lhe aguarda.')
            print('Você tem: 59:55:00 minutos disponíveis.')

            # ao apertar ENTER o valor
            # é alocado numa lista de baias
            # livres para coworking
    
        break
                        
                       

user = '0'
nome = 'fulano'
baias = 'B1', 'B2', 'B3'
card_id = '10 10', '10 11', '10 12'

while True:
    begin()


        
    
    

    


