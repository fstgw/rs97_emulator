#ifndef _JUEGO_ENEMIGOS_
#define _JUEGO_ENEMIGOS_

int TESC_Juego::ia_recorrido_pantallas[_MAX_PANTALLAS_]=
{
    11,14,20,16,13,17,15,18,19,12,
    31,34,40,36,33,37,35,38,39,32,
     1, 6,10, 3, 4, 7, 5, 8, 9, 2,
    21,25,30,26,24,23,27,28,29,22,
    44,41,42,43,45
};

// Tabla de Enemios por Pantalla
//
ScrInfo TESC_Juego::ia_ScrInfo[_MAX_PANTALLAS_]=
{
    // Pantalla 1
    {
        {
            // int tipo,int posx,int posy,int min,int max,int vel,int retardo
            {TSPR_GOTA_AZUL,15,3,3,7,4,4},
            {TSPR_HBABOSA_AMARILLA,28,4,19,28,2,3},
            {TSPR_VTABLA_ROJA,28,11,6,11,2,3}
        },
        false,27,0,false,false,
        0,0,2,0
    },

    // Pantalla 2
    {
        {
            {TSPR_HBOLAPINCHO_AZUL,9,4,5,9,4,3},
            {TSPR_HPALO_AMARILLO,12,13,12,12,0,1},
            {TSPR_SERPIENTE_VERDE,22,13,14,22,3,3}
        },
        false,0,0,false,false,
        1,0,0,3
    },

    // Pantalla 3
    {
        {
            #ifdef SMALL_GAME
                {TSPR_HTORNILLO_AZUL,22,3,21,22,102,5},
            #else
                {TSPR_HTORNILLO_AZUL,21,3,21,22,1,5},
            #endif
            {TSPR_MOMIA_AZUL,26,13,22,26,2,3},
            {TSPR_HSPIDER_VERDE,16,5,14,20,-2,2}
        },
        false,0,0,false,false,
        0,2,0,4
    },

    // Pantalla 4
    {
        {
            {TSPR_GOTA_AMARILLA,7,5,2,5,2,6},
            {TSPR_VTABLA_ROJA,15,9,5,9,4,1},
            {TSPR_SERPIENTE_VERDE,18,12,10,20,-2,3}
        },
        false,0,27,false,false,
        0,3,5,7
    },

    // Pantalla 5
    {
        {
            {TSPR_GOTA_AZUL,9,9,9,12,3,2},
            {TSPR_VSPIDER_AZUL,23,5,5,8,2,2},
            {TSPR_GOTA_AMARILLA,28,2,2,6,2,2}
        },
        false,0,0,false,false,
        0,0,6,0
    },

    // Pantalla 6
    {
        {
            {TSPR_GOTA_AMARILLA,4,4,2,6,4,2},
            {TSPR_HPELOTA_AZUL,10,10,8,13,3,3},
            {TSPR_MOMIA_AZUL,18,12,14,25,3,2}
        },
        false,37,0,false,false,
        5,0,4,0
    },

    // Pantalla 7
    {
        {
            {TSPR_HBOLAPINCHO_ROJA,11,4,8,12,4,2},
            {TSPR_HARO_AMARILLO,12,12,8,16,2,3},
            {TSPR_VBABOSA_AMARILLA,20,4,2,7,3,1}
        },
        false,0,0,false,false,
        0,4,8,0
    },

    // Pantalla 8
    {
        {
            {TSPR_HTORNILLO_AMARILLO,13,4,10,15,3,3},
            {TSPR_GOTA_VERDE,12,11,8,11,2,4},
            {TSPR_HSPIDER_AZUL,15,11,14,20,4,1}
        },
        false,26,0,false,false,
        7,0,9,0
    },

    // Pantalla 9
    {
        {
            {TSPR_HTABLA_MARRON,16,8,12,17,3,3},
            {TSPR_HPALO_AZUL,14,12,9,15,-3,1},
            {TSPR_HBOLAPINCHO_AZUL,26,10,23,29,-4,2}
        },
        false,0,26,false,false,
        0,0,10,0
    },

    // Pantalla 10
    {
        {
            {TSPR_GOTA_ROJA,4,2,2,6,2,4},
            {TSPR_VSPIDER_ROJO,19,6,5,9,2,2},
            {TSPR_SERPIENTE_VERDE,11,8,10,14,-2,3}
        },
        false,0,0,false,false,
        9,11,0,0
    },

    // Pantalla 11
    {
        {
            #ifdef SMALL_GAME
                {TSPR_GOTA_AMARILLA,10,7,0,7,102,6},
                {TSPR_RAYO_AZUL,16,3,3,9,103,2},
                {TSPR_RAYO_AMARILLO,16,9,3,9,102,2}
            #else
                {TSPR_GOTA_AMARILLA,10,7,0,7,2,4},
                {TSPR_RAYO_AZUL,16,3,3,9,2,2},
                {TSPR_RAYO_AMARILLO,16,9,3,9,3,2}
            #endif
        },
        false,false,false,false,false,
        0,12,0,10
    },

    // Pantalla 12
    {
        {
            {TSPR_HBOLAPINCHO_AZUL,3,4,2,7,2,2},
            {TSPR_HBABOSA_AMARILLA,7,8,2,13,3,3},
            {TSPR_GOTA_AZUL,28,9,2,9,6,6}
        },
        false,28,28,false,false,
        0,0,0,11
    },

    // Pantalla 13
    {
        {
            {TSPR_GOTA_AMARILLA,3,1,1,6,2,6},
            {TSPR_VSPIDER_AZUL,8,5,4,9,-2,2},
            {TSPR_GOTA_AZUL,11,5,1,6,2,6}
        },
        false,0,0,false,false,
        14,0,0,0
    },

    // Pantalla 14
    {
        {
            {TSPR_SERPIENTE_AMARILLA,16,12,2,25,4,2},
            {TSPR_SERPIENTE_VERDE,17,12,10,19,-3,2},
            {TSPR_SERPIENTE_ROSA,6,12,5,20,-2,4}
        },
        false,0,0,false,false,
        15,0,13,0
    },

    // Pantalla 15
    {
        {
            {TSPR_HBABOSA_VERDE,5,12,4,14,2,3},
            {TSPR_VSPIDER_AZUL,17,9,6,12,2,2},
            {TSPR_GOTA_AZUL,26,12,7,12,4,2}
        },
        false,0,0,false,false,
        0,0,14,16
    },

    // Pantalla 16
    {
        {
            {TSPR_HPELOTA_ROJA,16,12,8,16,-4,3},
            {TSPR_HBOLAPINCHO_ROJA,21,4,18,22,-2,3},
            {TSPR_GOTA_AMARILLA,24,4,4,12,4,4}
        },
        false,40,0,false,false,
        0,15,17,0
    },

    // Pantalla 17
    {
        {
            {TSPR_GOTA_VERDE,9,11,6,12,2,6},
            {TSPR_GOTA_AMARILLA,12,12,4,12,4,4},
            {TSPR_GOTA_ROJA,16,10,2,12,5,3}
        },
        false,0,37,false,false,
        0,0,0,0
    },

    // Pantalla 18
    {
        {
            {TSPR_MOMIA_ROJA,20,13,19,22,-2,3},
            {TSPR_HSPIDER_VERDE,25,5,24,28,-4,2},
            {TSPR_VPELOTA_AZUL,17,11,8,13,-3,3}
        },
        false,false,false,false,false,
        0,0,0,19
    },

    // Pantalla 19
    {
        {
            {TSPR_GOTA_AZUL,13,6,2,6,2,4},
            {TSPR_GOTA_ROJA,17,6,2,6,4,4},
            {TSPR_HTABLA_MARRON,21,12,12,23,3,3}
        },
        false,0,0,false,false,
        0,18,0,20
    },

    // Pantalla 20
    {
        {
            {TSPR_VARO_ROJO,13,4,2,10,-4,3},
            {TSPR_HBABOSA_AMARILLA,18,5,16,21,-2,3},
            {TSPR_GOTA_AMARILLA,10,8,8,12,3,4}
        },
        false,30,0,false,false,
        0,19,0,21
    },

    // Pantalla 21
    {
        {
            {TSPR_VARO_ROJO,7,8,8,12,2,2},
            {TSPR_VTABLA_MARRON,21,11,8,12,-2,3},
            {TSPR_GOTA_AZUL,9,1,1,4,2,16}
        },
        false,0,30,false,false,
        0,20,23,22
    },

    // Pantalla 22
    {
        {
            {TSPR_HSPIDER_ROJO,14,13,8,16,2,2},
            {TSPR_HSPIDER_AZUL,16,13,11,18,-2,2},
            {TSPR_GOTA_AMARILLA,19,2,2,13,4,4}
        },
        false,-1,0,false,false,
        0,21,0,0
    },

    // Pantalla 23
    {
        {
            #ifdef SMALL_GAME
                {TSPR_ROCA_BLANCA,13,2,2,7,3,4},
            #else
                {TSPR_ROCA_BLANCA,13,2,2,7,2,4},
            #endif
            {TSPR_HTABLA_MORADA,24,11,22,30,4,1},
            {TSPR_HBABOSA_AMARILLA,23,7,19,30,3,3}
        },
        false,0,0,false,false,
        0,0,24,0
    },

    // Pantalla 24
    {
        {
            {TSPR_SERPIENTE_ROSA,12,11,7,13,3,4},
            {TSPR_SERPIENTE_AZUL,18,11,20,30,-4,2},
            {TSPR_RAYO_VERDE,16,8,4,8,2,2}
        },
        false,0,0,false,false,
        23,0,25,0
    },

    // Pantalla 25
    {
        {
            {TSPR_ROCA_BLANCA,7,4,1,11,3,6},
            {TSPR_GOTA_AZUL,22,6,2,13,6,4},
            {TSPR_HORMIGUERO,26,13,26,26,0,3}
        },
        false,35,-1,false,false,
        24,0,28,0
    },

    // Pantalla 26
    {
        {
            {TSPR_ROCA_MARRON,11,7,0,12,6,4},
            {TSPR_HBABOSA_ROJA,6,12,6,18,-2,3},
            {TSPR_GOTA_AZUL,28,11,11,13,2,4}
        },
        false,0,35,false,false,
        0,27,0,29
    },

    // Pantalla 27
    {
        {
            {TSPR_VSPIDER_VERDE,2,4,4,11,4,1},
            {TSPR_HBABOSA_AMARILLA,13,7,4,15,4,3},
            {TSPR_GOTA_ROJA,7,9,2,11,4,4}
        },
        false,0,0,false,false,
        0,28,0,26
    },

    // Pantalla 28
    {
        {
            {TSPR_GOTA_ROJA,24,8,2,13,4,1},
            {TSPR_VSPIDER_VERDE,28,6,5,7,-1,2},
            {TSPR_HBOLAPINCHO_ROJA,15,7,8,16,4,2}
        },
        false,0,0,false,false,
        25,0,0,27
    },

    // Pantalla 29
    {
        {
            {TSPR_HARO_AMARILLO,18,12,17,27,4,2},
            {TSPR_VPELOTA_VERDE,6,8,7,10,-102,3},
            {TSPR_GOTA_AZUL,9,4,4,7,1,4},
        },
        false,29,0,false,false,
        0,26,0,30
    },

    // Pantalla 30
    {
        {
            {TSPR_PEZ_AMARILLO,7,12,6,14,-4,1},
            {TSPR_GOTA_VERDE,2,2,2,10,5,4},
            {0,0,0,0,0,0,0},
        },
        false,0,0,false,false,
        31,29,0,0
    },

    // Pantalla 31
    {
        {
            {TSPR_PEZ_VERDE,19,9,8,14,-2,2},
            {TSPR_GOTA_AZUL,16,0,0,11,5,4},
            {TSPR_VPELOTA_ROJA,6,13,11,14,-2,2   }
        },
        false,0,0,false,false,
        32,0,30,0
    },

    // Pantalla 32
    {
        {
            {TSPR_PEZ_AZUL,8,10,8,14,-2,2},            
            {TSPR_PEZ_VERDE,10,7,5,14,-3,2},            
            {TSPR_PEZ_AMARILLO,12,9,6,14,4,1} 
        },
        false,0,0,false,false,
        33,42,31,0
    },

    // Pantalla 33
    {
        {
            {TSPR_VSPIDER_ROJO,19,6,4,8,4,1},
            {TSPR_PEZ_AMARILLO,15,11,7,14,3,1},
            {TSPR_GOTA_AZUL,12,7,0,9,3,5}
        },
        false,0,0,false,false,
        34,43,32,0
    },

    // Pantalla 34
    {
        {
            {TSPR_SERPIENTE_AZUL,1,9,1,4,-2,1},
            {TSPR_PEZ_AMARILLO,14,10,9,14,2,1},
            {TSPR_GOTA_VERDE,18,8,5,11,4,8}
        },
        false,0,0,false,false,
        0,35,33,0
    },

    // Pantalla 35
    {
        {
            #ifdef SMALL_GAME
                {TSPR_GOTA_VERDE,23,11,6,12,2,4},
                {TSPR_MOMIA_VERDE,17,12,14,21,-2,3},
            #else
                {TSPR_GOTA_VERDE,23,11,6,12,2,4},
                {TSPR_MOMIA_VERDE,17,12,14,21,-3,3},
            #endif
            {TSPR_FLECHA,2,2,2,28,4,4}
        },
        false,0,0,false,false,
        0,36,0,34
    },

    // Pantalla 36
    {
        {
            {TSPR_HARO_AMARILLO,11,9,11,11,0,2},
            #ifdef SMALL_GAME
                {TSPR_HTABLA_MARRON,18,12,14,20,-3,3},
            #else
                {TSPR_HTABLA_MARRON,18,12,14,20,-4,3},
            #endif
            {TSPR_GOTA_ROJA,28,12,10,12,1,4}
        },
        false,-1,29,false,false,
        0,0,0,35
    },

    // Pantalla 37
    {
        {
            {TSPR_PELOTABOTA,6,2,11,8,2,2},
            {TSPR_GOTA_ROJA,14,2,2,6,2,2},
            {TSPR_HBABOSA_VERDE,20,5,14,24,-2,3}
        },
        false,38,38,false,false,
        0,0,0,0
    },

    // Pantalla 38
    {
        {
            {TSPR_GOTA_VERDE,11,4,1,7,3,8},
            {TSPR_HSPIDER_AZUL,22,11,18,27,3,2},
            {TSPR_HSPIDER_VERDE,19,11,19,27,2,2}
        },
        false,0,0,false,false,
        0,0,39,0
    },

    // Pantalla 39
    {
        {
            {TSPR_RAYO_MORADO,11,9,5,9,4,1},
            {TSPR_RAYO_AZUL,15,5,5,9,2,2},
            {TSPR_RAYO_AMARILLO,19,7,5,9,-3,1}
        },
        false,0,0,false,false,
        38,0,40,0
    },

    // Pantalla 40
    {
        {
            {TSPR_VSPIDER_VERDE,23,7,5,12,-4,1},
            {TSPR_HBABOSA_AMARILLA,16,4,13,21,-4,3},
            {TSPR_VBOLAPINCHO_ROJA,3,10,7,12,4,2}
        },
        false,0,0,false,false,
        39,0,0,41
    },

    // Pantalla 41
    {
        {
            {TSPR_HSPIDER_VERDE,24,12,16,27,4,1},
            {TSPR_HSPIDER_AZUL,22,12,16,26,4,1},
            {TSPR_HSPIDER_ROJO,19,12,17,27,-2,2}
        },
        false,0,0,false,false,
        0,40,0,42
    },

    // Pantalla 42
    {
        {
            #ifdef SMALL_GAME
                {TSPR_GOTA_VERDE,3,8,8,12,3,4},
                {TSPR_GOTA_AMARILLA,7,12,8,12,3,4},
                {TSPR_GOTA_AZUL,11,10,8,12,3,4}
            #else
                {TSPR_GOTA_VERDE,3,8,8,12,2,4},
                {TSPR_GOTA_AMARILLA,7,12,8,12,2,4},
                {TSPR_GOTA_AZUL,11,10,8,12,2,4}
            #endif
        },
        false,0,0,false,false,
        43,41,0,31
    },

    // Pantalla 43
    {
        {
            {TSPR_RAYO_VERDE,21,8,8,8,0,2},            
            {TSPR_SERPIENTE_AMARILLA,5,12,2,5,-3,3},
            {TSPR_GOTA_AZUL,13,10,2,12,6,6}
        },
        false,0,39,false,false,
        44,0,42,33
    },

    // Pantalla 44
    {
        {
            {TSPR_VSPIDER_VERDE,6,12,8,12,-4,1},
            {TSPR_HSPIDER_AZUL,25,12,22,26,4,1},
            {TSPR_GOTA_VERDE,20,4,4,12,4,6}
        },
        false,39,0,false,false,
        0,0,43,0
    },

    // Pantalla 45 (PANTALLA FINAL, SIN ENEMIGOS)
    {
        {
            {0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0}
        },
        false,0,0,false,false,
        0,0,0,0
    }

};

#endif
