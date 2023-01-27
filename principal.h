#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDebug>
#include <QInputDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


private slots:
    void on_actionAncho_triggered();

    void on_actionSalir_triggered();

    void on_actionColor_triggered();

    void on_actionNuevo_triggered();

    void on_actionGuardar_triggered();

    void on_actionLineas_triggered();

    void on_actionRect_nculos_triggered();

    void on_actionCircunferencias_triggered();

    void on_actionAbrir_triggered();

    void on_actionLibre_triggered();

private:
    Ui::Principal *ui;
    QImage *mImagen, m_picture;        // Imagen sobre la que se va a dibujar
    QPainter *mPainter;     // Painter de la imagen
    QPoint mInicial;        // Punto incial para dibujar la línea
    QPoint mFinal;          // Punto final para dibujar la línea
    bool mPuedeDibujar;     // Determina si debe o no dibujar
    int mAncho;             // Define el ancho del pincel
    QColor mColor;          // Define el color del pincel
    int mNumLineas;         // Cuenta el número de líneas
    int m_ops;
    QString m_nombre;
};
#endif // PRINCIPAL_H
