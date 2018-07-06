#ifndef _MAPAS_CPP_
#define _MAPAS_CPP_

#include "mapas.h"

// ***************************************************************************
// *************************************************************
// *************************************
// Clase: TMAScreenIndex
// *********************
//
REGISTER_CLASS_ID(TMAScreenIndex);

// ***************************************************************************
// *************************************************************
// *************************************
// Clase: TGraphBank
// *****************
//
REGISTER_CLASS_ID(TMAGraphBank);

TMAGraphBank::TMAGraphBank()
{
    io_bank = NULL;
    is_basedir = NULL;
    Transparente = T_NONE;
}

TMAGraphBank::~TMAGraphBank()
{
    if (io_bank != NULL) delete io_bank;
}

bool TMAGraphBank::readFromFile(FILE* f)
{
    int li_aux;
    int li_zonas,li_maxzone = 0,li_zoneid;
    long ll_offset,ll_current,ll_current1;
    
    // Leemos el nombre del banco.
    //
    Name = getString(f,80).trim();
    
    // Leemos el ID del Banco
    //
    BankID = get2BWord(f);
    
    // Leemos el Offset de este banco.
    //
    ll_offset = get4BWord(f);
    
    // Obtenemos la posición actual para guardarla
    //
    ll_current = getCurrentOffset(f);
    
    // Nos posicionamos en el lugar donde esta el resto de la información.
    //
    if (!seekTo(f,ll_offset)) return false;
    
    Tipo = getByte(f);
    TileAX = get2BWord(f);
    TileAY = get2BWord(f);
    int TileV = get2BWord(f);
    int TileH = get2BWord(f);
    
    // Obtenemos el color de Transparencia
    //
    TransColor = MAKERGBCOLOR(getByte(f),getByte(f),getByte(f)); 
    getByte(f); // Ignoramos el byte de alpha
    Transparente = (getByte(f)>0)?T_TRANSPARENT:T_NONE;
    
    // Leemos el nombre de la imagen.
    //
    li_aux = get2BWord(f);
    TMAString ImageName = (is_basedir==NULL)?"./":is_basedir;
    ImageName = ImageName + &(getString(f,li_aux).trim().text()[2]);
    ImageName.replaceChar('\\','/');
    
    // Leemos el numero de zonas.
    //
    li_zonas = get2BWord(f);
    
    // Buscamos el Máximo identificador de zona.
    //
    ll_current1 = getCurrentOffset(f);
    
    for(int li_i=0;li_i<li_zonas;li_i++)
    {
    	li_zoneid = get2BWord(f);
    	if (li_maxzone < li_zoneid) li_maxzone = li_zoneid;
    
    	// Saltamos hasta el comienzo de la siguiente zona.
    	//
    	seekTo(f,getCurrentOffset(f)+16);
    }
    
    // Volvemos al lugar donde comienzan a definirse las zonas.
    //
    seekTo(f,ll_current1);
    
    // Creamos el array para almacenar las zonas y lo rellenamos
    // de manera que el indice de cada elemento es el identificador de la zona.
    //
    TMAVector vectorZ(li_maxzone+1,5,true);
    vectorZ.fillEmpty(li_maxzone+1);
    if (li_zonas>0) 
    {    
        for (int li_i=0;li_i<li_zonas;li_i++)
        {
        	// Obtenemos el ID de Zona
        	//
        	li_zoneid = get2BWord(f);
        	PMARectangle lrect = new TMARectangle();
        	lrect->x = (int)get4BWord(f);
        	lrect->y = (int)get4BWord(f);
        	lrect->width = (int)get4BWord(f);
        	lrect->height = (int)get4BWord(f);
        	vectorZ.replaceElementAt(lrect,li_zoneid);
        }
        io_bank = TMAImageBank::createDynamic(*ImageName,vectorZ);        
    }
    else
    {
        io_bank = TMAImageBank::createStatic(*ImageName,TileH,TileV,TileAX,TileAY);
    }
    
    if (io_bank==NULL)
    {
        return false;
    }
    
    // Establecemos la transparencia si procede
    //
    if (isTransparent())
    {
        for (int i=0;i<io_bank->size();i++)
        {
            PMABitmap bmp = io_bank->getBitmap(i);
            if (bmp!=NULL) bmp->setTransparentColor(TransColor);
        }
    }
    
    // Volvemos al lugar del fichero donde sigue la definición
    //
    seekTo(f,ll_current);
    
    return true;
}

const PMABitmap TMAGraphBank::getImage(int index)
{
    return io_bank->getBitmap(index);
}

