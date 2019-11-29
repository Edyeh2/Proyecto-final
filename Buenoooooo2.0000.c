#include <string.h> //Manipula las cadenas, copia, cambia caracteres y compara caracteres// 
#include <stdio.h>
#include <stdlib.h> //Gestiona la memoria dinamica y control de procesos//
#define Max 15
#define valor -1

struct equipo {
	int tipoe;
	int nserie;
	char marca[20];
	char modelo[20];
};
typedef struct equipo Equipo;
struct historico {
	int id;
	char motivo[80];
	char persat[80];
	char fecha[Max];
};
typedef struct historico Historico;
void menuPrincipal();
void menuInsertar();
void menuInsertarHistorial();
void menuBuscar();
void menuBuscarH();
void menuEliminar();
void menuMostrar();
void menuMostrarHistorial();
void menuModificar();
void menuModificarH();

Equipo *obtenerEquipos(int *n); 
Historico *obtenerEquiposH(int *n);
char existeEquipo(int nserie, Equipo *equipo);
char existeEquipot(int tipo, Equipo *equipo);
char existeEquipom(char marcae, Equipo *equipo);
char existeHistorial(int nserie, Historico *historico);
char existeFecha(char f[Max], Historico *historico);
char insertarEquipo(Equipo equipo);
char insertarHistorial(Historico historico);
char eliminar(int nserie);
char modificarEquipo(Equipo equipo);
char modificarHistorial(Historico historico);

int leecad(char *cad, int n); //Acepta dos parametros: la variable donde almacenaremos la cadena, y su tamanio.//
char linea[Max];

int main(){
	menuPrincipal();
	return 0;
}

