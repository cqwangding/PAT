#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    scene=NULL;
    refresh=false;
    mouseFlag=0;
    ui->setupUi(this);
    ui->graphicsView->viewport()->installEventFilter( this );
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);
    loadconfig("config.ini");
}

MainWindow::~MainWindow()
{
    if(scene)
        delete scene;
    delete timer;
    delete ui;
}

void MainWindow::loadconfig(QString filename)
{
    config patconfig;
    if(patconfig.openfile(filename))
    {
        QString value;

        //device
        value=patconfig.getvalue("device,hole_diameter");
        spot::hole_diameter=value.toDouble();
        value=patconfig.getvalue("device,hole_space");
        spot::hole_space=value.toDouble();
        value=patconfig.getvalue("device,distance");
        spot::distance=value.toDouble();

        //data
        value=patconfig.getvalue("data,pixel");
        spot::pixel=value.toDouble();
        value=patconfig.getvalue("data,spot_intensitymin");
        spot::spot_intensitymin=value.toDouble();
        value=patconfig.getvalue("data,spot_areamin");
        spot::spot_areamin=value.toInt();
        value=patconfig.getvalue("data,particle_number");
        imageanalyse::particle_num=value.toInt();

        patconfig.closefile();
    }
}

void MainWindow::saveconfig(QString filename)
{
    config patconfig;
}