// ***************************************************************************
// *************************************************************
// *************************************
// Clase: TMAGraphOperation
// ************************
//
REGISTER_CLASS_ID(TMAGraphOperation);

bool TMAGraphOperation::readFromFile(FILE *f)
{
    // Leemos los valores de la operación Grafica
    //
    BankID = get2BWord(f);
    TileID = get2BWord(f);
    PosX = get2BWordSigned(f);
    PosY = get2BWordSigned(f);
    RepeatX = get2BWord(f);
    RepeatY = get2BWord(f);
    StepX = get2BWord(f);
    StepY = get2BWord(f);
    AlignGrid = (getByte(f)>0);
    Tipo = getByte(f);
    
    if (Tipo==OP_ANIM_FRONT || Tipo==OP_ANIM_NORMAL)
    {
    	InitFrame = get2BWord(f);
    	EndFrame = get2BWord(f);
    	PauseFrame = get2BWord(f);
    	PauseAnim = get2BWord(f);
    	PingPong = (getByte(f)>0);
    }
    
    return true;
}

// ***************************************************************************
// *************************************************************
// *************************************
// Clase: TMAGraphAnimation
// ************************
//
REGISTER_CLASS_ID(TMAGraphAnimation);

TMAGraphAnimation::TMAGraphAnimation(TMAGraphOperation& go) 
{
	BankID = go.BankID;
	TileID = go.TileID;
	PosX = go.PosX;
	PosY = go.PosY;
	RepeatX = go.RepeatX;
	RepeatY = go.RepeatY;
	StepX = go.StepX;
	StepY = go.StepY;
	AlignGrid = go.AlignGrid;
	Tipo = go.Tipo;
	InitFrame = go.InitFrame;
	EndFrame = go.EndFrame;
	PauseFrame = go.PauseFrame;
	PauseAnim = go.PauseAnim;
	PingPong = go.PingPong;
	
    a_PauseFrame=0;
    a_PauseAnim=0;
    a_Down=false;

    // Calculamos uno de los tiles aleatorios para comenzar
    // con la secuencia de animación.
    //
    a_CurFrame = InitFrame + (rand()% (EndFrame - InitFrame + 1) );
}

// ***************************************************************************
// *************************************************************
// *************************************
// Clase: TMAScreenMap
// *******************
//
REGISTER_CLASS_ID(TMAScreenMap);

TMAScreenMap::~TMAScreenMap()
{
    if (MaskBuff!=NULL) delete MaskBuff;
    MaskBuff = NULL;
}

TMAScreenMap::TMAScreenMap(int id)
{
    ScreenID = id;
    MaskBuff=NULL;
	_GetMask_lbits = 0;
	_GetMask_width = 0;
	_GetMask_height = 0;
	_GetMask_mask = 0;
	MaskCol=0;
    MaskRow=0;
}

TMAVector& TMAScreenMap::getGraphicsOperationsForType(int t)
{
	switch (t)
	{
		case TMAGraphOperation::OP_NORMAL:
			return iv_OpNormal;
			
		case TMAGraphOperation::OP_FRONT:
			return iv_OpFront;
			
		case TMAGraphOperation::OP_ANIM_FRONT:
			return iv_OpAnimFront;
		
        default:	
			return iv_OpAnimNormal;
    }
}

void TMAScreenMap::deleteGraphOperation(int tipo,int bankid,int tileid)
{
    TMAVector& v = getGraphicsOperationsForType(tipo);
	
	for (int li_i=0;li_i<v.size();li_i++)
	{
		PMAGraphOperation go = (PMAGraphOperation)v.elementAt(li_i);
		if (go->BankID == bankid && go->TileID == tileid)
		{
			v.removeElementAt(li_i);
			return;
		}
	}
}

