#include <iostream>
#include <fstream>
#include <string>

#include <sstream>
#include <vector>


void guardarDatos();
void creacionBasicaArchivoTexto();
void lecturaDeArchivosYaExistentes();
void escribirNuevaLinea();
int Logeo();
void ModificarPassword();
using namespace std;

struct Persona{	
	char nombre[20], apellido[20];
	int edad;
	char usu[9], pass[9];
};

// Global variables
string nombre, apellido, sexo;
int edad;

int main() {
	Persona Usuario;	
	ModificarPassword();
	
	/*int validadorLogeo = 0;
	validadorLogeo = Logeo();
	if(validadorLogeo==0){
		cout<<"Usuario o Contraseña incorrecta "<<endl;
	}*/
	
	return 0;
}

void escribirNuevaLinea() {
	ofstream foutput;
	ifstream finput;
	foutput.open("apnd.txt", ios::app);
	finput.open("apnd.txt");
	
	if (finput.is_open()) {
		cout << "Ingrese su Nombre: ";
		cin >> nombre;
		foutput << endl << nombre;
		
		cout << "Ingrese su Apellido: ";
		cin >> apellido;
		foutput << " | " << apellido;
		
		cout << "Ingrese su Edad: ";
		cin >> edad;
		foutput << " | " << edad;
		
		cout << "Ingrese su Sexo: ";
		cin >> sexo;
		foutput << " | " << sexo;
	}
	
	cout << "\nDatos ingresados correctamente";
	
	finput.close();
	foutput.close();
}

void guardarDatos() {
	
	ofstream archivo_txt;
	archivo_txt.open("datos.txt");
	
	if (archivo_txt.is_open()) {
		cout << "Ingrese su Nombre: ";
		cin >> nombre;
		
		cout << "Ingrese su Apellido: ";
		cin >> apellido;
		
		cout << "Ingrese su Edad: ";
		cin >> edad;
		
		cout << "Ingrese su Sexo: ";
		cin >> sexo;
		
		archivo_txt << nombre;
		archivo_txt << " | " << apellido;
		archivo_txt << " | " << edad;
		archivo_txt << " | " << sexo;
		
		archivo_txt.close();
	}
}

void creacionBasicaArchivoTexto() {
	ofstream txt_file;
	txt_file.open("myTextFile.txt");
	
	if (txt_file.is_open()) {
		txt_file << "This is the first line \n";
		txt_file << "This is the second line \n";
		txt_file << "This is the third line \n";
		txt_file << "This is the four line \n";
		txt_file.close();
	}
}

void lecturaDeArchivosYaExistentes() {
	// string line;
	ifstream txt_file_two;
	txt_file_two.open("myTextFile.txt");
	
	int id;
	string name;
	int age;
	
	if (txt_file_two.is_open()) {
		
		//while(getline(txt_file_two, line)){
		//    cout << line << endl;
		//
		
		while (txt_file_two >> id >> name >> age) {
			cout << id << " | " << name << " | " << age << endl;
		}
		
		txt_file_two.close();
	} else {
		cout << "File is not open" << endl;
	}
	
	//return 0;
}



//FV
//funcion
vector<string> split (string s, string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;
	
	while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
		token = s.substr (pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back (token);
	}
	
	res.push_back (s.substr (pos_start));
	return res;
}


int Logeo() {
	//variables
	string par_usu,par_pass;   //variables entrada
	string id,usu,pass,nombre; // variables interno
	string cadena; 			   // linea de texto
	string delimiter = "|";	   // delimitador
	
	cout<<"Ingrese el usuario "<<endl;
	cin >> par_usu;
	cout<<"Ingrese la contraseña "<<endl;
	cin >> par_pass;
	
	//seleccion archivo
	ifstream fe("usuarios.txt");	
	
	//lectura de informacon
	while(!fe.eof()) {		
		fe >> cadena; //cadena - linea de texto
		
		vector<string> v = split (cadena, delimiter);
		id     = v[0]; 
		usu    = v[1]; 
		pass   = v[2]; 
		nombre = v[3]; 
		
		if (usu==par_usu && pass==par_pass ){			
			cout<<"Bienvenido "<<nombre;
			fe.close();	
			return 1;
		}
	}
	
	fe.close();
	return 0;
}


void ModificarPassword() {
	string contenido;
	string buscar;      // texto a buscar
	string reemplazar;  // reemplazar por
	string id,usu,pass,nombre; 
	
	//ingresa textos
	cout << "Ingresa el usuario a buscar: ";
	cin >> buscar;
	cout << "Ingresa la nueva contraseña para reemplazarlo: ";
	cin >> reemplazar;
	
	
	ifstream fs("usuarios.txt"); //leer de este archivo
	ofstream fstemp("usuariostemp.txt"); //escribir en este archivo
	if(!fs || !fstemp) //no se pudo abrir alguno de los 2
	{
		cout << "Error al abrir el archivo!" << endl;
		exit;
	}
	
	//modificar linea a linea
	while(fs >> contenido)
	{	
		
		vector<string> v = split (contenido, "|");
		id     = v[0]; 
		usu    = v[1]; 
		//pass   = v[2]; 
		nombre = v[3]; 
		
		if(usu == buscar){  //se encontro
			contenido = id + "|"+ usu +"|"+ reemplazar + "|"+nombre;
		}		
		fstemp << contenido << endl;
	}
	
	//reemplazar un archivo por otro
	fs.close();
	fstemp.close();
	remove("usuarios.txt");                    // borrar el original
	rename("usuariostemp.txt", "usuarios.txt");  // renombrar el temporal
	
	//siguiendo la logica que usaste en el resto
	cout << "El archivo ha sido modificado correctamente" << endl;
	system("pause");
	exit;
}
