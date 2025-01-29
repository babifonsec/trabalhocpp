#include <iostream>
#include <fstream>

using namespace std;

struct Planta {
	int id;
	string nome; //PODE possuir espacos
	string nomeCientifico; //possui espacos
	int nCotiledones;
	int nPetalas;
	char classe; //se e mono ou dicotiledonea
	};


	
Planta *importarCSV(Planta *vetor, int &tam, int &qtde) {
    string lixo; 
    ifstream arquivo("arquivo.csv");
    int i = 0;
    qtde = 0;
    
    getline(arquivo, lixo);
    while (arquivo >> vetor[i].id) {
        arquivo >> lixo;
        arquivo>>vetor[i].nome;
        arquivo>>lixo;
        getline(arquivo, vetor[i].nomeCientifico, ',');
        arquivo >> lixo;
        arquivo >> vetor[i].nCotiledones;
        arquivo >> lixo;
        arquivo >> vetor[i].nPetalas;
        arquivo>>lixo;
        arquivo>>vetor[i].classe;
        i++;
        qtde++;
  
    }
    arquivo.close();
    cout << "Dados importados com sucesso" << endl;
    return vetor;
}

void imprimir(Planta vetor[], int tam){
	for (int i=0; i<tam;i++){
		if(vetor[i].id!=0){
			cout<< "ID:" << vetor[i].id <<endl;
			cout<< "Nome:" << vetor[i].nome <<endl;
			cout<< "Nome Científico:" << vetor[i].nomeCientifico <<endl;
			cout<< "Número de Cotiledones:" << vetor[i].nCotiledones <<endl;
			cout<< "Número de Petálas:" << vetor[i].nPetalas <<endl;
			cout<< "Classe:" << vetor[i].classe <<endl;
		}
	}

}

void menu (){
		cout<< "Escolha uma opção abaixo:" << endl;
        cout << "Opção 1: Importar dados CSV" << endl;
        cout << "Opção 2: Busca" << endl;
        cout << "Opção 3: Inserir dados" << endl;
        cout << "Opção 4: Listar dados" << endl;
        cout << "Opção 5: Ordenar" << endl;
        cout << "Opção 6: Remover" << endl;
        cout << "Opção 7: Imprimir intervalo de elementos" << endl;
        cout << "Opção 0: Sair" << endl;	
}

int main (){
	int tam =40, opc, qtde=0;
	Planta *vetor = new Planta [tam];
	
	while(opc!=0){
	menu();
	cin>>opc;
	
	switch(opc){
		case 1: 
		importarCSV(vetor,tam, qtde);
		break;
		case 2:
		break;
		case 3:
		break;
		case 4:
		imprimir(vetor,tam);
		break;
		}
	}
	
	delete [] vetor;
	return 0;
	};