void MainWindow::update()
{
    if(!step.contains("loadimage"))
        return;
    else if(step.last()=="selectrange")
    {
        if(mouseFlag==1)
        {
            showimage=selectimage.scaled(ui->graphicsView->width(),ui->graphicsView->height());
            putimage(showimage);
        }
        else if(mouseFlag==2)
        {
            if(selectBegin.x()<0)
                selectBegin.setX(0);
            if(selectBegin.y()<0)
                selectBegin.setY(0);
            if(selectBegin.x()>ui->graphicsView->width())
                selectBegin.setX(ui->graphicsView->width());
            if(selectBegin.y()>ui->graphicsView->height())
                selectBegin.setY(ui->graphicsView->height());
            if(selectEnd.x()<0)
                selectEnd.setX(0);
            if(selectEnd.y()<0)
                selectEnd.setY(0);
            if(selectEnd.x()>ui->graphicsView->width())
                selectEnd.setX(ui->graphicsView->width());
            if(selectEnd.y()>ui->graphicsView->height())
                selectEnd.setY(ui->graphicsView->height());
            showimage=selectimage.scaled(ui->graphicsView->width(),ui->graphicsView->height());
            QColor color(255,0,0);
            QPainter painter(&showimage);
            painter.setPen(color);
            painter.drawLine(selectBegin.x(),selectBegin.y(),selectEnd.x(),selectBegin.y());
            painter.drawLine(selectBegin.x(),selectBegin.y(),selectBegin.x(),selectEnd.y());
            painter.drawLine(selectBegin.x(),selectEnd.y(),selectEnd.x(),selectEnd.y());
            painter.drawLine(selectEnd.x(),selectBegin.y(),selectEnd.x(),selectEnd.y());
            putimage(showimage);
        }
        else if(mouseFlag==3)
        {
            if(selectBegin.x()<0)
                selectBegin.setX(0);
            if(selectBegin.y()<0)
                selectBegin.setY(0);
            if(selectBegin.x()>ui->graphicsView->width())
                selectBegin.setX(ui->graphicsView->width());
            if(selectBegin.y()>ui->graphicsView->height())
                selectBegin.setY(ui->graphicsView->height());
            if(selectEnd.x()<0)
                selectEnd.setX(0);
            if(selectEnd.y()<0)
                selectEnd.setY(0);
            if(selectEnd.x()>ui->graphicsView->width())
                selectEnd.setX(ui->graphicsView->width());
            if(selectEnd.y()>ui->graphicsView->height())
                selectEnd.setY(ui->graphicsView->height());
            mouseFlag=0;
            QPoint sBegin,sEnd;
            sBegin.setX(selectBegin.x()/double(ui->graphicsView->width())*double(selectimage.width()));
            sBegin.setY(selectBegin.y()/double(ui->graphicsView->height())*double(selectimage.height()));
            sEnd.setX(selectEnd.x()/double(ui->graphicsView->width())*double(selectimage.width()));
            sEnd.setY(selectEnd.y()/double(ui->graphicsView->height())*double(selectimage.height()));
            selectimage=selectimage.copy(sBegin.x(),sBegin.y(),sEnd.x()-sBegin.x(),sEnd.y()-sBegin.y());
            showimage=selectimage.scaled(ui->graphicsView->width(),ui->graphicsView->height());
            putimage(showimage);
        }
    }
    else if(step.last()=="rotateimage")
    {
        if(mouseFlag==1)
        {
            showimage=selectimage.scaled(ui->graphicsView->width(),ui->graphicsView->height());
            putimage(showimage);
        }
        else if(mouseFlag==2)
        {
            if(selectBegin.x()<0)
                selectBegin.setX(0);
            if(selectBegin.y()<0)
                selectBegin.setY(0);
            if(selectBegin.x()>ui->graphicsView->width())
                selectBegin.setX(ui->graphicsView->width());
            if(selectBegin.y()>ui->graphicsView->height())
                selectBegin.setY(ui->graphicsView->height());
            if(selectEnd.x()<0)
                selectEnd.setX(0);
            if(selectEnd.y()<0)
                selectEnd.setY(0);
            if(selectEnd.x()>ui->graphicsView->width())
                selectEnd.setX(ui->graphicsView->width());
            if(selectEnd.y()>ui->graphicsView->height())
                selectEnd.setY(ui->graphicsView->height());
            showimage=selectimage.scaled(ui->graphicsView->width(),ui->graphicsView->height());
            QColor color(255,0,0);
            QPainter painter(&showimage);
            painter.setPen(color);
            painter.drawLine(selectBegin.x(),selectBegin.y(),selectEnd.x(),selectEnd.y());
            putimage(showimage);
        }
        else if(mouseFlag==3)
        {
            if(selectBegin.x()<0)
                selectBegin.setX(0);
            if(selectBegin.y()<0)
                selectBegin.setY(0);
            if(selectBegin.x()>ui->graphicsView->width())
                selectBegin.setX(ui->graphicsView->width());
            if(selectBegin.y()>ui->graphicsView->height())
                selectBegin.setY(ui->graphicsView->height());
            if(selectEnd.x()<0)
                selectEnd.setX(0);
            if(selectEnd.y()<0)
                selectEnd.setY(0);
            if(selectEnd.x()>ui->graphicsView->width())
                selectEnd.setX(ui->graphicsView->width());
            if(selectEnd.y()>ui->graphicsView->height())
                selectEnd.setY(ui->graphicsView->height());
            mouseFlag=0;
            double dx,dy;
            dx=qAbs(selectEnd.x()-selectBegin.x());
            dy=qAbs(selectEnd.y()-selectBegin.y());
            double angle;
            if(dx>dy)
                angle=-atan(dy/dx);
            else
                angle=atan(dx/dy);
            QTransform myTransform;
            myTransform.rotate(angle/3.1415926535*180);
            selectimage=selectimage.transformed(myTransform);
            showimage=selectimage.scaled(ui->graphicsView->width(),ui->graphicsView->height());
            putimage(showimage);
        }
    }
    else if(step.last()=="separatespots")
    {
        if(mouseFlag==1)
        {
            showimage=selectimage.scaled(ui->graphicsView->width(),ui->graphicsView->height());
            putimage(showimage);
        }
        else if(mouseFlag==2)
        {
            if(selectBegin.x()<0)
                selectBegin.setX(0);
            if(selectBegin.y()<0)
                selectBegin.setY(0);
            if(selectBegin.x()>ui->graphicsView->width())
                selectBegin.setX(ui->graphicsView->width());
            if(selectBegin.y()>ui->graphicsView->height())
                selectBegin.setY(ui->graphicsView->height());
            if(selectEnd.x()<0)
                selectEnd.setX(0);
            if(selectEnd.y()<0)
                selectEnd.setY(0);
            if(selectEnd.x()>ui->graphicsView->width())
                selectEnd.setX(ui->graphicsView->width());
            if(selectEnd.y()>ui->graphicsView->height())
                selectEnd.setY(ui->graphicsView->height());
            showimage=selectimage.scaled(ui->graphicsView->width(),ui->graphicsView->height());
            QColor color(255,0,0);
            QPainter painter(&showimage);
            painter.setPen(color);
            painter.drawLine(selectBegin.x(),selectBegin.y(),selectEnd.x(),selectEnd.y());
            putimage(showimage);
        }
        else if(mouseFlag==3)
        {
            if(selectBegin.x()<0)
                selectBegin.setX(0);
            if(selectBegin.y()<0)
                selectBegin.setY(0);
            if(selectBegin.x()>ui->graphicsView->width())
                selectBegin.setX(ui->graphicsView->width());
            if(selectBegin.y()>ui->graphicsView->height())
                selectBegin.setY(ui->graphicsView->height());
            if(selectEnd.x()<0)
                selectEnd.setX(0);
            if(selectEnd.y()<0)
                selectEnd.setY(0);
            if(selectEnd.x()>ui->graphicsView->width())
                selectEnd.setX(ui->graphicsView->width());
            if(selectEnd.y()>ui->graphicsView->height())
                selectEnd.setY(ui->graphicsView->height());
            mouseFlag=0;
            center=selectBegin;
            spot::center.setX(center.x()/double(ui->graphicsView->width())*double(selectimage.width()));
            spot::center.setY(center.y()/double(ui->graphicsView->height())*double(selectimage.height()));
            spotscountDialog scdialog;
            int spotscount=scdialog.exec();
            spot_space_x=double(fabs(selectEnd.x()-selectBegin.x()))/double(spotscount);
            spot::spot_space=spot_space_x/double(ui->graphicsView->width())*double(selectimage.width());
            spot_space_y=spot::spot_space/double(selectimage.height())*double(ui->graphicsView->height());
            imageanalyse::spot_x_min=-int(spot::center.x()/spot::spot_space-0.5);
            imageanalyse::spot_x_max=int((double(selectimage.width())-spot::center.x())/spot::spot_space-0.5);
            imageanalyse::spot_y_min=-int(spot::center.y()/spot::spot_space-0.5);
            imageanalyse::spot_y_max=int((double(selectimage.height())-spot::center.y())/spot::spot_space-0.5);
            imageanalyse::spot_num=(imageanalyse::spot_x_max-imageanalyse::spot_x_min+1)*(imageanalyse::spot_y_max-imageanalyse::spot_y_min+1);
            //imanalyse.getallspots();
            showimage=selectimage.scaled(ui->graphicsView->width(),ui->graphicsView->height());
            QColor color(255,0,0);
            QPainter painter(&showimage);
            painter.setPen(color);
            int i,j;
            for(i=imageanalyse::spot_x_min;i<=imageanalyse::spot_x_max+1;i++)
            {
                j=int(center.x()+(double(i)-0.5)*spot_space_x);
                painter.drawLine(j,0,j,showimage.height());
            }
            for(i=imageanalyse::spot_y_min;i<=imageanalyse::spot_y_max+1;i++)
            {
                j=int(center.y()+(double(i)-0.5)*spot_space_y);
                painter.drawLine(0,j,showimage.width(),j);
            }
            putimage(showimage);
        }
    }
}