void menuPrincipal(){
	char repite = 1;
	int opcion = -1;

	do{
		printf("\n\t\t[1 ]. Insertar nuevo equipo\n");
		printf("\t\t[2 ]. Modificar un equipo\n");
		printf("\t\t[3 ]. Eliminar un equipo\n");
		printf("\t\t[4 ]. Mostrar listado de los equipos\n");
		printf("\t\t[5 ]. Buscar equipo por numero de serie o tipo o marca de equipo\n");
		printf("\t\t[6 ]. Insertar nuevo historial\n");
		printf("\t\t[7 ]. Modificar historial\n");
		printf("\t\t[8 ]. Buscar historial por numero de serie\n");
		printf("\t\t[9]. Mostrar historial\n");
		printf("\t\t[10]. Salir\n");
		printf("\n\t\tIngrese su opcion: [ ] \b\b");
		leecad(linea, Max);
		sscanf(linea, "%d", &opcion); //la diferencia es que en lugar de tomar los datos de la entrada, los toma del propio programa.//
//se uitliza para obetener los datos de una variable atraves de un puntero//
		switch (opcion) {
			case 1:
				menuInsertar();
				break;
			case 2:
				menuModificar();
				break;
			case 3:
				menuEliminar();
				break;
			case 4:
				menuMostrar();
				break;
			case 5:
				menuBuscar();
				break;
			case 6:
				menuInsertarHistorial();
				break;
			case 7:
				menuModificarH();
				break;
			case 8:
				menuBuscarH();
				break;
			case 9:
				menuMostrarHistorial();
					break;
			case 10:
				repite = 0;
		}
	} while (repite);
}
void menuInsertarHistorial(){
	Historico historico;
	Equipo equipo;
	int nserie = 0;
	char repite = 1;
	char respuesta[Max];
	do {
		printf("\n\t\t\t INSERTAR HISTORIAL \n");
		printf("\n\tNumero de serie de equipo: ");
		leecad(linea, Max);
		sscanf(linea, "%d", &nserie);
		if (existeEquipo(nserie, &equipo)) {
			historico.id = nserie;
			printf("\tPersona que atendio: ");
			leecad(historico.persat, 80);
			printf("\tMotivo: ");
		  leecad(historico.motivo, 80);
			printf("\tFecha de registro: ");
			leecad(historico.fecha, Max);
			if (insertarHistorial(historico)) {
				printf("\n\tEl historial fue insertado correctamente\n");
			} else {
				printf("\n\tOcurrio un error al intentar insertar el equipo\n");
			}
		} else {
			printf("\n\tEl equipo de numero de serie %d ya existe.\n", nserie);
			printf("\tNo puede ingresar dos equipos distintos con el mismo numero de serie.\n");
		}
		printf("\n\tDesea seguir ingresando equipos? [S/N]: ");
		leecad(respuesta, Max);
		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) { //Devuelve 0 si las cadenas de texto son iguales//
			repite = 0;}// si la primera cadena es mayor que la segunda, devuelve un número positivo; si es mayor la segunda, devuelve un valor negativo//
} while (repite);}
void menuInsertar(){
	Equipo equipo;
	int nserie = 0;
	char repite = 1;
	char respuesta[Max];
	do{
		printf("\n\t\t\t INSERTAR EQUIPO \n");
		printf("\n\tNumero de serie: ");
		leecad(linea, Max);
		sscanf(linea, "%d", &nserie);
		if (!existeEquipo(nserie, &equipo)) {
			equipo.nserie = nserie;
			printf("\tTipo de equipo: ");
			int tipo=0;
			printf("1 = Cpu \n 2 = Monitor \n 3 = Impresora \n 4 = Escaner");
			scanf("%d\n",&tipo);
			switch(tipo){
				case 1:
				printf("Cpu");
				equipo.tipoe=tipo;
				break;
			    case 2:
			    printf("Monitor");
			    equipo.tipoe=tipo;
			    break;
			    case 3:
			    printf("Impresora");
			    equipo.tipoe=tipo;
			   	break;
			    case 4:
				printf("Escaner");
				equipo.tipoe=tipo;
				break;
				default:
				printf("No existe el equipo que selecciono");
							}
			printf("\n\tMarca del equipo: ");
		  leecad(equipo.marca, 20);
			printf("\tmodelo: ");
			leecad(equipo.modelo, 20);
			if (insertarEquipo(equipo)) {
				printf("\n\tEl equipo fue insertado correctamente\n");
			}else{
				printf("\n\tOcurrio un error al intentar insertar el equipo\n");
			}
			}else {
			printf("\n\tEl equipo de numero de serie %d ya existe.\n", nserie);
			printf("\tNo puede ingresar dos equipos distintos con el mismo id.\n");
		}
		printf("\n\tDesea seguir ingresando equipos? [S/N]: ");
		leecad(respuesta, Max);
		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
	}   }while (repite);
}
void menuBuscar(){
	Equipo equipo;
	int nserie;
	int opcion=0;
	int tipo;
	char repite = 1;
	char respuesta[Max];
	char marcae;
	do {
		printf("\n\t\t\t BUSCAR EQUIPO POR NUMERO DE SERIE, TIPO O MARCA \n");
	printf("1 = Buscar por numero de serie \n 2 = Buscar por tipo de equipo \n 3 = buscar por marca de equipo\n");
		scanf("%d\n",&opcion);	
		switch(opcion){
			case 1:
			printf("Buscar por numero de serie");
			printf("\n\tNumero de serie del EQUIPO: ");
			leecad(linea, Max);
			sscanf(linea, "%d", &nserie);
			if(existeEquipo(nserie, &equipo)) {
				printf("\n\tNumero de serie del equipo: %d\n", equipo.nserie);
				printf("\tTipo de equipo: %d\n", equipo.tipoe);
				printf("\tMaarca de equipo: %s\n", equipo.marca);
				printf("\tModelo del equipo: %s\n", equipo.modelo);
			} else {
				printf("\n\tEl equipo de numero de serie %d no existe.\n", nserie);
			}
			break;
				case 2:
				printf("\n\tNumero del tipo de equipo: ");
				leecad(linea, Max);
				sscanf(linea, "%d", &tipo);
				if(existeEquipot(tipo, &equipo)) {
					printf("\n\tNumero de serie del equipo: %d\n", equipo.nserie);
					printf("\tTipo de equipo: %d\n", equipo.tipoe);
					printf("\tMaarca de equipo: %s\n", equipo.marca);
					printf("\tmodelo: %s\n", equipo.modelo);
				} else {
					printf("\n\tEl equipo de tipo %d no existe.\n", tipo);
				}
				break;
				case 3:
				printf("Buscar por marca del equipo:");
				printf("\n\tMarca del tipo de equipo: ");
				leecad(linea, Max);
				// sscanf(linea, "%s", marcae);
				fgets(marcae, Max, stdin);
				if(!(strcmp(marcae,equipo.marca)== 0 || strcmp(marcae,equipo.marca ) == 0))
				if(existeEquipom(marcae, &equipo)) {
					printf("\n\tNumero de serie del equipo: %d\n", equipo.nserie);
					printf("\tTipo de equipo: %d\n", equipo.tipoe);
					printf("\tMaarca de equipo: %s\n", equipo.marca);
					printf("\tmodelo: %s\n", equipo.modelo);
				} else {
					printf("\n\tEl equipo de marca %s no existe.\n", marcae);
				}
				break;
			default:
			printf("No existe el equipo que selecciono");
						}
		printf("\n\tDesea seguir buscando algun equipo ? [S/N]: ");
		leecad(respuesta, Max);
		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
		}
	} while (repite);
}
void menuBuscarH(){
	Historico historico;
	int idHis;
	char repite = 1;
	char respuesta[Max];
	do {
		printf("\n\t\t\t BUSCAR HISTORIAL POR NUMERO DE SERIE \n");
		printf("\n\tNUMERO DE SERIE: ");
		leecad(linea, Max);
		sscanf(linea, "%d", &idHis);
		if (existeHistorial(idHis, &historico)) {
			printf("\n\tNumero de serie del equipo: %d\n", historico.id);
			printf("\tMotivo del servicio: %s\n", historico.motivo);
			printf("\tPersona que lo atendio: %s\n", historico.persat);
			printf("\tFecha de servicio: %s\n", historico.fecha);
		} else {
			printf("\n\tEl equipo con numero de serie %d no tiene historial.\n", idHis);
		}
		printf("\n\tDesea seguir buscando algun equipo? [S/N]: ");
		leecad(respuesta, Max);
		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
		}
	} while (repite);
}
void menuEliminar(){
	Equipo equipo;
	int nserie;
	char repite = 1;
	char respuesta[Max];
	do {
		printf("\n\t\t\t ELIMINAR EQUIPO POR NUMERO DE SERIE \n");
		printf("\n\tNUEMERO DE SERIE: ");
		leecad(linea, Max);
		sscanf(linea, "%d", &nserie);
		if (existeEquipo(nserie, &equipo)) {
			printf("\n\tNumero de Equipo: %d\n", equipo.nserie);
			printf("\tTIPO DEL EQUIPO: %d\n", equipo.tipoe);
			printf("\tMARCA DEL EQUIPO: %s\n", equipo.marca);
			printf("\tMODELO DEL EQUIPO: %s\n", equipo.modelo);
			printf("\n\tSeguro que desea eliminar el equipo? [S/N]: ");
			leecad(respuesta, Max);
			if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
				if (eliminar(nserie)) {
					printf("\n\tEquipo eliminado satisfactoriamente.\n");
				} else {
					printf("\n\tEl equipo no pudo ser eliminado\n");
				}
			}
		} else {
			printf("\n\tEl equipo de numero de serie %d no existe.\n", nserie);
		}
		printf("\n\tDesea eliminar otro equipo? [S/N]: ");
		leecad(respuesta, Max);
		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
		}
	} while (repite);
}
void menuMostrarHistorial(){
	Historico *historicos;
	int numeroEquipos;
	int i;
	char respuesta[Max];
	historicos = obtenerEquiposH(&numeroEquipos);
	if (numeroEquipos == 0) {
		printf("\n\tEl archivo esta vacio!!\n");
	} else {
		printf("\n\t\t   LISTADO DE HISTORIAL \n");
		printf(" -------------------------------------------------------------\n");
		printf("%8s\t%-20s\t%7s\t%15s\n", "NUMERO DE SERIE", "P. ATENDIO", "MOTIVO", "FECHA");
		printf(" -------------------------------------------------------------\n");
		for (i = 0; i < numeroEquipos; i++) {
			if (historicos[i].id != valor) {
				printf("%7d \t%-20s\t%-20s\t%s\n", historicos[i].id, historicos[i].persat, historicos[i].motivo, historicos[i].fecha);
			}
		}
		printf(" ------------------------------------------------------------\n");
		}
	}
