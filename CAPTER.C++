#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->tabWidget->setTabIcon(0, QIcon(":/new/prefix1/c1.png"));
    ui->tabWidget->setTabIcon(1, QIcon(":/new/prefix1/c2.png"));
    ui->tabWidget->setTabIcon(2, QIcon(":/new/prefix1/c3.png"));
    ui->tabWidget->setTabIcon(3, QIcon(":/new/prefix1/c4.png"));
    ui->tabWidget->setTabIcon(4, QIcon(":/new/prefix1/c5.png"));

    ui->tabWidget->setIconSize(QSize(60, 50));
    maxSize = 85535; // 只存储最新的数据
    maxX = 855350000;
    maxY = 200;
    splineSeries1 = new QSplineSeries();
    splineSeries2 = new QSplineSeries();
    splineSeries3 = new QSplineSeries();

    scatterSeries = new QScatterSeries();
    scatterSeries->setMarkerSize(0); //设置点的大小

    scatterSeries2 = new QScatterSeries();
    scatterSeries2->setMarkerSize(0); //设置点的大小

    scatterSeries3 = new QScatterSeries();
    scatterSeries3->setMarkerSize(0); //设置点的大小

    chart->setAnimationOptions(QChart::GridAxisAnimations);
    chart2->setAnimationOptions(QChart::GridAxisAnimations);
    chart3->setAnimationOptions(QChart::GridAxisAnimations);

    chart->legend()->setVisible(true); //设置图例可见
    chart2->legend()->setVisible(true); //设置图例可见
    chart3->legend()->setVisible(true); //设置图例可见

    chart->addSeries(splineSeries1);
    chart2->addSeries(splineSeries2);
    chart3->addSeries(splineSeries3);

    chart->addSeries(scatterSeries);
    chart->legend()->hide();
    chart->setTitle("温度曲线");
    chart->createDefaultAxes();

    chart2->addSeries(scatterSeries2);
    chart2->legend()->hide();
    chart2->setTitle("湿度曲线");
    chart2->createDefaultAxes();

    chart3->addSeries(scatterSeries3);
    chart3->legend()->hide();
    chart3->setTitle("光强度曲线");
    chart3->createDefaultAxes();

    chart->axisX()->setGridLineVisible(true); //网格
    axisX->setLabelFormat("%d"); //图例的格式  %d为十进制显示
    axisX->setTickCount(1); //主要刻度
    chart->axisX()->setTitleText("time/ms"); //标题

    chart->axisX()->setLabelsBrush(QColor(255, 255, 255));
    chart->axisY()->setLabelsBrush(QColor(255, 255, 255));
    chart->axisX()->setTitleBrush(QColor(255, 255, 255));
    chart->axisY()->setTitleBrush(QColor(255, 255, 255));
    chart->setTitleBrush(QColor(255, 255, 255));

    chart2->axisX()->setLabelsBrush(QColor(255, 255, 255));
    chart2->axisY()->setLabelsBrush(QColor(255, 255, 255));
    chart2->axisX()->setTitleBrush(QColor(255, 255, 255));
    chart2->axisY()->setTitleBrush(QColor(255, 255, 255));
    chart2->setTitleBrush(QColor(255, 255, 255));

    chart3->axisX()->setLabelsBrush(QColor(255, 255, 255));
    chart3->axisY()->setLabelsBrush(QColor(255, 255, 255));
    chart3->axisX()->setTitleBrush(QColor(255, 255, 255));
    chart3->axisY()->setTitleBrush(QColor(255, 255, 255));
    chart3->setTitleBrush(QColor(255, 255, 255));

    chart->axisX()->setRange(0, 30);
    chart->axisY()->setRange(-10, 100);
    chart->axisY()->setTitleText("温度/·C"); //标题
    chart->setBackgroundVisible(false);
    ui->tem->setChart(chart);
    ui->tem->setRubberBand(QChartView::RectangleRubberBand); //矩形缩放
    ui->tem->setRenderHint(QPainter::Antialiasing);
    ui->tem->resize(350, 410);
    ui->tem->show();

    chart2->axisX()->setGridLineVisible(true); //网格
    axisX2->setLabelFormat("%d"); //图例的格式  %d为十进制显示
    axisX2->setTickCount(1); //主要刻度
    chart2->axisX()->setTitleText("time/ms"); //标题
    chart2->axisX()->setRange(0, 30);
    chart2->axisY()->setRange(0, 100);
    chart2->axisY()->setTitleText("湿度/·%"); //标题
    chart2->setBackgroundVisible(false);

    ui->hum->setChart(chart2);
    ui->hum->setRubberBand(QChartView::RectangleRubberBand); //矩形缩放
    ui->hum->setRenderHint(QPainter::Antialiasing);
    ui->hum->resize(350, 410);
    ui->hum->show();

    chart3->axisX()->setGridLineVisible(true); //网格
    axisX3->setLabelFormat("%d"); //图例的格式  %d为十进制显示
    axisX3->setTickCount(1); //主要刻度
    chart3->axisX()->setTitleText("time/ms"); //标题
    chart3->axisX()->setRange(0, 30);
    chart3->axisY()->setRange(0, 200);
    chart3->axisY()->setTitleText("光强度/·lux"); //标题
    chart3->setBackgroundVisible(false);

    ui->lux->setChart(chart3);
    ui->lux->setRubberBand(QChartView::RectangleRubberBand); //矩形缩放
    ui->lux->setRenderHint(QPainter::Antialiasing);
    ui->lux->resize(350, 410);
    ui->lux->show();

    m_accessManager = new QNetworkAccessManager();

    QFile crtFile("D:/Desktop/postman/client.crt");
    crtFile.open(QIODevice::ReadOnly);
    const QSslCertificate certificate(&crtFile, QSsl::Pem);
    crtFile.close();
    QFile keyFile("D:/Desktop/postman/client.key");
    keyFile.open(QIODevice::ReadOnly);
    const QSslKey prvateKey(&keyFile, QSsl::Rsa);
    keyFile.close();
    config.setPeerVerifyMode(QSslSocket::VerifyNone); //*****
    config.setProtocol(QSsl::TlsV1_2);
    config.setLocalCertificate(certificate);
    config.setPrivateKey(prvateKey);
    request.setSslConfiguration(config);
    //QTimer::singleShot(1000, this, &Widget::on_pushButton_clicked);
    //Delay_MSec(1000);
    TIM = new QTimer();
    splineSeries1->clear();
    splineSeries2->clear();
    splineSeries3->clear();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Delay_MSec(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec); //非阻塞延时
    while (QTime::currentTime() < _Timer)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void Widget::on_pushButton_clicked() //POST
{
    url = "https://49.4.92.191:8743/iocm/app/sec/v1.1.0/login";
    if (!url.isValid())
        return;
    else {
        request.setUrl(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
        request.setRawHeader("Host", "49.4.92.191:8743");
        request.setRawHeader("Content-Length", "70");
    }
    QByteArray postData;
    postData.append("appId=ssaA4IxYelQDonk8g2eIhu7jbG0a&secret=aBd1S5cud2aGJnPaF4ECTpDMHgka");
    m_accessManager->post(request, postData);
    connect(m_accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)), Qt::UniqueConnection);
    m_accessManager->destroyed();
    //qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();
}

