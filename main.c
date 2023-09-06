#include <stdio.h>
#include <stdlib.h>
#include<wchar.h>
#include<locale.h>
#include<time.h>
#include<unistd.h>
#include<string.h>

struct Libros{
    int referencia;
    char titulo[50];
    char autor[50];
    char editorial[50];
    int edicion;
    int publicacion;

    //Clase: Libro
};

struct Revistas{
    int referencia;
    char titulo[50];
    char autor[50];
    char editorial[50];
    char nombre[50];

    //Clase: Revista
};

int validarAnio(int anio) {
    // Verificar si el a�o tiene cuatro d�gitos
    if (anio >= 1000 && anio <= 9999) {
        return 1; // A�o v�lido
    } else {
        return 0; // A�o no v�lido
    }
}

int validarCodigo(int codigo) {
    // Verificar si el c�digo tiene exactamente cinco d�gitos
    if (codigo >= 10000 && codigo <= 99999) {
        return 1; // C�digo v�lido
    } else {
        return 0; // C�digo no v�lido
    }
}

int estaVacioLibros(struct Libros *libros, int cantLibros,int i) {
    if (libros[i].referencia != 0 ||
            strcmp(libros[i].titulo, "-") != 0 ||
            strcmp(libros[i].autor, "-") != 0 ||
            strcmp(libros[i].editorial, "-") != 0 ||
            libros[i].edicion != 0 ||
            libros[i].publicacion != 0) {
            return 0; // No est� vac�o
        }else{
            return 1; // Est� vac�o
        }
}

int estaVacioRevistas(struct Revistas *revistas, int cantRevistas, int i) {
        if (revistas[i].referencia != 0 ||
            strcmp(revistas[i].titulo, "-") != 0 ||
            strcmp(revistas[i].autor, "-") != 0 ||
            strcmp(revistas[i].editorial, "-") != 0 ||
            strcmp(revistas[i].nombre, "-") != 0) {
            return 0; // No est� vac�o
        }else{
            return 1; // Est� vac�o
        }

}