unsigned char TMAScreenMap::getMask(int X,int Y)
{	
    unsigned int li_byte,li_off,li_valor;
	unsigned char *PByte;
	
	// Caso que se solicite un valor que se sale del rango
	//
	if (Y>=_GetMask_height || Y<0 || X<0 ) return 0;
		
    // Calculamos el BYTE y el OFFSET en el que estan
    // contenidos los bits de máscara.
	//
    li_byte = Y*_GetMask_width + ((X * _GetMask_lbits) >> 3);
    li_off  = 8 - ((X * _GetMask_lbits) % 8);

     // Si el valor cabe en un solo byte...
     //
     if (li_off >= (unsigned int)_GetMask_lbits) 
	 {
		 PByte = this->MaskBuff;
		 PByte += li_byte;
         li_valor = *PByte;

         // Rotamos el valor hacia la derecha, para normalizarlo.
         //
         if (li_off > (unsigned int)_GetMask_lbits) li_valor >>= (li_off - _GetMask_lbits);
         li_valor &= _GetMask_mask;
	 }
     else
     {
		 // La mascara esta partida en 2 bytes, leemos los 2 bytes en
         // un buffer, y luego hacemos la misma operación anterior..
         //
		 PByte = this->MaskBuff;
		 PByte += li_byte;
         
		 li_valor = (*PByte);
		 li_valor <<= 8;
		 li_valor |= *(PByte + 1);
         li_valor >>= (8 - (_GetMask_lbits - li_off));
         li_valor &= _GetMask_mask;
     }

	 return (unsigned char)(li_valor & 0x00FF);
}

bool TMAScreenMap::readFromFile(FILE* f)
{
    int li_operaciones=0;
    		
    MaskCol = get2BWord(f);
    MaskRow = get2BWord(f);
    
    // Reservamos el buffer de Mascaras de la pantalla y cargamos.
    //
    MaskBuff = new unsigned char[MaskCol * MaskRow];
    getBytes(f,MaskBuff,MaskCol * MaskRow);
    
    // Leemos el numero de operaciones graficas
    //
    li_operaciones = get2BWord(f);
    
    // Desglosamos los elementos segun su tipo en diferentes listas
    //
    for(int li_i=0;li_i<li_operaciones;li_i++)
    {
    	PMAGraphOperation go = new TMAGraphOperation();
    	go->readFromFile(f);
    
    	// 0->Normal, 1-> Por delante, etc...
    	//
    	switch (go->Tipo)
    	{
       		case TMAGraphOperation::OP_NORMAL:
    			iv_OpNormal.addElement(go);
    			break;
    			
    		case TMAGraphOperation::OP_FRONT:
    			iv_OpFront.addElement(go);
    			break;
    			
    		case TMAGraphOperation::OP_ANIM_FRONT:
    			iv_OpAnimFront.addElement(new TMAGraphAnimation(*go));
    			delete go;
    			break;
    		
            default:	
    			iv_OpAnimNormal.addElement(new TMAGraphAnimation(*go));
    			delete go;
    	}
    }    
    return true;
}

// ***************************************************************************
// *************************************************************
// *************************************
// Clase: TMAGameMap
// *******************
//
REGISTER_CLASS_ID(TMAGameMap);

TMAGameMap::TMAGameMap()
{
    io_FastBuffer=NULL;
    clear();
}

TMAGameMap::~TMAGameMap()
{
    clear();
}

void TMAGameMap::clear()
{
    ib_iniciado=false;
    is_FileName=(char *)"";
    ScreenX=0; ScreenY=0; TilesAX=0; TilesAY=0;
    BitMask=0; ColorFondo=0;        
    iv_Bancos.clear();
    iv_Screen.clear();
        
    if (io_FastBuffer!=NULL) delete io_FastBuffer;
    io_FastBuffer = NULL;
}

int TMAGameMap::nBits(int valores)
{
	int cuenta=0;
		
	for(;;)
	{
		if (((valores >> cuenta) & 0x01)>0) return cuenta;
		cuenta++;
		if (cuenta>8) return 0;
	} 
}

int TMAGameMap::nBitsMask(int bits)
{
	int mask=0x00;
	while (bits>0)
	{
		mask = ((mask << 1)|0x01);
		bits--;
	}
	return mask;
}

void TMAGameMap::drawGraphOperation(TMABitmap& buff,TMAGraphOperation& op)
{	
    int dx,dy;
    
	// Determinamos el banco al que pertenece la operacion.
	// y la imagen origen de la operación
	//
	PMAGraphBank lBanco = (PMAGraphBank)iv_Bancos.elementAt(op.BankID);
	PMABitmap ImgOrigen = (lBanco!=NULL)?lBanco->getImage(op.TileID):NULL;
	if (ImgOrigen==NULL || lBanco==NULL)
	{
        //allegro_message("Error drawGraphOperation. Banco = %i, TileID = %i",op.BankID,op.TileID);
        return;
    }
    
    //bool isAlpha = lBanco->isAlpha();
    
	// Hacemos la copia de los graficos
	//
	int li_bx = 0;

	while (li_bx < op.RepeatX )
	{
		int lx = op.PosX + li_bx;
		int li_by = 0;

		while (li_by < op.RepeatY ) 
		{
			int ly = op.PosY + li_by;

		    if (op.AlignGrid)	// Caso que se elinee a la reticula
            {
                dx = lx * TilesAX;
                dy = ly * TilesAY;
			} 
			else 
			{
                dx = (op.PosX + (li_bx * TilesAX));
                dy =  (op.PosY + (li_by * TilesAY));
			}
			
			/*
            if (isAlpha)
            {
                buff.setAlphaBlending();
                buff.drawAlpha(ImgOrigen,dx,dy);
            }
            else 
            */
            buff.draw(ImgOrigen,dx,dy);
			
			li_by += op.StepY;
		}
		li_bx += op.StepX;
	}	
}