void Widget::finishedSlot(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        QJsonDocument docment = QJsonDocument::fromJson(bytes);
        QJsonObject jsonData = docment.object();
        if (jsonData.contains("accessToken")) {
            QJsonValue value = jsonData.value("accessToken");
            QString toKen = value.toString();
            access = toKen.toUtf8().prepend("Bearer ");
            qDebug() << "access:" << qPrintable(access); //去除双引号
            ui->textEdit->setText(access);
        }
        if (jsonData.contains("devices")) {
            QJsonValue Js = jsonData.value("devices");
            QJsonArray arry = Js.toArray();
            for (int i = 0; i < arry.size(); i++) {
                QJsonValue value = arry.at(i);
                QJsonObject obj = value.toObject();
                if (obj.contains("services")) {
                    QJsonValue service = obj.value("services");
                    QJsonArray arrys = service.toArray();
                    for (int j = 0; j < arrys.size(); j++) {
                        QJsonValue values = arrys.at(j);
                        QJsonObject objs = values.toObject();
                        if (objs.contains("data")) {
                            QJsonValue data = objs.value("data");
                            QJsonObject jsobs = data.toObject();
                            if (jsobs.contains("Temperature")) {
                                QJsonValue Temper = jsobs.value("Temperature");
                                Temperature = Temper.toInt();
                                qDebug().nospace().noquote() << "Temperature: " << Temperature;
                            }
                            if (jsobs.contains("Humidity")) {
                                QJsonValue Hum = jsobs.value("Humidity");
                                Humidity = Hum.toInt();
                                qDebug().noquote().nospace() << "Humidity: " << Humidity;
                            }
                        }
                    }
                }
            }
        }
        dataReceived(Temperature, Humidity, luminance);
    } else {
        qDebug() << "has errors here";
        QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        qDebug("error code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
    }
    reply->deleteLater();
}