void MainWindow::putimage(QImage image)
{
    if (scene)
        delete scene;
    scene=new QGraphicsScene();
    scene->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView->setScene(scene);
}

void MainWindow::putstatus(QString _s, bool _clear=false)
{
    if(_clear)
        ui->Status->setPlainText(_s);
    else
    {
        QString temp;
        temp=ui->Status->toPlainText();
        ui->Status->setPlainText(_s+"\r\n"+temp);
    }
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    QMouseEvent *mouseEvent;
    if (event->type() == QEvent::MouseButtonPress )
    {
        if ( object == ui->graphicsView->viewport() )
        {
            mouseFlag=1;
            mouseEvent = static_cast<QMouseEvent*>(event);
            selectBegin.setX(mouseEvent->x());
            selectBegin.setY(mouseEvent->y());
            selectEnd.setX(mouseEvent->x());
            selectEnd.setY(mouseEvent->y());
            ui->graphicsView->setMouseTracking( true );
        }
        return QObject::eventFilter(object, event);
    }
    else if (event->type() == QEvent::MouseMove )
    {
        if ( object == ui->graphicsView->viewport() )
        {
            mouseFlag=2;
            mouseEvent = static_cast<QMouseEvent*>(event);
            selectEnd.setX(mouseEvent->x());
            selectEnd.setY(mouseEvent->y());
         }
        return QObject::eventFilter(object, event);
    }
    else if (event->type() == QEvent::MouseButtonRelease )
    {
        if ( object == ui->graphicsView->viewport() )
        {
            mouseFlag=3;
            mouseEvent = static_cast<QMouseEvent*>(event);
            selectEnd.setX(mouseEvent->x());
            selectEnd.setY(mouseEvent->y());
            ui->graphicsView->setMouseTracking( false );
         }
        return QObject::eventFilter(object, event);
    }
    return QObject::eventFilter(object, event);
}

