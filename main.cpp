//Grupo 54: Bárbara Oliveira Fonseca e Thiago Antônio (14B), Carlos Eduardo Sarto (14A)
//Tema: Plantas
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

struct Planta {
    int id;
    string nome; // PODE possuir espacos
    string nomeCientifico; // possui espacos
    int nCotiledones;
    int nPetalas;
    char classe; // se e mono ou dicotiledonea
};

Planta* alocacao(Planta* vetor, int& tam) {
    int novoTam = tam + 10;
    Planta* novo = new Planta[novoTam];

    for (int i = 0; i < tam; ++i) {
        novo[i] = vetor[i];
    }
    
    tam = novoTam;
    delete[] vetor;
    vetor = novo;
    
    return vetor;
}

Planta* importarCSV(Planta* vetor, int& tam, int& qtde) {
    string linha;
    ifstream arquivo("arquivo.csv");

    getline(arquivo, linha); // joga fora a primeira linha
    
    while (getline(arquivo, linha)) { 
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

        if (qtde >= tam) {
            vetor = alocacao(vetor, tam);
        }
    }

    arquivo.close();
    cout << "Dados importados com sucesso" << endl;
    return vetor;
}

void inserir(Planta *vetor, int& tam, int& qtde){
    Planta novaPlantinha;

    cout << "Nome popular:" << endl;
    cin.ignore(); // ignora o caractere no buffer
    getline(cin, novaPlantinha.nome); // getline para permitir espaços 
    cout << "Nome cientifico:" << endl;
    getline(cin, novaPlantinha.nomeCientifico); 
    cout << "Numero de cotiledones:" << endl;
    cin >> novaPlantinha.nCotiledones;
    cout << "Numero de petalas:" << endl;
    cin >> novaPlantinha.nPetalas;
    cout << "Classe (M OU D):" << endl;
    cin >> novaPlantinha.classe;
    
    // encontrar um id único para a nova planta
    int novoId = 1;
    for (int i = 0; i < qtde; i++) {
        if (vetor[i].id >= novoId) {
            novoId = vetor[i].id + 1;
        }
    }
    novaPlantinha.id = novoId;
    
    if (qtde >= tam) {
        vetor = alocacao(vetor, tam);
    }
    
    vetor[qtde] = novaPlantinha;
    qtde++;
}

void remover (Planta *vetor, int& tam){
	int id;
	cout<<"Digite o id da planta a ser removida"<<endl;
	cin>>id;
	for(int i =0; i<tam; i++){
		if(vetor[i].id == id){
			vetor[i].id=0;
		}	
	
	}
	cout<<"Item removido com sucesso"<<endl;
	
}