void Widget::on_pushButton_2_clicked() //GET
{
    url = "https://49.4.92.191:8743/iocm/app/dm/v1.4.0/devices?deviceId=51a613d866c3775af1f536c68780be";
    if (!url.isValid())
        return;
    else {
        request.setUrl(url);
        request.setRawHeader("app_key", "ssaA4IxYelQDonk8g2eIhu7jbG0a");
        request.setRawHeader("Authorization", "Bearer 3ab03c8ba9dca0eb797296b6c63f3a");
        m_accessManager->get(request);
        connect(m_accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)), Qt::UniqueConnection);
        m_accessManager->destroyed();

        //QTimer* time = new QTimer(this);
        //connect(time, SIGNAL(timeout()), SLOT(on_refresh_clicked())); //每2S获取一次传感器数据
        //time->start(2000);
    }
}

void Widget::on_refresh_clicked()
{
    //url = "https://49.4.92.191:8743/iocm/app/data/v1.2.0/deviceDataHistory?deviceId=4a917508-8e0c-4c2a-91ff-f009d9e0b0f3&gatewayId=4a917508-8e0c-4c2a-91ff-f009d9e0b0f3";
    url = "https://49.4.92.191:8743/iocm/app/dm/v1.4.0/devices?deviceId=51a613d866c3775af1f536c68780be";
    if (!url.isValid())
        return;
    else {
        request.setUrl(url);
        request.setRawHeader("app_key", "ssaA4IxYelQDonk8g2eIhu7jbG0a");
        request.setRawHeader("Authorization", "Bearer bbe2ce3f7faea6986bb768e1b95bf");
        m_accessManager->get(request);
        connect(m_accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlots(QNetworkReply*)), Qt::UniqueConnection); //获取传感器数据
        m_accessManager->deleteResource(request);
    }
}

void Widget::finishedSlots(QNetworkReply* reply) //处理传感器数据
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        qDebug() << "RecBuf is:" << bytes;
        QString string = QString::fromUtf8(bytes);
        ui->textEdit->setText(string.toUtf8());
        sl = string.split(",");
        ui->textEdit->setText(string.toUtf8());

        QRegExp rx("(\\d+)"); // 正则表达式，匹配数字

        i = 0;
        while ((i = rx.indexIn(sl.value(21), i)) != -1) {
            Temperature = rx.cap(0).toInt();

            i += rx.matchedLength();
        }
        qDebug() << "Temperature is " << Temperature;

        i = 0;
        while ((i = rx.indexIn(sl.value(22), i)) != -1) {
            Humidity = rx.cap(0).toInt();

            i += rx.matchedLength();
        }
        qDebug() << "Humidity is " << Humidity;

        i = 0;
        while ((i = rx.indexIn(sl.value(23), i)) != -1) {
            luminance = rx.cap(0).toInt();

            i += rx.matchedLength();
        }
        qDebug() << "luminance is " << luminance;
    }

    else {
        qDebug() << "handle errors here";
        QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        qDebug("found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
    }
    reply->deleteLater();
}

