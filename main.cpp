#include <allegro.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define PI 3.141592654



void init();
void deinit();
static clock_t t_ini, t_fin;
double tiempo;
void dibujarCirculoPolar(int r, int xc, int yc);
void dibujarCirculoBresenham(int r, int xc, int yc);
void dibujarLineaBresenham(int x0, int y0, int x1, int y1);
void dibujarLineaDDA(int x0, int y0, int x1, int y1);

double toRadians(int r, int xc, int yc);
void dibujarPixel(int x, int y);

/* Imprime el menu principal de la aplicacion */
void menu(){
	 
	 clear_to_color(screen, 0x000000);
 	 textout_ex(screen, font, "ALGORITMOS PARA DIBUJAR PRIMITIVAS" , 200, 50, 0xFFFFFF, 0x000000);
   	 textout_ex(screen, font, "1.Linea DDA" , 150, 100, 0xFFFFFF, 0x000000);
   	 textout_ex(screen, font, "2.Linea Bresenham" , 150, 130, 0xFFFFFF, 0x000000);
   	 textout_ex(screen, font, "3.Circulo Polar" , 150, 160, 0xFFFFFF, 0x000000);
   	 textout_ex(screen, font, "4.Circulo Bresenham" , 150, 190, 0xFFFFFF, 0x000000);   
   	 textout_ex(screen, font, "PRESIONE LA TECLA ESC PARA SALIR" , 200, 300, 0xFFFFFF, 0x000000);	 
   	 textout_ex(screen, font, "<<  Computacion grafica Unimag 2014-I  >>" , 15, 430, 0xFFFFFF, 0x000000);	
  	 rest(200);
}
int main() {
	init(); 
    
	while (!key[KEY_ESC]) {
		menu(); //se imprime el menu y se espera un golpe de tecla
				//que indique el paso a una opcion, o la salida del programa.
		int x0=0,x1=0,y0=0,y1=0;
		bool listo = false, presionado = false; //variables para manejar el raton
		
		if(key[KEY_1]){ //si presiona 1, se ejecuta el algoritmo de linea DDA
			clear(screen);			
			while(!key[KEY_ENTER]){	
					textout_ex(screen, font, "Mantenga pulsado el boton del raton y suelte en la posion final" , 100, 10, 0xFFFFFF, 0x000000);										
			    /* cuando presiona el boton izquierdo del mouse se captura la posicion inicial */
				    if(mouse_b & 1 && presionado == false){
						x0= mouse_x;
						y0 = mouse_y;
						presionado = true;
					}
				/* cuando suelta el boton se captura la posicion final */	
					if(!mouse_b & 1 && presionado == true){						
						x1= mouse_x;
						y1 = mouse_y;
						presionado = false;
						listo = true;						
					}
					if(listo){ /*despues que indique la trayectoria se pasan los parametros a la funcion encargada de ejecutar
								el algoritmo */
						t_ini = clock();
						dibujarLineaDDA(x0,y0,x1,y1);						
						t_fin = clock();
        				tiempo = t_fin - t_ini;
						
						textout_ex(screen, font, "Presione la tecla Enter para regresar al menu " , 140, 450, 0xFFFFFF, 0x000000);
						textprintf(screen, font , 30, 50, makecol(255,255,255), "TIEMPO: %e ms",tiempo);   
						listo = false;
					}										 
			}
			
		}
		if(key[KEY_2]){//si presiona 2, se ejecuta el algoritmo de bresenham para lineas
			clear(screen);			
			while(!key[KEY_ENTER]){		
					textout_ex(screen, font, "Mantenga pulsado el boton del raton y suelte en la posion final" , 100, 10, 0xFFFFFF, 0x000000);			
				    if(mouse_b & 1 && presionado == false){
						x0= mouse_x;
						y0 = mouse_y;
						presionado = true;
					}
					
					if(!mouse_b & 1 && presionado == true){						
						x1= mouse_x;
						y1 = mouse_y;
						presionado = false;
						listo = true;						
					}
					if(listo){						
						t_ini = clock();
						dibujarLineaBresenham(x0,y0,x1,y1);						
						t_fin = clock();
        				tiempo = t_fin - t_ini;
						textout_ex(screen, font, "Presione la tecla Enter para regresar al menu" , 140, 450, 0xFFFFFF, 0x000000);
						textprintf(screen, font , 30, 50, makecol(255,255,255), "TIEMPO: %e ms",tiempo);   
						listo = false;
					}										 
			}
		}
		if(key[KEY_3]){//si presiona 2, se ejecuta el algoritmo Polar para cincunferencias
			listo = true;
			clear(screen);
			while(!key[KEY_ENTER]){									
					if(listo){
						t_ini = clock();
						dibujarCirculoPolar(50, 100, 200);	//se llama a la funcion con parametros por defecto
						t_fin = clock();
	        			tiempo = t_fin - t_ini;
						
						textout_ex(screen, font, "Presione la tecla Enter para regresar al menu" , 140, 450, 0xFFFFFF, 0x000000);
						textprintf(screen, font , 30, 50, makecol(255,255,255), "TIEMPO: %e ms",tiempo);   
						listo = false;	
					}
					
							
			}
		
		}	
		if(key[KEY_4]){//si presiona 2, se ejecuta el algoritmo de bresenham para cincunferencias
			clear(screen);
			listo = true;
			while(!key[KEY_ENTER]){									
					if(listo){
						t_ini = clock();
						dibujarCirculoBresenham(80, 200, 200);	//se llama a la funcion con parametros por defecto
						t_fin = clock();
	        			tiempo = t_fin - t_ini;
	        
						textprintf(screen, font , 30, 50, makecol(255,255,255), "TIEMPO: %e ms",tiempo);   
						textout_ex(screen, font, "Presione la tecla Enter para regresar al menu" , 140, 450, 0xFFFFFF, 0x000000); 
						listo = false;
					}
				}
			}		
		}	
	
	deinit();
	return 0;
}
END_OF_MAIN()
/* 
	Este metodo inicializa todos los componentes de allegro para la ejecucion
	del programa, la pantalla, la ventanta, el mouse y el teclado.
*/
void init() {	
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	//detecta drivers de video automaticamente
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	show_mouse(screen);
}

