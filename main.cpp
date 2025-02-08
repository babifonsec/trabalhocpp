//Grupo 54: Bárbara Oliveira Fonseca e Thiago Antônio (14B), Carlos Eduardo Sarto (14A)
//Tema: Plantas
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>

using namespace std;

struct Planta{
	int id;
	string nome;
	string nomeCientifico; 
	int nCotiledones;
	int nPetalas;
	char classe;
};

Planta* aumentarCapacidade(Planta*& vetor, int& tam){
	int novoTam = tam + 10;
	Planta* novo = new Planta[novoTam];
      
	if (novo == nullptr) {
		cerr << "Erro ao alocar memoria" << endl;
		return vetor;
	}

	for (int i = 0; i < tam; ++i){
		novo[i] = vetor[i];
	}
    
	tam = novoTam;
	delete[] vetor;
	vetor = novo;
    
	return vetor;
}

Planta* importarCSV(Planta* vetor, int& tam, int& qtde){
	string linha;
	ifstream arquivo("arquivo.csv");
    
	if (!arquivo.is_open()){
		cerr << "Erro ao abrir o arquivo CSV" << endl;
		return vetor;
	}

	getline(arquivo, linha); // joga fora a primeira linha
    
	while (getline(arquivo, linha)){
			if (qtde >= tam){
			vetor = aumentarCapacidade(vetor, tam);
		}
		
		stringstream ss(linha); // passa a linha para a ss
		string campo;
		getline(ss, campo, ','); // separa a linha em campos ate a virgula
		vetor[qtde].id = stoi(campo); // stoi = string to int 
		getline(ss, vetor[qtde].nome, ',');
		getline(ss, vetor[qtde].nomeCientifico, ',');
		getline(ss, campo, ',');
		vetor[qtde].nCotiledones = stoi(campo);
		getline(ss, campo, ',');
		vetor[qtde].nPetalas = stoi(campo);
		getline(ss, campo, ',');
		vetor[qtde].classe = campo[0]; // como é char, pega somente o primeiro caractere

		qtde++;

	};

	arquivo.close();
	cout << "Dados importados com sucesso" << endl;
	return vetor;
}

int validaInt(){
	int inteiro;
	bool valido = false;
	while(!valido){
		cin>>inteiro;
		if(cin.fail() || inteiro<0){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr<<"Por favor, insira um numero valido"<<endl;
		}
		else{
		valido = true;
		}
	};
	
	return inteiro;
}

char validaClasse(){
	char classe;
	bool valido = false;
	while(!valido){
		cin>>classe;
		classe = toupper(classe);
		if(cin.fail() || (classe != 'M' && classe!= 'D')){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr<<"Por favor, insira uma classe valida (M ou D)"<<endl;
		}
		else{
		valido = true;
		}
	};
	
	return classe;
}

string formataString(string texto){
	
	if (!texto.empty()) {
	transform(texto.begin(), texto.end(), texto.begin(), ::tolower);
	texto[0] = toupper(texto[0]); 
	}
	
	return texto;
}

void inserir(Planta *vetor, int& tam, int& qtde){
	Planta novaPlantinha;
    
	cout << "Nome popular:" << endl;
	cin.ignore(); // ignora o caractere no buffer
	getline(cin, novaPlantinha.nome); // getline para permitir espaços 
	novaPlantinha.nome = formataString(novaPlantinha.nome);
			
	cout << "Nome cientifico:" << endl;
	getline(cin, novaPlantinha.nomeCientifico); 
	novaPlantinha.nomeCientifico = formataString(novaPlantinha.nomeCientifico);
	
	cout << "Numero de cotiledones:" << endl;
	novaPlantinha.nCotiledones = validaInt();
	
	cout << "Numero de petalas:" << endl;
	novaPlantinha.nPetalas = validaInt();
    
	cout << "Classe (M ou D):" << endl;
	novaPlantinha.classe = validaClasse();
    
    // encontrar um id unico para a nova planta
	int novoId = 1;
	for (int i = 0; i < qtde; i++){
		if (vetor[i].id >= novoId){
			novoId = vetor[i].id + 1;
		}
	}
	novaPlantinha.id = novoId;
    
	if (qtde >= tam){
		vetor = aumentarCapacidade(vetor, tam);
	}
    
	vetor[qtde] = novaPlantinha;
	qtde++;
	cout << "Dados inseridos com sucesso" << endl;
   
}