void shellSortPorNome(Planta vetor[], int tam) {
    for (int gap = tam / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < tam; i++) {
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

void shellSortPorID(Planta vetor[], int tam) {
    for (int gap = tam / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < tam; i++) {
            Planta aux = vetor[i];
            int j;
            for (j = i; j >= gap && vetor[j - gap].id > aux.id; j -= gap) {
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
	cout<< "Nome Científico: " <<planta.nomeCientifico<<endl;
	cout<< "Número de Cotiledones: " <<planta.nCotiledones<<endl;
	cout<< "Número de Petálas: " <<planta.nPetalas<<endl;
	cout<< "Classe: " <<planta.classe<<endl;

}

void buscarPorID(Planta vetor[], int tam) {
    int id = 0;
    cout << "Digite o ID da planta a ser procurada: ";
    cin >> id;
    
    int inicio = 0, fim = tam - 1;
    bool encontrada = false;
    while (inicio <= fim && !encontrada) {
        int meio = inicio + (fim - inicio) / 2;

        // verifica se o id está no meio
        if (vetor[meio].id == id) {
            toString(vetor[meio]);
            encontrada = true;
        }
        // ignora a metade esquerda
        else if (vetor[meio].id < id) {
            inicio = meio + 1;
        }
        // ignora a metade direita
        else {
            fim = meio - 1;
        }
    }

    if (!encontrada) {
        cout << "Planta não encontrada." << endl;
    }
}

void buscarPorNome(Planta vetor[], int tam) {
    string nome = "";
    cout << "Digite o Nome da planta a ser procurada: ";
    cin >> nome;
    
    int inicio = 0, fim = tam - 1;
    bool encontrada = false; 
    while (inicio <= fim && !encontrada) {
        int meio = inicio + (fim - inicio) / 2;

        if (vetor[meio].nome == nome) {
            toString(vetor[meio]);
            encontrada = true;
        }
        else if (vetor[meio].nome < nome) {
            inicio = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }

    if (!encontrada) {
        cout << "Planta não encontrada." << endl;
    }
}


void converterEmBinario(Planta* arquivoCSV, int tamanho) {
    ofstream arquivoBinario("plantas.bin", ios::binary | ios::out);
    if (!arquivoBinario) {
        cout << "Erro ao carregar o arquivo binário" << endl;
    } else {
        for (int i = 0; i < tamanho; i++) {
            arquivoBinario.write(reinterpret_cast<const char*>(&arquivoCSV[i]), sizeof(Planta));
        }
        arquivoBinario.close();
        cout << "Arquivo binário criado com sucesso" << endl;
    }
}

void imprimir(Planta vetor[], int tam) { //imprime o vetor inteiro
    for (int i = 0; i < tam; i++) {
        if (vetor[i].id != 0) {
            cout << "ID: " << vetor[i].id << endl;
            cout << "Nome: " << vetor[i].nome << endl;
            cout << "Nome Científico: " << vetor[i].nomeCientifico << endl;
            cout << "Número de Cotiledones: " << vetor[i].nCotiledones << endl;
            cout << "Número de Petálas: " << vetor[i].nPetalas << endl;
            cout << "Classe: " << vetor[i].classe << endl;
        }
    }
}

void imprimirIntervalo(Planta vetor[], int tam){
	int fim=0, inicio=0;
	cout<< "Digite o indice de inicio:"<<endl;
	cin>>inicio;
	cout<<"Digite o indice de fim:"<<endl;
	cin>>fim;
	
	if (inicio >= 0 && inicio <= fim && fim < tam) {
		for(int i=inicio; i<=fim; i++){
			cout << "ID: " << vetor[i].id << endl;
            cout << "Nome: " << vetor[i].nome << endl;
            cout << "Nome Científico: " << vetor[i].nomeCientifico << endl;
            cout << "Número de Cotiledones: " << vetor[i].nCotiledones << endl;
            cout << "Número de Petálas: " << vetor[i].nPetalas << endl;
            cout << "Classe: " << vetor[i].classe << endl;
		}
	}
}

void salvarAlteracoes(Planta vetor[], int tam){
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
	cout<<"Dados salvos com sucesso"<<endl;
    
}

void menu() {
    cout << "Escolha uma opção abaixo:" << endl;
    cout << "Opção 1: Importar dados CSV" << endl;
    cout << "Opção 2: Inserir dados" << endl;
    cout << "Opção 3: Remover dados" << endl;
    cout << "Opção 4: Busca" << endl;
    cout << "Opção 5: Ordenar" << endl;
    cout << "Opção 6: Imprimir vetor" << endl;
    cout << "Opção 7: Imprimir intervalo de elementos" << endl;
    cout << "Opção 8: Salvar alterações" << endl;
    cout << "Opção 9: Converter CSV em arquivo binario"<<endl;
    cout << "Opção 0: Sair" << endl;
    
}

int main() {
    int tam = 40, opc = -1, qtde = 0;
    int opc1 = 0, opc2=0;
    Planta* vetor = new Planta[tam];

    while (opc != 0) {
        menu();
        cin >> opc;

        switch (opc) {
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
				cout<<"Deseja buscar por Nome Popular(1) ou por ID (2)"<<endl;
				cin>>opc1;
				if(opc1==1){
				buscarPorNome(vetor,tam);
				}
				else if(opc1==2){
				buscarPorID(vetor, tam);
				}
				else cout<<"Opcao invalida"<<endl;
                break;
            case 5:
				cout<<"Deseja ordenar por Nome Popular(1) ou por ID (2)"<<endl;
				cin>>opc2;
				if(opc2==1){
				shellSortPorNome(vetor,tam);
				}
				else if(opc2==2){
				shellSortPorID(vetor, tam);
				}
				else cout<<"Opcao invalida"<<endl;
				break;
            case 6:
				imprimir(vetor, tam);
				break;
			case 7:
				imprimirIntervalo(vetor,tam);
				break;
			case 8:
				salvarAlteracoes(vetor,tam);
				break;
			case 9:
				converterEmBinario(vetor, tam);
				break;
			case 0:
				cout<<"Saindo.."<<endl;
				break;
			default:
				cout<<"Opcao invalida"<<endl;
				break;
        }
    }

    delete[] vetor;
    return 0;
}