void InicializarCatalogo(struct Libros *libros, struct Revistas *revistas,int cantLibros, int cantRevistas){
    for (int i = 0; i < cantLibros; i++) {
        libros[i].referencia = 0;
        strcpy(libros[i].titulo, "-");
        strcpy(libros[i].autor, "-");
        strcpy(libros[i].editorial, "-");
        libros[i].edicion = 0;
        libros[i].publicacion = 0;
    }
    for (int i = 0; i < cantRevistas; i++) {
        revistas[i].referencia = 0;
        strcpy(revistas[i].titulo, "-");
        strcpy(revistas[i].autor, "-");
        strcpy(revistas[i].editorial, "-");
        strcpy(revistas[i].nombre, "-");
    }
}
void agregarCatalogo(struct Libros *libros, struct Revistas *revistas, int cantLibros, int cantRevistas){
    int j,i,op,anio;
    int totalElementos = cantLibros + cantRevistas;
    j = 1;

    //Crea un arreglo dependiendo la cantidad de libros para garantizar c�digos �nicos
    int *codigosLibros = (int *)malloc(cantLibros * sizeof(int));
    int *codigosRevistas = (int *)malloc(cantRevistas * sizeof(int));

    //Muestra el cat�logo de libros
    if (cantLibros > 0) {
        printf("Libros:\n");
        for (int i = 0; i < cantLibros; i++) {
            if(estaVacioLibros(libros,cantLibros,i)){
                printf("%d. Lugar disponible\n",i+1);
            }else{
                printf("%d. Lugar ocupado\n", i + 1);
            }

            j = j + 1;
        }
    }
    //Muestra el cat�logo de revistas
    if (cantRevistas > 0) {
        printf("\nRevistas:\n");
        for (int i = 0; i < cantRevistas; i++) {
            if(estaVacioRevistas(revistas,cantRevistas,i)){
                printf("%d. Lugar disponible\n",i+1 + cantLibros);
            }else{
                printf("%d. Lugar ocupado\n", i + 1 + cantLibros);
            }
            j = j + 1;
        }
    }
    puts("-----------------");
    printf("%d. Salir\n",j);
    puts("-----------------");
    printf("Elegir opci�n: ");
    scanf("%d",&op);
    while (op>j || op<1){
        puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        puts("Opci�n invalida, intente de nuevo...");
        puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        puts("-----------------");
        printf("Elegir opci�n: ");
        scanf("%d",&op);
    }

    if (op >= 1 && op <= totalElementos) {
        if (op <= cantLibros) {
            if (!estaVacioLibros(libros, cantLibros, op - 1)) {
                system("cls");
                puts("-----------------------------------------------------");
                puts("El lugar seleccionado ya est� ocupado por un libro...");
                puts("-----------------------------------------------------");
                system("pause");

            } else {
                // Inicializa los arreglos de c�digos
                for(int i = 0; i < cantLibros; i++) {
                    codigosLibros[i] = -1; // Valor inicial que no se repite
                }
                //Ingresar datos de los Libros
                for(int i = 0; i < cantLibros; i++) {
                    int codigo;
                    int codigoRepetido;
                    //Verifica que el c�digo de referencia sea �nico y diferente
                    do {
                        system("cls");
                        printf("Ingrese el n�mero de referencia del libro %d: ", op);
                        scanf("%d", &codigo);

                        while (!validarCodigo(codigo)) {
                            puts("--------------------------------------------");
                            puts("C�digo no v�lido (deben ser cinco d�gitos): ");
                            puts("--------------------------------------------");
                            system("pause");
                            system("cls");
                            printf("Ingrese el n�mero de referencia del libro %d: ", op);
                            scanf("%d", &codigo);
                        }
                        // Verificar si el c�digo ya existe
                        codigoRepetido = 0;
                        for(int j = 0; j < cantLibros; j++) {
                            if (libros[j].referencia == codigo) {
                                codigoRepetido = 1;
                                break;
                            }
                        }
                         for (int k = 0; k < cantRevistas; k++) {
                            if (revistas[k].referencia == codigo) {
                                codigoRepetido = 1;
                                break;
                            }
                        }

                        if (codigoRepetido) {
                            puts("----------------------------------------------------------------");
                            puts("Ese c�digo de referencia ya fue utilizado. Ingrese uno diferente");
                            puts("----------------------------------------------------------------");
                            system("pause");
                            system("cls");
                        } else {
                            libros[op - 1].referencia = codigo;
                            codigosLibros[op - 1] = codigo;
                        }
                    } while (codigoRepetido);

                    fflush(stdin);
                    printf("Ingrese el titulo del libro %d: ",libros[op - 1].referencia);
                    gets(libros[op - 1].titulo);
                    fflush(stdin);
                    printf("Ingrese el autor del libro %d: ",libros[op - 1].referencia);
                    gets(libros[op - 1].autor);
                    fflush(stdin);
                    printf("Ingrese el editorial del libro %d: ",libros[op - 1].referencia);
                    gets(libros[i].editorial);
                    printf("Ingrese el n�mero de edici�n del libro %d: ",libros[op - 1].referencia);
                    scanf("%d",&libros[op - 1].edicion);
                    printf("Ingrese el a�o de publicaci�n del libro %d: ",libros[op - 1].referencia);
                    scanf("%d",&anio);
                    while (!validarAnio(anio)) {
                            puts("---------------------------------------");
                            puts("A�o no v�lido(deben ser cuatro d�gitos)");
                            puts("---------------------------------------");
                            printf("Ingrese el a�o de publicaci�n del libro %d: ",libros[op - 1].referencia);
                            scanf("%d", &anio);
                        }
                    libros[op - 1].publicacion = anio;
                    puts("---------------------------------------");
                    system("pause");
                    return 0;
                }
            }
        }else{
            if (!estaVacioRevistas(revistas, cantRevistas, op - 1 - cantLibros)) {
                system("cls");
                puts("-----------------------------------------------------");
                puts("El lugar seleccionado ya est� ocupado por un libro...");
                puts("-----------------------------------------------------");
                system("pause");
            } else {
                for (int i = 0; i < cantRevistas; i++) {
                codigosRevistas[i] = -1; // Valor inicial que no se repite
                }
                //Ingresar datos de las Revistas
                for (int i = 0; i < cantRevistas; i++) {
                    int codigo;
                    int codigoRepetido;
                    //Verifica que el c�digo de referencia sea �nico y diferente
                    do {
                        system("cls");
                        printf("Ingrese el n�mero de referencia de la revista %d: ", op);
                        scanf("%d", &codigo);

                        // Verificar si el c�digo ya existe
                        codigoRepetido = 0;
                        for (int j = 0; j < cantLibros; j++) {
                            if (libros[j].referencia == codigo) {
                                codigoRepetido = 1;
                                break;
                            }
                        }
                        for (int j = 0; j < cantRevistas; j++) {
                            if (revistas[j].referencia == codigo) {
                                codigoRepetido = 1;
                                break;
                            }
                        }

                        if (codigoRepetido) {
                            puts("----------------------------------------------------------------");
                            puts("Ese c�digo de referencia ya fue utilizado. Ingrese uno diferente");
                            puts("----------------------------------------------------------------");
                            system("pause");
                            system("cls");
                        } else {
                            revistas[op - 1 - cantLibros].referencia = codigo;
                            codigosRevistas[op - 1 - cantLibros] = codigo;
                        }
                    } while (codigoRepetido);

                    fflush(stdin);
                    printf("Ingrese el titulo de la revista %d: ",revistas[op - 1 - cantLibros].referencia);
                    gets(revistas[op - 1 - cantLibros].titulo);
                    fflush(stdin);
                    printf("Ingrese el autor de la revista %d: ",revistas[op - 1 - cantLibros].referencia);
                    gets(revistas[op - 1 - cantLibros].autor);
                    fflush(stdin);
                    printf("Ingrese el editorial de la revista %d: ",revistas[op - 1 - cantLibros].referencia);
                    gets(revistas[op - 1 - cantLibros].editorial);
                    printf("Ingrese el nombre de la revista %d: ",revistas[op - 1 - cantLibros].referencia);
                    gets(revistas[op - 1 - cantLibros].nombre);
                    puts("---------------------------------------");
                    system("pause");
                    return 0;
                }
            }
        }
    }else if (op == j){
        return 0;
    }
}

