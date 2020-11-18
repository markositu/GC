#include "definitions.h"
#include "load_obj.h"
#include <GL/glut.h>
#include <stdio.h>

extern object3d * _first_object;
extern object3d * _selected_object;
extern camara *_selected_camara;

extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;
void  liberar_objeto(object3d *optr)
    
    {
        int i;
        for(i=0;i<optr->num_faces;i++)
        {
                free(optr->face_table[i].vertex_table);
                
        }
        free(optr->vertex_table);
        free(optr->face_table);
        free(optr);
    }
void undo(object3d *optr)
        {//optr->matriz=optr->matriz.prev;
        }
/**
 * @brief This function just prints information about the use
 * of the keys
 */

void print_help(){
    printf("KbG Irakasgaiaren Praktika. Programa honek 3D objektuak \n");
    printf("aldatzen eta bistaratzen ditu.  \n\n");
    printf("\n\n");
    printf("FUNTZIO NAGUSIAK \n");
    printf("<?>\t\t Laguntza hau bistaratu \n");
    printf("<ESC>\t\t Programatik irten \n");
    printf("<F>\t\t Objektua bat kargatu\n");
    printf("<TAB>\t\t Kargaturiko objektuen artean bat hautatu\n");
    printf("<DEL>\t\t Hautatutako objektua ezabatu\n");
    printf("<CTRL + ->\t Bistaratze-eremua handitu\n");
    printf("<CTRL + +>\t Bistaratze-eremua txikitu\n");
    printf("\n\n");
}

/**
 * @brief Callback function to control the basic keys
 * @param key Key that has been pressed
 * @param x X coordinate of the mouse pointer when the key was pressed
 * @param y Y coordinate of the mouse pointer when the key was pressed
 */ int modo=0;//traslación=0,rotación=1,escalado=2 
