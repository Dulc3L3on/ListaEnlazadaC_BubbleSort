#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Persona{
    int CUI;
    char nombre[30];
    int edad;
};

struct Nodo{    
    struct Nodo *nodoSiguiente;
    struct Persona elementoPersona; //aquí tendría que almacenar la ubicación del "objeto persona"... no, no debe ser la dirección pues no requiere ser un apuntador...
};

struct ListaEnlazada{
    struct Nodo *primerNodo;//estos serán apuntadores por el hecho de que, solo requiero hacer alamcenar la dirección de lo que ya se creó, para hacer referencia...
    struct Nodo *ultimoNodo;
    int tamanioLista;   
};//podrías haber inicializado la var aquí, pero como no se requiere un dato en especifico, entonces mejor abajito xD, así como lo dejé anoche xD

/*struct Nodo *primerNodo;
struct Nodo *ultimoNodo;
int tamanioLista = 0;*/

void anadirAlFinal(struct Persona persona);
struct Persona crearPersona();
int solicitarCodigo();
void buscarAPersona(int codigoUnico);
void eliminarAPersona(int codigoUnico);
void mostrarElementosLista();

struct ListaEnlazada listaDePersonas;//te falta inicializar la lista... eso mañanita xD descansa :)zZZZZ

void anadirAlFinal(struct Persona persona){//persona en este punto ya posee contenido, puesto que lo recibirá directamente de lo ingreado por el usuario
    if(&listaDePersonas!=NULL){//aunque esto no tendŕia que suceder nunca porque yo la inicializo antes de que se muentre el menú para exe las opciones xD y por lo tanto la dirección de la lista debería tener mas de algun dato que corresponda a una dirección xD
        if(listaDePersonas.tamanioLista == 0){
            listaDePersonas.primerNodo = malloc(sizeof(struct Nodo));//la "instacia del nodo"
            listaDePersonas.ultimoNodo = listaDePersonas.primerNodo;//la instancia del primer nodo

            listaDePersonas.primerNodo->elementoPersona = persona;//no coloco al úlimo, porque apunta a a misma dirección que el primero...
        }else{//me parece que quizá hubiera sido necesario solamente hacer al último nodo = al nuevo... pues de todos modos su siguiente cb a nulo xD [tal y como sucede al hacer esto...]
            listaDePersonas.ultimoNodo = listaDePersonas.ultimoNodo->nodoSiguiente = malloc(sizeof(struct Nodo));//instacia del nodo nuevo, no de un puntero de tipo nodo!!! esto es así porque requiero almacenar datos en el nodo y eso no lo podría hacer en el apuntador, pues este sólo almacena direcciones!!!
            listaDePersonas.ultimoNodo->elementoPersona = persona;//debe ser el struct persona como tal, pues en el Nodo, el elePersona es un struct "normal" y no un apuntador struct
        }//o bien lo que podrías haber hecho es crear un nodo temporal en el que posea el nuevo contenido y que a ese se le agregue como siguiente lo que se tenía enlzadco con anterioridad, de tal manera que no haya que estar revisando si es la primer inserción o no xD y que el primer elemento insertado pase a ser el último y por ello la cabeza tega la dir del último insertado, el cual sería el primero en la lista xD

        listaDePersonas.tamanioLista++;
        printf("\t--Se ha añadido correctamente a %s al listado--\n", persona.nombre);
        return;
    }
    printf("NO existe una lista en la cual añadir");
    return;
}//Sin el último nodo lo que tendrías que hacer es: colocar el if para cuando no tenga elementos y además colocar un for [en lugar de un while, que mientras la posición < tamLista se acceda al siguiente nodo en el cuerpo del for, para que así cuando se encuentre que es igual, se haga la asignación al nodo nulo para darle un valor diferente a él y así se agregue el elemento al final... actuando de esta manera el for, me hace pensar que no debería colocar el if[para el primer elemento] porque de todos modos no se invoaría al siguiente de un nulo, porque no se entraría al cuerpo del for por el hecho de que 0 no es < 0 y se haría la asignación como con todos los demás xD...]

struct Persona crearPersona(){
    struct Persona persona;

    printf("Ingrese el nombre de la persona a añadir: ");
    scanf("%s", persona.nombre);
    printf("Ingrese el código de %s: ", persona.nombre);
    scanf("%d", &persona.CUI);//pues el scanf requiere una dirección de memoria para almacenar los datos en ella... [es decir la var en sí xD]    
    printf("Ahora ingrese la edad de %s: ", persona.nombre);
    scanf("%d", &persona.edad);//suponiendo que no hay errores xD

    return persona;
}

