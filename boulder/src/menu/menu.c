#include <stdio.h>
#include <stdlib.h>

#include "../evenement/touche/touche.h"
#include "../moteur_graphique/moteur_graphique.h"

#include "menu.h"


#define TAILLE_TEXTE 10
#define DECALAGE_INTER_TEXTE 2

Menu_resultat menu(G_fenetre* fenetre, Menu_etat etat)
{
  G_surface* fond;
  G_surface* surf;
  G_rectangle rect;
  int x_deb;
  int y_deb;
  
  G_surface* stexte;
  G_font* font_menu;
  G_couleur noir;
  G_couleur blanc;
  

  
  font_menu = g_fontCharger("./data/fonts/times.ttf", TAILLE_TEXTE);
  if (font_menu==NULL)
    fprintf(stderr, "\n** menu: Problème chargement font\n");  
 
  fond = g_surfaceChargerBMP("./data/image/bouldfond.bmp");
  if (fond==NULL)
    fprintf(stderr, "\n** menu: Problème chargement fond\n");
 
  surf = g_fenetreLireSurface(fenetre);
  noir =  g_couleurCreer(surf, 255,255,255);
  blanc =  g_couleurCreer(surf, 0,0,0);
 
  x_deb =  (g_surfaceLongueurx(surf)-g_surfaceLongueurx(fond))/2;
  y_deb = 200;
  
  g_rectangleInitialiser(&rect, x_deb,0,0,0);
  g_surfaceCopie(fond, NULL, surf, &rect);
  
  
  switch(etat)
  {
    case MENU_INTRODUCTION: 
         g_rectangleInitialiser(&rect, x_deb, y_deb ,0,0);
         stexte = g_surfaceEcrireTexte(font_menu, "Appuyez sur B pour commencer le jeu normal", blanc, noir);
         g_surfaceCopie(stexte, NULL, surf, &rect);
    
         g_rectangleInitialiser(&rect, x_deb, y_deb+TAILLE_TEXTE+DECALAGE_INTER_TEXTE ,0,0);
         stexte = g_surfaceEcrireTexte(font_menu, "Appuyez sur X pour joueur au mode Flo", blanc, noir);
         g_surfaceCopie(stexte, NULL, surf, &rect);
  
         g_rectangleInitialiser(&rect, x_deb, y_deb+2*TAILLE_TEXTE+2*DECALAGE_INTER_TEXTE ,0,0);
         stexte = g_surfaceEcrireTexte(font_menu, "Appuyez sur SELECT pour quitter", blanc, noir);
         g_surfaceCopie(stexte, NULL, surf, &rect);
  
         g_fenetreAfficher(fenetre);
            
     
        while(1)
        {        
          if (toucheEstAppuyer(T_ESCAPE))
           return MENU_QUITTER;
          if (toucheEstAppuyer(T_LALT))
           return MENU_UN_JOUEUR;
          if (toucheEstAppuyer(T_SPACE))
           return MENU_UN_JOUEUR_MODE_FLO;
        }
        
        break;
    
    case MENU_NIVEAU_PERDU: 
         g_rectangleInitialiser(&rect, x_deb, y_deb ,0,0);
         stexte = g_surfaceEcrireTexte(font_menu, "Appuyez sur B pour recommencer le niveau", blanc, noir);
         g_surfaceCopie(stexte, NULL, surf, &rect);
    
         g_rectangleInitialiser(&rect, x_deb, y_deb+TAILLE_TEXTE+DECALAGE_INTER_TEXTE ,0,0);
         stexte = g_surfaceEcrireTexte(font_menu, "Appuyez sur SELECT pour quitter", blanc, noir);
         g_surfaceCopie(stexte, NULL, surf, &rect);
  
  
         g_fenetreAfficher(fenetre);
            
     
        while(1)
        {        
          if (toucheEstAppuyer(T_ESCAPE))
           return MENU_QUITTER;
          if (toucheEstAppuyer(T_LALT))
           return MENU_CONTINU;
        }
        
        break;
     case MENU_GAME_OVER_PERD: 
         g_rectangleInitialiser(&rect, x_deb, y_deb ,0,0);
         stexte = g_surfaceEcrireTexte(font_menu, "GAME OVER, vous avez perdu", blanc, noir);
         g_surfaceCopie(stexte, NULL, surf, &rect);
    
         g_rectangleInitialiser(&rect, x_deb, y_deb+TAILLE_TEXTE+DECALAGE_INTER_TEXTE ,0,0);
         stexte = g_surfaceEcrireTexte(font_menu, "Appuyez sur SELECT pour quitter", blanc, noir);
         g_surfaceCopie(stexte, NULL, surf, &rect);
  
  
         g_fenetreAfficher(fenetre);
            
     
        while(1)
        {        
          if (toucheEstAppuyer(T_ESCAPE))
           return MENU_QUITTER;
        }
        
        break;   
     case MENU_GAME_OVER_GAGNE: 
         g_rectangleInitialiser(&rect, x_deb, y_deb ,0,0);
         stexte = g_surfaceEcrireTexte(font_menu, "Félicitations, vous avez gagner", blanc, noir);
         g_surfaceCopie(stexte, NULL, surf, &rect);
    
         g_rectangleInitialiser(&rect, x_deb, y_deb+TAILLE_TEXTE+DECALAGE_INTER_TEXTE ,0,0);
         stexte = g_surfaceEcrireTexte(font_menu, "Appuyez sur SELECT pour quitter", blanc, noir);
         g_surfaceCopie(stexte, NULL, surf, &rect);
  
  
         g_fenetreAfficher(fenetre);
            
     
        while(1)
        {        
          if (toucheEstAppuyer(T_ESCAPE))
           return MENU_QUITTER;
        }
        
        break;   
    case MENU_NIVEAU_REUSSI: 
         g_rectangleInitialiser(&rect, x_deb, y_deb ,0,0);
         stexte = g_surfaceEcrireTexte(font_menu, "Appuyez sur B pour aller au niveau suivant", blanc, noir);
         g_surfaceCopie(stexte, NULL, surf, &rect);
    
         g_rectangleInitialiser(&rect, x_deb, y_deb+TAILLE_TEXTE+DECALAGE_INTER_TEXTE ,0,0);
         stexte = g_surfaceEcrireTexte(font_menu, "Appuyez sur SELECT pour quitter", blanc, noir);
         g_surfaceCopie(stexte, NULL, surf, &rect);
  
  
         g_fenetreAfficher(fenetre);
            
     
        while(1)
        {        
          if (toucheEstAppuyer(T_ESCAPE))
           return MENU_QUITTER;
          if (toucheEstAppuyer(T_LALT))
           return MENU_CONTINU;
        }
        
        break;                  
    default:
       return  MENU_QUITTER;
    
  }  

    
    
}