void deinit() {//se libera memoria
	clear_keybuf();
}
//funcion para convertir de grados a radianes
double toRadians(int grados){
    	return grados*PI/180;
}
/* esta funcion facilita el dibujado del pixel, automatizando 
   el ingreso del la superfice de destino (pantalla) y el color
*/
void dibujarPixel(int x, int y){ 
   putpixel(screen, x , y, makecol(255,255,255));
}

/************** ALGORITMOS PARA PRIMITIVAS **********************/
/*****************************************************************/

void dibujarCirculoBresenham(int r, int xc, int yc) {		
        // Punto inicial del círculo
        int x = 0;
        int y = r;
        // Cálcular el parámetro inicial de decisión
        int pk = 1-r;
        
        // verificar el pk para determinar las posiciones de pixel siguuientes
        
        while (x<=y)
        {
            dibujarPixel( xc+x,yc+y);            
            dibujarPixel( xc-x,yc+y); 
            dibujarPixel( xc+x,yc-y);            
            dibujarPixel( xc-x,yc-y); 			
            dibujarPixel( yc+y,xc+x);            
            dibujarPixel( yc-y,xc+x);    
            dibujarPixel( yc+y,xc-x);            
            dibujarPixel( yc-y,xc-x);            
            
            if (pk<0){
                pk+=2*(x+1)+1;
                x++;
            }
            else // pk>=0
            {
                pk+=2*(x+1)+1 - 2*(y-1);
                x++;
                y--;
            }
        }
        
    }
 void dibujarCirculoPolar(int r, int xc, int yc) { 		
 		
        // Determinar el angulo de variaci?n
        double theta = toRadians(0);
        // Punto inicial
        int x = r;
        int y = 0;
        // Mientras el angulo no exceda a 360 dibujar puntos
        while (theta <= 2*PI) {
        	dibujarPixel(x+xc,y+yc);
            // Incrementar el ?ngulo
            theta += toRadians(1);
            // C?lcular los valores x e y de forma par?metrica
            double xd = r *cos(theta);
            x = (int) floor(xd);
            double yd = r * sin(theta);
            y = (int) floor(yd);            
        }
    }


//se modifico para que aceptara cualquier pendiente
void dibujarLineaDDA(int x0, int y0, int x1, int y1)
{
	        int dx = x1 - x0;
	        int dy = y1 - y0;
	
	        if (abs(dx) > abs(dy)) {          // pendiente < 1
	            float m = (float) dy / (float) dx;
	            float b = y0 - m*x0; 
	            if(dx<0)
	                dx =  -1;
	            else
	                dx =  1;
	            while (x0 != x1) {
	                x0 += dx;
	                y0 = round(m*x0 + b); //calcula con la ecuacion de la recta
	                dibujarPixel(x0,y0);	                
	            }
	        } else
	        if (dy != 0) {                              // pendiente >= 1
	            float m = (float) dx / (float) dy;      
	            float b = x0 - m*y0;
	            if(dy<0)
	                dy =  -1;
	            else
	                dy =  1;
	            while (y0 != y1) {
	                y0 += dy;
	                x0 = round(m*y0 + b);
	                dibujarPixel(x0,y0);//calcula con la ecuacion de la recta	                
	            }
	        }
}
//se modifico para que aceptara cualquier pendiente
void dibujarLineaBresenham(int x0, int y0, int x1, int y1)
{
	int x, y, dx, dy, p, sigX, sigY;
	  dx = (x1 - x0);
	  dy = (y1 - y0);
	/* determinar que punto usar para empezar, cual para terminar */
	  if (dy < 0) { 
	    dy = -dy; 
		sigY = -1; 
	  } 
	  else{
	  	sigY = 1;
	  }
	    
	    
	  if (dx < 0) {  
	    dx = -dx; 
		sigX = -1; 
	  } 
	  else {
	  	sigX = 1;
	  }
	    
	    
	  x = x0;
	  y = y0;
	   
	/* se cicla hasta llegar al extremo de la línea */
	  if(dx>dy){
	    p = 2*dy - dx;;
	    while (x != x1){
		      x = x + sigX;
		      if (p < 0){
		        p = p + (2*dy);
		      }
		      else {
		        y = y + sigY;
		        p = p + (2*(dy-dx));
		      }
		      dibujarPixel(x,y);
		      
	    }
	  }
	  else{
	    p = 2*dx - dy;
	    while (y != y1){
		      y = y + sigY;
		      if (p < 0){
		        p = p + 2*dy;
		      }
		      else {
		        x = x + sigX;
		        p = p + 2*(dy-dx);
		      }
	    	  dibujarPixel(x,y);	    	 
	    }
	  }
}