int solicitarCodigo(){
    printf("Ingrese el código a buscar: ");
    int codigo;
    scanf("%d", &codigo);
    return codigo;
}

void buscarAPersona(int codigoUnico){
    struct Nodo *nodoAuxiliar = listaDePersonas.primerNodo;//pues para que tendría que tendría que colocar en otro espacio, algo que ya ocupa un espacio xD, por eso mejor hago referencia xD y no coloco el &, pues el primer nodo es un puntero, por lo cual el valor por default que dará es una dirección xD
    int hallado=0;

    if(&listaDePersonas != NULL && listaDePersonas.tamanioLista>0){
        for (int elementoActual = 0; elementoActual < listaDePersonas.tamanioLista; elementoActual++)
        {
            if(nodoAuxiliar->elementoPersona.CUI == codigoUnico){//a mi pensar si debería colocar el * , pues lo que quiero no es la dirección sino el valor del nodoAuxiliar... en este caso el de elementoPersona
                printf("     --Se ha encontrado a %s con el codigo %d especificado--\n", nodoAuxiliar->elementoPersona.nombre, nodoAuxiliar->elementoPersona.CUI);//pues así obtengo el contenido[el Nodo] de la dirección de memoria [a la que puede hacer ref] que a su vez contiene dentro de sí a la Persona                                
                hallado++;                
            }

            nodoAuxiliar = nodoAuxiliar->nodoSiguiente;//aquí podría decir que: el valor de la dirección que alamacena el puntero ahora sea = al siguiente ó que la dirección del apuntador ahora sea la del siguiente [usaré la segunda xD, pra el caso de un alista 2blemente enlazada, yo diría que si tendría que usarse la primera opción, por el hecho de que podrías, por la naturaleza de la lista, hacer que se se tenga que llegar a un nodo anterior... pero pensándolo bien, daría lo mismo, porque en cualquiera de los casos, no perdería la referencia a los nodos que se "dejaron atrás"]
        }//no coloqué el & porque nodoSig es un puntero, por lo tanto el valor que devolverá por default, será una dirección
        if(hallado ==0){
            printf("    --No se encontró a la persona--\n");//Ahí buscas si a un struct se le puede hacer null... yo creo que no xD
        }else{
            printf("\t\t\t\tcoincidencias halladas %d: \n", hallado);
        }    
        return;            
    }           
    printf("\t--Listado vacío, nada que buscar--\n");
}


void eliminarAPersona(int codigoUnico){//para ahorrarte el tener que estar pasando cada vez la lista como argumento, podrías haberla hecho global para aśi hacer referencia a la varibale que le representa, sin problemas xD
    if(&listaDePersonas!=NULL && listaDePersonas.tamanioLista>0){
        struct Nodo *nodoAuxiliar = listaDePersonas.primerNodo;//por lo que mencione arriba del default de retorno de los punteros, el & no debería estar aquí, pues 1er nodo es un puntero, así que tb app para él...
        
        if(nodoAuxiliar->elementoPersona.CUI == codigoUnico){
            //limpio l auibcación y pierdo la referencia...
            printf("  --Se ha eliminado correctamente a %s que poseia el codigo %d especificado--\n", nodoAuxiliar->elementoPersona.nombre ,nodoAuxiliar->elementoPersona.CUI);
            listaDePersonas.primerNodo = nodoAuxiliar->nodoSiguiente;//no habrá problema si este aún no tiene nada, es decir si es null el siguiente, pues al insertar se verá el tamabño y con eso se arreglará el probelma xD
            free(nodoAuxiliar);
            //no ahgo el nodo = null porque lo que se revisa es el tamaño de la lista...
            listaDePersonas.tamanioLista--;
            return;
        }else{
            for (int elementoActual = 1; elementoActual < listaDePersonas.tamanioLista; elementoActual++)//o podría ser 0 y eleAct < tamList -1
            {
                    if(nodoAuxiliar->nodoSiguiente->elementoPersona.CUI == codigoUnico){
                        //limpio la ubicación y pierdo la referencia 
                        struct Nodo *nodoAEliminar = nodoAuxiliar->nodoSiguiente;//se hace con un puntero porque de esa manera se le dirá a C que se libere la dirección, pues este solo almacena direcciones...
                        printf("  --Se ha eliminado correctamente a %s que poseia el codigo %d especificado--\n", nodoAEliminar->elementoPersona.nombre ,nodoAEliminar->elementoPersona.CUI);
                        nodoAuxiliar->nodoSiguiente = nodoAuxiliar->nodoSiguiente->nodoSiguiente;//lo puedo hacer así porque noSig y nodAux son ambos, punteros...
                        free(nodoAEliminar);//Se limpia los datos de la dirección que tenía almacenada xD  
                        if(elementoActual == (listaDePersonas.tamanioLista-1)){
                            listaDePersonas.ultimoNodo = nodoAuxiliar;//pues así se podrá hacer bien la inserción después de esto xD y si fuera de 2, volvería a apuntar al mismo lugar que al primer nodo, lo cual era lo que hacía al insertar el primero xD
                        }                      
                        listaDePersonas.tamanioLista--;
                        return;//podría quitarlo para hacer que se eliminen todos los que tengan el código, tal y como se hizo para mostrar el método buscar (con todas las coincidencias xD)
                    }
                    nodoAuxiliar = nodoAuxiliar->nodoSiguiente;//Recuerda, el & no se pone porque el valor por defecto que devuelve el puntero es una dirección xD
            }
        }     
        printf("\t--NO se halló ningún codigo = %d--\n", codigoUnico);   
        return;//es decir que no se encontró el dato, ya sea porque no tenía nada la lista o porque de verdad no está xD
    }           
    printf("    --El listado está vacío, nada que eliminar--\n");//Este será para cuando la lista no posee nada [por el hecho de ser null]    
}