int global= 0;//local=0 global=1
int modoCamara=0;//objetos=0 camara=1
void specialKeyboard(int key, int x, int y) {
 char* fname = malloc(sizeof (char)*128); /* Note that scanf adds a null character at the end of the vector*/    
    lista_matrices* nuevaMatriz=(lista_matrices*)malloc(10*sizeof(lista_matrices));//crea un nuevo puntero a lista_matrices y reserva espacio
    if (_selected_object!=0){
    switch (key) {

     
     case GLUT_KEY_UP:
         
                
                 glMatrixMode(GL_MODELVIEW);
               
                 nuevaMatriz->pmptr=_selected_object->primera_matrizptr; //se hace que el puntero a siguiente Lista_matrices(pmptr) apunte a la lista_matrices actual
                 
                 
                   if(global==0)glLoadMatrixf(_selected_object->primera_matrizptr->matriz);//se carga en el Modelview la matriz actual
                    else glLoadIdentity();
                 
                 switch(modo){
                    case 0:
                    glTranslatef(0,0.5,0);
                    break;
                    case 1:
                    glRotatef(5,0.5,0,0);
                    break;
                    case 2:
                    glScalef(1,2,1);
                    break;
                    default:;
                 }
                if(global==1)glMultMatrixf(_selected_object->primera_matrizptr->matriz);
                 glGetFloatv(GL_MODELVIEW_MATRIX,nuevaMatriz->matriz);//guarda el resultado en la matriz nueva
                 _selected_object->primera_matrizptr=nuevaMatriz;//asigna al objeto la nueva matriz
                 
         
         
         glutPostRedisplay();
         break;
     case GLUT_KEY_DOWN:
        
                 glMatrixMode(GL_MODELVIEW);
                 nuevaMatriz->pmptr=_selected_object->primera_matrizptr; //se hace que el puntero a siguiente Lista_matrices(pmptr) apunte a la lista_matrices actual
                if(global==0)glLoadMatrixf(_selected_object->primera_matrizptr->matriz);//se carga en el Modelview la matriz actual
                    else glLoadIdentity();
                 switch(modo){
                    case 0:
                    glTranslatef(0,-0.5,0);//genera una matriz de transición y se lo multiplica a la matriz actual
                    break;
                    case 1:
                    glRotatef(5,-0.5,0,0);
                    break;
                    default:
                    glScalef(1,0.5,1);
                    break;
                 }
                 if(global==1)glMultMatrixf(_selected_object->primera_matrizptr->matriz);
                 glGetFloatv(GL_MODELVIEW_MATRIX,nuevaMatriz->matriz);//guarda el resultado en la matriz nueva
                 _selected_object->primera_matrizptr=nuevaMatriz;//asigna al objeto la nueva matriz
                 
          glutPostRedisplay();   
         break;
          case GLUT_KEY_LEFT:
         
         
                 glMatrixMode(GL_MODELVIEW);
                 nuevaMatriz->pmptr=_selected_object->primera_matrizptr; //se hace que el puntero a siguiente Lista_matrices(pmptr) apunte a la lista_matrices actual
                 if(global==0)glLoadMatrixf(_selected_object->primera_matrizptr->matriz);//se carga en el Modelview la matriz actual
                    else glLoadIdentity();
                 switch(modo){
                    case 0:
                    glTranslatef(-0.5,0,0);//genera una matriz de transición y se lo multiplica a la matriz actual
                    break;
                    case 1:
                    glRotatef(5,0,-0.5,0);
                    break;
                    default:
                    glScalef(0.5,1,1);
                    break;
                 }
                 if(global==1)glMultMatrixf(_selected_object->primera_matrizptr->matriz);
                 glGetFloatv(GL_MODELVIEW_MATRIX,nuevaMatriz->matriz);//guarda el resultado en la matriz nueva
                 _selected_object->primera_matrizptr=nuevaMatriz;//asigna al objeto la nueva matriz
                 
             
         
         
         glutPostRedisplay();
         break;
     case GLUT_KEY_RIGHT:

            
                   glMatrixMode(GL_MODELVIEW);
                   nuevaMatriz->pmptr=_selected_object->primera_matrizptr; //se hace que el puntero a siguiente Lista_matrices(pmptr) apunte a la lista_matrices actual
                    if(global==0)glLoadMatrixf(_selected_object->primera_matrizptr->matriz);//se carga en el Modelview la matriz actual
                    else glLoadIdentity();
                     switch(modo){
                    case 0:
                    glTranslatef(0.5,0,0);//genera una matriz de transición y se lo multiplica a la matriz actual
                    break;
                    case 1:
                    glRotatef(5,0,0.5,0);
                    break;
                    case 2:
                    glScalef(2,1,1);
                    break;
                    default:;
                    
                 }
                     if(global==1)glMultMatrixf(_selected_object->primera_matrizptr->matriz);
                     glGetFloatv(GL_MODELVIEW_MATRIX,nuevaMatriz->matriz);//guarda el resultado en la matriz nueva
                     _selected_object->primera_matrizptr=nuevaMatriz;//asigna al objeto la nueva matriz
                     
        glutPostRedisplay();  
         break;
         case GLUT_KEY_PAGE_UP:

                   glMatrixMode(GL_MODELVIEW);
                   nuevaMatriz->pmptr=_selected_object->primera_matrizptr; //se hace que el puntero a siguiente Lista_matrices(pmptr) apunte a la lista_matrices actual
                    if(global==0)glLoadMatrixf(_selected_object->primera_matrizptr->matriz);//se carga en el Modelview la matriz actual
                    else glLoadIdentity();
                     switch(modo){
                    case 0:
                    glTranslatef(0,0,0.5);//genera una matriz de transición y se lo multiplica a la matriz actual
                    break;
                    case 1:
                    glRotatef(5,0,0,0.5);
                    break;
                    case 2:
                    glScalef(1,1,2);
                    break;
                    default:;
                    
                 }
                     if(global==1)glMultMatrixf(_selected_object->primera_matrizptr->matriz);
                     glGetFloatv(GL_MODELVIEW_MATRIX,nuevaMatriz->matriz);//guarda el resultado en la matriz nueva
                     _selected_object->primera_matrizptr=nuevaMatriz;//asigna al objeto la nueva matriz
                     
        glutPostRedisplay();  
         break;
        case GLUT_KEY_PAGE_DOWN:
        glMatrixMode(GL_MODELVIEW);
                   nuevaMatriz->pmptr=_selected_object->primera_matrizptr; //se hace que el puntero a siguiente Lista_matrices(pmptr) apunte a la lista_matrices actual
                    if(global==0)glLoadMatrixf(_selected_object->primera_matrizptr->matriz);//se carga en el Modelview la matriz actual
                    else glLoadIdentity();
                     switch(modo){
                    case 0:
                    glTranslatef(0,0,-0.5);//genera una matriz de transición y se lo multiplica a la matriz actual
                    break;
                    case 1:
                    glRotatef(5,0,0,-0.5);
                    break;
                    case 2:
                    glScalef(1,1,0.5);
                    break;
                    default:;
                    
                 }
                     if(global==1)glMultMatrixf(_selected_object->primera_matrizptr->matriz);
                     glGetFloatv(GL_MODELVIEW_MATRIX,nuevaMatriz->matriz);//guarda el resultado en la matriz nueva
                     _selected_object->primera_matrizptr=nuevaMatriz;//asigna al objeto la nueva matriz
                     
        glutPostRedisplay();  
         break;
    default:
        /*In the default case we just print the code of the key. This is usefull to define new cases*/
        printf("%d %c\n", key, key);
    }
}
 
}






 // int modo=0;//traslación=0,rotación=1,escalado=2
