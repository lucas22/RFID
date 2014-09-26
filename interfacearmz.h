#include <QMainWindow>
#include <QtSql/QtSql>
#include <QtSql/qsqldatabase.h>
#include <QtSql/QSqlError>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
using namespace std;

namespace Ui {
class interfaceArmz;
}

class interfaceArmz : public QMainWindow
{
    Q_OBJECT

public:
    explicit interfaceArmz(QWidget *parent = 0);
    ~interfaceArmz();
    void iniciarUi();
    bool sair();

private slots:
    void on_pushButton_clicked();

    void on_actionCarregarMapa_triggered();

    void on_actionSair_triggered();

    void on_pushButton_2_clicked();

private:
    Ui::interfaceArmz *ui;

};

class dealQuery {
public:
    static string query_;
    static void set_str(string new_str){
        query_ = new_str;
    }
    static std::string get() {
        return query_;
    }
};