void MainWindow::on_loadImage_clicked()
{
    putstatus("Loadimage start!");
    step.clear();
    QString filename=QFileDialog::getOpenFileName();
    image.load(filename);
    selectimage=image;
    step.push_back("loadimage");
    showimage=selectimage.scaled(ui->graphicsView->width(),ui->graphicsView->height());
    putimage(showimage);
    putstatus("Loadimage End!");
}

void MainWindow::on_selectRage_clicked()
{
    if(step.contains("loadimage"))
        while(step.last()!="loadimage")
            step.pop_back();
    else
    {
        putstatus("Please loadimage first!");
        return;
    }
    step.push_back("selectrange");
    selectimage=image;
    showimage=selectimage.scaled(ui->graphicsView->width(),ui->graphicsView->height());
    putimage(showimage);
    putstatus("Select image range!");
}

void MainWindow::on_ratateImage_clicked()
{
    if(step.contains("loadimage"))
        while(step.last()!="loadimage"&&step.last()!="selectrange")
            step.pop_back();
    else
    {
        putstatus("Please loadimage first!");
        return;
    }
    step.push_back("rotateimage");
    putstatus("Set spot alignment!");
}

void MainWindow::on_separateSpots_clicked()
{
    if(step.contains("loadimage"))
        while(step.last()!="loadimage"&&step.last()!="selectrange"&&step.last()!="rotateimage")
            step.pop_back();
    else
    {
        putstatus("Please loadimage first!");
        return;
    }
    step.push_back("separatespots");
    putstatus("Set spot center and spot distance!");
}

void MainWindow::on_denoise_clicked()
{
    if(step.contains("signalmark"))
        while(step.last()!="signalmark")
            step.pop_back();
    else
    {
        putstatus("Please signal mark first!");
        return;
    }
    step.push_back("denoise");
    putstatus("Denoise start!");
    //imanalyse.loadimage(selectimage);
    imanalyse.denoise();
    showimage=imanalyse.getdenoiseimage().scaled(ui->graphicsView->width(),ui->graphicsView->height());
    QColor color(255,0,0);
    QPainter painter(&showimage);
    painter.setPen(color);
    int i,j;
    for(i=imageanalyse::spot_x_min;i<=imageanalyse::spot_x_max+1;i++)
    {
        j=int(center.x()+(double(i)-0.5)*spot_space_x);
        painter.drawLine(j,0,j,showimage.height());
    }
    for(i=imageanalyse::spot_y_min;i<=imageanalyse::spot_y_max+1;i++)
    {
        j=int(center.y()+(double(i)-0.5)*spot_space_y);
        painter.drawLine(0,j,showimage.width(),j);
    }
    putimage(showimage);
    putstatus("Denoise end!");
}

