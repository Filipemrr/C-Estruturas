achar_mais_proximo(int andar, int porta){
    while (1)
    {
        int flag_up = 0;
        int flag_down = 0;

        if(flag_up == 1 && flag_down == 1){
            exit(1);
        }

        //varre pra cima
        for (int i = 1; i < 300; i++){
            for (int w = 0; w <3 ; w++){
                if(matriz[andar + i][porta + w] == '[⊠]'){
                    flag_up = 1;
                    break;
                }
                if (andar+i == 0 && porta+w == 2){
                    flag_up = 0;
                    break;
                }
            }   
        }

        //varre pra baixo
        for (int i = 300; i > 0; i--){
            for (int w = 3; w > 0; w--){
                if (i == 299 && w== 2){
                    flag_down = 0;
                    break;
                }
                if(matriz[andar + i][porta + w] == '[⊠]'){
                    flag_down = 1;
                    break;
                }
            }   
        }
        
        
    }
    
}


printf("%s ", matriz[199][2]);
    printf("%s ", matriz[199][1]);
    printf("%s ", matriz[199][2]);
    printf("\n");
    printf("%s ", matriz[198][2]);
    printf("%s ", matriz[198][1]);
    printf("%s ", matriz[198][0]);
    printf("\n");
    printf("%s ", matriz[197][2]);
    printf("%s ", matriz[197][1]);
    printf("%s ", matriz[197][0]);
    printf("\n");
    printf("%s ", matriz[196][2]);
    printf("%s ", matriz[196][1]);
    printf("%s ", matriz[196][0]);
    printf("\n");
    printf("%s ", matriz[195][2]);
    printf("%s ", matriz[195][1]);
    printf("%s ", matriz[195][0]);

    printf("\n");
    printf("%s ", matriz[194][2]);
    printf("%s ", matriz[194][1]);
    printf("%s ", matriz[194][0]);
    