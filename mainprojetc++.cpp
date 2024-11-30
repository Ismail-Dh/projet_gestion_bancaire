
                                        /*PROJET REALISE PAR :
                                        Damouh Ismail
                                        Daouah Imane
                                        Bouhaba Imane9


                                        Assisté par : Mme.Ennaji
                                         */


#include <stdio.h> /*Cette bibliothèque fournit des fonctionnalités d'entrée et de sortie standard,
                     telles que la lecture et l'écriture de fichiers, les opérations d'entrée et de sortie de la console,
                     entre autres choses*/
#include <iostream> //La bibliotheque d entree/sortie
#include <vector> // Bibliothèque pour utiliser des vecteurs
#include <cstdlib> // Bibliothèque pour utiliser des fonctions comme srand, rand, etc.
#include <ctime> // Bibliothèque pour manipuler le temps
#include<string> // Bibliothèque pour manipuler les chaînes de caractères
#include <cctype> // Bibliothèque pour les fonctions de classification de caractères (isalpha, isdigit, etc.)
#include <iomanip> // Bibliothèque pour manipuler la sortie (formatage, etc.)
#include <Windows.h> // Bibliothèque spécifique à Windows pour utiliser des fonctions système
#include<cstdlib> // Redondant, déjà inclus précédemment
#include <fstream> // Bibliothèque pour manipuler les fichiers
#include <algorithm> // Bibliothèque pour utiliser des algorithmes génériques sur des séquences



using namespace std;

class compte
{
public:
    unsigned long long numero; // Numéro de compte
    string type; // Type de compte
    string nomComplet; // Nom complet du titulaire
    double solde; // Solde du compte

public:
    // Constructeur par défaut avec des valeurs par défaut pour les paramètres
    compte(string nomComplet="/0" ,string type="0" ,double solde=0, unsigned long long numero=0){
        srand(time(0)); // Initialisation du générateur de nombres aléatoires
        this->numero= rand() % 10000000000 + 1000000000; // Génération d'un numéro de compte aléatoire
        this->nomComplet=nomComplet; // Initialisation du nom complet
        this->solde=solde; // Initialisation du solde
        this->type=type; // Initialisation du type de compte
    }

    // Constructeur de copie pour créer une copie d'un objet compte
    compte( const compte & c){
        this->numero=c.numero; // Copie du numéro de compte
        this->nomComplet=c.nomComplet; // Copie du nom complet
        this->solde=c.solde; // Copie du solde
        this->type=c.type; // Copie du type de compte
    }

    // Méthode pour afficher les informations d'un compte
    void afficherCompte() {
        cout << " >>> Details du compte <<<" << endl;
        cout << "Numero de compte : " << numero << endl;
        cout << "Nom Complet : " << nomComplet << endl;
        cout << "Type : " << type << endl;
        cout << "Solde : " << solde << "DH" << endl;
    }

