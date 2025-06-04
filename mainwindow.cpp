#include "mainwindow.h"
#include "./ui_mainwindow.h"


typedef union _virtual_address {
    unsigned long long  value;
    struct {
        unsigned long long offset : 12;
        unsigned long long table : 9;
        unsigned long long directory : 9;
        unsigned long long directory_ptr : 9;
        unsigned long long pml4 : 9;
        unsigned long long reserved : 16;
    };
}VA;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //不可编辑
    ui->PML4_Index->setReadOnly(true);
    ui->PDPTE_Index->setReadOnly(true);
    ui->PDE_Index->setReadOnly(true);
    ui->PTE_Index->setReadOnly(true);   
    ui->offset->setReadOnly(true);
    //设置标题
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_address_textChanged(){
    QString arg1 = ui->address->toPlainText();
    if(arg1.length() >= 16){
        QString cleaned=normalizeKernelAddress(arg1);
        if(!cleaned.isEmpty()){
            bool ok=false;
            unsigned long long addr=cleaned.toULongLong(&ok,16);
            if(ok){
                VA va;
                va.value = addr;
                ui->PML4_Index->setText(QString::number(va.pml4));
                ui->PDPTE_Index->setText(QString::number(va.directory_ptr));
                ui->PDE_Index->setText(QString::number(va.directory));
                ui->PTE_Index->setText(QString::number(va.table));
                ui->offset->setText(QString::number(va.offset));
                ui->PML4_Index_hex->setText(QString::number(va.pml4,16));
                ui->PDPTE_Index_hex->setText(QString::number(va.directory_ptr,16));
                ui->PDE_Index_hex->setText(QString::number(va.directory,16));
                ui->PTE_Index_hex->setText(QString::number(va.table,16));
                ui->offset_hex->setText(QString::number(va.offset,16));
            }else{
                showError("转换失败");
            }
        }else{
            showError("错误的内核地址格式");
        }
    }
}

QString MainWindow::normalizeKernelAddress(const QString& input){
    //
    QString cleaned = input;
    cleaned.remove(QRegularExpression("[^0-9a-fA-F]"));
    cleaned = cleaned.toUpper();
    if (cleaned.length() != 16) {
        return QString();
    }
    return cleaned;
}

void MainWindow::showError(const QString& error){
    QString msg = "Error: " + error;
    ui->PML4_Index->setText(msg);
    ui->PDPTE_Index->setText(msg);
    ui->PDE_Index->setText(msg);
    ui->PTE_Index->setText(msg);
    ui->offset->setText(msg);
    ui->PML4_Index_hex->setText(msg);
    ui->PDPTE_Index_hex->setText(msg);
    ui->PDE_Index_hex->setText(msg);
    ui->PTE_Index_hex->setText(msg);
    ui->offset_hex->setText(msg);
}