void keyboard(unsigned char key, int x, int y) {

    char* fname = malloc(sizeof (char)*128); /* Note that scanf adds a null character at the end of the vector*/
    int read = 0;
    object3d *auxiliar_object = 0;
   
    
    GLdouble wd,he,midx,midy;
    
    lista_matrices* nuevaMatriz=(lista_matrices*)malloc(10*sizeof(lista_matrices));//crea un nuevo puntero a lista_matrices y reserva espacio
    camara* camaraDefault=(camara*)malloc(10*sizeof(camara));
    switch (key) {
    case 'b':
    case 'B':
    printf("Modo rotacion activado\n");
    modo=1;
    break;
    case 'm':
    case 'M':
    printf("Modo traslacion activado\n");
    modo=0;
    break;
     case 't':
    case 'T':
    printf("Modo escalado activado\n");
    modo=2;
    
    break;
     case 'g':
    case 'G':
    printf("Modo global activado\n");
    global=1;
    break;
      case 'l':
    case 'L':
    printf("Modo local activado\n");
    global=0;
    break;

    
    case 'k':
    case 'K':

    glLoadMatrixf(_selected_camara->matrizTransformaciones);
    glTranslatef(1,0,0);
    glGetFloatv(GL_MODELVIEW_MATRIX,_selected_camara->matrizTransformaciones);
    glLoadIdentity();
    glutPostRedisplay();


    break;
    case 'f':
    case 'F':
        /*Ask for file*/
        printf("%s", KG_MSSG_SELECT_FILE);
        scanf("%s", fname);
        /*Allocate memory for the structure and read the file*/
        auxiliar_object = (object3d *) malloc(sizeof (object3d));
        read = read_wavefront(fname, auxiliar_object);
        switch (read) {
        /*Errors in the reading*/
        case 1:
            printf("%s: %s\n", fname, KG_MSSG_FILENOTFOUND);
            break;
        case 2:
            printf("%s: %s\n", fname, KG_MSSG_INVALIDFILE);
            break;
        case 3:
            printf("%s: %s\n", fname, KG_MSSG_EMPTYFILE);
            break;
        /*Read OK*/
        case 0:
            /*Insert the new object in the list*/
            auxiliar_object->next = _first_object;
            _first_object = auxiliar_object;
            _selected_object = _first_object;
            //
            _selected_object->primera_matrizptr=(lista_matrices*)malloc(1000*sizeof(lista_matrices));// poner en documentación que solo se pueden hacer mil transformaciones
          
            glLoadIdentity();
            glGetFloatv(GL_MODELVIEW_MATRIX,_selected_object->primera_matrizptr->matriz);
            /*_selected_object->primera_matrizptr->matriz[12]=0;
            _selected_object->primera_matrizptr->matriz[13]=0;
            _selected_object->primera_matrizptr->matriz[14]=0;*/
           
            //
            printf("%s\n",KG_MSSG_FILEREAD);
            printf("Modo transformaciones activado\n");
            break;
        }
        break;

    case 9: /* <TAB> */
         if (_selected_object!=0){
        _selected_object = _selected_object->next;
    }
        /*The selection is circular, thus if we move out of the list we go back to the first element*/
        if (_selected_object == 0) _selected_object = _first_object;
        break;

    case 127: /* <SUPR> */
        /*Erasing an object depends on whether it is the first one or not*/
         if (_selected_object!=0){
        if (_selected_object == _first_object)
        {
            /*To remove the first object we just set the first as the current's next*/
            _first_object = _first_object->next;
            /*Once updated the pointer to the first object it is save to free the memory*/
            liberar_objeto(_selected_object);
            /*Finally, set the selected to the new first one*/
            _selected_object = _first_object;
        } 
        else {
            /*In this case we need to get the previous element to the one we want to erase*/
            auxiliar_object = _first_object;
            while (auxiliar_object->next != _selected_object)
                auxiliar_object = auxiliar_object->next;
            /*Now we bypass the element to erase*/
            auxiliar_object->next = _selected_object->next;
            /*free the memory*/
            liberar_objeto(_selected_object);
            /*and update the selection*/
            _selected_object = auxiliar_object;
        }
    }
        break;

    case '-':
     if (_selected_object!=0){
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
            /*Increase the projection plane; compute the new dimensions*/
            wd=(_ortho_x_max-_ortho_x_min)/KG_STEP_ZOOM;
            he=(_ortho_y_max-_ortho_y_min)/KG_STEP_ZOOM;
            /*In order to avoid moving the center of the plane, we get its coordinates*/
            midx = (_ortho_x_max+_ortho_x_min)/2;
            midy = (_ortho_y_max+_ortho_y_min)/2;
            /*The the new limits are set, keeping the center of the plane*/
            _ortho_x_max = midx + wd/2;
            _ortho_x_min = midx - wd/2;
            _ortho_y_max = midy + he/2;
            _ortho_y_min = midy - he/2;
        }
        else{
        glMatrixMode(GL_MODELVIEW);
                   nuevaMatriz->pmptr=_selected_object->primera_matrizptr; //se hace que el puntero a siguiente Lista_matrices(pmptr) apunte a la lista_matrices actual
                    if(global==0)glLoadMatrixf(_selected_object->primera_matrizptr->matriz);//se carga en el Modelview la matriz actual
                    else glLoadIdentity();
                     
                    
                    glScalef(0.8,0.8,0.8);
                    
                    
                 
                     if(global==1)glMultMatrixf(_selected_object->primera_matrizptr->matriz);
                     glGetFloatv(GL_MODELVIEW_MATRIX,nuevaMatriz->matriz);//guarda el resultado en la matriz nueva
                     _selected_object->primera_matrizptr=nuevaMatriz;//asigna al objeto la nueva matriz
                     
         
         
        
         
        }}
        break;

    case '+':
     if (_selected_object!=0){
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
            /*Increase the projection plane; compute the new dimensions*/
            wd=(_ortho_x_max-_ortho_x_min)*(KG_STEP_ZOOM);
            he=(_ortho_y_max-_ortho_y_min)*(KG_STEP_ZOOM);
            /*In order to avoid moving the center of the plane, we get its coordinates*/
            midx = (_ortho_x_max+_ortho_x_min)/2;
            midy = (_ortho_y_max+_ortho_y_min)/2;
            /*The the new limits are set, keeping the center of the plane*/
            _ortho_x_max = midx + wd/2;
            _ortho_x_min = midx - wd/2;
            _ortho_y_max = midy + he/2;
            _ortho_y_min = midy - he/2;
        }
        else{glMatrixMode(GL_MODELVIEW);
                   nuevaMatriz->pmptr=_selected_object->primera_matrizptr; //se hace que el puntero a siguiente Lista_matrices(pmptr) apunte a la lista_matrices actual
                    if(global==0)glLoadMatrixf(_selected_object->primera_matrizptr->matriz);//se carga en el Modelview la matriz actual
                    else glLoadIdentity();
                     
                    
                    glScalef(1.25,1.25,1.25);
                    
                    
                 
                     if(global==1)glMultMatrixf(_selected_object->primera_matrizptr->matriz);
                     glGetFloatv(GL_MODELVIEW_MATRIX,nuevaMatriz->matriz);//guarda el resultado en la matriz nueva
                     _selected_object->primera_matrizptr=nuevaMatriz;//asigna al objeto la nueva matriz
                     
         
         
        
         
        }}
        //INPLEMENTA EZAZU CTRL + + KONBINAZIOAREN FUNTZIOANLITATEA
        break;
   case 26://CTRL +Z
    if (_selected_object!=0){
        if (_selected_object->primera_matrizptr->pmptr!= NULL){
        _selected_object->primera_matrizptr=_selected_object->primera_matrizptr->pmptr;
      
         }
     }
   break;


    case '?':
        print_help();
        break;

    case 27: /* <ESC> */
        exit(0);
        break;
    

     
     
 
    default:
        /*In the default case we just print the code of the key. This is usefull to define new cases*/
        printf("%d %c\n", key, key);
    }  
    /*In case we have do any modification affecting the displaying of the object, we redraw them*/
    glutPostRedisplay();

}