    // Méthode pour sauvegarder les informations du compte dans un fichier
    void sauvegarderCompte(ofstream& fichier) const {
        // Serialisation des données du compte dans le fichier
        fichier << numero << " " << type << " " << nomComplet << " " << solde << endl;
    }
};
class Banque
{
    friend class compte;

private:
    vector<compte>comptes;
public:
    Banque(vector<compte> comptes){
        this->comptes=comptes;
    }
    Banque(const Banque & b){
        this->comptes=b.comptes;
    }
    void Update_Data();
    void retirerArgent(unsigned long long numCompte, double montant);
    void afficherTousLesComptes() {
        cout << "Comptes bancaires :" << endl;
        for (int i=0;i<comptes.size();i++){
            cout<<"le compte "<<i+1<< ":"<<endl;
            comptes[i].afficherCompte();
            cout <<"************************"<< endl;
        }
    }
    void chargerComptesDepuisFichier();
    void ouvrirCompte() {
        string type, nomComplet,type1;
        double soldeInit;
        cout << " >>>> Entrez les details du compte : <<<<" << endl;
        cout << " Votre Nom Complet : ";
        cin.clear();   //cin.clear() : efface le signe d'erreur sur cin
	    fflush(stdin);
        getline(cin, nomComplet);
        cout<<" Vous avez le choix entre deux types de comptes : un est specifique aux etudiants[entre E]  et autre est destine aux salaries [entre S] : ";
        cin.clear();
        cin>>type;
        type1=toupper(type[0]);
        while (type1!="E" && type1!="S")
        {
            cout << "Type incorrect : ";
		    cin.clear();
		    fflush(stdin);
            cin >> type;
            type1 = toupper(type[0]);
        }
        if (type1=="S") {
        cout << "\nCombien voulez-vous deposer : [Min=1000] ";
        cin >> soldeInit;
		while (soldeInit < 1000)
		{
			cout << "Minimum est 1000 Ressayer: "<<endl;; //affichage message
			cin >> soldeInit;                    // lire une donnee entree par l'utilisateur
		}
        compte compte(nomComplet,type1,soldeInit);
        comptes.push_back(compte);
        Write_Data();
        cout << "\n\nCompte creer avec succes."<<endl;
       }
        else if (type1=="E") {           // blocks de condition (IF) imbriquées
        cout << "\nCombien voulez-vous deposer : [Min=100] "<<endl;;
        cin >> soldeInit;
		while (soldeInit < 100) //boucle ( while ) avec condition d'arret
		{
			cout << "Minimum est  100 Ressayer: ";
			cin >> soldeInit;    // lire le solde entré par le client
		}
        compte compte(nomComplet,type1,soldeInit);
        comptes.push_back(compte);
        Write_Data();
        cout << "\n\nCompte creer avec succes."<<endl;
    }

    }
    void Write_Data();
    void ajouterArgent(unsigned long long numCompte, double montant);
    void transfererArgent(unsigned long long numero1,unsigned long long numero2,double montant);
    void afficherCompte1(unsigned long long numero);
    void supprimerCompte(unsigned long long numero);
    void modifierCompte(unsigned long long numero, string& nouveauNom, string& nouveauType);
};
void Banque::Write_Data() {  //fonction qui enregistre les information dans un fichier
    ofstream outFile("comptes.txt", ios::app); // Ouverture du fichier en mode ajout (append)

    if (outFile.is_open()) {
        for (const compte& c : comptes) {
            c.sauvegarderCompte(outFile); // Appel de la methode de serialisation pour chaque compte
        }
        outFile.close(); // Fermeture du fichier apres ecriture
        //cout << "Donnees ecrites dans le fichier avec succes." << endl;
    } else {
        cout << "Impossible d'ouvrir le fichier." << endl;
    }
}
void Banque::chargerComptesDepuisFichier() {
    ifstream fichier("comptes.txt");

    if (fichier.is_open()) {
        string ligne;
        while (getline(fichier, ligne)) {
            istringstream iss(ligne);
            unsigned long long   number1 = 0;
            double number2 = 0;
            string str1, str2, str3;

            if (iss >> number1 >> str1 >> str2 >> str3 >> number2) {
                compte c;
                c.numero=number1;
                c.solde=number2;
                c.type=str1;
                c.nomComplet=str2+" "+str3;
                comptes.push_back(c);
            }
        }
        fichier.close();
        cout << "Comptes charges depuis le fichier avec succes."<<endl;
    }
    else {
        cout << "Impossible d'ouvrir le fichier pour charger les comptes."<<endl;
    }
}
void Banque::Update_Data() {
    ofstream outFile("comptes.txt"); // Ouvre le fichier en mode écriture (ce qui écrase le fichier existant)

    if (outFile.is_open()) {
        // Écriture de tous les comptes dans le fichier
        for (const compte& c : comptes) {
            outFile << c.numero << " " << c.type << " " << c.nomComplet << " " << c.solde <<endl;
        }
        outFile.close(); // Ferme le fichier après l'écriture
        cout << "Donnees mises a jour dans le systeme avec succes." <<endl;
    } else {
        cout << "Impossible de ouvrir le fichier." <<endl;
    }
}
void Banque::retirerArgent(unsigned long long numCompte, double montant) {
    // Recherche du compte dans le vecteur 'comptes'
    for (compte& c : comptes) {
        if (c.numero == numCompte) {
            // Vérification si le solde est suffisant pour le retrait
            if (c.solde >= montant) {
                c.solde -= montant; // Effectue le retrait
                Update_Data(); // Met à jour les données dans le fichier après le retrait
                cout << "Retrait de " << montant << " DH effectue avec succes pour le compte numero " << numCompte <<endl;
            } else {
                cout << "Solde insuffisant pour effectuer ce retrait." <<endl;
            }
            return; // Sort de la fonction après le traitement du compte
        }
    }
    cout << "Compte numero " << numCompte << " non trouve." << endl;
}
void Banque::ajouterArgent(unsigned long long numCompte, double montant) {
    // Recherche du compte dans le vecteur 'comptes'
    for (compte& c : comptes) {
        if (c.numero == numCompte) {
                c.solde += montant; // Effectue le retrait
                Update_Data(); // Met à jour les données dans le fichier après le retrait
                cout << "Ajoutait de " << montant << " DH effectue avec succes pour le compte numero " << numCompte <<endl;
            return; // Sort de la fonction après le traitement du compte
        }
    }
    cout << "Compte numero " << numCompte << " non trouve." << endl;
}
void Banque::transfererArgent(unsigned long long numero1, unsigned long long numero2, double montant) {
    compte* source = nullptr;
    compte* destination = nullptr;

    // Recherche du compte source et du compte destination
    for (compte& c : comptes) {
        if (c.numero == numero1) {
            source = &c;
        }
        if (c.numero == numero2) {
            destination = &c;
        }

        // Si les deux comptes ont été trouvés, effectuer le transfert
        if (source != nullptr && destination != nullptr) {
            if (source->solde >= montant) {
                source->solde -= montant;
                destination->solde += montant;
                Update_Data(); // Mettre à jour les données dans le fichier après le transfert
                cout << "Transfert effectue avec succes !" << endl;
            } else {
                cout << "Solde insuffisant pour effectuer le transfert !" << endl;
            }
            return;
        }
    }

    cout << "Compte source ou compte destination introuvable !" << endl;
}
void Banque::afficherCompte1(unsigned long long numero){
    for (compte& c : comptes) {
        if (c.numero == numero) {
            c.afficherCompte();
        }

    }
}
void Banque::supprimerCompte(unsigned long long numero) {
        for (auto it = comptes.begin(); it != comptes.end(); ++it) {
        if (it->numero == numero) {
            comptes.erase(it);
            cout << "Compte supprime avec succes !" << endl;

            // Mise à jour du fichier après la suppression du compte
            Update_Data();
            return;
        }

        }
}
void Banque::modifierCompte(unsigned long long numero, string& nouveauNom, string& nouveauType) {
    for (compte& c : comptes) {
        if (c.numero == numero) {
            c.nomComplet = nouveauNom;
            string type1;
            type1=toupper(nouveauType[0]);
            if(type1=="S"&&c.solde<1000){
                cout<<" votre solde est insuffisant pour effectuer cette modification [Min 1000DH] !"<<endl;
                return;
            }
            c.type = type1;
            Update_Data(); // Mettre à jour les données dans le fichier après la modification
            cout << "Compte modifie avec succes !" << endl;
            return;
        }
    }
    cout << "Compte non trouve." << endl;
}
void LoadingEffect() {
    system("COLOR 0e");
    system("cls");
    std::cout << "\e[?25l";

    // Code page 437 : caractères spéciaux
    int spec = 219;

    std::cout << "\t\t\t\t\t\t------------------------";
    std::cout << "\n\t\t\t\t\t\t|                      | ";
    std::cout << "\n\t\t\t\t\t\t|    Votre banque     |";
    std::cout << "\n\t\t\t\t\t\t|                      |";
    std::cout << "\n\t\t\t\t\t\t------------------------ ";
    std::cout << "\n\n\n\t\t\t\tChargement...";
    std::cout << "\n\n\n\t\t\t\t";

    for (int i = 0; i < 50; ++i) {
        if (i < 10) {
            system("COLOR 0A"); // Change la couleur pour la première partie
        } else if (i < 20) {
            system("COLOR 0B"); // Change la couleur pour la deuxième partie
        } else if (i < 30) {
            system("COLOR 0C"); // Change la couleur pour la troisième partie
        } else if (i < 40) {
            system("COLOR 0D"); // Change la couleur pour la quatrième partie
        } else {
            system("COLOR 0E"); // Change la couleur pour la dernière partie
        }

        std::cout << (char)spec; // Affiche un caractère
        Sleep(60); // Temps d'attente pendant le chargement du menu, ici 60 millisecondes
    }

    system("cls");
    system("COLOR 0b");
    std::cout << "\e[?25h";
}
void system_clear() {  // cette fonction efface l'ecran
    system("cls");
}
int main(){
    LoadingEffect();
    vector<compte> comptes;
    Banque b(comptes);
    b.chargerComptesDepuisFichier();

    int choix;
    do {
        system_clear();
        cout << "\n\t\t\t\t\t***************************************" << endl;
        cout << "\n\t\t\t\t\tBienvenue dans le programme bancaire !" << endl;
        cout << "\n\t\t\t\t\t***************************************" << endl;
        cout << "\n\n\t\t\t\t\t1. Ouvrir un compte";
        cout << "\n\n\t\t\t\t\t2. Afficher un compte";
        cout << "\n\n\t\t\t\t\t3. Modifier un compte";
        cout << "\n\n\t\t\t\t\t4. Ajouter de l'argent";
        cout << "\n\n\t\t\t\t\t5. Retirer de l'argent";
        cout << "\n\n\t\t\t\t\t6. Afficher tous les comptes";
        cout << "\n\n\t\t\t\t\t7. Supprimer un compte";
        cout << "\n\n\t\t\t\t\t8. Transferer de l'argent";
        cout << "\n\n\t\t\t\t\t9. Quitter";
        cout << "\n\n\t\t\t\t\tChoix : ";
        cin >> choix;
        system_clear();
        switch (choix) {
            case 1: {
                b.ouvrirCompte();
                break;
            }
            case 2: {
                unsigned long long numero;
                cout << "Entrez le numero du compte a afficher : ";
                cin >> numero;
                b.afficherCompte1(numero);
                break;
            }
            case 3: {
                unsigned long long numero;
                string nouveauNom, nouveauType;
                cout << "Entrez le numero du compte a modifier : ";
                cin >> numero;
                cout << "Nouveau nom : ";
                cin.ignore(); // Pour vider le buffer
                getline(cin, nouveauNom);
                cout << "Nouveau type : ";
                cin >> nouveauType;
                b.modifierCompte(numero, nouveauNom,nouveauType);
                break;
            }
            case 4: {
                unsigned long long numero;
                double montant;
                cout << "Entrez le numero du compte : ";
                cin >> numero;
                cout << "Montant a ajouter : ";
                cin >> montant;
                b.ajouterArgent(numero, montant);
                break;
            }
            case 5: {
                unsigned long long numero;
                double montant;
                cout << "Entrez le numero du compte : ";
                cin >> numero;
                cout << "Montant a retirer : ";
                cin >> montant;
                b.retirerArgent(numero, montant);
                break;
            }
            case 6: {
                b.afficherTousLesComptes();
                break;
            }
            case 7: {
                unsigned long long numero;
                cout << "Entrez le numero du compte a supprimer : ";
                cin >> numero;
                b.supprimerCompte(numero);
                break;
            }
            case 8: {
                unsigned long long numero1, numero2;
                double montant;
                cout << "Entrez le numero du compte source : ";
                cin >> numero1;
                cout << "Entrez le numero du compte destination : ";
                cin >> numero2;
                cout << "Montant a transferer : ";
                cin >> montant;
                b.transfererArgent(numero1, numero2, montant);
                break;
            }
            case 9: {
                cout << "\n\n\n\n\t\t\t\tMerci pour votre confiance ";
                cout << "\n\n\t\t\t\tCe Projet est realiser par : ";
                system("COLOR 0E");
                cout << "\n\t\t\t\tISMAIL DAMOUH GI 1 ";
                cout << "\n\t\t\t\tIMANE DAOUAH GI 1 ";
                cout << "\n\t\t\t\tIMANE BOUHABA GI 1 "<<endl;
                cout << "\n\t\t\t\tAu revoir !" << endl;
                break;
            }
            default: {
                cout << "Choix invalide !" << endl;
                break;
            }
        }
        cin.clear();
		fflush(stdin);
        cin.get();  // entrer un caractere
        system_clear();
    } while (choix != 9);

    return 0;
}