void MainWindow::on_signalMark_clicked()
{
    if(step.contains("separatespots"))
        while(step.last()!="separatespots")
            step.pop_back();
    else
    {
        putstatus("Please separate spots first!");
        return;
    }
    step.push_back("signalmark");
    putstatus("Signal mark start!");
    imanalyse.loadimage(selectimage);
    imanalyse.signalmark();
    showimage=imanalyse.getsignalimage().scaled(ui->graphicsView->width(),ui->graphicsView->height());
    QColor color(255,0,0);
    QPainter painter(&showimage);
    painter.setPen(color);
    int i,j;
    for(i=imageanalyse::spot_x_min;i<=imageanalyse::spot_x_max+1;i++)
    {
        j=int(center.x()+(double(i)-0.5)*spot_space_x);
        painter.drawLine(j,0,j,showimage.height());
    }
    for(i=imageanalyse::spot_y_min;i<=imageanalyse::spot_y_max+1;i++)
    {
        j=int(center.y()+(double(i)-0.5)*spot_space_y);
        painter.drawLine(0,j,showimage.width(),j);
    }
    putimage(showimage);
    putstatus("Signal mark end!");
}

void MainWindow::on_curveFit_clicked()
{
    if(step.contains("signalmark"))
        while(step.last()!="signalmark")
            step.pop_back();
    else
    {
        putstatus("Please signal mark first!");
        return;
    }
    step.push_back("curvefit");
    putstatus("Curvefit start!");
    //imanalyse.loadimage(selectimage);
    imanalyse.curvefitting();
    showimage=imanalyse.getfitimage().scaled(ui->graphicsView->width(),ui->graphicsView->height());
    QColor color(255,0,0);
    QPainter painter(&showimage);
    painter.setPen(color);
    int i,j;
    for(i=imageanalyse::spot_x_min;i<=imageanalyse::spot_x_max+1;i++)
    {
        j=int(center.x()+(double(i)-0.5)*spot_space_x);
        painter.drawLine(j,0,j,showimage.height());
    }
    for(i=imageanalyse::spot_y_min;i<=imageanalyse::spot_y_max+1;i++)
    {
        j=int(center.y()+(double(i)-0.5)*spot_space_y);
        painter.drawLine(0,j,showimage.width(),j);
    }
    putimage(showimage);
    putstatus("Curvefit end!");
}

void MainWindow::on_combineData_clicked()
{
    if(step.contains("curvefit"))
        while(step.last()!="curvefit")
            step.pop_back();
    else
    {
        putstatus("Please curve fit first!");
        return;
    }
    step.push_back("combinedata");
    putstatus("Combine data start!");
    //imanalyse.loadimage(selectimage);
    imanalyse.datacombine();
    showimage=imanalyse.getcombineimage().scaled(ui->graphicsView->width(),ui->graphicsView->height());
    QColor color(255,0,0);
    QPainter painter(&showimage);
    painter.setPen(color);
    int i,j;
    for(i=imageanalyse::spot_x_min;i<=imageanalyse::spot_x_max+1;i++)
    {
        j=int(center.x()+(double(i)-0.5)*spot_space_x);
        painter.drawLine(j,0,j,showimage.height());
    }
    for(i=imageanalyse::spot_y_min;i<=imageanalyse::spot_y_max+1;i++)
    {
        j=int(center.y()+(double(i)-0.5)*spot_space_y);
        painter.drawLine(0,j,showimage.width(),j);
    }
    putimage(showimage);
    putstatus("Combine data end!");
}

void MainWindow::on_dataAnalyze_clicked()
{
    if(step.contains("separatespots"))
        while(step.last()!="separatespots"&&step.last()!="denoise"&&step.last()!="curvefit"&&step.last()!="combinedata")
            step.pop_back();
    else
    {
        putstatus("Please separate spots first!");
        return;
    }
    if(step.last()=="separatespots")
    {
        imanalyse.loadimage(selectimage);
        imanalyse.keepnoise();
    }
    step.push_back("dataanalyze");
    putstatus("Data analyse start!");
    imanalyse.preprocess();
    imanalyse.generateparticles(imageanalyse::particle_num);
    putstatus("Data analyse end!");
}