void borrarCatalogo(struct Libros *libros, struct Revistas *revistas, int cantLibros, int cantRevistas){
    int i,j = 1, op;
    int totalElementos = cantLibros + cantRevistas;

    // Verificar si hay elementos en el cat�logo
    if (totalElementos == 0) {
        printf("El cat�logo est� vac�o.\n");
        return;
    }
    //Muestra el cat�logo de libros
    puts("-----------------");
    printf("Cat�logo:\n");
    puts("-----------------");
    //Muestra los libros
    if (cantLibros > 0) {
        printf("Libros:\n");
        for (int i = 0; i < cantLibros; i++) {
            if(estaVacioLibros(libros,cantLibros,i)){
                printf("%d. Lugar disponible\n",i+1);
            }else{
                printf("%d. %s\n", i + 1, libros[i].titulo);
            }

            j = j + 1;
        }
    }
    //Muestra el cat�logo de revistas
    if (cantRevistas > 0) {
        printf("\nRevistas:\n");
        for (int i = 0; i < cantRevistas; i++) {
            if(estaVacioRevistas(revistas,cantRevistas,i)){
                printf("%d. Lugar disponible\n",i+1 + cantLibros);
            }else{
                printf("%d. %s\n", i + 1 + cantLibros, revistas[i].titulo);
            }
            j = j + 1;
        }
    }
    puts("-----------------");
    printf("%d. Salir\n",j);
    puts("-----------------");
    printf("Elegir opci�n: ");
    scanf("%d",&op);
    while (op>j || op<1){
        puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        puts("Opci�n invalida, intente de nuevo...");
        puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        puts("-----------------");
        printf("Elegir opci�n: ");
        scanf("%d",&op);
    }
    if (op >= 1 && op <= totalElementos) {
        if (op <= cantLibros) {
            if (estaVacioLibros(libros, cantLibros, op - 1)) {
                system("cls");
                puts("----------------------------------------");
                puts("El lugar seleccionado ya estaba vacio...");
                puts("----------------------------------------");
                system("pause");
            } else {
                libros[op - 1].referencia = 0;
                strcpy(libros[op - 1].titulo, "-");
                strcpy(libros[op - 1].autor, "-");
                strcpy(libros[op - 1].editorial, "-");
                libros[op - 1].edicion = 0;
                libros[op - 1].publicacion = 0;
            }
        } else {
            if(estaVacioRevistas(revistas, cantRevistas, op - 1 - cantLibros)) {
                system("cls");
                puts("----------------------------------------");
                puts("El lugar seleccionado ya estaba vacio...");
                puts("----------------------------------------");
                system("pause");
            } else {
                revistas[op - 1 - cantLibros].referencia = 0;
                strcpy(revistas[op - 1 - cantLibros].titulo, "-");
                strcpy(revistas[op - 1 - cantLibros].autor, "-");
                strcpy(revistas[op - 1 - cantLibros].editorial, "-");
                strcpy(revistas[op - 1 - cantLibros].nombre, "-");
            }
        }
    }else if (op == j){
        return 0;
    }
}

