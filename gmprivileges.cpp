#include "gmprivileges.h"
#include "ui_gmprivileges.h"

GMPrivileges::GMPrivileges(int tid, QList<int> p, QWidget *parent) :
    QDialog(parent),
    id(tid),
    privileges(p),
    ui(new Ui::GMPrivileges)
{
    ui->setupUi(this);

    list.append("0 - Alterar nome/ID do personagem");
    list.append("1 - Ativar furtividade/invencibilidade");
    list.append("2 - Mudar online ou não");
    list.append("3 - Mutar jogador");
    list.append("4 - Mover para o personagem");
    list.append("5 - Puxar personagem");
    list.append("6 - Mover com Ctrl+Click");
    list.append("7 - Mover para NPC");
    list.append("8 - Mover para mapa específico");
    list.append("9 - Melhora a velocidade");
    list.append("10 - Seguir o jogador");
    list.append("11 - Obter a lista de jogadores online");
    list.append("100 - Força o jogador a ficar offline");
    list.append("101 - Proibir conversa");
    list.append("102 - Proibir comércio");
    list.append("103 - Proibir vendas");
    list.append("104 - Transmissão de chat do sistema");
    list.append("105 - Desligar o servidor");
    list.append("200 - Invocar monstros");
    list.append("201 - Desativar eventos");
    list.append("202 - Ativar eventos");
    list.append("203 - Ícone GM");
    list.append("204 - Duplo exp");
    list.append("205 - Conexões simultâneas");
    list.append("206 - Gerencia atividades");
    list.append("207 - Proibir comércio (lojinha)");
    list.append("208 - Proibir leilão");
    list.append("209 - Proibir correio");
    list.append("210 - Proibir facção");
    list.append("211 - Duplo dinheiro");
    list.append("212 - Duplo drop");
    list.append("213 - Duplo alma");
    list.append("214 - Desativa cartões de ponto de venda");
    list.append("215 - Interruptor PVP");
    Load();
}

GMPrivileges::~GMPrivileges()
{
    delete ui;
}

void GMPrivileges::Load()
{
    for (QString &text : list)
    {
        QListWidgetItem *item = new QListWidgetItem(text, ui->listWidget);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        auto split = text.split(' ');
        int num = split[0].toInt();
        if (privileges.contains(num))
            item->setCheckState(Qt::Checked);
        else item->setCheckState(Qt::Unchecked);
    }
}

void GMPrivileges::on_btnCancel_clicked()
{
    close();
}


void GMPrivileges::on_btnConfirm_clicked()
{
    for(int i = 0; i < ui->listWidget->count(); ++i)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        if (item->checkState() == Qt::Checked)
        {
            returnPrivileges.append(item->text().split(' ')[0].toInt());
        }
    }
    close();
    setResult(QDialog::Accepted);
}


void GMPrivileges::on_btn_checkAll_clicked()
{
    for(int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem *item = ui->listWidget->item(i);
        item->setCheckState(Qt::Checked);
    }
}


void GMPrivileges::on_btn_uncheckAll_clicked()
{
    for(int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem *item = ui->listWidget->item(i);
        item->setCheckState(Qt::Unchecked);
    }
}