void MainWindow::on_getTwiss_clicked()
{
    if(step.contains("dataanalyze"))
        while(step.last()!="dataanalyze")
            step.pop_back();
    else
    {
        putstatus("Please analyse data first!");
        return;
    }
    putstatus("Get Twiss parameters start!");
    imanalyse.gettwiss();
    QString temp="";
    temp=temp+"Emittance_x: "+QString::number(imageanalyse::emittance_x)+"\r\n";
    temp=temp+"Alpha_x: "+QString::number(imageanalyse::alpha_x)+"\r\n";
    temp=temp+"Beta_x: "+QString::number(imageanalyse::beta_x)+"\r\n";
    temp=temp+"Gama_x: "+QString::number(imageanalyse::gama_x)+"\r\n";
    temp=temp+"Emittance_y: "+QString::number(imageanalyse::emittance_y)+"\r\n";
    temp=temp+"Alpha_y: "+QString::number(imageanalyse::alpha_y)+"\r\n";
    temp=temp+"Beta_y: "+QString::number(imageanalyse::beta_y)+"\r\n";
    temp=temp+"Gama_y: "+QString::number(imageanalyse::gama_y);
    putstatus(temp);
    putstatus("Get Twiss parameters End!");
}

void MainWindow::on_getPhaseX_clicked()
{
    if(step.contains("dataanalyze"))
        while(step.last()!="dataanalyze")
            step.pop_back();
    else
    {
        putstatus("Please analyse data first!");
        return;
    }
    putstatus("Phase space x vs x' start!");
    showimage=imanalyse.getphaseX(-20,1,20,-20,1,20).scaled(ui->graphicsView->width(),ui->graphicsView->height());
    QColor color(255,0,0);
    QPainter painter(&showimage);
    painter.setPen(color);
    painter.setFont(QFont("Chicago", 12));
    painter.drawText(10,20,"20 mrad");
    painter.drawText(10,390,"0 mm/mrad");
    painter.drawText(350,390,"20 mm");
    putimage(showimage);
    putstatus("Phase space x vs x' end!");
}

void MainWindow::on_getPhaseY_clicked()
{
    if(step.contains("dataanalyze"))
        while(step.last()!="dataanalyze")
            step.pop_back();
    else
    {
        putstatus("Please analyse data first!");
        return;
    }
    putstatus("Phase space y vs y' start!");
    showimage=imanalyse.getphaseY(-20,1,20,-20,1,20).scaled(ui->graphicsView->width(),ui->graphicsView->height());
    QColor color(255,0,0);
    QPainter painter(&showimage);
    painter.setPen(color);
    painter.setFont(QFont("Chicago", 12));
    painter.drawText(10,20,"20 mrad");
    painter.drawText(10,390,"0 mm/mrad");
    painter.drawText(350,390,"20 mm");
    putimage(showimage);
    putstatus("Phase space y vs y' end!");
}

void MainWindow::on_saveParticles_clicked()
{
    if(step.contains("dataanalyze"))
        while(step.last()!="dataanalyze")
            step.pop_back();
    else
    {
        putstatus("Please analyse data first!");
        return;
    }
    putstatus("Save particles start!");
    QString filename=QFileDialog::getSaveFileName();
    imanalyse.saveparticles(filename.toLatin1().data());
    putstatus("Save particles End!");
}

void MainWindow::on_saveImage_clicked()
{
    if(step.contains("dataanalyze"))
        while(step.last()!="dataanalyze")
            step.pop_back();
    else
    {
        putstatus("Please analyse data first!");
        return;
    }
    putstatus("Save image start!");
    QString filename=QFileDialog::getSaveFileName();
    showimage.save(filename,"BMP",100);
    putstatus("Save image End!");
}