void mostrarCatalogo(struct Libros *libros, struct Revistas *revistas,int cantLibros,int cantRevistas){
    int j = 1, op;
    int totalElementos = cantLibros + cantRevistas;

    // Verificar si hay elementos en el cat�logo
    if (totalElementos == 0) {
        printf("El cat�logo est� vac�o.\n");
        return;
    }
    //Muestra el cat�logo de libros
    puts("-----------------");
    printf("Cat�logo:\n");
    puts("-----------------");
    //Muestra los libros
    if (cantLibros > 0) {
        printf("Libros:\n");
        for (int i = 0; i < cantLibros; i++) {
            if(estaVacioLibros(libros,cantLibros,i)){
                printf("%d. Lugar disponible\n",i+1);
            }else{
                printf("%d. %d\n", i + 1, libros[i].referencia);
            }

            j = j + 1;
        }
    }
    //Muestra el cat�logo de revistas
    if (cantRevistas > 0) {
        printf("\nRevistas:\n");
        for (int i = 0; i < cantRevistas; i++) {
            if(estaVacioRevistas(revistas,cantRevistas,i)){
                printf("%d. Lugar disponible\n",i+1 + cantLibros);
            }else{
                printf("%d. %d\n", i + 1 + cantLibros, revistas[i].referencia);
            }
            j = j + 1;
        }
    }
    puts("-----------------");
    printf("%d. Salir\n",j);
    puts("-----------------");
    printf("Elegir opci�n: ");
    scanf("%d",&op);
    while (op>j || op<1){
        puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        puts("Opci�n invalida, intente de nuevo...");
        puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        puts("-----------------");
        printf("Elegir opci�n: ");
        scanf("%d",&op);
    }
    if (op >= 1 && op <= totalElementos) {
        if (op <= cantLibros) {
            if (estaVacioLibros(libros, cantLibros, op - 1)) {
                system("cls");
                puts("------------------------------------------------------");
                puts("El lugar seleccionado est� vacio, nada para mostrar...");
                puts("------------------------------------------------------");
                system("pause");
            } else {
                system("cls");
                printf("Informaci�n del libro seleccionado:\n");
                printf("Clase del cat�logo: Libro\n");
                printf("T�tulo: %s\n", libros[op - 1].titulo);
                printf("Autor: %s\n", libros[op - 1].autor);
                printf("Editorial: %s\n", libros[op - 1].editorial);
                printf("N�mero de edici�n: %d\n", libros[op - 1].edicion);
                printf("A�o de publicaci�n: %d\n", libros[op - 1].publicacion);
                puts("---------------------------------------");
                system("pause");
            }
        } else {
            if (estaVacioRevistas(revistas, cantRevistas, op - 1 - cantLibros)) {
                system("cls");
                puts("------------------------------------------------------");
                puts("El lugar seleccionado est� vacio, nada para mostrar...");
                puts("------------------------------------------------------");
                system("pause");
            } else {
                system("cls");
                printf("Informaci�n de la revista seleccionada:\n");
                printf("Clase del cat�logo: Revistas\n");
                printf("T�tulo: %s\n", revistas[op - 1 - cantLibros].titulo);
                printf("Autor: %s\n", revistas[op - 1 - cantLibros].autor);
                printf("Editorial: %s\n", revistas[op - 1 - cantLibros].editorial);
                printf("Nombre: %s\n", revistas[op - 1 - cantLibros].nombre);
                puts("---------------------------------------");
                system("pause");
            }
        }
    }else if (op == j){
        return 0;
    }
}

