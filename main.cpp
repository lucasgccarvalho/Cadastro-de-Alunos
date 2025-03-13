#include <iostream>
#include <locale.h>
#include <string>
#include <vector>

using namespace std;

struct gradesStruct {
    string name;
    double grades[5];
    string subjects[5];
    int numOfGrades;
    double media;
};

vector<gradesStruct> studentsArray;
vector<string> historyArray;
double averageGrades;
int chooseStudent;
int switchGeneralMenu;

// Utilitários
void pressEnterKey() {    
    cout << endl << "Pressione Enter para continuar..." << endl;
    cin.get();
    cin.ignore();
}

void clearTerminal() {
    #if defined(_WIN32) || defined(_WIN64)
            system("cls"); 
    #elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
            system("clear");
    #else
            cout << "Não foi possível limpar a tela nesse OS." << endl;
    #endif
}

void addOnHistory(string operation) {
    historyArray.push_back(operation);
}

bool verifyStudents() {
    if (studentsArray.size() == 0) {
        cout << "Ainda não há alunos cadastrados!" << endl;
        return false;
    }
    return true;
}

void showHistory() {
    clearTerminal();
    if (historyArray.size() == 0) {
        cout << "Nenhuma operação foi realizada ainda!" << endl;
    } else {
        for (int i = 0; i < historyArray.size(); i++) {
            cout << i + 1 << ". " << historyArray[i] << endl;
        }
    }
    pressEnterKey();
}

void addNewStudent() {
    clearTerminal();
    gradesStruct newStudent;

    cout << "Insira o nome do " << studentsArray.size() + 1 << "° Aluno: ";
    getline(cin >> ws, newStudent.name);

    cout << "Quantas disciplinas deseja inserir? ";
    cin >> newStudent.numOfGrades;
    cin.ignore();

    while (newStudent.numOfGrades > 5 || newStudent.numOfGrades <= 0) {
        cout << "Número de disciplinas inválido! Insira de 1 a 5: ";
        cin >> newStudent.numOfGrades;
        cin.ignore();
    }

    for (int i = 0; i < newStudent.numOfGrades; i++) {
        cout << endl;
        cout << "Insira o nome da " << i + 1 << "° disciplina: ";
        getline(cin >> ws, newStudent.subjects[i]);
        cout << "Insira a nota da " << i + 1 << "° disciplina: ";
        cin >> newStudent.grades[i];
        cin.ignore();

        while (newStudent.grades[i] > 10 || newStudent.grades[i] < 0) {
            cout << "Nota inválida! Insira uma nota válida (0 a 10): ";
            cin >> newStudent.grades[i];
            cin.ignore();
        }
    }

    studentsArray.push_back(newStudent);
    addOnHistory("O aluno " + newStudent.name + " foi adicionado.");
}

void showStudents() {
    for (int i = 0; i < studentsArray.size(); i++) {
        cout << endl << i + 1 << ". " << studentsArray[i].name << ": " << endl;
        for (int j = 0; j < studentsArray[i].numOfGrades; j++) {
            cout << studentsArray[i].subjects[j] << ": " << studentsArray[i].grades[j] << endl;
        }
         
    }
    cout << endl;
}

void verifyStudentChoosed(int choosedStudent) {
    choosedStudent--;
    while (choosedStudent >= studentsArray.size() || choosedStudent < 0) {
        cout << "Valor Inválido!!\nSelecione um número de 1 a " << studentsArray.size() << ": ";
        cin >> choosedStudent;
        choosedStudent--;
    }
    chooseStudent = choosedStudent;
}

double aStudentAverageUtil(int choosedStudent) {
    double sumAllGrades = 0;
    for (int i = 0; i < studentsArray[choosedStudent].numOfGrades; i++) {
        sumAllGrades += studentsArray[choosedStudent].grades[i];
    }
    return sumAllGrades / studentsArray[choosedStudent].numOfGrades;
}

void aStudentAverage() {
    clearTerminal();
    if (verifyStudents()) {
        cout << "Escolha um aluno para exibir a média: " << endl;
        showStudents();
        cin >> chooseStudent;
        verifyStudentChoosed(chooseStudent);
        cout << endl << "A média das notas de " << studentsArray[chooseStudent].name << " é " << aStudentAverageUtil(chooseStudent) << endl;
        addOnHistory("Exibição da média das notas de " + studentsArray[chooseStudent].name + ".");
    }
    pressEnterKey();
}

void studentStatus() {
    clearTerminal();
    if (verifyStudents()) {
        cout << "Escolha um aluno para exibir o status: " << endl;
        showStudents();
        cin >> chooseStudent;
        verifyStudentChoosed(chooseStudent);

        double average = aStudentAverageUtil(chooseStudent);
        if (average >= 7) {
            cout << endl << studentsArray[chooseStudent].name << " foi APROVADO!" << endl;
        } else if (average > 5) {
            cout << endl << studentsArray[chooseStudent].name << " ficou de RECUPERAÇÃO!" << endl;
        } else {
            cout << endl << studentsArray[chooseStudent].name << " foi REPROVADO!" << endl;
        }
        addOnHistory("Exibição do status de " + studentsArray[chooseStudent].name + ".");
    }
    pressEnterKey();
}

void allStudentsAverages() {
    clearTerminal();
    if (verifyStudents()) {
        for (int i = 0; i < studentsArray.size(); i++) {
            cout << "[" << i + 1 << "] " << studentsArray[i].name << ": " << endl;
            for (int j = 0; j < studentsArray[i].numOfGrades; j++) {
                cout << studentsArray[i].subjects[j] << ": " << studentsArray[i].grades[j] << endl;
            }
            cout << "Média: " << aStudentAverageUtil(i) << endl << endl;
        }
        addOnHistory("Exibição das notas e médias de todos os alunos.");
    }
    pressEnterKey();
}

void mainMenu() {
    clearTerminal();
    cout << "Insira uma das opções abaixo: " << endl;
    cout << "[1] Inserir notas." << endl;
    cout << "[2] Calcular média de um aluno." << endl;
    cout << "[3] Exibir status do aluno." << endl;
    cout << "[4] Exibir notas e médias de todos os alunos." << endl;
    cout << "[5] Histórico de operações." << endl;
    cout << "[6] Sair." << endl;
    cin >> switchGeneralMenu;
    while (switchGeneralMenu > 6 || switchGeneralMenu < 1) {
        cout << "Valor inválido! Insira um valor válido (1 a 6): ";
        cin >> switchGeneralMenu;
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    while (true) {
    mainMenu();

    if (switchGeneralMenu == 6) {
        break;
    }

    switch (switchGeneralMenu) {
        case 1:
            addNewStudent();
            break;
        case 2:
            aStudentAverage();
            break;
        case 3:
            studentStatus();
            break;
        case 4:
            allStudentsAverages();
            break;
        case 5:
            showHistory();
            break;
    }
}
    return 0;
}