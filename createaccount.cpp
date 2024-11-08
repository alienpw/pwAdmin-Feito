#include "createaccount.h"
#include "ui_createaccount.h"

CreateAccount::CreateAccount(User u, bool edit, QWidget *parent) :
    QDialog(parent), isEdit(edit), user(u),
    ui(new Ui::CreateAccount)
{
    ui->setupUi(this);

    ui->txtId->setEnabled(isEdit);
    if (user.id > 0 && isEdit)
    {
        ui->txtId->setText(QString::number(user.id));
        ui->txtNome->setText(user.name.toName());
        ui->txtEmail->setText(user.email.toName());
        ui->txtPergunta->setText(user.prompt.toName());
        ui->txtResposta->setText(user.answer.toName());
        ui->txtTelefone->setText(user.mobilenumber.toName());
        ui->txtUsuario->setText(user.user.toName());
        ui->dtNascimento->setDate(QDate::fromString(user.birthday.toName(), "yyyy-MM-dd"));
    } else
    {
        ui->dtNascimento->setDate(QDate::currentDate());
    }

    if (!isEdit)
    {
        ui->label_2->setText(ui->label_2->text() + "*");
        ui->label_3->setText(ui->label_3->text() + "*");
        ui->label_4->setText(ui->label_4->text() + "*");
    }
}

CreateAccount::~CreateAccount()
{
    delete ui;
}

void CreateAccount::on_btnConfirm_clicked()
{
    QMessageBox msg;
    msg.setStyleSheet(
                "QMessageBox {"
                "background-color: #121212;"
                "color: #ffffff;"
                "}"
                "QPushButton {"
                "background-color: rgb(25,25,25);"
                "color: #ffffff;"
                "}"
                "QLabel {"
                "color: #ffffff;"
                "}");
    msg.setStandardButtons(QMessageBox::Ok);
    if (!isEdit && ui->txtUsuario->text().length() <= 0)
    {
        msg.setWindowTitle("Atenção!");
        msg.setText("Defina um nome de usuário.");
        msg.exec();
        return;
    }
    if (!isEdit && ui->txtNome->text().length() <= 0)
    {
        msg.setWindowTitle("Atenção!");
        msg.setText("Defina um nome.");
        msg.exec();
        return;
    }
    if (!isEdit && ui->txtSenha->text().length() <= 0)
    {
        msg.setWindowTitle("Atenção!");
        msg.setText("Defina uma senha.");
        msg.exec();
        return;
    }
    pwAdmin &pw = pwAdmin::getInstance();
    QByteArray data = (ui->txtUsuario->text() + ui->txtSenha->text()).toUtf8();
    QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Md5);
    QByteArray salt = hash.toHex();
    QByteArray binsalt = "0x" + salt;
    QByteArray base64 = hash.toBase64();
    QString senha = "";
    switch(ui->cbTipoSenha->currentIndex())
    {
    case 0:
        senha = QString(base64); break;
    case 1:
        senha = QString(salt); break;
    case 2:
        senha = QString(binsalt); break;
    }
    QString criar_conta = QString("mysql -h%1 -u%2 -p%3 -P%4 -D%5 -e\"call adduser('%6', '%7', '%8', '%9', '%10', '0', '%11', '%12', '', '', '', '', '', '%13', '%14', '', '%15');\"")
            .arg(pw.infos.mysql_host)
            .arg(pw.infos.mysql_user)
            .arg(pw.infos.mysql_pass)
            .arg(pw.infos.mysql_port)
            .arg(pw.infos.mysql_base)
            .arg(ui->txtUsuario->text())
            .arg(senha)
            .arg(ui->txtPergunta->text())
            .arg(ui->txtResposta->text())
            .arg(ui->txtNome->text())
            .arg(ui->txtEmail->text())
            .arg(ui->txtTelefone->text())
            .arg(ui->cbGenero->currentIndex())
            .arg(ui->dtNascimento->date().toString("yyyy-MM-dd"))
            .arg(ui->txtSenha->text());
    QString alterar_conta = QString("mysql -h%1 -u%2 -p%3 -P%4 -D%5 -e\"UPDATE users SET id='%6', name='%7', %8 Prompt='%9', answer='%10', truename='%11', email='%12', mobilenumber='%13', gender='%14', birthday='%15' %16 WHERE id=%17\"")
            .arg(pw.infos.mysql_host)
            .arg(pw.infos.mysql_user)
            .arg(pw.infos.mysql_pass)
            .arg(pw.infos.mysql_port)
            .arg(pw.infos.mysql_base)
            .arg(ui->txtId->text())
            .arg(ui->txtUsuario->text())
            .arg(ui->txtSenha->text().length() > 0 ? QString("passwd='%1',").arg(senha) : "")
            .arg(ui->txtPergunta->text())
            .arg(ui->txtResposta->text())
            .arg(ui->txtNome->text())
            .arg(ui->txtEmail->text())
            .arg(ui->txtTelefone->text())
            .arg(ui->cbGenero->currentIndex())
            .arg(ui->dtNascimento->date().toString("yyyy-MM-dd"))
            .arg(ui->txtSenha->text().length() > 0 ? QString(",passwd2='%1'").arg(ui->txtSenha->text()) : "")
            .arg(user.id);
    Octets o(criar_conta.toUtf8());
    Octets o2(alterar_conta.toUtf8());
    OctetsStream arg;
    arg.socket = &pw.client;
    arg.compact_uint32(1);
    if (isEdit)
        arg << o2;
    else
        arg << o;
    arg.Send(13);
    msg.setText(isEdit ? "Conta editada com sucesso!" : "Conta criada com sucesso!");
    msg.setWindowTitle("Sucesso!");
    if (msg.exec() == QMessageBox::Ok)
    {
        close();
        setResult(QDialog::Accepted);
    }
}


void CreateAccount::on_btnCancel_clicked()
{
    close();
    setResult(QDialog::Rejected);
}