void remover(Planta* vetor, int& tam) {
	int id=0;
	cout << "Digite o id da planta a ser removida" << endl;
	id = validaInt();

	int i = 0; 
	bool encontrado = false; 

	while (i < tam && !encontrado) { 
		if (vetor[i].id == id) {
			vetor[i].id = 0; 
			cout << "Item removido com sucesso" << endl;
			encontrado = true; 
		}
		i++; 
	}

	if (!encontrado) {
		cout << "Item nao encontrado" << endl;
	}
}

void editar(Planta* vetor, int tam) {
	int id;
	cout << "Digite o ID da planta a ser editada:" << endl;
	id=validaInt();

	bool encontrado = false;
	int i=0;
	while(i<tam && !encontrado){
		if (vetor[i].id == id) {
			cout << "Digite o novo nome:" << endl;
			cin.ignore();
			getline(cin, vetor[i].nome);
			vetor[i].nome = formataString(vetor[i].nome);
			
			cout << "Digite o novo nome cientifico:" << endl;
			getline(cin, vetor[i].nomeCientifico);
			vetor[i].nomeCientifico = formataString(vetor[i].nomeCientifico);
			
			cout << "Digite o novo numero de cotiledones:" << endl;
			vetor[i].nCotiledones=validaInt();
			cout << "Digite o novo numero de petalas:" << endl;
			vetor[i].nPetalas=validaInt();
			cout << "Digite a nova classe:" << endl;
			vetor[i].classe = validaClasse();
			cout << "Dados editados com sucesso" << endl;
			encontrado = true;
		}
		i++;
	}

	if (!encontrado) {
		cout << "Planta nao encontrada" << endl;
	}
}

void shellSortPorNome(Planta vetor[], int tam){
	for (int gap = tam / 2; gap > 0; gap /= 2){
		for (int i = gap; i < tam; i++){
			Planta aux = vetor[i];
			int j;
			for (j = i; j >= gap && vetor[j - gap].nome > aux.nome; j -= gap) {
				vetor[j] = vetor[j - gap];
			}
			vetor[j] = aux;
		}
	}
	cout<<"Vetor ordenado com sucesso"<<endl;
}

void shellSortPorID(Planta vetor[], int tam){
	for (int gap = tam / 2; gap > 0; gap /= 2){
		for (int i = gap; i < tam; i++){
			Planta aux = vetor[i];
			int j;
			for (j = i; j >= gap && vetor[j - gap].id > aux.id; j -= gap){
				vetor[j] = vetor[j - gap];
			}
			vetor[j] = aux;
		}
	}
	cout<<"Vetor ordenado com sucesso"<<endl;
}

void toString (Planta planta){ //para imprimir uma planta so
	cout<< "ID: " <<planta.id<<endl;
	cout<< "Nome: " <<planta.nome<<endl;
	cout<< "Nome Cientifico: " <<planta.nomeCientifico<<endl;
	cout<< "Numero de Cotiledones: " <<planta.nCotiledones<<endl;
	cout<< "Numero de Petalas: " <<planta.nPetalas<<endl;
	cout<< "Classe: " <<planta.classe<<endl;

}

void buscarPorID(Planta vetor[], int tam){
	shellSortPorID(vetor,tam);
	int id = 0;
	cout << "Digite o ID da planta a ser procurada: ";
	id=validaInt();
    
	int inicio = 0, fim = tam - 1;
	bool encontrada = false;
	while (inicio <= fim && !encontrada){
		int meio = inicio + (fim - inicio) / 2;

        // verifica se o id está no meio
		if (vetor[meio].id == id){
			toString(vetor[meio]);
			encontrada = true;
		}
        // ignora a metade esquerda
		else if (vetor[meio].id < id){
			inicio = meio + 1;
		}
        // ignora a metade direita
		else {
			fim = meio - 1;
		}
	}

	if (!encontrada){
		cout << "Planta nao encontrada." << endl;
	}
}

void buscarPorNome(Planta vetor[], int tam){
	shellSortPorNome(vetor,tam);
	string nome = "";
	cout << "Digite o Nome da planta a ser procurada: ";
	cin.ignore();
	getline(cin, nome);
	nome = formataString(nome);
    
	int inicio = 0, fim = tam - 1;
	bool encontrada = false; 
	while (inicio <= fim && !encontrada){
		int meio = inicio + (fim - inicio) / 2;

		if (vetor[meio].nome == nome){
			toString(vetor[meio]);
			encontrada = true;
		}
		else if (vetor[meio].nome < nome){
			inicio = meio + 1;
		}
		else{
			fim = meio - 1;
		}
	}

	if (!encontrada){
		cout << "Planta nao encontrada." << endl;
	}
}

