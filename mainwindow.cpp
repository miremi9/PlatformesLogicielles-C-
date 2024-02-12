#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //manager = new DataBaseManager();
    //this->setStyleSheet("background-color: black;");

    //connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(whenButtonIsClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::whenButtonIsClicked()
{
    ui->label->setText("the button has been clicked !");
}

bool MainWindow::verifyInput(QString nom, QString prenom, QString motDePasse, QString typeUtilisateur){
    return nom.isEmpty() || prenom.isEmpty() || motDePasse.isEmpty() || typeUtilisateur.isEmpty();
}

void MainWindow::on_pushButton_clicked()
{
    // Récupérer les informations saisies par l'utilisateur
    QString nom = ui->lineEdit->text();
    QString prenom = ui->lineEdit_2->text();
    QString motDePasse = ui->lineEdit_3->text();
    QString typeUtilisateur;

    // Vérifier le type d'utilisateur sélectionné (utilisateur ou administrateur)
    if(ui->radioButton->isChecked())
    {
        typeUtilisateur = "Utilisateur";
    } else if(ui->radioButton_2->isChecked())
    {
        typeUtilisateur = "Administrateur";
    }

    // Vérifier si tous les champs sont remplis
    if(verifyInput(nom, prenom, motDePasse, typeUtilisateur)) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs !");
    } else {
        User user(nom.toStdString() + prenom.toStdString(), nom.toStdString(), motDePasse.toStdString());
        // Charger les utilisateurs existants depuis le fichier
        QJsonDocument usersDoc = manager->getUsersJSON("users.json");

        if (usersDoc.isNull()) {
            qDebug() << "Erreur lors du chargement du fichier users.json";
            return;
        }

        // Ajouter le nouvel utilisateur à la liste
        manager->addUser(user, usersDoc);

        // Sauvegarder la liste mise à jour dans le fichier
        manager->saveUsers("chemin/vers/le/fichier.json", usersDoc);

        QString message = QString("Utilisateur ajouté : Nom - %1, Prénom - %2, Type - %3")
                              .arg(nom)
                              .arg(prenom)
                              .arg(typeUtilisateur);

        QMessageBox::information(this, "Compte créé", message);

        // Effacer les champs de saisie après la création du compte
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->radioButton->setChecked(false);
        ui->radioButton_2->setChecked(false);
    }

    ui->label->setText("Remplissez tous les champs!");
    ui->pushButton->setStyleSheet(QString::fromUtf8("background-color: blue;"));
}

void MainWindow::on_radioButton_clicked()
{
    ui->label_7->setText("Vous avez choisi utilisateur");
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->label_7->setText("Vous avez choisi Admin");
}