void Widget::on_STARTLED_clicked() //json数据解析
{
    QJsonObject command;
    QJsonObject paras;
    QJsonObject End;

    if (ui->STARTLED->text() == tr("关")) {
        End.insert("deviceId", "4a917508-8e0c-4c2a-91ff-f009d9e0b0f3");
        command.insert("serviceId", "Agriculture");
        command.insert("method", "Agriculture_Control_Light");
        paras.insert("Light", "ON");
        command.insert("paras", paras);
        End.insert("command", command);
        QJsonDocument Document;
        Document.setObject(End);
        QByteArray ba = Document.toJson(QJsonDocument::Compact);
        url = "https://49.4.92.191:8743/iocm/app/cmd/v1.4.0/deviceCommands";
        request.setUrl(url);
        request.setRawHeader("app_key", "EXGjD3g9pUdik0fFFAeN_MG89IIa");
        request.setRawHeader("Authorization", access);
        request.setRawHeader("Content-Type", "application/json");
        request.setRawHeader("Host", "49.4.92.191:8743");
        length = strlen(ba);
        Len = QString("%1").arg(length);
        request.setRawHeader("Content-Length", Len.toLatin1());
        m_accessManager->post(request, ba);
        connect(m_accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(Endjson(QNetworkReply*)), Qt::UniqueConnection);
        m_accessManager->destroyed();
        ui->STARTLED->setStyleSheet("border-image: url(:/new/prefix1/LED ON.png);");
        ui->STARTLED->setText("开");
        qDebug() << "ba is:" << ba;
    }

    else if (ui->STARTLED->text() == tr("开")) {
        End.insert("deviceId", "4a917508-8e0c-4c2a-91ff-f009d9e0b0f3");
        command.insert("serviceId", "Agriculture");
        command.insert("method", "Agriculture_Control_Light");
        paras.insert("Light", "OFF");
        command.insert("paras", paras);
        End.insert("command", command);
        QJsonDocument Document;
        Document.setObject(End);
        QByteArray ba = Document.toJson(QJsonDocument::Compact);
        url = "https://49.4.92.191:8743/iocm/app/cmd/v1.4.0/deviceCommands";
        request.setUrl(url);
        request.setRawHeader("app_key", "EXGjD3g9pUdik0fFFAeN_MG89IIa");
        request.setRawHeader("Authorization", access);
        request.setRawHeader("Content-Type", "application/json");
        request.setRawHeader("Host", "49.4.92.191:8743");
        length = strlen(ba);
        Len = QString("%1").arg(length);
        request.setRawHeader("Content-Length", Len.toLatin1());
        m_accessManager->post(request, ba);
        connect(m_accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(Endjson(QNetworkReply*)), Qt::UniqueConnection);
        m_accessManager->destroyed();
        ui->STARTLED->setStyleSheet("border-image: url(:/new/prefix1/LED OFF.png);"); //:/new/prefix1/LED OFF.png
        ui->STARTLED->setText("关");
        qDebug().noquote() << "ba is:" << ba;
    }
}

void Widget::dataReceived(int value, int value2, int value3)
{
    data << value;
    data2 << value2;
    data3 << value3;
    /*数据个数超过最大数量，则删除最先接收到的数据，实现曲线向前移动*/
    while (data.size() > 31 || data2.size() > 31 || data3.size() > 31) {
        data.removeFirst();
        data2.removeFirst();
        data3.removeFirst();
    }
    int dx = maxX / (maxSize - 1);
    for (int ii = 0; ii < data.size(); ++ii) {
        splineSeries1->append(ii * dx, data.at(ii));
        splineSeries2->append(ii * dx, data2.at(ii));
        splineSeries3->append(ii * dx, data3.at(ii));

        //        chart->axisX()->setRange(10, ii);
        //        chart2->axisX()->setRange(10, ii);
        //        chart3->axisX()->setRange(10, ii);

        scatterSeries->append(ii * dx, data.at(ii));
        scatterSeries2->append(ii * dx, data2.at(ii));
        scatterSeries3->append(ii * dx, data3.at(ii));
    }
}

void Widget::on_acce_clicked() //刷新鉴权
{
    QJsonObject act;
    act.insert("appId", "EXGjD3g9pUdik0fFFAeN_MG89IIa");
    act.insert("secret", "aTX45jYGQ_6vrKkdOjoDKZ62zfca");
    reflash = QString("%1").arg(retoken); //获取最新鉴权

    act.insert("refreshToken", reflash);
    qDebug() << "ba is:" << act;

    QJsonDocument Document;
    Document.setObject(act);
    QByteArray ba = Document.toJson(QJsonDocument::Compact);
    url = "https://49.4.92.191:8743/iocm/app/sec/v1.1.0/refreshToken";
    request.setUrl(url);
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Host", "49.4.92.191:8743");
    length = strlen(ba);
    Len = QString("%1").arg(length);
    request.setRawHeader("Content-Length", Len.toLatin1());
    m_accessManager->post(request, ba);
    connect(m_accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(Endjson(QNetworkReply*)), Qt::UniqueConnection);
}

void Widget::Endjson(QNetworkReply* reply)
{

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        QString string = QString::fromLatin1(bytes);

        ui->textEdit->setText(string.toLatin1());
    } else {
        qDebug() << "has errors here";
        QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        qDebug("error code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
    }
    reply->deleteLater();
}

void Widget::on_tabWidget_currentChanged(int index)
{
    switch (index) {
    case 0:
        qDebug() << "case 0";
        TIM->start(500);
        connect(TIM, &QTimer::timeout, this, &Widget::on_pushButton_2_clicked);
        break;
    case 1:
        qDebug() << "case 1";

        break;
    case 2:
        qDebug() << "case 2";

        break;
    case 3:
        qDebug() << "case 3";

        break;
    case 4:
        qDebug() << "case 4";

        break;
    default:
        break;
    }
}