int main()
{
    int cantLibros, cantRevistas;
    int bandera;
    int op,iniciar;

    iniciar = 0;
    bandera = 0;

    setlocale(LC_ALL, "");
    srand(time(NULL));

    do{
        system("cls");
        puts("////////////////////");
        puts("//// Biblioteca ////");
        puts("////////////////////");
        puts("Men�: ");
        puts("1. Iniciar/Limpiar cat�logo");
        puts("2. Agregar libro/revista");
        puts("3. Eliminar libro/revista");
        puts("4. Mostrar cat�logo");
        puts("5. Salir");
        puts("-----------------");
        printf("Elegir opci�n: ");
        scanf("%d",&op);

        while (op>5 || op<1){
                puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                puts("Opcion no valida, intente de nuevo...");
                puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                printf("Opcion: ");
                scanf("%d",&op);
        }
        if(op==1){
                system("cls");
                puts("------------------------------------------");
                puts("�Atenci�n!");
                puts("Se eliminar�n todos los registros actuales");
                puts("------------------------------------------");
                puts("�Desea continuar?");
                puts("1. Si");
                puts("2. No");
                puts("-----------------");
                printf("Elegir opci�n: ");
                scanf("%d",&op);
                while(op>2 || op<1){
                    puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    puts("Opci�n invalida, intente de nuevo");
                    puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    printf("Elegir opci�n: ");
                    scanf("%d",&op);
                }
                if(op==2){
                    system("cls");
                    puts("Volviendo al men�...");
                    sleep(2);
                    op = 0;
                }
        }

        switch(op){
            case 1:
                system("cls");
                puts("Cargando cat�logo, espere...");
                sleep(2);
                system("cls");

                printf("Espacio disponible para Libros: ");
                scanf("%d",&cantLibros);
                puts("--------------------------------------");
                printf("Espacio disponible para Revistas: ");
                scanf("%d",&cantRevistas);

                //Crea un arreglo dinamico dependiendo los valores que ingres� el usuario
                struct Libros *libros = (struct Libros *)malloc(cantLibros * sizeof(struct Libros));
                struct Revistas *revistas = (struct Revistas *)malloc(cantRevistas * sizeof(struct Revistas));
                /////////////////////////////////////////////////////////////
                InicializarCatalogo(libros,revistas,cantLibros,cantRevistas);
                /////////////////////////////////////////////////////////////
                system("cls");
                puts("�C�talogo Iniciado/Limpiado con �xito!");
                puts("--------------------------------------");
                system("pause");
                iniciar = 1;
                break;
            case 2:
                system("cls");
                if(iniciar!=1){
                    puts("------------------------------");
                    puts("�Debe inicializar el catalogo!");
                    puts("------------------------------");
                    system("pause");
                }else{
                    agregarCatalogo(libros,revistas,cantLibros,cantRevistas);
                }
                system("cls");
                puts("Volviendo al men�...");
                sleep(2);
                break;
            case 3:
                system("cls");
                if(iniciar!=1){
                    puts("------------------------------");
                    puts("�Debe inicializar el catalogo!");
                    puts("------------------------------");
                    system("pause");
                }else{
                    borrarCatalogo(libros,revistas,cantLibros,cantRevistas);
                }
                system("cls");
                puts("Volviendo al men�...");
                sleep(2);
                break;
            case 4:
                system("cls");
                if(iniciar!=1){
                    puts("------------------------------");
                    puts("�Debe inicializar el catalogo!");
                    puts("------------------------------");
                    system("pause");
                }else{
                    mostrarCatalogo(libros,revistas,cantLibros,cantRevistas);
                }
                system("cls");
                puts("Volviendo al men�...");
                sleep(2);
                break;
            case 5:
                bandera = 1;
                break;
        }
    }while(bandera!=1);

    return 0;
}