bool TMAGameMap::setMapFile(const char *filename,const TMAString& basedir)
{
    if (ib_iniciado) clear();
    is_FileName = basedir;
    is_FileName = is_FileName + filename;
    is_BaseDir = basedir;
    FILE *f = fopen(*is_FileName,"rb");
    if (!f) return false;
    ib_iniciado = readFromFile(f);
    fclose(f);
    return ib_iniciado;
}

bool TMAGameMap::readFromFile(FILE *f)
{
	int li_bancos;
	
	// Saltamos la cabecera..
	//
	seekTo(f,0x20);
	
	// Leemos los datos del mapa
	//
	ScreenX = get2BWord(f);
	ScreenY = get2BWord(f);
	TilesAX = get2BWord(f);
	TilesAY = get2BWord(f);
	
	int lr = getByte(f);
	int lg = getByte(f);
	int lb = getByte(f);
	getByte(f); // Despreciamos el 1º byte del color de fondo.
	
	ColorFondo = MAKERGBCOLOR(lr,lg,lb);
	get4BWord(f);	// Color del GRID que se ignora.
	BitMask = getByte(f); // Numero de Máscaras
	get4BWord(f); // Offset de las Mascaras, que se ignora.
	li_bancos = get2BWord(f);
		
	// Ahora cargamos los bancos graficos, pero buscamos primero el indice
	// del mayor de los bancos
	//
	int l_offset1 = getCurrentOffset(f);
	int li_maxbank=0,li_aux;

	for(int li_i=0;li_i<li_bancos;li_i++)
	{
		// Saltamos el nombre del banco.
		//
		seekTo(f,getCurrentOffset(f)+80);

		// Leemos el ID del Banco
		//
		li_aux = get2BWord(f);
		if (li_maxbank < li_aux) li_maxbank = li_aux;

		// Saltamos el Offset
		//
		seekTo(f,getCurrentOffset(f)+4);
	}

	// Volvemos al lugar donde comienzan a definirse los bancos.
	//
	seekTo(f,l_offset1);

	if (li_bancos>0)
	{
        iv_Bancos.redim(li_maxbank+1);
        iv_Bancos.fillEmpty(li_maxbank+1);
        
		for (int li_i=0;li_i<li_bancos;li_i++)
		{
			PMAGraphBank tb = new TMAGraphBank();
			tb->is_basedir = (is_BaseDir.length()==0)?NULL:is_BaseDir.text();
			if (!tb->readFromFile(f))
			{
                delete tb;
                clear();
                return false;
            }
            iv_Bancos.replaceElementAt(tb,tb->BankID);
            
		}
	}
	
	// Leemos el numero de pantallas que hay.
	//
	int li_pantallas = get2BWord(f);
	
	// Ahora leemos la información de las pantallas
	//		
	for (int li_i=0;li_i<li_pantallas;li_i++)
	{
        PMAScreenIndex scr = new TMAScreenIndex();
        iv_Screen.addElement(scr);
		scr->name = getString(f,32).trim();
		scr->id = get2BWord(f);
		scr->offset = get4BWord(f);
	}
	return true;
}


PMAScreenMap TMAGameMap::getScreen(int id)
{
    long ll_offset=0;
    if (!ib_iniciado) return NULL;
    
    // Localizamos el offset de la pantalla dentro del fichero.
    //
    for (int li_i=0;li_i<iv_Screen.size();li_i++)
    {
        PMAScreenIndex oscr = (PMAScreenIndex)iv_Screen.elementAt(li_i);
    	if (oscr->id == id)
    	{
    		ll_offset = oscr->offset;
    		break;
    	}
    }
    
    // No se encuentra la pantalla indicada
    //
    if (ll_offset == 0) return NULL;
    
    FILE *f = fopen(*is_FileName,"rb");
    if (!f) return NULL;
    seekTo(f,ll_offset);

    PMAScreenMap scr = new TMAScreenMap(id);   
    if (!scr->readFromFile(f))
    {
        delete scr;
        TMAGame::showAlert("TMAGameMap: Error cargado TMAScreenMap en getScreen().");
        return NULL;
    }
    
    // Actualizamos la información sobre máscaras en la pantalla
	scr->_GetMask_width  = scr->MaskCol;
	scr->_GetMask_height = scr->MaskRow;
	scr->_GetMask_lbits = nBits(BitMask);
	scr->_GetMask_mask = nBitsMask(scr->_GetMask_lbits);

    fclose(f);
    return scr;	
}