void salvarEmBinario(Planta* vetor, int tam) {
	ofstream arquivoBinario("plantas.bin", ios::binary | ios::out);
	if (!arquivoBinario) {
		cout << "Erro ao carregar o arquivo binario" << endl;
		return;
	}

	for (int i = 0; i < tam; i++) {
		if(vetor[i].id !=0){
			arquivoBinario.write(reinterpret_cast<const char*>(&vetor[i].id), sizeof(int));

			size_t tamanhoNome = vetor[i].nome.size(); 
			arquivoBinario.write(reinterpret_cast<const char*>(&tamanhoNome), sizeof(size_t));
			arquivoBinario.write(vetor[i].nome.c_str(), tamanhoNome);

			size_t tamanhoNomeCientifico = vetor[i].nomeCientifico.size();
			arquivoBinario.write(reinterpret_cast<const char*>(&tamanhoNomeCientifico), sizeof(size_t));
			arquivoBinario.write(vetor[i].nomeCientifico.c_str(), tamanhoNomeCientifico);

			arquivoBinario.write(reinterpret_cast<const char*>(&vetor[i].nCotiledones), sizeof(int));
			arquivoBinario.write(reinterpret_cast<const char*>(&vetor[i].nPetalas), sizeof(int));

			arquivoBinario.write(&vetor[i].classe, sizeof(char));
		}
	}
	arquivoBinario.close();
	cout << "Arquivo binario salvo com sucesso" << endl;
}

Planta* importarBin(Planta*& vetor, int& tam, int& qtde) {
	ifstream arquivoBinario("plantas.bin", ios::binary | ios::in);

	if (!arquivoBinario) {
		cout << "Erro ao carregar o arquivo binario." << endl;
		return vetor;
	}

	// move o ponteiro para o final do arquivo para calcular o tamanho
	arquivoBinario.seekg(0, ios::end);
	int tamanhoArquivo = arquivoBinario.tellg();
	arquivoBinario.seekg(0, ios::beg);

	//calcula quantas plantas cabem no arquivo
	int numPlantas = 0;
	while (arquivoBinario.tellg() < tamanhoArquivo) {

		int id;
		arquivoBinario.read(reinterpret_cast<char*>(&id), sizeof(int));

		size_t tamanhoNome;
		arquivoBinario.read(reinterpret_cast<char*>(&tamanhoNome), sizeof(size_t));
		arquivoBinario.seekg(tamanhoNome, ios::cur);

		size_t tamanhoNomeCientifico;
		arquivoBinario.read(reinterpret_cast<char*>(&tamanhoNomeCientifico), sizeof(size_t));
		arquivoBinario.seekg(tamanhoNomeCientifico, ios::cur);

		arquivoBinario.seekg(sizeof(int) + sizeof(int) + sizeof(char), ios::cur);

		numPlantas++;
	}

	if (numPlantas > tam) {
		while (numPlantas > tam) {
			vetor = aumentarCapacidade(vetor, tam);
		}
	}

	// volta para o começo do arquivo para ler os dados
	arquivoBinario.seekg(0, ios::beg);

	// le os dados e armazena no vetor
	qtde = 0;
	while (arquivoBinario.tellg() < tamanhoArquivo) {

		arquivoBinario.read(reinterpret_cast<char*>(&vetor[qtde].id), sizeof(int));

		size_t tamanhoNome;
		arquivoBinario.read(reinterpret_cast<char*>(&tamanhoNome), sizeof(size_t));
		vetor[qtde].nome.resize(tamanhoNome);
		arquivoBinario.read(&vetor[qtde].nome[0], tamanhoNome);

		size_t tamanhoNomeCientifico;
		arquivoBinario.read(reinterpret_cast<char*>(&tamanhoNomeCientifico), sizeof(size_t));
		vetor[qtde].nomeCientifico.resize(tamanhoNomeCientifico);
		arquivoBinario.read(&vetor[qtde].nomeCientifico[0], tamanhoNomeCientifico);

		arquivoBinario.read(reinterpret_cast<char*>(&vetor[qtde].nCotiledones), sizeof(int));
		arquivoBinario.read(reinterpret_cast<char*>(&vetor[qtde].nPetalas), sizeof(int));

		arquivoBinario.read(&vetor[qtde].classe, sizeof(char));

		qtde++;
	}

	arquivoBinario.close();
	cout << "Dados importados com sucesso " << endl;
	return vetor;
}

void imprimir(Planta vetor[], int tam){ //imprime o vetor inteiro
	for (int i = 0; i < tam; i++){
		if (vetor[i].id != 0){
			cout << "ID: " << vetor[i].id << endl;
			cout << "Nome: " << vetor[i].nome << endl;
			cout << "Nome Cientifico: " << vetor[i].nomeCientifico << endl;
			cout << "Numero de Cotiledones: " << vetor[i].nCotiledones << endl;
			cout << "Numero de Petalas: " << vetor[i].nPetalas << endl;
			cout << "Classe: " << vetor[i].classe << endl;
		}
	}
}