void menuMostrar(){
	Equipo *equipos;
	int numeroEquipos;
	int i;
	char respuesta[Max];
	equipos = obtenerEquipos(&numeroEquipos);
	if (numeroEquipos == 0) {
		printf("\n\tEl archivo esta vacio!!\n");
	} else {
		printf("\n\t\t   LISTADO DE Equipos REGISTRADOS \n");
		printf(" --------------------------------------------------------------\n");
		printf("%8s\t%-20s%7s%15s\n", "NUMERO DE SERIE", "MARCA", "TIPO DE EQUIPO", "MODELO");
		printf(" ---------------------------- --------------------------------\n");
		for (i = 0; i < numeroEquipos; i++) {
			if (equipos[i].nserie != valor) {
				printf("%7d \t%-20s\t%-20d\t%-20s\n", equipos[i].nserie, equipos[i].marca, equipos[i].tipoe, equipos[i].modelo);
			}
		}
		printf(" -------------------------------------------------------------\n");
		}
	}
void menuModificar(){
	Equipo equipo;
	int idEquipo;
	char repite = 1;
	char respuesta[Max];
	do {
		printf("\n\t\t\t MODIFICAR POR Numero de SERIE\n");
		printf("\n\tNumero de serie del equipo: ");
		leecad(linea, Max);
		sscanf(linea, "%d", &idEquipo);
		if (existeEquipo(idEquipo, &equipo)) {
			printf("\n\tMarca del equipo: %s\n", equipo.marca);
			printf("\tTipo de equipo: %d\n", equipo.tipoe);
			printf("\tModelo de equipo: %s\n", equipo.modelo);
			printf("\n\tElija los datos a modificar\n");
			printf("\n\tMarca del equipo actual: %s\n", equipo.marca);
			printf("\tDesea modificar la marca del equipo? [S/N]: ");
			leecad(respuesta, Max);
			if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
				printf("\tNueva marca del equipo: ");
				leecad(equipo.marca, Max);
			}
			printf("\n\tTipo de equipo actual: %d\n", equipo.tipoe);
			printf("\tDesea modificar el tipo del equipo? [S/N]: ");
			leecad(respuesta, Max);
			if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
				printf("\tNuevo tipo del equipo: ");
				leecad(linea, Max);
				sscanf(linea, "%s", &equipo.tipoe);
			}
			printf("\n\tModelo del equipo actual: %s\n", equipo.modelo);
			printf("\tDesea modificar el tipo del equipo? [S/N]: ");
			leecad(respuesta, Max);
			if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
				printf("\tNueva marca del equipo: ");
				leecad(linea, Max);
				sscanf(linea, "%s", &equipo.modelo);
			}
			printf("\n\tEsta seguro que desea modificar los datos del equipo? [S/N]: ");
			leecad(respuesta, Max);
			if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
				if (modificarEquipo(equipo)) {
					printf("\n\tEl equipo fue modificado correctamente\n");
				} else {
					printf("\n\tOcurrio un error al intentar modificar el equipo\n");
					printf("\tIntentelo mas tarde\n");
				}
			}
		} else {
			printf("\n\tEl equipo de numero de serie %d no existe.\n", idEquipo);
		}
		printf("\n\tDesea modificar algun otro equipo? [S/N]: ");
		leecad(respuesta, Max);
		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
		}
	} while (repite);
}
void menuModificarH(){
	Historico historico;
	int idEquipo;
	char repite = 1;
	char respuesta[Max];
	do {
		printf("\n\t\t\t MODIFICAR HISTORIAL POR NUMERO DE SERIE \n");
		printf("\n\tNumero de sere del equipo: ");
		leecad(linea, Max);
		sscanf(linea, "%d", &idEquipo);
		if (existeHistorial(idEquipo, &historico)) {
			printf("\tMotivo del servicio: %s\n", historico.motivo);
			printf("\tPersona que atendio: %s\n", historico.persat);
     printf("\tFecha del servicio: %s\n", historico.fecha);
			printf("\n\tElija los datos a modificar\n");
			printf("\n\tMotivo  del servicio actual: %s\n", historico.motivo);
			printf("\tDeseas modificar el motivo del servicio? [S/N]: ");
			leecad(respuesta, Max);
			if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
				printf("\tNuevo motivo del servicio: ");
				leecad(historico.motivo, 80);
			}
			printf("\n\tPersona que atendio en el servico actualmente: %s\n", historico.persat);
			printf("\tDesea modificar la persona que atendio? [S/N]: ");
			leecad(respuesta, Max);
			if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
				printf("\tNueva persona que atendio el serivicio: ");
				leecad(historico.persat,80);
			printf("\n\tfecha actual: %s\n", historico.fecha);
			printf("\tDesea modificar la fecha del servicio? [S/N]: ");
			leecad(respuesta, Max);
			if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
				printf("\tNueva fecha del servicio: ");
				leecad(historico.fecha, 15);
			}
			printf("\n\tEsta seguro que desea modificar los datos del equipo? [S/N]: ");
			leecad(respuesta, Max);
			if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
				if (modificarHistorial(historico)) {
					printf("\n\tEl historial fue modificado correctamente\n");
				} else {
					printf("\n\tOcurrio un error al intentar modificar el historial\n");
				}
			}
		}}
		 else {
			printf("\n\tEl equipo de numero de serie %d no existe.\n", idEquipo);
		}
		printf("\n\tDesea modificar algun otro equipo? [S/N]: ");
		leecad(respuesta, Max);
		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
		}
	} while(repite);
}
Equipo *obtenerEquipos(int *n){
	FILE *archivo;
	Equipo equipo;
	Equipo *equipos;
	int i;
	archivo = fopen("equipos.dat", "rb");//abrimos el archivo y leemos los datos//
	if (archivo == NULL) {
		*n = 0;
		equipos = NULL;
	} else { //fseek Sitúa el puntero de lectura/escritura de un archivo en la posición indicada.//
		fseek(archivo, 0, SEEK_END);  // Posición respecto al final del archivo//
		*n = ftell(archivo) / sizeof(Equipo);
		equipos = (Equipo *)malloc((*n) * sizeof(Equipo)); /* Se reserva memoria para todos los registros almacenados en el archivo */
		fseek(archivo, 0, SEEK_SET); /* Posiciona el cursor al principio del archivo */
		fread(&equipo, sizeof(equipo), 1, archivo);
		i = 0;
		while (!feof(archivo)) { //utilizamos este while para que la entrada de datos no sobre pase el final del archivo//
			equipos[i++] = equipo;
			fread(&equipo, sizeof(equipo), 1, archivo);
		}
		fclose(archivo);//cerramos el archivo//
	}
	return equipos;
}
Historico *obtenerEquiposH(int *n){
	FILE *archivo;
	Historico historico;
	Historico *equipos;
	int i;
	archivo = fopen("historico.dat", "rb");
	if (archivo == NULL) {
		*n = 0;
		equipos = NULL;
	} else {
		fseek(archivo, 0, SEEK_END);
		*n = ftell(archivo) / sizeof(Historico);
		equipos = (Historico *)malloc((*n) * sizeof(Historico));
		fseek(archivo, 0, SEEK_SET); /* Posiciona el cursor al principio del archivo */
		fread(&historico, sizeof(historico), 1, archivo);
		i = 0;
		while (!feof(archivo)) {
			equipos[i++] = historico;
			fread(&historico, sizeof(historico), 1, archivo);
		}
		fclose(archivo);
	}
	return equipos;
}
char existeEquipo(int idEquipo, Equipo *equipo){
	FILE *archivo; //decalracion del archivo//
	char existe;
	archivo = fopen("equipos.dat", "rb");
	if (archivo == NULL) {
		existe = 0;
	} else {
		existe = 0;
		fread(&(*equipo), sizeof(*equipo), 1, archivo);
		while (!feof(archivo)) {//utilizamos este while para que la entrada de datos no sobre pase el final del archivo//
			if ((*equipo).nserie == idEquipo) {
				existe = 1;
				break;
			}
		fread(&(*equipo), sizeof(*equipo), 1, archivo);
		}
		fclose(archivo);
	}
	return existe;
}
char existeEquipot(int tipo, Equipo *equipo){
	FILE *archivo; //decalracion del archivo//
	char existet;
	archivo = fopen("equipos.dat", "rb");
	if (archivo == NULL) {
		existet = 0;
	} else {
		existet = 0;
		fread(&(*equipo), sizeof(*equipo), 1, archivo);
		while (!feof(archivo)) {//utilizamos este while para que la entrada de datos no sobre pase el final del archivo//
			if ((*equipo).tipoe == tipo) {
				existet = 1;
				break;
			}
		fread(&(*equipo), sizeof(*equipo), 1, archivo);
		}
		fclose(archivo);
	}
	return existet;
}
char existeEquipom(char marcae, Equipo *equipo){
	FILE *archivo; //decalracion del archivo//
	char existem;
	archivo = fopen("equipos.dat", "rb");
	if (archivo == NULL) {
		existem = 0;
	} else {
		existem = 0;
		fread(&(*equipo), sizeof(*equipo), 1, archivo);
		while (!feof(archivo)) {//utilizamos este while para que la entrada de datos no sobre pase el final del archivo//
			if ((*equipo).marca == marcae) {
				existem = 1;
				break;
			}
		fread(&(*equipo), sizeof(*equipo), 1, archivo);
		}
		fclose(archivo);
	}
	return existem;
}
char existeHistorial(int idHis, Historico *historico){
	FILE *archivo;
	char existe;
	archivo = fopen("historico.dat", "rb");
	if (archivo == NULL) {
	} else {
		existe = 0;
		fread(&(*historico), sizeof(*historico), 1, archivo);
		while (!feof(archivo)) {
			if ((*historico).id == idHis) {
				existe = 1;
				break;
			}
			fread(&(*historico), sizeof(*historico), 1, archivo);
		}
		fclose(archivo);
	}
	return existe;
}
char existeFecha(char f[Max], Historico *historico){
	FILE *archivo;
	char existe;
	archivo = fopen("historico.dat", "rb");
	if (archivo == NULL) {
	} else {
		existe = 0;
		fread(&(*historico), sizeof(*historico), 1, archivo);
		while (!feof(archivo)) {
			if ((*historico).fecha == f) {
				existe = 1;
				break;
			}
			fread(&(*historico), sizeof(*historico), 1, archivo);
		}
		fclose(archivo);
	}
	return existe;
}
char insertarEquipo(Equipo equipo){
	FILE *archivo;
	char insercion;
	archivo = fopen("equipos.dat", "ab");
	if (archivo == NULL) {
		insercion = 0;
	} else {
		fwrite(&equipo, sizeof(equipo), 1, archivo);
		insercion = 1;
		fclose(archivo);
	}
	return insercion;
}
char insertarHistorial(Historico historico){
	FILE *archivo;
	char insercion;
	archivo = fopen("historico.dat", "ab");
	if (archivo == NULL) {
		insercion = 0;
	} else {
		fwrite(&historico, sizeof(historico), 1, archivo);
		insercion = 1;
		fclose(archivo);
	}
	return insercion;
}
char eliminar(int idEquipo){
	FILE *archivo;
	FILE *auxiliar;
	Equipo equipo;
	char elimina;
	archivo = fopen("equipos.dat", "r+b");
	if (archivo == NULL) {
		elimina = 0;
	} else {
		elimina = 0;
		fread(&equipo, sizeof(equipo), 1, archivo);
		while (!feof(archivo)) {
			if (equipo.nserie == idEquipo) {
				fseek(archivo, ftell(archivo) - sizeof(equipo), SEEK_SET);
				equipo.nserie = valor;
				fwrite(&equipo, sizeof(equipo), 1, archivo);
				elimina = 1;
				break;
				}
			fread(&equipo, sizeof(equipo), 1, archivo);
		}
		fclose(archivo);
	}
	return elimina;
}
char modificarEquipo(Equipo equipo){
	FILE *archivo;
	char modifica;
	Equipo equipo2;
	archivo = fopen("equipos.dat", "rb+");
	if (archivo == NULL) {
		modifica = 0;
	} else {
		modifica = 0;
		fread(&equipo2, sizeof(equipo2), 1, archivo);
		while (!feof(archivo)) {
			if (equipo2.nserie == equipo.nserie) {
				fseek(archivo, ftell(archivo) - sizeof(equipo), SEEK_SET);
				fwrite(&equipo, sizeof(equipo), 1, archivo);
				modifica = 1;
				break;
			}
			fread(&equipo2, sizeof(equipo2), 1, archivo);
		}
		fclose(archivo);
	}
	return modifica;
}
char modificarHistorial(Historico historico){
	FILE *archivo;
	char modifica;
	Historico historico2;
	archivo = fopen("historico.dat", "rb+");
	if (archivo == NULL) {
		modifica = 0;
	} else {
		modifica = 0;
		fread(&historico2, sizeof(historico2), 1, archivo);
		while (!feof(archivo)) {
			if (historico2.id == historico.id) {
				fseek(archivo, ftell(archivo) - sizeof(historico), SEEK_SET);
				fwrite(&historico, sizeof(historico), 1, archivo);
				modifica = 1;
				break;
			}
			fread(&historico2, sizeof(historico2), 1, archivo);
		}
		fclose(archivo);
	}
	return modifica;
}
int leecad(char *cad, int n){ 
	int i, c;
	c = getchar();
	if (c == EOF) {
		cad[0] = '\0';
		return 0;
	}
	if (c == '\n') {
		i = 0;
	} else {
		cad[0] = c;
		i = 1;
	}//el for empieza con un ; porque estamos omitiendo la inicialización del contador, ya que fue inicializado//
	for (; i < n - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		cad[i] = c;
	}
	cad[i] = '\0';  //Hay que verificar si el buffer está limpio, o si hay un '\n' dejado por scanf y, en ese caso, limpiarlo//
	if (c != '\n' && c != EOF)
		while ((c = getchar()) != '\n' && c != EOF);
	return 1;
}