void mostrarElementosLista(){//también podrías haber colocado un número para que vean solo cierta cantidad, pero si por el hecho de que podrían colocar un número > a los existentes, tendrías que hacer algo para evitarlo xD, sino tronitos xD
    if(listaDePersonas.tamanioLista ==0){
        printf("    --Lista vacía, nada que mostrar--\n");
        
    }else{
        struct Nodo *nodoAuxiliar = listaDePersonas.primerNodo;
        
        printf("No.\tCodigo\t\tNombre\t  Edad\n");
        printf(">>>>>>>>>>>>>>>>>>>>----ooo----<<<<<<<<<<<<<<<<<<<<\n");
        for (int elementoActual = 0; elementoActual < listaDePersonas.tamanioLista; elementoActual++)
        {
            printf("%d\t%d\t\t%s\t  %d\n", elementoActual+1, nodoAuxiliar->elementoPersona.CUI, nodoAuxiliar->elementoPersona.nombre, nodoAuxiliar->elementoPersona.edad);//si me da error por no haber colocado el * en el que el atrib es de tipo str entonces, es falso lo que había dicho de un puntero struct [es decir que "sabe" que posee atribs y por lo tanto no se debe add el * para obtenerlos...]

            nodoAuxiliar = nodoAuxiliar->nodoSiguiente;//lo hago así puesto que el nodoSig, es un puntero xD
        }
        printf("---------------------------------------------------\n\n");
    }     
}

int main(){    
    listaDePersonas.tamanioLista = 0;
    int opcion=-1;

    printf("\n\t\t\tBIENVENIDO");
    while(opcion!=0){//tambien hubiera podido ser un doWhile xD
        printf("\nQué desea realizar? :)\n\n");
        printf("1. Agregar personas\t\t");       
        printf("2. buscar personas\n");        
        printf("3. eliminar a personas\t\t");
        printf("4. ver las personas agregadas\n");
        printf("\t\t\t0. salir\n");
        
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            anadirAlFinal(crearPersona());
            break;
        case 2: 
            buscarAPersona(solicitarCodigo());//supondremos que no se le ocurre presionar 2 cuando no lo vea xD
            break;  
        case 3: 
            eliminarAPersona(solicitarCodigo());
            break;  
        case 4: 
            mostrarElementosLista();
            break;
        case 0:
            printf("Bye :), fue un placer xD\n");
            break;
        default:
            printf("el numero ingresado no pertenece a ninguna de las opciones\n");
            break;
        }
    }   

    return 0;
}


//en este caso así como en Java hubieras podido crear 3 arch "auxiliares" para el funcionamiento y el que tendría el main para la exe
//solo que los arch del nodo y persona solo contendrían los struct xD y el de la lista enlazada tendría el struct corresp y además 
//tendŕá los métodos que serían capaces de recibir una instacia del tipo que corresp al nombre del archivo, para así simular el que 
//Estas sean las anx de la instacia de la clase xD, si te da tiempo pruebas importar xD, si no pues entonces en un solo arch xD


//pasos a hacer en la exe
//crear el objeto lista, que será global para permitir la manipulación de lo que contiene, con mayor facilidad [esto solo lo harás una vez duh! :D xD]
//por cada inserción que se haga con la opción de crear, crearás una nueva instacia de persona y la mandarás de una vez al método añadirALFinal
//no mostrarás los elementos a menos que presione esa opción