void imprimirIntervalo(Planta vetor[], int qtde) {
	int inicio = 0, fim = 0;
	cout << "Digite o indice de inicio:" << endl;
	inicio=validaInt();
	cout << "Digite o indice de fim:" << endl;
	fim=validaInt();

	if (inicio >= 0 && inicio <= fim && fim < qtde) {
		for (int i = inicio; i <= fim; i++) {
			cout << "ID: " << vetor[i].id << endl;
			cout << "Nome: " << vetor[i].nome << endl;
			cout << "Nome Cientifico: " << vetor[i].nomeCientifico << endl;
			cout << "Numero de Cotiledones: " << vetor[i].nCotiledones << endl;
			cout << "Numero de Petalas: " << vetor[i].nPetalas << endl;
			cout << "Classe: " << vetor[i].classe << endl;
		}
	} else {
		cout << "Intervalo invalido." << endl;
	}
}

void salvarEmCSV(Planta vetor[], int tam){
	ofstream arquivo("arquivo.csv");
	
	arquivo << "ID,Nome,Nome Cientifico,Numero de Cotiledones,Numero de Petalas,Classe\n"; //reescrevendo o cabecalho
    
	for(int i =0; i<tam;i++){
		if(vetor[i].id!=0){
		arquivo<<vetor[i].id << ",";
		arquivo<<vetor[i].nome << ",";
		arquivo<<vetor[i].nomeCientifico << ",";
		arquivo<<vetor[i].nCotiledones << ",";
		arquivo<<vetor[i].nPetalas << ",";
		arquivo<<vetor[i].classe << "\n";
		}
	}
	
	arquivo.close();
	cout<<"Arquivo CSV salvo com sucesso"<<endl;
    
}

void menu(){
	cout << "Escolha uma opcao abaixo:" << endl;
	cout << "Opcao 1: Importar dados do arquivo CSV" << endl;
	cout << "Opcao 2: Inserir dados" << endl;
	cout << "Opcao 3: Remover dados" << endl;
	cout << "Opcao 4: Editar dados" << endl;
	cout << "Opcao 5: Buscar" << endl;
	cout << "Opcao 6: Ordenar" << endl;
	cout << "Opcao 7: Imprimir vetor" << endl;
	cout << "Opcao 8: Imprimir intervalo de elementos" << endl;
	cout << "Opcao 9: Salvar em arquivo CSV" << endl;
	cout << "Opcao 10: Salvar em arquivo binario"<<endl;
	cout << "Opcao 11: Importar dados do arquivo binario"<<endl;
	cout << "Opcao 0: Sair" << endl << endl;
    
}

int main(){
	int tam = 40, opc = -1, qtde = 0, opc1 = 0, opc2=0;
	Planta* vetor = new Planta[tam];

	while (opc != 0){
		menu();
		cin >> opc;

		switch (opc){
			case 1: 
				vetor = importarCSV(vetor, tam, qtde);
				break;

			case 2:
				inserir(vetor, tam, qtde);
				break;

			case 3:
				remover(vetor, tam);
				break;

			case 4:
				editar(vetor, tam);
				break;
                
			case 5:
				cout<<"Deseja buscar por Nome Popular (1) ou por ID (2)?"<<endl;
				cout<<"(Para buscar, ordenaremos o vetor automaticamente)"<<endl;
				opc1=validaInt();
				
				if(opc1==1){
					buscarPorNome(vetor,tam);
				}
				else if(opc1==2){
					buscarPorID(vetor, tam);
				}
				else cout<<"Opcao invalida"<<endl;
				break;

			case 6:
				cout<<"Deseja ordenar por Nome Popular (1) ou por ID (2)?"<<endl;
				opc2=validaInt();
				
				if(opc2==1){
					shellSortPorNome(vetor,tam);
				}
				else if(opc2==2){
					shellSortPorID(vetor, tam);
				}
				else cout<<"Opcao invalida"<<endl;
				break;

			case 7:
				imprimir(vetor, tam);
				break;

			case 8:
				imprimirIntervalo(vetor,tam);
				break;

			case 9:
				salvarEmCSV(vetor,tam);
				break;

			case 10:
				salvarEmBinario(vetor, tam);
				break;
				
			case 11:
				vetor = importarBin(vetor,tam,qtde);
				break;

			case 0:
				cout<<"Saindo..."<<endl;
				break;

			default:
				cout<<"Opcao invalida"<<endl;
				break;
		}
	}

	delete[] vetor;
	return 0;
}
