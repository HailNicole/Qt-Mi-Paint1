#include "principal.h"
#include "ui_principal.h"

#define DEFAULT_ANCHO 3

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    setWindowTitle("MI PAINT");
    // Instanciando la imagen (creando)
    mImagen = new QImage(this->size(),QImage::Format_ARGB32_Premultiplied);
    // Rellenar la imagen de color blanco
    mImagen->fill(Qt::white);
    // Instanciar el Painter a partir de la imagen
    mPainter = new QPainter(mImagen);
    mPainter->setRenderHint(QPainter::Antialiasing);
    // Inicializar otras variables
    mPuedeDibujar = false;
    mColor = Qt::black;
    mAncho = DEFAULT_ANCHO;
    mNumLineas = 0;
    m_ops = 1;
    ui->actionLibre->setChecked(true);
}

Principal::~Principal()
{
    delete ui;
    delete mPainter;
    delete mImagen;
}

void Principal::paintEvent(QPaintEvent *event)
{
    // Crear el painter de la ventana principal
    QPainter painter(this);
    // Dibujar la imagen
    painter.drawImage(0, 0, *mImagen);
    // Aceptar el evento
    event->accept();
}

void Principal::mousePressEvent(QMouseEvent *event)
{
    // Levanta la bandera (para que se pueda dibujar)
    mPuedeDibujar = true;
    // Captura la posición (punto x,y) del mouse
    mInicial = event->pos();
    // Acepta el evento
    event->accept();
}

void Principal::mouseMoveEvent(QMouseEvent *event)
{
    // Validar si se puede dibujar
    if ( !mPuedeDibujar ) {
        // Acepta el evento
        event->accept();
        // Salir del método
        return;
    }
    // Capturar el punto a donde se mueve el mouse
    mFinal = event->pos();
    // Crear un pincel y establecer atributos
    QPen pincel;
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);
    if(m_ops==1){
        // Dibujar una linea
        mPainter->setPen(pincel);
        mPainter->drawLine(mInicial, mFinal);
        // Mostrar el número de líneas en la barra de estado
        ui->statusbar->showMessage("Número de líneas: " + QString::number(++mNumLineas));
        // Actualizar la interfaz (repinta con paintEvent)
        update();
        // actualizar el punto inicial
        mInicial = mFinal;
     }
}

void Principal::mouseReleaseEvent(QMouseEvent *event)
{
    // Bajar la bandera (no se puede dibujar)
    mPuedeDibujar = false;
    mFinal= event->pos();
    QPen pincel;
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);

    if(m_ops==2){
        mPainter->setPen(pincel);
        mPainter->drawLine(mInicial,mFinal);
        update();
        event->accept();
    }
    if(m_ops==3){
        QRect rectangulo (mInicial, mFinal);
        mPainter->setPen(pincel);
        mPainter->drawRect(rectangulo);
        update();
        event->accept();
    }
    if(m_ops==4){
        QRectF circulos (mInicial, mFinal);
        mPainter->setPen(pincel);
        mPainter->drawEllipse(circulos);
        update();
        event->accept();
    }
}


void Principal::on_actionAncho_triggered()
{
    mAncho = QInputDialog::getInt(this,
                                  "Ancho del pincel",
                                  "Ingrese el ancho del pincel de dibujo",
                                  mAncho,
                                  1, 20);
}

void Principal::on_actionSalir_triggered()
{
    this->close();
}

void Principal::on_actionColor_triggered()
{
    mColor = QColorDialog::getColor(mColor,
                                    this,
                                    "Color del pincel");
}

void Principal::on_actionNuevo_triggered()
{
    mImagen->fill(Qt::white);
    mNumLineas = 0;
    update();
}

void Principal::on_actionGuardar_triggered()
{
    // Abrir cuadro de diálogo para obtener el nombre del archivo
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar imagen",
                                                         QDir::home().absolutePath() + "/img.png",
                                                         "Imágenes .png (*.png)");
    // Validar que el nombre del archivo no sea vacío
    if ( !nombreArchivo.isEmpty() ){
        // Guardar imagen
        if (mImagen->save(nombreArchivo)){
            // Si todo va bien, muestra un mensaje de información
            QMessageBox::information(this,
                                     "Guardar imagen",
                                     "Archivo almacenado en: " + nombreArchivo);
        } else{
            // Si hay algún error, muestro advertencia
            QMessageBox::warning(this,
                                 "Guardar imagen",
                                 "No se pudo almacenar la imagen.");
        }
    }
}

void Principal::on_actionLibre_triggered()
{
    ui->actionLineas->setChecked(false);
    ui->actionLibre->setChecked(true);
    ui->actionRect_nculos->setChecked(false);
    ui->actionCircunferencias->setChecked(false);
}

void Principal::on_actionLineas_triggered()
{
    m_ops = 2;
    ui->actionLineas->setChecked(true);
    ui->actionLibre->setChecked(false);
    ui->actionRect_nculos->setChecked(false);
    ui->actionCircunferencias->setChecked(false);
}


void Principal::on_actionRect_nculos_triggered()
{
    m_ops = 3;
    ui->actionLineas->setChecked(false);
    ui->actionLibre->setChecked(false);
    ui->actionRect_nculos->setChecked(true);
    ui->actionCircunferencias->setChecked(false);
}


void Principal::on_actionCircunferencias_triggered()
{
    m_ops = 4;
    ui->actionLineas->setChecked(false);
    ui->actionLibre->setChecked(false);
    ui->actionRect_nculos->setChecked(false);
    ui->actionCircunferencias->setChecked(true);
}


void Principal::on_actionAbrir_triggered()
{
    QString nombreArchivo = QFileDialog::getOpenFileName(this,"Imagen",QDir::home().absolutePath(),"Imagenes(*.jpg *.jpeg *.png);;Todos los ficheros(*)");

           if (nombreArchivo.isNull()){
              QMessageBox::warning(this, "Mi Paint", "No se puede abrir el archivo");
              return;
        }
        m_picture.load(nombreArchivo);
        m_picture = m_picture.scaled(ui->centralwidget->size(), Qt::KeepAspectRatio);
        mImagen = new QImage(m_picture);

        mPainter = new QPainter(mImagen);
        mPainter->setRenderHint(QPainter::Antialiasing);
}