const PMAGraphBank TMAGameMap::getGraphBank(int index)
{
	if (!ib_iniciado) return NULL;
	return (PMAGraphBank)iv_Bancos.elementAt(index);
}

const PMAImageBank TMAGameMap::getImageBank(int index)
{
    PMAGraphBank gb = getGraphBank(index);
    if (gb!=NULL) return gb->getImageBank();
    return NULL;
}

bool TMAGameMap::createBufferForFastDrawing(int width,int height)
{
    if (io_FastBuffer!=NULL)
    {
        delete io_FastBuffer;
        io_FastBuffer=NULL;
    }
    io_FastBuffer = TMABitmap::create(width,height,false);
    return (io_FastBuffer!=NULL);
}
        

void TMAGameMap::drawFastBuffer(const PMAScreenMap scr,int ColorBack)
{
	if (io_FastBuffer==NULL) return;
	io_FastBuffer->clear(ColorBack);
	drawScreenGraphOperations(*io_FastBuffer,scr,TMAGraphOperation::OP_NORMAL);
}

void TMAGameMap::drawScreenGraphOperations(TMABitmap& buff,const PMAScreenMap scr,int tipo)
{
	TMAVector& v=scr->getGraphicsOperationsForType(tipo);
	for (int li_i=0;li_i<v.size();li_i++)
	{
		PMAGraphOperation go = (PMAGraphOperation)v.elementAt(li_i);
        if (go) drawGraphOperation(buff,*go);
	}		
}

void TMAGameMap::animateGraphOperations(const PMAScreenMap scr,int tipo)
{
	bool lb_anim=(tipo == TMAGraphOperation::OP_ANIM_FRONT ||
	              tipo == TMAGraphOperation::OP_ANIM_NORMAL);
    if (!lb_anim) return;

	TMAVector& v=scr->getGraphicsOperationsForType(tipo);

	for (int li_i=0;li_i<v.size();li_i++)
	{
		PMAGraphOperation go = (PMAGraphOperation)v.elementAt(li_i);

		if (lb_anim)
		{
			TMAGraphAnimation& lanim = *((PMAGraphAnimation)go);

			if (lanim.a_PauseFrame<lanim.PauseFrame)
			{
				lanim.a_PauseFrame ++;
			}
			else
			{
				lanim.a_PauseFrame = 0;

				if (!lanim.a_Down && lanim.a_CurFrame < lanim.EndFrame)
				{
					lanim.a_CurFrame ++;
				}
				else if (lanim.a_Down && lanim.a_CurFrame > lanim.InitFrame)
				{
				    lanim.a_CurFrame --;
				}
				else
				{
				    if (lanim.PingPong)
					{
				    	if (lanim.a_PauseAnim >= lanim.PauseAnim)
						{
						    lanim.a_PauseAnim = 0;
                            lanim.a_Down = (!lanim.a_Down);
						}
						else lanim.a_PauseAnim ++;
					}
					else
					{
						if (lanim.a_PauseAnim >= lanim.PauseAnim)
						{
						    lanim.a_CurFrame = lanim.InitFrame;
						    lanim.a_PauseAnim = 0;
					    }
						else lanim.a_PauseAnim ++;
					}
				}
			}
			lanim.TileID = lanim.a_CurFrame;
		}
	}
}

void TMAGameMap::drawScreen(TMABitmap& buff,const PMAScreenMap scr,bool use_fast_buffer)
{
	if (use_fast_buffer && io_FastBuffer!=NULL)
	{
		buff.draw(io_FastBuffer,0,0);
	}
	else
	{
		drawScreenGraphOperations(buff,scr,TMAGraphOperation::OP_NORMAL);
	}
	drawScreenGraphOperations(buff,scr,TMAGraphOperation::OP_FRONT);
	drawScreenGraphOperations(buff,scr,TMAGraphOperation::OP_ANIM_NORMAL);
	drawScreenGraphOperations(buff,scr,TMAGraphOperation::OP_ANIM_FRONT);
}


#endif
